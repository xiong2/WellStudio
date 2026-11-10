#include <qpainter.h>
#include <qdebug.h>
#include <qmenu.h>
#include "xcolormapwidget.h"
#include "xcolormap.h"
#include "xautogrid.h"
#include <qicon.h>


CXColormapWidget::CXColormapWidget(QWidget* parent) :
	QWidget(parent)
{
	_Init();
}

CXColormapWidget::CXColormapWidget(QString strColormapName, QWidget* parent, Qt::WindowFlags f) 
    : QWidget(parent, f)
    , m_strName(strColormapName)
{
	_Init();
}

void CXColormapWidget::_Init()
{
	m_dMin = -999.;
	m_dMax = -999.;

	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &CXColormapWidget::customContextMenuRequested, this, &CXColormapWidget::slotTableMenuRequest);
}

void CXColormapWidget::slotTableMenuRequest(const QPoint & point)
{
	QMenu menu;
	QStringList listColormap = CXColormap::GetAllColormapsName();
	for (int i = 0; i < listColormap.size(); ++i)
	{
		QAction* pAction = menu.addAction(listColormap[i], this, &CXColormapWidget::slotChangeColormap);
		pAction->setData(QVariant(listColormap[i]));
	}

	menu.exec(QCursor::pos());
}

void CXColormapWidget::slotChangeColormap()
{
	QAction* pAction = dynamic_cast<QAction*>(sender());
	if (!pAction)
		return;

	QString strColormapName = pAction->data().toString();

	SetColormapName(strColormapName);
	emit signalChangedColormap(strColormapName);
}

QSize CXColormapWidget::sizeHint() const
{
    QFontMetrics fontMetrics(this->font());
    int textWidth = qMax(fontMetrics.width(QString::number(m_dMin, 'f', 2)), fontMetrics.width(QString::number(m_dMax, 'f', 2)));

    return QSize(3 * m_margin + m_rainbowWidth + textWidth + 2 * m_scaleWidth, this->height());
}

void CXColormapWidget::SetDisplayRange(qreal dMin, qreal dMax)
{
    m_dMin = dMin;
    m_dMax = dMax;

    QFontMetrics fontMetrics(this->font());
    m_textHeight = fontMetrics.height();
    m_textWidth = qMax(fontMetrics.width(QString::number(m_dMin, 'f', 2)), fontMetrics.width(QString::number(m_dMax, 'f', 2)));

    update();
}

void CXColormapWidget::SetColormapName(const QString& name)
{
    m_strName = name;

    update();
}

void CXColormapWidget::paintEvent(QPaintEvent *)
{
    CXColormap *pColormap = CXColormap::GetColormap(m_strName);
    if (!pColormap || m_dMin >= m_dMax)
        return;

    int iHeight = height() - 2 * m_margin;
	float fCellHeight	= iHeight / 256.;

	QPainter painter(this);
    painter.save();

	if(m_dMin != -999.)
	{
		double dUniStart, dUniStop, dStep;
		CXAutoGrid::AutoGrid(m_dMin, m_dMax, 10, dUniStart, dUniStop, dStep);
		float fLineStep = dStep / (m_dMax - m_dMin) * iHeight;
		float fLineStart = (dUniStart - m_dMin) / (m_dMax - m_dMin) * iHeight;
		float fLineStop = (dUniStop - m_dMin) / (m_dMax - m_dMin) * iHeight;

		while (fLineStart < iHeight)
		{
			painter.drawLine(m_margin, m_margin + fLineStart, m_margin + m_rainbowWidth + m_scaleWidth, m_margin + fLineStart);
			painter.drawText(m_margin + m_rainbowWidth + m_margin, fLineStart, m_textWidth, m_textHeight, Qt::AlignLeft, CXAutoGrid::TrimToString(dUniStop));

			fLineStart += fLineStep;
			dUniStop -= dStep;
		}
	}

	for(int i = 0; i < 256; i++)
	{
		painter.setPen(pColormap->GetColorAt(i));
        painter.setBrush(pColormap->GetColorAt(i));
        painter.drawRect(m_margin, iHeight + m_margin - (i + 1) * fCellHeight, m_rainbowWidth, fCellHeight);
	}

    painter.restore();
}

void CXColormapWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    emit OpenColormapEditingDialog();
}


