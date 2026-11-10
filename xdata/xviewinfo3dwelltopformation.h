#ifndef X3DWELLTOPFORMATIONVIEWINFO_H
#define X3DWELLTOPFORMATIONVIEWINFO_H

#include "xviewinfoobject.h"
#include "xdata_global.h"

///@brief	view info of well top formation(3d)
///@author	PEZY
///@date	2014-06-12
///@see

class XDATA_EXPORT CXViewInfo3DWellTopFormation : public CXViewInfoObject
{
public:
	CXViewInfo3DWellTopFormation();
	
	enum EDisplayMode {WT_SPHERE, WT_DISK, WT_CUBE};

	///@brief Set object ID
	virtual void SetViewObjectID(const QUuid& objID) override;

	void SetDisplayMode(EDisplayMode mode){m_eDisplayMode = mode;}
	EDisplayMode GetDisplayMode() const {return m_eDisplayMode;}

	X_PROPERTY(float, Radius);
	X_PROPERTY(float, Height);
	X_PROPERTY(QColor, WellTopFormationColor);
	X_PROPERTY(bool, WellTopFormationUseObjColor);
	X_PROPERTY(bool, FormationAnnVisible);
	X_PROPERTY(QColor, FormationAnnColor);
	X_PROPERTY(bool, FormationAnnUseObjColor);
	X_PROPERTY(int, FormationAnnSize);
	X_PROPERTY(QString, FormationAnnFont);
	X_PROPERTY(QColor, FormationBgrColor);
	X_PROPERTY(bool, FormationBgrUseObjColor);
	X_PROPERTY(int, FormationBgrTrans);

	///@brief Apply some of other view info into current one
    virtual bool ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo) override;

private:
	EDisplayMode m_eDisplayMode;
};

#endif // RL3DWELLTOPFORMATIONVIEWINFO_H
