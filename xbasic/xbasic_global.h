#ifndef XBASIC_GLOBAL_H
#define XBASIC_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef XBASIC_LIB
# define XBASIC_EXPORT Q_DECL_EXPORT
#else
# define XBASIC_EXPORT Q_DECL_IMPORT
#endif

#endif // XBASIC_GLOBAL_H
