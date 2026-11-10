#ifndef XSECTIONWINDOW_GLOBAL_H
#define XSECTIONWINDOW_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef XSECTIONWINDOW_LIB
# define XSECTIONWINDOW_EXPORT Q_DECL_EXPORT
#else
# define XSECTIONWINDOW_EXPORT Q_DECL_IMPORT
#endif

enum EXSectionEditMode
{
	Edit_NULL,
	Edit_Fault,
	Edit_Horizon,
	Edit_OrthoSection,
	Edit_RectZoom,
};

enum EXHorizonSnapMode
{
	ENone,
	EPeak,
	ETrough,
	ECrossA,
	ECrossB,
};

enum EXHorizonTrackMode
{
	EOverWrite,
	EStop,
	ELockAndContinue,
};

enum EXMouseEventType
{
	eSecButtonPress,
	eSecButtonRelease,
	eSecMouseMove,
	eSecDoubleClick,
};

#endif // XSECTIONWINDOW_GLOBAL_H
