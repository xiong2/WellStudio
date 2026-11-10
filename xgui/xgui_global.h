#ifndef XGUI_GLOBAL_H
#define XGUI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef XGUI_LIB
# define XGUI_EXPORT Q_DECL_EXPORT
#else
# define XGUI_EXPORT Q_DECL_IMPORT
#endif

#endif // XGUI_GLOBAL_H
