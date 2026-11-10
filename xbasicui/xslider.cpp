#include "xslider.h"

#pragma warning( push, 0 )
#include <QKeyEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QStyle>
#include <QStylePainter>
#include <QStyleOptionSlider>
#include "xslider.h"
#pragma warning( pop )

class CXSliderPrivate : public QObject
{
public:
	CXSliderPrivate(CXSlider* pRangeSlider);
	void initStyleOption(QStyleOptionSlider* option, CXSlider::RangeHandle handle = CXSlider::MaxHandle) const;
	int pixelPosToRangeValue(int pos) const;
	void handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, CXSlider::RangeHandle handle);
	void drawHandle(QStylePainter* painter, CXSlider::RangeHandle handle) const;
	void setupPainter(QPainter* painter, Qt::Orientation orientation, qreal x1, qreal y1, qreal x2, qreal y2) const;
	void drawRange(QStylePainter* painter, const QRect& rect) const;
	void triggerAction(QAbstractSlider::SliderAction action, bool main);
	void swapControls();
	void movePressedHandle();
	int pick(const QPoint& pt) const
	{
		return m_pSlider->orientation() == Qt::Horizontal ? pt.x() : pt.y();
	}

	int min;
	int max;
	int minPos;
	int maxPos;
	int offset;
	int position;
	CXSlider::RangeHandle lastPressed;
	CXSlider::RangeHandle mainControl;
	QStyle::SubControl minPressed;
	QStyle::SubControl maxPressed;
	CXSlider::HandleMovementMode movement;
	bool firstMovement;
	bool blockTracking;
	CXSlider* m_pSlider;
};

CXSliderPrivate::CXSliderPrivate(CXSlider* pRangeSlider) :
min(0),
max(0),
minPos(0),
maxPos(0),
offset(0),
position(0),
lastPressed(CXSlider::NoHandle),
mainControl(CXSlider::MinHandle),
minPressed(QStyle::SC_None),
maxPressed(QStyle::SC_None),
movement(CXSlider::FreeMovement),
firstMovement(false),
blockTracking(false),
m_pSlider(pRangeSlider)
{
}

void CXSliderPrivate::initStyleOption(QStyleOptionSlider* option, CXSlider::RangeHandle handle) const
{
	m_pSlider->initStyleOption(option);
	option->sliderPosition = (handle == CXSlider::MinHandle ? minPos : maxPos);
	option->sliderValue = (handle == CXSlider::MinHandle ? min : max);
}

int CXSliderPrivate::pixelPosToRangeValue(int pos) const
{
	QStyleOptionSlider opt;
	initStyleOption(&opt);

	int sliderMin = 0;
	int sliderMax = 0;
	int sliderLength = 0;
	const QSlider* p = const_cast<const QSlider*>(qobject_cast<QSlider*>(m_pSlider));
	const QRect gr = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, p);
	const QRect sr = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, p);
	if (p->orientation() == Qt::Horizontal)
	{
		sliderLength = sr.width();
		sliderMin = gr.x();
		sliderMax = gr.right() - sliderLength + 1;
	}
	else
	{
		sliderLength = sr.height();
		sliderMin = gr.y();
		sliderMax = gr.bottom() - sliderLength + 1;
	}
	return QStyle::sliderValueFromPosition(p->minimum(), p->maximum(), pos - sliderMin,
		sliderMax - sliderMin, opt.upsideDown);
}

void CXSliderPrivate::handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, CXSlider::RangeHandle handle)
{
	QStyleOptionSlider opt;
	initStyleOption(&opt, handle);
	CXSlider* p = m_pSlider;
	const QStyle::SubControl oldControl = control;
	control = p->style()->hitTestComplexControl(QStyle::CC_Slider, &opt, pos, p);
	const QRect sr = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, p);
	if (control == QStyle::SC_SliderHandle)
	{
		position = value;
		offset = pick(pos - sr.topLeft());
		lastPressed = handle;
		p->setSliderDown(true);
		emit p->sliderPressed(handle);
	}
	if (control != oldControl)
		p->update(sr);
}

void CXSliderPrivate::setupPainter(QPainter* painter, Qt::Orientation orientation, qreal x1, qreal y1, qreal x2, qreal y2) const
{
	QColor highlight = m_pSlider->palette().color(QPalette::Highlight);
	QLinearGradient gradient(x1, y1, x2, y2);
	gradient.setColorAt(0, highlight.dark(130));
	gradient.setColorAt(1, highlight.light(116));
	painter->setBrush(gradient);
	int penLight = orientation == Qt::Horizontal ? 140 : 160;
	painter->setPen(QPen(highlight.dark(penLight), 0));

}

void CXSliderPrivate::drawRange(QStylePainter* painter, const QRect& rect) const
{
	QStyleOptionSlider opt;
	initStyleOption(&opt);
	const QSlider* p = const_cast<const QSlider*>(qobject_cast<QSlider*>(m_pSlider));;

	// area
	QRect groove = p->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, p);
	if (opt.orientation == Qt::Horizontal)
		groove.adjust(0, 0, -1, 0);
	else
		groove.adjust(0, 0, 0, -1);

	// pen & brush
	painter->setPen(QPen(p->palette().color(QPalette::Dark).light(110), 0));
	if (opt.orientation == Qt::Horizontal)
		setupPainter(painter, opt.orientation, groove.center().x(), groove.top(), groove.center().x(), groove.bottom());
	else
		setupPainter(painter, opt.orientation, groove.left(), groove.center().y(), groove.right(), groove.center().y());

	// draw groove
	painter->drawRect(rect.intersected(groove));
}

void CXSliderPrivate::drawHandle(QStylePainter* painter, CXSlider::RangeHandle handle) const
{
	QStyleOptionSlider opt;
	initStyleOption(&opt, handle);
	opt.subControls = QStyle::SC_SliderHandle;
	QStyle::SubControl pressed = (handle == CXSlider::MinHandle ? minPressed : maxPressed);
	if (pressed == QStyle::SC_SliderHandle)
	{
		opt.activeSubControls = pressed;
		opt.state |= QStyle::State_Sunken;
	}
	painter->drawComplexControl(QStyle::CC_Slider, opt);
}

void CXSliderPrivate::triggerAction(QAbstractSlider::SliderAction action, bool main)
{
	int value = 0;
	bool no = false;
	bool up = false;
	const int minim = m_pSlider->minimum();
	const int maxim = m_pSlider->maximum();
	const CXSlider::RangeHandle altControl = (mainControl == CXSlider::MinHandle ? CXSlider::MaxHandle : CXSlider::MinHandle);

	blockTracking = true;

	switch (action)
	{
	case QAbstractSlider::SliderSingleStepAdd:
		if ((main && mainControl == CXSlider::MaxHandle) || (!main && altControl == CXSlider::MaxHandle))
		{
			value = qBound(minim, max + m_pSlider->singleStep(), maxim);
			up = true;
			break;
		}
		value = qBound(minim, min + m_pSlider->singleStep(), maxim);
		break;
	case QAbstractSlider::SliderSingleStepSub:
		if ((main && mainControl == CXSlider::MaxHandle) || (!main && altControl == CXSlider::MaxHandle))
		{
			value = qBound(minim, max - m_pSlider->singleStep(), maxim);
			up = true;
			break;
		}
		value = qBound(minim, min - m_pSlider->singleStep(), maxim);
		break;
	case QAbstractSlider::SliderToMinimum:
		value = minim;
		if ((main && mainControl == CXSlider::MaxHandle) || (!main && altControl == CXSlider::MaxHandle))
			up = true;
		break;
	case QAbstractSlider::SliderToMaximum:
		value = maxim;
		if ((main && mainControl == CXSlider::MaxHandle) || (!main && altControl == CXSlider::MaxHandle))
			up = true;
		break;
	case QAbstractSlider::SliderMove:
		if ((main && mainControl == CXSlider::MaxHandle) || (!main && altControl == CXSlider::MaxHandle))
			up = true;
	case QAbstractSlider::SliderNoAction:
		no = true;
		break;
	default:
		break;
	}

	if (!no && !up)
	{
		if (movement == CXSlider::NoCrossing)
			value = qMin(value, max);
		else if (movement == CXSlider::NoOverlapping)
			value = qMin(value, max - 1);

		if (movement == CXSlider::FreeMovement && value > max)
		{
			swapControls();
			m_pSlider->setMaxPosition(value);
		}
		else
		{
			m_pSlider->setMinPosition(value);
		}
	}
	else if (!no)
	{
		if (movement == CXSlider::NoCrossing)
			value = qMax(value, min);
		else if (movement == CXSlider::NoOverlapping)
			value = qMax(value, min + 1);

		if (movement == CXSlider::FreeMovement && value < min)
		{
			swapControls();
			m_pSlider->setMinPosition(value);
		}
		else
		{
			m_pSlider->setMaxPosition(value);
		}
	}

	blockTracking = false;
	m_pSlider->setMinValue(minPos);
	m_pSlider->setMaxValue(maxPos);
}

void CXSliderPrivate::swapControls()
{
	qSwap(min, max);
	qSwap(minPressed, maxPressed);
	lastPressed = (lastPressed == CXSlider::MinHandle ? CXSlider::MaxHandle : CXSlider::MinHandle);
	mainControl = (mainControl == CXSlider::MinHandle ? CXSlider::MaxHandle : CXSlider::MinHandle);
}

//void CXSliderPrivate::updateRange(int min, int max)
//{
//    Q_UNUSED(min);
//    Q_UNUSED(max);
//
//    m_pSlider->setRange(min, max);
//}

void CXSliderPrivate::movePressedHandle()
{
	switch (lastPressed)
	{
	case CXSlider::MinHandle:
		if (minPos != min)
		{
			bool main = (mainControl == CXSlider::MinHandle);
			triggerAction(QAbstractSlider::SliderMove, main);
		}
		break;
	case CXSlider::MaxHandle:
		if (maxPos != max)
		{
			bool main = (mainControl == CXSlider::MaxHandle);
			triggerAction(QAbstractSlider::SliderMove, main);
		}
		break;
	default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

CXSlider::CXSlider(QWidget* parent) : QSlider(parent)
{
	m_pSliderPrivate = new CXSliderPrivate(this);
	connect(this, SIGNAL(rangeChanged(int, int)), this, SLOT(SetRange(int, int)));
	connect(this, SIGNAL(sliderReleased()), this, SLOT(slotMovePressedHandle()));
}


CXSlider::CXSlider(Qt::Orientation orientation, QWidget* parent) : QSlider(orientation, parent)
{
	m_pSliderPrivate = new CXSliderPrivate(this);
	connect(this, SIGNAL(rangeChanged(int, int)), this, SLOT(SetRange(int, int)));
	connect(this, SIGNAL(sliderReleased()), this, SLOT(slotMovePressedHandle()));
}


CXSlider::~CXSlider()
{
	delete m_pSliderPrivate;
	m_pSliderPrivate = NULL;
}

void CXSlider::slotMovePressedHandle()
{
	m_pSliderPrivate->movePressedHandle();
}


CXSlider::HandleMovementMode CXSlider::handleMovementMode() const
{
	return m_pSliderPrivate->movement;
}

void CXSlider::setHandleMovementMode(CXSlider::HandleMovementMode mode)
{
	m_pSliderPrivate->movement = mode;
}


int CXSlider::minValue() const
{
	return qMin(m_pSliderPrivate->min, m_pSliderPrivate->max);
}

void CXSlider::setMinValue(int min)
{
	SetRange(min, m_pSliderPrivate->max);
}


int CXSlider::maxValue() const
{
	return qMax(m_pSliderPrivate->min, m_pSliderPrivate->max);
}

void CXSlider::setMaxValue(int max)
{
	SetRange(m_pSliderPrivate->min, max);
}


void CXSlider::SetRange(int min, int max)
{
	const int low = qBound(minimum(), qMin(min, max), maximum());
	const int upp = qBound(minimum(), qMax(min, max), maximum());
	if (low != m_pSliderPrivate->min || upp != m_pSliderPrivate->max)
	{
		if (low != m_pSliderPrivate->min)
		{
			m_pSliderPrivate->min = low;
			m_pSliderPrivate->minPos = low;
			emit minValueChanged(low);
		}
		if (upp != m_pSliderPrivate->max)
		{
			m_pSliderPrivate->max = upp;
			m_pSliderPrivate->maxPos = upp;
			emit maxValueChanged(upp);
		}
		emit rangeChanged(m_pSliderPrivate->min, m_pSliderPrivate->max);
		update();
	}
}


int CXSlider::minPosition() const
{
	return m_pSliderPrivate->minPos;
}

void CXSlider::setMinPosition(int min)
{
	if (m_pSliderPrivate->minPos != min)
	{
		m_pSliderPrivate->minPos = min;
		if (!hasTracking())
			update();
		if (isSliderDown())
			emit minPositionChanged(min);
		if (hasTracking() && !m_pSliderPrivate->blockTracking)
		{
			bool main = (m_pSliderPrivate->mainControl == CXSlider::MinHandle);
			m_pSliderPrivate->triggerAction(SliderMove, main);
		}
	}
}


int CXSlider::maxPosition() const
{
	return m_pSliderPrivate->maxPos;
}

void CXSlider::setMaxPosition(int max)
{
	if (m_pSliderPrivate->maxPos != max)
	{
		m_pSliderPrivate->maxPos = max;
		if (!hasTracking())
			update();
		if (isSliderDown())
			emit maxPositionChanged(max);
		if (hasTracking() && !m_pSliderPrivate->blockTracking)
		{
			bool main = (m_pSliderPrivate->mainControl == CXSlider::MaxHandle);
			m_pSliderPrivate->triggerAction(SliderMove, main);
		}
	}
}


void CXSlider::keyPressEvent(QKeyEvent* event)
{
	QSlider::keyPressEvent(event);

	bool main = true;
	SliderAction action = SliderNoAction;
	switch (event->key())
	{
	case Qt::Key_Left:
		main = (orientation() == Qt::Horizontal);
		action = !invertedAppearance() ? SliderSingleStepSub : SliderSingleStepAdd;
		break;
	case Qt::Key_Right:
		main = (orientation() == Qt::Horizontal);
		action = !invertedAppearance() ? SliderSingleStepAdd : SliderSingleStepSub;
		break;
	case Qt::Key_Up:
		main = (orientation() == Qt::Vertical);
		action = invertedControls() ? SliderSingleStepSub : SliderSingleStepAdd;
		break;
	case Qt::Key_Down:
		main = (orientation() == Qt::Vertical);
		action = invertedControls() ? SliderSingleStepAdd : SliderSingleStepSub;
		break;
	case Qt::Key_Home:
		main = (m_pSliderPrivate->mainControl == CXSlider::MinHandle);
		action = SliderToMinimum;
		break;
	case Qt::Key_End:
		main = (m_pSliderPrivate->mainControl == CXSlider::MaxHandle);
		action = SliderToMaximum;
		break;
	default:
		event->ignore();
		break;
	}

	if (action)
		m_pSliderPrivate->triggerAction(action, main);
}


void CXSlider::mousePressEvent(QMouseEvent* event)
{
	if (minimum() == maximum() || (event->buttons() ^ event->button()))
	{
		event->ignore();
		return;
	}

	m_pSliderPrivate->handleMousePress(event->pos(), m_pSliderPrivate->maxPressed, m_pSliderPrivate->max, CXSlider::MaxHandle);
	if (m_pSliderPrivate->maxPressed != QStyle::SC_SliderHandle)
		m_pSliderPrivate->handleMousePress(event->pos(), m_pSliderPrivate->minPressed, m_pSliderPrivate->min, CXSlider::MinHandle);

	m_pSliderPrivate->firstMovement = true;
	event->accept();
}


void CXSlider::mouseMoveEvent(QMouseEvent* event)
{
	if (m_pSliderPrivate->minPressed != QStyle::SC_SliderHandle && m_pSliderPrivate->maxPressed != QStyle::SC_SliderHandle)
	{
		event->ignore();
		return;
	}

	QStyleOptionSlider opt;
	m_pSliderPrivate->initStyleOption(&opt);
	const int m = style()->pixelMetric(QStyle::PM_MaximumDragDistance, &opt, this);
	int newPosition = m_pSliderPrivate->pixelPosToRangeValue(m_pSliderPrivate->pick(event->pos()) - m_pSliderPrivate->offset);
	if (m >= 0)
	{
		const QRect r = rect().adjusted(-m, -m, m, m);
		if (!r.contains(event->pos()))
		{
			newPosition = m_pSliderPrivate->position;
		}
	}

	// pick the preferred handle on the first movement
	if (m_pSliderPrivate->firstMovement)
	{
		if (m_pSliderPrivate->min == m_pSliderPrivate->max)
		{
			if (newPosition < minValue())
			{
				m_pSliderPrivate->swapControls();
				m_pSliderPrivate->firstMovement = false;
			}
		}
		else
		{
			m_pSliderPrivate->firstMovement = false;
		}
	}

	if (m_pSliderPrivate->minPressed == QStyle::SC_SliderHandle)
	{
		if (m_pSliderPrivate->movement == NoCrossing)
			newPosition = qMin(newPosition, maxValue());
		else if (m_pSliderPrivate->movement == NoOverlapping)
			newPosition = qMin(newPosition, maxValue() - 1);

		if (m_pSliderPrivate->movement == FreeMovement && newPosition > m_pSliderPrivate->max)
		{
			m_pSliderPrivate->swapControls();
			setMaxPosition(newPosition);
		}
		else
		{
			setMinPosition(newPosition);
		}
	}
	else if (m_pSliderPrivate->maxPressed == QStyle::SC_SliderHandle)
	{
		if (m_pSliderPrivate->movement == NoCrossing)
			newPosition = qMax(newPosition, minValue());
		else if (m_pSliderPrivate->movement == NoOverlapping)
			newPosition = qMax(newPosition, minValue() + 1);

		if (m_pSliderPrivate->movement == FreeMovement && newPosition < m_pSliderPrivate->min)
		{
			m_pSliderPrivate->swapControls();
			setMinPosition(newPosition);
		}
		else
		{
			setMaxPosition(newPosition);
		}
	}
	event->accept();
}


void CXSlider::mouseReleaseEvent(QMouseEvent* event)
{
	QSlider::mouseReleaseEvent(event);
	setSliderDown(false);
	m_pSliderPrivate->minPressed = QStyle::SC_None;
	m_pSliderPrivate->maxPressed = QStyle::SC_None;
	update();
}


void CXSlider::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QStylePainter painter(this);

	// groove & ticks
	QStyleOptionSlider opt;
	m_pSliderPrivate->initStyleOption(&opt);
	opt.sliderValue = 0;
	opt.sliderPosition = 0;
	opt.subControls = QStyle::SC_SliderGroove | QStyle::SC_SliderTickmarks;
	painter.drawComplexControl(QStyle::CC_Slider, opt);

	// handle rects
	opt.sliderPosition = m_pSliderPrivate->minPos;
	const QRect lr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
	const int lrv = m_pSliderPrivate->pick(lr.center());
	opt.sliderPosition = m_pSliderPrivate->maxPos;
	const QRect ur = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
	const int urv = m_pSliderPrivate->pick(ur.center());

	// handles
	switch (m_pSliderPrivate->lastPressed)
	{
	case CXSlider::MinHandle:
		m_pSliderPrivate->drawHandle(&painter, CXSlider::MaxHandle);
		m_pSliderPrivate->drawHandle(&painter, CXSlider::MinHandle);
		break;
	case CXSlider::MaxHandle:
	default:
		m_pSliderPrivate->drawHandle(&painter, CXSlider::MinHandle);
		m_pSliderPrivate->drawHandle(&painter, CXSlider::MaxHandle);
		break;
	}
}
