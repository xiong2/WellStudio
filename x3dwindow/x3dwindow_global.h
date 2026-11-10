#ifndef X3DWINDOW_GLOBAL_H
#define X3DWINDOW_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef X3DWINDOW_LIB
# define X3DWINDOW_EXPORT Q_DECL_EXPORT
#else
# define X3DWINDOW_EXPORT Q_DECL_IMPORT
#endif

#endif // X3DWINDOW_GLOBAL_H
