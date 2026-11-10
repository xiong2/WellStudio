#ifndef XCONSOLE_GLOBAL_H
#define XCONSOLE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef XCONSOLE_LIB
# define XCONSOLE_EXPORT Q_DECL_EXPORT
#else
# define XCONSOLE_EXPORT Q_DECL_IMPORT
#endif

#endif // XCONSOLE_GLOBAL_H
