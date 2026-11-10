#ifndef XGUIPLUS_GLOBAL_H
#define XGUIPLUS_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef XGUIPLUS_LIB
# define XGUIPLUS_EXPORT Q_DECL_EXPORT
#else
# define XGUIPLUS_EXPORT Q_DECL_IMPORT
#endif

#endif // XGUIPLUS_GLOBAL_H
