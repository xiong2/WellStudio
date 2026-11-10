#include "xosgwidget.h"
#include "xpickhandle.h"

#include <QPainter>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>

std::unordered_map<int, int> CXOSGWidget::m_mapKeys =
{
	{ Qt::Key_Escape, osgGA::GUIEventAdapter::KEY_Escape },
	{ Qt::Key_Tab, osgGA::GUIEventAdapter::KEY_Tab },
	{ Qt::Key_Backspace, osgGA::GUIEventAdapter::KEY_BackSpace },
	{ Qt::Key_Return, osgGA::GUIEventAdapter::KEY_Return },
	{ Qt::Key_Enter, osgGA::GUIEventAdapter::KEY_KP_Enter },
	{ Qt::Key_Insert, osgGA::GUIEventAdapter::KEY_Insert },
	{ Qt::Key_Delete, osgGA::GUIEventAdapter::KEY_Delete },
	{ Qt::Key_Pause, osgGA::GUIEventAdapter::KEY_Pause },
	{ Qt::Key_Print, osgGA::GUIEventAdapter::KEY_Print },
	{ Qt::Key_SysReq, osgGA::GUIEventAdapter::KEY_Sys_Req },
	{ Qt::Key_Clear, osgGA::GUIEventAdapter::KEY_Clear },
	{ Qt::Key_Home, osgGA::GUIEventAdapter::KEY_Home },
	{ Qt::Key_End, osgGA::GUIEventAdapter::KEY_End },
	{ Qt::Key_Left, osgGA::GUIEventAdapter::KEY_Left },
	{ Qt::Key_Up, osgGA::GUIEventAdapter::KEY_Up },
	{ Qt::Key_Right, osgGA::GUIEventAdapter::KEY_Right },
	{ Qt::Key_Down, osgGA::GUIEventAdapter::KEY_Down },
	{ Qt::Key_PageUp, osgGA::GUIEventAdapter::KEY_Page_Up },
	{ Qt::Key_PageDown, osgGA::GUIEventAdapter::KEY_Page_Down },
	{ Qt::Key_Shift, osgGA::GUIEventAdapter::KEY_Shift_L },
	{ Qt::Key_Control, osgGA::GUIEventAdapter::KEY_Control_L },
	{ Qt::Key_Meta, osgGA::GUIEventAdapter::KEY_Meta_L },
	{ Qt::Key_Alt, osgGA::GUIEventAdapter::KEY_Alt_L },
	{ Qt::Key_CapsLock, osgGA::GUIEventAdapter::KEY_Caps_Lock },
	{ Qt::Key_NumLock, osgGA::GUIEventAdapter::KEY_Num_Lock },
	{ Qt::Key_ScrollLock, osgGA::GUIEventAdapter::KEY_Scroll_Lock },
	{ Qt::Key_F1, osgGA::GUIEventAdapter::KEY_F1 },
	{ Qt::Key_F2, osgGA::GUIEventAdapter::KEY_F2 },
	{ Qt::Key_F3, osgGA::GUIEventAdapter::KEY_F3 },
	{ Qt::Key_F4, osgGA::GUIEventAdapter::KEY_F4 },
	{ Qt::Key_F5, osgGA::GUIEventAdapter::KEY_F5 },
	{ Qt::Key_F6, osgGA::GUIEventAdapter::KEY_F6 },
	{ Qt::Key_F7, osgGA::GUIEventAdapter::KEY_F7 },
	{ Qt::Key_F8, osgGA::GUIEventAdapter::KEY_F8 },
	{ Qt::Key_F9, osgGA::GUIEventAdapter::KEY_F9 },
	{ Qt::Key_F10, osgGA::GUIEventAdapter::KEY_F10 },
	{ Qt::Key_F11, osgGA::GUIEventAdapter::KEY_F11 },
	{ Qt::Key_F12, osgGA::GUIEventAdapter::KEY_F12 },
	{ Qt::Key_Space, osgGA::GUIEventAdapter::KEY_Space },
	{ Qt::Key_Exclam, osgGA::GUIEventAdapter::KEY_Exclaim },
	{ Qt::Key_QuoteDbl, osgGA::GUIEventAdapter::KEY_Quotedbl },
	{ Qt::Key_NumberSign, osgGA::GUIEventAdapter::KEY_Hash },
	{ Qt::Key_Dollar, osgGA::GUIEventAdapter::KEY_Dollar },
	{ Qt::Key_Ampersand, osgGA::GUIEventAdapter::KEY_Ampersand },
	{ Qt::Key_Apostrophe, osgGA::GUIEventAdapter::KEY_Quote },
	{ Qt::Key_ParenLeft, osgGA::GUIEventAdapter::KEY_Leftparen },
	{ Qt::Key_ParenRight, osgGA::GUIEventAdapter::KEY_Rightparen },
	{ Qt::Key_Asterisk, osgGA::GUIEventAdapter::KEY_Asterisk },
	{ Qt::Key_Plus, osgGA::GUIEventAdapter::KEY_Plus },
	{ Qt::Key_Comma, osgGA::GUIEventAdapter::KEY_Comma },
	{ Qt::Key_Minus, osgGA::GUIEventAdapter::KEY_Minus },
	{ Qt::Key_Period, osgGA::GUIEventAdapter::KEY_Period },
	{ Qt::Key_Slash, osgGA::GUIEventAdapter::KEY_Slash },
	{ Qt::Key_0, osgGA::GUIEventAdapter::KEY_0 },
	{ Qt::Key_1, osgGA::GUIEventAdapter::KEY_1 },
	{ Qt::Key_2, osgGA::GUIEventAdapter::KEY_2 },
	{ Qt::Key_3, osgGA::GUIEventAdapter::KEY_3 },
	{ Qt::Key_4, osgGA::GUIEventAdapter::KEY_4 },
	{ Qt::Key_5, osgGA::GUIEventAdapter::KEY_5 },
	{ Qt::Key_6, osgGA::GUIEventAdapter::KEY_6 },
	{ Qt::Key_7, osgGA::GUIEventAdapter::KEY_7 },
	{ Qt::Key_8, osgGA::GUIEventAdapter::KEY_8 },
	{ Qt::Key_9, osgGA::GUIEventAdapter::KEY_9 },
	{ Qt::Key_Colon, osgGA::GUIEventAdapter::KEY_Colon },
	{ Qt::Key_Semicolon, osgGA::GUIEventAdapter::KEY_Semicolon },
	{ Qt::Key_Less, osgGA::GUIEventAdapter::KEY_Less },
	{ Qt::Key_Equal, osgGA::GUIEventAdapter::KEY_Equals },
	{ Qt::Key_Greater, osgGA::GUIEventAdapter::KEY_Greater },
	{ Qt::Key_Question, osgGA::GUIEventAdapter::KEY_Question },
	{ Qt::Key_At, osgGA::GUIEventAdapter::KEY_At },
	{ Qt::Key_A, osgGA::GUIEventAdapter::KEY_A },
	{ Qt::Key_B, osgGA::GUIEventAdapter::KEY_B },
	{ Qt::Key_C, osgGA::GUIEventAdapter::KEY_C },
	{ Qt::Key_D, osgGA::GUIEventAdapter::KEY_D },
	{ Qt::Key_E, osgGA::GUIEventAdapter::KEY_E },
	{ Qt::Key_F, osgGA::GUIEventAdapter::KEY_F },
	{ Qt::Key_G, osgGA::GUIEventAdapter::KEY_G },
	{ Qt::Key_H, osgGA::GUIEventAdapter::KEY_H },
	{ Qt::Key_I, osgGA::GUIEventAdapter::KEY_I },
	{ Qt::Key_J, osgGA::GUIEventAdapter::KEY_J },
	{ Qt::Key_K, osgGA::GUIEventAdapter::KEY_K },
	{ Qt::Key_L, osgGA::GUIEventAdapter::KEY_L },
	{ Qt::Key_M, osgGA::GUIEventAdapter::KEY_M },
	{ Qt::Key_N, osgGA::GUIEventAdapter::KEY_N },
	{ Qt::Key_O, osgGA::GUIEventAdapter::KEY_O },
	{ Qt::Key_P, osgGA::GUIEventAdapter::KEY_P },
	{ Qt::Key_Q, osgGA::GUIEventAdapter::KEY_Q },
	{ Qt::Key_R, osgGA::GUIEventAdapter::KEY_R },
	{ Qt::Key_S, osgGA::GUIEventAdapter::KEY_S },
	{ Qt::Key_T, osgGA::GUIEventAdapter::KEY_T },
	{ Qt::Key_U, osgGA::GUIEventAdapter::KEY_U },
	{ Qt::Key_V, osgGA::GUIEventAdapter::KEY_V },
	{ Qt::Key_W, osgGA::GUIEventAdapter::KEY_W },
	{ Qt::Key_X, osgGA::GUIEventAdapter::KEY_X },
	{ Qt::Key_Y, osgGA::GUIEventAdapter::KEY_Y },
	{ Qt::Key_Z, osgGA::GUIEventAdapter::KEY_Z },
	{ Qt::Key_BracketLeft, osgGA::GUIEventAdapter::KEY_Leftbracket },
	{ Qt::Key_Backslash, osgGA::GUIEventAdapter::KEY_Backslash },
	{ Qt::Key_BracketRight, osgGA::GUIEventAdapter::KEY_Rightbracket },
	{ Qt::Key_Underscore, osgGA::GUIEventAdapter::KEY_Underscore }
};

CXOSGWidget::CXOSGWidget(QWidget *parent, bool bBasemap) 
	: QOpenGLWidget(parent)
{
	m_dDevicePixelRatio = devicePixelRatio();
	resize(800, 600);

	m_pGraphWin = setUpViewerAsEmbeddedInWindow(x(), y(), width(), height());

	osg::Camera* pCamera = getCamera();
	pCamera->setGraphicsContext(m_pGraphWin);
	pCamera->setClearMask(pCamera->getClearMask() | GL_STENCIL_BUFFER_BIT);
	pCamera->setClearStencil(0);
	pCamera->setClearDepth(1.0f);
	pCamera->setClearColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	pCamera->setViewport(new osg::Viewport(x(), y(), width(), height()));

	if (!bBasemap)
	{
		pCamera->setProjectionMatrixAsPerspective(30.0, static_cast<float>(width()) / height(), 1.0, 10000.0);
	}
	else
	{
		pCamera->setProjectionMatrixAsOrtho(-width() / 2, width() / 2, -height() / 2, height() / 2, -10000.f, 10000.0f);
	}

	addEventHandler(new osgGA::StateSetManipulator(pCamera->getOrCreateStateSet()));
	addEventHandler(new osgViewer::StatsHandler);
	setThreadingModel(osgViewer::Viewer::SingleThreaded);
	realize();

	// enable multisampling for anti aliasing.
	QSurfaceFormat format;
	format.setSamples(8);
	this->setFormat(format);

	setMouseTracking(true);
	setFocusPolicy(Qt::ClickFocus);
}

CXOSGWidget::~CXOSGWidget()
{
}

CXPickhandle* CXOSGWidget::GetPickhandle()
{
	for (osg::ref_ptr<osgGA::EventHandler> handle : getEventHandlers())
	{
		if (handle->getName() == "PickHandle")
			return dynamic_cast<CXPickhandle*>(handle.get());
	}
	return nullptr;
}

void CXOSGWidget::paintGL()
{
	frame();
	update();
}

void CXOSGWidget::resizeGL(int w, int h)
{
	m_pGraphWin->getEventQueue()->windowResize(0, 0, w, h);
	m_pGraphWin->resized(0, 0, w, h);
	getCamera()->setViewport(0, 0, w, h);
}

void CXOSGWidget::keyPressEvent(QKeyEvent * event)
{
	_SetKeyboardModifiers(event);
	auto found = m_mapKeys.find(event->key());
	if (found == m_mapKeys.end())
		return;

	m_pGraphWin->getEventQueue()->keyPress(found->second);
}

void CXOSGWidget::keyReleaseEvent(QKeyEvent * event)
{
	if (event->isAutoRepeat())
	{
		event->ignore();
	}
	else
	{
		_SetKeyboardModifiers(event);

		auto found = m_mapKeys.find(event->key());
		if (found == m_mapKeys.end())
			return;

		m_pGraphWin->getEventQueue()->keyRelease(found->second);
	}
}

void CXOSGWidget::mousePressEvent(QMouseEvent * event)
{
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	_SetKeyboardModifiers(event);
	m_pGraphWin->getEventQueue()->mouseButtonPress(event->x() * m_dDevicePixelRatio, event->y() * m_dDevicePixelRatio, button);
}

void CXOSGWidget::mouseReleaseEvent(QMouseEvent * event)
{
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	_SetKeyboardModifiers(event);
	m_pGraphWin->getEventQueue()->mouseButtonRelease(event->x() * m_dDevicePixelRatio, event->y() * m_dDevicePixelRatio, button);
}

void CXOSGWidget::mouseMoveEvent(QMouseEvent * event)
{
	_SetKeyboardModifiers(event);
	m_pGraphWin->getEventQueue()->mouseMotion(event->x() * m_dDevicePixelRatio, event->y() * m_dDevicePixelRatio);
}

void CXOSGWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	_SetKeyboardModifiers(event);
	m_pGraphWin->getEventQueue()->mouseDoubleButtonPress(event->x() * m_dDevicePixelRatio, event->y() * m_dDevicePixelRatio, button);
}

void CXOSGWidget::wheelEvent(QWheelEvent * event)
{
	_SetKeyboardModifiers(event);
	m_pGraphWin->getEventQueue()->mouseScroll(event->orientation() == Qt::Vertical ?
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));
}

void CXOSGWidget::paintEvent(QPaintEvent * event)
{
	QOpenGLWidget::makeCurrent();

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	paintGL();

	QOpenGLWidget::paintEvent(event);

	painter.end();

	QOpenGLWidget::doneCurrent();
}

void CXOSGWidget::_SetKeyboardModifiers(QInputEvent * event) const
{
	int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
	unsigned int mask = 0;
	if (modkey & Qt::ShiftModifier) mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
	if (modkey & Qt::ControlModifier) mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
	if (modkey & Qt::AltModifier) mask |= osgGA::GUIEventAdapter::MODKEY_ALT;
	m_pGraphWin->getEventQueue()->getCurrentEventState()->setModKeyMask(mask);
}