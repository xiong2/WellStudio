#ifndef XGEOMODEL_GLOBAL_H
#define XGEOMODEL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef XGEOMODEL_LIB
# define XGEOMODEL_EXPORT Q_DECL_EXPORT
#else
# define XGEOMODEL_EXPORT Q_DECL_IMPORT
#endif

#endif // XGEOMODEL_GLOBAL_H
