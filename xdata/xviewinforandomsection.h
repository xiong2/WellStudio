#ifndef XVIEWINFORANDOMSECTION_H
#define XVIEWINFORANDOMSECTION_H

/*!
 *	@brief	data structure for view info of random section
 *	@author	pezy
 *	@date	2016-07-21
 *	@see	CXSeismicRandomSection
 */

#include "xviewinfoobject.h"
#include "xdata_global.h"

class XDATA_EXPORT CXViewInfoRandomSection : public CXViewInfoObject
{
public:
	CXViewInfoRandomSection();
	~CXViewInfoRandomSection();

	//! @brief	basemap window:
	X_PROPERTY(bool, BMLineUseObjectColor)
	X_PROPERTY(QColor, BMLineColor)
	X_PROPERTY(int, BMLineWidth)
	X_PROPERTY(int, BMPointSize)

	X_PROPERTY(QColor, BMPickedLineColor)
	X_PROPERTY(int, BMPickedLineWidth)


	virtual void SetViewObjectID(const QUuid& objID) override;
};

#endif // KEVIEWINFORANDOMSECTION_H
