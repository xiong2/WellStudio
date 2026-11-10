#include "xview.h"
#include "xeventconsole.h"

IKEView::IKEView()
{
	CXEventConsole::Instance().RegisterView(this);
}

IKEView::~IKEView()
{
	CXEventConsole::Instance().UnregisterView(this);
}
