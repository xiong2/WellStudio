#include "xwaitcursor.h"
#include <qapplication.h>


CXWaitCursor::CXWaitCursor()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
}

CXWaitCursor::~CXWaitCursor()
{
	QApplication::restoreOverrideCursor();
}
