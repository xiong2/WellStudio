#include <QWheelEvent>
#include "xscrollarea.h"
#include "xdlgwelltie.h"

void CXScrollArea::wheelEvent(QWheelEvent *e)
	{
	CXDlgWellTie *pDlg = dynamic_cast<CXDlgWellTie *>(parent());

	pDlg->MoveScrollBar(e->angleDelta().y());
	}
