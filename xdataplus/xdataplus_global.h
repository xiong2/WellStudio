#ifndef XDATAPLUS_GLOBAL_H
#define XDATAPLUS_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef XDATAPLUS_LIB
# define XDATAPLUS_EXPORT Q_DECL_EXPORT
#else
# define XDATAPLUS_EXPORT Q_DECL_IMPORT
#endif

#endif // XDATAPLUS_GLOBAL_H
