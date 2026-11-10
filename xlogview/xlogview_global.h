#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(XLOGVIEW_LIB)
#  define XLOGVIEW_EXPORT Q_DECL_EXPORT
# else
#  define XLOGVIEW_EXPORT Q_DECL_IMPORT
# endif
#else
# define XLOGVIEW_EXPORT
#endif
