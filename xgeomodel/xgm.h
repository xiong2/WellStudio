#ifndef XGM_H
#define XGM_H

#include "xobject.h"
#include "xgeomodel_global.h"

class CXArchive;

class XGEOMODEL_EXPORT CXGM : public CXObject
{
public:
    CXGM(const QString& strName = "");
    ~CXGM();

    ///@brief Serialization using the binary data array
    virtual bool SerializeData(CXArchive& ar) override;

private:

};

#endif // GMGEOMODEL_H
