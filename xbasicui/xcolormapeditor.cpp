#include "xcolormapeditor.h"

#include <QPainter>
#include <QResizeEvent>
#include <QDebug>
#include <qmath.h>
#include <QColorDialog>

#include "xcolormap.h"

CXColormapEditor::CXColormapEditor(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(QSize(200, 320));
    setMouseTracking(true);
}

CXColormapEditor::~CXColormapEditor()
{

}

void CXColormapEditor::SetColormap(const QString& colormapName)
{
	m_templateName = colormapName;
	m_pColormap = CXColormap::GetColormap(colormapName);

	update();
}

void CXColormapEditor::SetHistogram(const QMap<double, double>& mapPercent)
{
	m_mapPercent = mapPercent;

	QList<double>& listValue = m_mapPercent.values();
	auto maxIter = std::max_element(listValue.begin(), listValue.end());
	listValue.erase(maxIter);

	m_maxPercent = *std::max_element(listValue.begin(), listValue.end());
	update();
}

void CXColormapEditor::slotReset()
{
	if (m_templateName.isEmpty())
        return;

	m_pColormap = CXColormap::GetCustomizedColormap(CXColormap::GetColormap(m_templateName));
	_SendChangeInfoAndUpdate();
}

void CXColormapEditor::slotFlip()
{
	_TransformToCustom();
    m_pColormap->Flip();
	_SendChangeInfoAndUpdate();
}

void CXColormapEditor::slotAddControlPoint()
{
	_TransformToCustom();
    m_pColormap->SetControlPointRgb(m_selectedColorIndex, m_pColormap->ColorAt(m_selectedColorIndex).rgb());
	_SendChangeInfoAndUpdate();
}

void CXColormapEditor::slotAddGeologicMask()
{
    Q_ASSERT(m_selectedColorIndex != -1);

	_TransformToCustom();
	m_pColormap->SetGeologicMask(m_selectedColorIndex, qRgb(255, 0, 255));
	_SendChangeInfoAndUpdate();
}

void CXColormapEditor::slotDeleteControlPointOrMask()
{
	_TransformToCustom();

	if (!m_pColormap->DeleteGeologicMask(m_selectedColorIndex))
    {
		m_pColormap->DeleteControlPoint(m_selectedColorIndex);
    }

	_SendChangeInfoAndUpdate();
}

void CXColormapEditor::slotAllOpaque()
{
	_TransformToCustom();
	m_pColormap->ClearAlpha();
	_SendChangeInfoAndUpdate();
}

void CXColormapEditor::slotDeleteOpacityPoint()
{
	_TransformToCustom();
	m_pColormap->DeleteOpacityPoint(m_selectedColorIndex);
	_SendChangeInfoAndUpdate();
}

void CXColormapEditor::slotAddOpacityPoint()
{
	_TransformToCustom();
	m_pColormap->SetAlpha(m_selectedColorIndex, static_cast<uchar>(m_selectedAlpha));
	_SendChangeInfoAndUpdate();
}

void CXColormapEditor::slotSetAsMin()
{
	if (m_selectedHistogramIndex == -1)
		return;

	const QList<double>& listKey = m_mapPercent.keys();
	double dCurr = listKey.at(m_selectedHistogramIndex);
	emit MinValueChanged(dCurr);

	m_selectedHistogramIndex = -1;
}

void CXColormapEditor::slotSetAsMax()
{
	if (m_selectedHistogramIndex == -1)
		return;

	const QList<double>& listKey = m_mapPercent.keys();
	double dCurr = listKey.at(m_selectedHistogramIndex);
	emit MaxValueChanged(dCurr);

	m_selectedHistogramIndex = -1;
}

void CXColormapEditor::slotSetOpacityFreeDrawing(bool bChecked)
{
	m_bFreeDrawing = bChecked;
}

void CXColormapEditor::paintEvent(QPaintEvent* event)
{
    if (!m_pColormap)
        return;

    QPixmap tile = QPixmap(16, 16);
    tile.fill(Qt::white);
    QPainter pt(&tile);
    QColor color(230, 230, 230);
    pt.fillRect(0, 0, 8, 8, color);
    pt.fillRect(8, 8, 8, 8, color);
    pt.end();

    m_singleColorBarWidth = m_colorBarRect.width() / m_pColormap->GetColorNum();

    QPainter painter(this);
    painter.save();
    painter.drawTiledPixmap(m_colorBarRect, tile);

    for (int i = 0; i != m_pColormap->GetColorNum(); ++i)
    {
        painter.setPen(m_pColormap->ColorAt(i));
        painter.setBrush(m_pColormap->ColorAt(i));
        painter.drawRect(i * m_singleColorBarWidth, m_colorBarRect.y(), m_singleColorBarWidth, m_colorBarRect.height());
    }

	if (!m_mapPercent.empty())
	{
		m_singleHistogramBarWidth = m_colorBarRect.width() / m_mapPercent.size();
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(173, 173, 173, 128));

		const QList<double>& listValue = m_mapPercent.values();
		for (size_t i = 0; i != listValue.size(); ++i)
		{
			qreal height = listValue.at(i) / m_maxPercent * m_colorBarRect.height() * 0.9;
			qreal y = m_colorBarRect.y() + m_colorBarRect.height() - height;
			painter.drawRect(i * m_singleHistogramBarWidth, y, m_singleHistogramBarWidth * 0.9, height);
		}
	}

    for (auto i : m_pColormap->GetControlPointsIndex())
    {
        _DrawControlPoint(i);
    }

	_DrawOpacityPoint();
    _DrawGeologicMask();
}

void CXColormapEditor::resizeEvent(QResizeEvent* event)
{
    m_colorBarRect.setRect(0, 0, event->size().width(), event->size().height() - m_controlRectHeight);
    m_controlRect.setRect(0, event->size().height() - m_controlRectHeight, event->size().width(), m_controlRectHeight);
}

void CXColormapEditor::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bGeologicMaskChanged)
    {
        int newIndex = _PosToColorIndex(event->pos());
		if (m_listFixedMask.contains(newIndex) || newIndex == m_selectedColorIndex || newIndex == -1)
            return;

		_TransformToCustom();

		m_pColormap->UpdateGeologicMask(m_selectedColorIndex, newIndex, m_selectedMaskRgb);
        m_selectedColorIndex = newIndex;

		update();
        return;
    }
    
    if (m_bControlIndexChanged)
    {
        int newIndex = _PosToColorIndex(event->pos());
		if (m_listFixedControlPoints.contains(newIndex) || newIndex == -1)
            return;

		_TransformToCustom();

        m_pColormap->UpdateControlPoint(m_selectedColorIndex, newIndex, m_selectedControlPointRgb);
        m_selectedColorIndex = newIndex;

		update();
        return;
    }

	if (m_bDrawingStart)
	{
		int newIndex = _PosToColorIndex(event->pos());
		int newAlpha = _PosToAlpha(event->pos());

		if (newIndex == -1 || newAlpha == -1)
			return;

		int indexBeg = qMin(m_selectedColorIndex, newIndex);
		int indexEnd = qMax(m_selectedColorIndex, newIndex);

		_TransformToCustom();

		const QMap<int, uchar>& mapAlpha = m_pColormap->GetAlphaMap();
		for (int i = indexBeg + 1; i < indexEnd; ++i)
		{
			if (mapAlpha.contains(i))
				m_pColormap->DeleteOpacityPoint(i);
		}

		m_pColormap->SetAlpha(newIndex, newAlpha);
		m_selectedColorIndex = newIndex;

		update();
		return;
	}

    if (m_colorBarRect.contains(event->pos()))
    {
		_ShowHistogramDataRange(event->pos());
    }
	else
	{
		emit ShowMsg("");
	}
    /*else if (m_controlRect.contains(event->pos()))
    {
        int possibleControlIndex;
        if (_IsInControlPoint(event->pos(), possibleControlIndex))
        {
            const QColor& color = m_pColormap->ColorAt(possibleControlIndex);
			emit ShowMsg(QString("Control point: %5\tColor: %1,%2,%3,%4\tAlpha: (null)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()).arg(possibleControlIndex));
        }
    }*/
}

void CXColormapEditor::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        _ShowMenu(event->pos(), event->globalPos());
    }
    else if (event->button() == Qt::LeftButton)
    {
        _SelectControlPointOrMask(event->pos());
		_BeginFreeDrawing(event->pos());
    }
}

void CXColormapEditor::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        _SetControlPointColor(event->pos());
		_SetGeologicMaskColor(event->pos());
    }
}

void CXColormapEditor::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_bGeologicMaskChanged || m_bControlIndexChanged || m_bDrawingStart)
	{
		emit ColormapChanged();
	}

    m_selectedColorIndex = -1;
    m_bControlIndexChanged = false;
    m_selectedControlPointRgb = 0u;
    m_listFixedControlPoints.clear();
    m_bGeologicMaskChanged = false;
    m_listFixedMask.clear();
	m_bDrawingStart = false;
}

QPointF CXColormapEditor::_ColorIndexToControlPos(int index)
{
    if (qFuzzyCompare(m_singleColorBarWidth, 0.0))
        return QPointF();

    qreal x = index * m_singleColorBarWidth + m_singleColorBarWidth / 2;
    qreal y = height() - m_controlRectHeight;
    return QPointF(x, y);
}

QPointF CXColormapEditor::_IndexAlphaToOpacityPos(int index, int alpha)
{
	if (qFuzzyCompare(m_singleColorBarWidth, 0.0))
		return QPointF();

	qreal x = index * m_singleColorBarWidth + m_singleColorBarWidth / 2;
	qreal y = (1 - alpha * 1.0 / 255) * m_colorBarRect.height();
	return QPointF(x, y);
}

int CXColormapEditor::_PosToColorIndex(const QPointF& pos)
{
	if (m_singleColorBarWidth == 0.0)
        return -1;
    else
		return qFloor(qBound(0.0, pos.x(), m_colorBarRect.width() - 1) / m_singleColorBarWidth);
}

int CXColormapEditor::_PosToAlpha(const QPointF& pos)
{
	if (pos.y() > m_colorBarRect.height() || pos.y() < 0)
		return -1;
	else
		return qRound((1 - pos.y() / m_colorBarRect.height()) * 255);
}

int CXColormapEditor::_PosToHistogramIndex(const QPointF& pos)
{
	if (m_singleHistogramBarWidth == 0.0 || pos.x() >= m_colorBarRect.width() || pos.x() < 0)
		return -1;
	else
		return qFloor(pos.x() / m_singleHistogramBarWidth);
}

void CXColormapEditor::_DrawControlPoint(int index)
{
    if (index < 0 || m_pColormap->GetColorNum() <= index)
        return;

    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.setBrush(m_pColormap->ColorAt(index));

    QPointF pos = _ColorIndexToControlPos(index);
    if (pos.isNull())
        return;

    QPolygonF polygon;
    polygon << pos + QPointF(-5, 10) << pos + QPointF(5, 10) << pos;
    painter.drawPolygon(polygon);
}

void CXColormapEditor::_DrawGeologicMask()
{
    QPainter painter(this);
    painter.setPen(Qt::black);

	const QMap<int, QRgb>& mapGeologicMask = m_pColormap->GetGeologicMask();
	for (auto iter = mapGeologicMask.cbegin(); iter != mapGeologicMask.cend(); ++iter)
    {
        painter.setBrush(QColor(iter.value()));

        QPointF pos = _ColorIndexToControlPos(iter.key());
        if (pos.isNull())
            return;

        painter.drawRect(QRectF(pos.x() - 5, pos.y(), 10, 10));
    }
}

void CXColormapEditor::_DrawOpacityPoint()
{
	QPolygonF alphaPoint;
	const QMap<int, uchar>& mapAlpah = m_pColormap->GetAlphaMap();
	for (auto iter = mapAlpah.cbegin(); iter != mapAlpah.cend(); ++iter)
	{
		QPointF pos = _IndexAlphaToOpacityPos(iter.key(), iter.value());
		if (pos.isNull())
			return;

		alphaPoint.push_back(pos);
	}

	QPainter painter(this);

	painter.save();
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(Qt::white, 3));
	painter.drawPolyline(alphaPoint);
	painter.setPen(QColor(153, 153, 153));
	painter.drawPolyline(alphaPoint);
	painter.restore();

	painter.setPen(Qt::black);
	painter.setBrush(Qt::yellow);

	for (auto pos : alphaPoint)
	{
		painter.drawRect(QRectF(pos.x() - 4, pos.y() - 4, 8, 8));
	}
}

void CXColormapEditor::_OpenControlMenu(QMenu& menu, const QPoint& pos)
{
    QAction *pAddControlPointAction = menu.addAction("Add control point", this, SLOT(slotAddControlPoint()));
    QAction *pAddGeologicMaskAction = menu.addAction("Add geologic mask", this, SLOT(slotAddGeologicMask()));
    QAction *pDeleteAction = menu.addAction("Delete control point or mask", this, SLOT(slotDeleteControlPointOrMask()));

    m_selectedColorIndex = _PosToColorIndex(pos);

	if (_IsInControlPoint(pos, m_selectedColorIndex) || _IsInGeologicMask(pos, m_selectedColorIndex, m_selectedMaskRgb))
    {
        pAddControlPointAction->setDisabled(true);
        pDeleteAction->setDisabled(false);
    }
    else
    {
        pAddControlPointAction->setDisabled(false);
        pDeleteAction->setDisabled(true);
    }
}

void CXColormapEditor::_OpenOpacityMenu(QMenu& menu, const QPoint& pos)
{
	QAction *pAddOpacityPointAction = menu.addAction("Add opacity point", this, SLOT(slotAddOpacityPoint()));
	QAction *pDelOpacityPointAction = menu.addAction("Delete opacity point", this, SLOT(slotDeleteOpacityPoint()));
	QAction *pAllOpaqueAction = menu.addAction("All opaque", this, SLOT(slotAllOpaque()));
	menu.addSeparator();
	QAction *pSetAsMin = menu.addAction("Set as Minimum", this, SLOT(slotSetAsMin()));
	QAction *pSetAsMax = menu.addAction("Set as Maximum", this, SLOT(slotSetAsMax()));

	m_selectedHistogramIndex = _PosToHistogramIndex(pos);
	m_selectedColorIndex = _PosToColorIndex(pos);
	m_selectedAlpha = _PosToAlpha(pos);
	
	if (_IsInOpacityPoint(pos, m_selectedColorIndex, m_selectedAlpha))
	{
		pAddOpacityPointAction->setDisabled(true);
		pDelOpacityPointAction->setDisabled(false);
	}
	else
	{
		pAddOpacityPointAction->setDisabled(false);
		pDelOpacityPointAction->setDisabled(true);
	}
}

bool CXColormapEditor::_IsInControlPoint(const QPoint& pos, int& controlIndex)
{
	// first and last

	/*if (0 < pos.x() && pos.x() <= 5)
	{
		int firstIndex = m_pColormap->GetControlPointsIndex().first();
		if (firstIndex == 0)
		{
			controlIndex = firstIndex;
			return true;
		}
		else
		{
			return false;
		}
		
	}
	else if (m_colorBarRect.width() - 5 <= pos.x() && pos.x() < m_colorBarRect.width())
	{
		int lastIndex = m_pColormap->GetControlPointsIndex().last();
		if (lastIndex == m_pColormap->GetColorNum() - 1)
		{
			controlIndex = lastIndex;
			return true;
		}
		else
		{
			return false;
		}
	}*/

	// common

    int indexBeg = _PosToColorIndex(pos + QPointF(-5, 0));
    int indexEnd = _PosToColorIndex(pos + QPointF(5, 0));

    if (indexBeg == -1 || indexEnd == -1)
        return false;

    const std::list<int>& controlPointIndices = m_pColormap->GetControlPointsIndex().toStdList();
    for (auto iter = controlPointIndices.rbegin(); iter != controlPointIndices.rend(); ++iter)
    {
        if (indexBeg <= *iter && *iter <= indexEnd)
        {
            controlIndex = *iter;
            return true;
        }
    }

    return false;
}

bool CXColormapEditor::_IsInGeologicMask(const QPoint& pos, int& maskIndex, QRgb& maskRgb)
{
    int indexBeg = _PosToColorIndex(pos + QPointF(-5, 0));
    int indexEnd = _PosToColorIndex(pos + QPointF(5, 0));

    if (indexBeg == -1 || indexEnd == -1)
        return false;

    const std::map<int, QRgb>& mapMask = m_pColormap->GetGeologicMask().toStdMap();
	for (auto iter = mapMask.crbegin(); iter != mapMask.crend(); ++iter)
    {
		if (indexBeg <= iter->first && iter->first <= indexEnd)
        {
			maskIndex = iter->first;
			maskRgb = iter->second;
            return true;
        }
    }

    return false;
}

bool CXColormapEditor::_IsInOpacityPoint(const QPoint& pos, int& controlIndex, int& alpha)
{
	int indexBeg = _PosToColorIndex(pos + QPointF(-4, 0));
	int indexEnd = _PosToColorIndex(pos + QPointF( 4, 0));
	int alphaBeg = _PosToAlpha(pos + QPointF(0,  4));
	int alphaEnd = _PosToAlpha(pos + QPointF(0, -4));

	if (indexBeg == -1 || indexEnd == -1)
		return false;

	const std::map<int, uchar>& mapAlpha = m_pColormap->GetAlphaMap().toStdMap();
	for (auto iter = mapAlpha.crbegin(); iter != mapAlpha.crend(); ++iter)
	{
		if (indexBeg <= iter->first && iter->first <= indexEnd && alphaBeg <= iter->second && iter->second <= alphaEnd)
		{
			controlIndex = iter->first;
			alpha = iter->second;
			return true;
		}
	}

	return false;
}

void CXColormapEditor::_ShowMenu(const QPoint& position, const QPoint& cursorPos)
{
    QMenu menu(this);
	if (m_controlRect.contains(position))
	{
		_OpenControlMenu(menu, position);
	}
	else if (m_colorBarRect.contains(position))
	{
		_OpenOpacityMenu(menu, position);
	}
    menu.exec(cursorPos);
}

void CXColormapEditor::_SetControlPointColor(const QPoint& position)
{
    if (!m_controlRect.contains(position))
        return;

    int possibleControlIndex;
    if (!_IsInControlPoint(position, possibleControlIndex))
        return;

    QColor color = QColorDialog::getColor(m_pColormap->ColorAt(possibleControlIndex), this, "Select Color", QColorDialog::DontUseNativeDialog);
    if (color.isValid())
    {
		_TransformToCustom();
        m_pColormap->SetControlPointRgb(possibleControlIndex, color.rgb());
		_SendChangeInfoAndUpdate();
    }
}

void CXColormapEditor::_SetGeologicMaskColor(const QPoint& position)
{
	if (!m_controlRect.contains(position))
		return;

	int possibleMaskIndex;
	QRgb maskRgb;
	if (!_IsInGeologicMask(position, possibleMaskIndex, maskRgb))
		return;

	QColor color = QColorDialog::getColor(maskRgb, this, "Select Color", QColorDialog::DontUseNativeDialog);
	if (color.isValid())
	{
		_TransformToCustom();
		m_pColormap->SetGeologicMask(possibleMaskIndex, color.rgb());
		_SendChangeInfoAndUpdate();
	}
}

void CXColormapEditor::_ShowColorInfo(const QPoint& position)
{
	int currIndex = _PosToColorIndex(position);
	int currAlpha = _PosToAlpha(position);
	if (currIndex == -1)
		return;

	if (_IsInOpacityPoint(position, currIndex, currAlpha))
	{
		const QColor& color = m_pColormap->ColorAt(currIndex);
		emit ShowMsg(QString("Opacity point: %1\nColor: %2,%3,%4,%5\nAlpha: %6").arg(currIndex).arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()).arg(currAlpha));

	}
	else
	{
		const QColor& color = m_pColormap->ColorAt(currIndex);
		emit ShowMsg(QString("Index: %1\nColor: %2,%3,%4,%5\nAlpha: %6").arg(currIndex).arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()).arg(currAlpha));

	}
}

void CXColormapEditor::_ShowHistogramDataRange(const QPoint& position)
{
	int currIndex = _PosToHistogramIndex(position);
	if (currIndex == -1)
		return;

	const QList<double>& listKey = m_mapPercent.keys();

	double dCurr = listKey.at(currIndex);
	double dNext = currIndex + 1 >= listKey.size() ? listKey.last() : listKey.at(currIndex + 1);
	double dPercent = m_mapPercent.value(listKey.at(currIndex));
	emit ShowMsg(QString("Data range: %1 ~ %2 | Data percentage: %3%").arg(dCurr).arg(dNext).arg(dPercent * 100));
}

void CXColormapEditor::_SelectControlPointOrMask(const QPoint& pos)
{
    if (!m_controlRect.contains(pos))
        return;

	if (_IsInGeologicMask(pos, m_selectedColorIndex, m_selectedMaskRgb))
    {
        m_bGeologicMaskChanged = true;
		m_listFixedMask = m_pColormap->GetGeologicMask().keys();
        m_listFixedMask.removeOne(m_selectedColorIndex);
    }
    else if (_IsInControlPoint(pos, m_selectedColorIndex))
    {
        m_bControlIndexChanged = true;
        m_selectedControlPointRgb = m_pColormap->GetRgbAt(m_selectedColorIndex);
        m_listFixedControlPoints = m_pColormap->GetControlPointsIndex();
        m_listFixedControlPoints.removeOne(m_selectedColorIndex);
    }
}

void CXColormapEditor::_BeginFreeDrawing(const QPoint& pos)
{
	if (!m_colorBarRect.contains(pos) || !m_bFreeDrawing)
		return;

	m_bDrawingStart = true;
	m_selectedColorIndex = _PosToColorIndex(pos);
}

void CXColormapEditor::_SendChangeInfoAndUpdate()
{
	update();
	emit ColormapChanged();
}

void CXColormapEditor::_TransformToCustom()
{
	if (m_pColormap->GetName() != "customized")
	{
		m_pColormap = CXColormap::GetCustomizedColormap(CXColormap::GetColormap(m_templateName));
	}
}