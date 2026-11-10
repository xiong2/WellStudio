#include "stdafx.h"
#include "gsbmcoordinateitem.h"
#include "gsbasemapwindow.h"
#include "xglobalcoordtransform.h"
#include "xmath.h"
#include <QBrush>
#include <QPen>

class GSBMCoordinateItem::Impl
{
public:
    Impl(const CXGlobalCoordTransform& coordTrans);

    const QPainterPath& GetTicksPath();
    void buildAxes(const QRectF& rect, const QFont& font, double tickSize);

private:
    const CXGlobalCoordTransform& m_coordTrans;
    QPainterPath m_axesPath;
};

GSBMCoordinateItem::Impl::Impl(const CXGlobalCoordTransform& coordTrans)
    : m_coordTrans(coordTrans)
{
}

const QPainterPath& GSBMCoordinateItem::Impl::GetTicksPath()
{
    return m_axesPath;
}

void GSBMCoordinateItem::Impl::buildAxes(const QRectF& rect, const QFont& font, double dTickSize)
{
    m_axesPath = QPainterPath();
    QFontMetrics fontMetrics(font);

    const QPointF& topLeft     = m_coordTrans.Local2World(rect.topLeft());
    const QPointF& bottomRight = m_coordTrans.Local2World(rect.bottomRight());

    double dXMin = topLeft.x();
    double dXMax = bottomRight.x();
    double dYMin = bottomRight.y();
    double dYMax = topLeft.y();

    double dIntervalX = XMath::NiceInterval(dXMin, dXMax, 10);
    double dIntervalY = XMath::NiceInterval(dYMin, dYMax, 10);

    double dTickFirstX, dTickFirstY;
    int nTickNumX, nTickNumY;
    XMath::NiceLevel(dIntervalX, dXMin, dXMax, &dTickFirstX, &nTickNumX);
    XMath::NiceLevel(dIntervalY, dYMin, dYMax, &dTickFirstY, &nTickNumY);

    for (int i = 0; i != nTickNumX; ++i)
    {
        double x      = dTickFirstX + i * dIntervalX;
        QString markX = QString::number(x, 'f', 0);

        QPointF pTop0 = m_coordTrans.World2Local(QPointF(x, dYMax));
        QPointF pTop1(pTop0.x(), pTop0.y() - dTickSize);
        QPointF pTop2(pTop0.x() - fontMetrics.width(markX) / 2, pTop0.y() - 3 * dTickSize);
        m_axesPath.moveTo(pTop0);
        m_axesPath.lineTo(pTop1);
        m_axesPath.addText(pTop2, font, markX);

        QPointF pBottom0 = m_coordTrans.World2Local(QPointF(x, dYMin));
        QPointF pBottom1 = QPointF(pBottom0.x(), pBottom0.y() + dTickSize);
        QPointF pBottom2 = QPointF(pBottom0.x() - fontMetrics.width(markX) / 2, pBottom0.y() + 3 * dTickSize + fontMetrics.height());
        m_axesPath.moveTo(pBottom0);
        m_axesPath.lineTo(pBottom1);
        m_axesPath.addText(pBottom2, font, markX);
    }

    for (int i = 0; i != nTickNumY; ++i)
    {
        double y      = dTickFirstY + i * dIntervalY;
        QString markY = QString::number(y, 'f', 0);

        QPointF pLeft0 = m_coordTrans.World2Local(QPointF(dXMin, y));
        QPointF pLeft1(pLeft0.x() - dTickSize, pLeft0.y());
        QPointF pLeft2(pLeft0.x() - 3 * dTickSize - fontMetrics.width(markY), pLeft0.y() + fontMetrics.height() / 2);
        m_axesPath.moveTo(pLeft0);
        m_axesPath.lineTo(pLeft1);
        m_axesPath.addText(pLeft2, font, markY);

        QPointF pRight0 = m_coordTrans.World2Local(QPointF(dXMax, y));
        QPointF pRight1(pRight0.x() + dTickSize, pRight0.y());
        QPointF pRight2(pRight0.x() + 3 * dTickSize, pRight0.y() + fontMetrics.height() / 2);
        m_axesPath.moveTo(pRight0);
        m_axesPath.lineTo(pRight1);
        m_axesPath.addText(pRight2, font, markY);
    }
}

GSBMCoordinateItem::GSBMCoordinateItem(const CXGlobalCoordTransform& coordTrans, QGraphicsItem* parent)
    : QGraphicsRectItem(parent), m_pImpl(std::make_unique<Impl>(coordTrans))
{
    setBrush(Qt::NoBrush);
    QPen pen(Qt::white);
    pen.setCosmetic(true);
    setPen(pen);
}

GSBMCoordinateItem::~GSBMCoordinateItem()
{
}

QRectF GSBMCoordinateItem::boundingRect() const
{
    qreal marginHorizontal = rect().width() * 0.1;
    qreal marginVertical   = rect().height() * 0.1;

    return rect().adjusted(-marginHorizontal, -marginVertical, marginHorizontal, marginVertical);
}

void GSBMCoordinateItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsRectItem::paint(painter, option, widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(Qt::white);
    painter->drawPath(m_pImpl->GetTicksPath());
}

void GSBMCoordinateItem::UpdateByItem(const QGraphicsItem* pItem)
{
    QRectF r = rect();

    if (r.isNull())
    {
        r = pItem->boundingRect();
    }
    else
    {
        QRectF unitedRect = r.united(pItem->boundingRect());
        if (unitedRect == r)
            return;
		r = unitedRect;
    }

    qreal paddingHorizontal = r.width() * 0.05;
    qreal paddingVertical   = r.height() * 0.05;
    r.adjust(-paddingHorizontal, -paddingVertical, paddingHorizontal, paddingVertical);
    setRect(r);
    m_pImpl->buildAxes(r, QFont("Arial", 400), 200);
}
