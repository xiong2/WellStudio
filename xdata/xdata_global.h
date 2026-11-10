#ifndef XDATA_GLOBAL_H
#define XDATA_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef XDATA_LIB
# define XDATA_EXPORT Q_DECL_EXPORT
#else
# define XDATA_EXPORT Q_DECL_IMPORT
#endif

#endif // XDATA_GLOBAL_H
