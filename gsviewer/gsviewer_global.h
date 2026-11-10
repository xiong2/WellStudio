#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(GSVIEWER_LIB)
#  define GSVIEWER_EXPORT Q_DECL_EXPORT
# else
#  define GSVIEWER_EXPORT Q_DECL_IMPORT
# endif
#else
# define GSVIEWER_EXPORT
#endif
