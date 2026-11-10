#ifndef XBASICUI_GLOBAL_H
#define XBASICUI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef XBASICUI_LIB
# define XBASICUI_EXPORT Q_DECL_EXPORT
#else
# define XBASICUI_EXPORT Q_DECL_IMPORT
#endif

#endif // XBASICUI_GLOBAL_H
