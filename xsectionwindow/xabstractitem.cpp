#include "xabstractitem.h"

#include <assert.h>
#include "xobject.h"
#include "xglobal.h"

CXAbstractItem::CXAbstractItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent)
	: QGraphicsItem(parent), m_pViewInfo(nullptr), m_pSectionWindow(pWindow)
{
	m_pAxis = m_pSectionWindow->GetAxisWidget();
}

CXAbstractItem::~CXAbstractItem(void)
{}

void CXAbstractItem::ResetData(QUuid objID)
{
    assert(m_pSectionWindow);
	m_objID = objID;
    m_pViewInfo = m_pSectionWindow->GetObjectViewInfo(objID);
    _UpdateData();
}

void CXAbstractItem::UpdateView(EEventType eType)
{
	if (EDataChanged == eType)
	{
		_UpdateData();
	}
	else
	{
		MapToScene();
	}

    update();
}

QRectF CXAbstractItem::_CalcDrawPathBoundingRect(const QPainterPath& path, const QPen& pen) const
{
    if (path.isEmpty()) return QRectF();

    qreal minX, maxX, minY, maxY;
    minX = maxX = path.elementAt(0).x;
    minY = maxY = path.elementAt(0).y;

    for (auto i = 1; i != path.elementCount(); ++i)
    {
        const auto& element = path.elementAt(i);
        if (pen.widthF() == 0.0 && element.type == QPainterPath::CurveToElement) continue;

        minX = qMin(element.x, minX);
        maxX = qMax(element.x, maxX);
        minY = qMin(element.y, minY);
        maxY = qMax(element.y, maxY);
    }
    return QRectF(minX, minY, maxX - minX, maxY - minY);
}

QPainterPath CXAbstractItem::_CalcShapeFromPath(const QPainterPath& path, const QPen& pen) const
{
    if (path.isEmpty()) return path;

    // We unfortunately need this hack as QPainterPathStroker will set a width of 1.0
    // if we pass a value of 0.0 to QPainterPathStroker::setWidth()
    const auto penWidthZero = 0.00000001;

    QPainterPathStroker pathStroker;
    pathStroker.setCapStyle(pen.capStyle());
    pathStroker.setWidth(pen.widthF() > 0.0 ? pen.widthF() : penWidthZero);
    pathStroker.setJoinStyle(pen.joinStyle());
    pathStroker.setMiterLimit(pen.miterLimit());

    QPainterPath StrokePath = pathStroker.createStroke(path);
    StrokePath.addPath(path);
    return StrokePath;
}

CXObject* CXAbstractItem::GetItemObject() const
{
	return ::GetObjectByID(m_objID);
}