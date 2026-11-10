#ifndef XVIEWINFOSEISMICDV_H
#define XVIEWINFOSEISMICDV_H

/*!
 *	@brief	data structure for view info of seismic data volume
 *	@author	pezy
 *	@date	2015-09-23
 *	@see	CXSeismicDataVolume
 */

#include "xviewinfoobject.h"
#include "xdata_global.h"
#include "xhistogram.h"

class CXObject;

class XDATA_EXPORT CXViewInfoSeismicDV : public CXViewInfoObject
{
public:
	CXViewInfoSeismicDV();
	~CXViewInfoSeismicDV();

	//! @brief	basemap window:
	X_PROPERTY(bool, BMUseObjectColor)
	X_PROPERTY(QColor, BMFrameColor)
	X_PROPERTY(int, BMFrameWidth)

	virtual void SetViewObjectID(const QUuid& objID) override;

	void CalcFoldHistogram(CXObject* pObjDV);
	const CXHistogram& GetFoldHistogram() { return m_histogramFold; }
	bool HasFold() { return m_histogramFold.m_nValidDataNum != 0; }

private:
	CXHistogram m_histogramFold;
};

#endif // KEVIEWINFOSEISMICDV_H
