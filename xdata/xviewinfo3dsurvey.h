#ifndef XVIEWINFO3DSURVEY_H
#define XVIEWINFO3DSURVEY_H

/*!
 *	@brief	view info for 3D survey.
 *	@author	pezy
 *	@date	2016-05-18
 *	@see
 */

#include "xviewinfoobject.h"
#include "xdata_global.h"

class XDATA_EXPORT CXViewInfo3DSurvey : public CXViewInfoObject
{
public:
	CXViewInfo3DSurvey();
	~CXViewInfo3DSurvey();

	void SetViewObjectID(const QUuid& objID) override;
	
	X_PROPERTY(bool, BoundaryLineUseObjColor);
	X_PROPERTY(QColor, BoundaryLineColor);
	X_PROPERTY(int, BoundaryLineWidth);
	
	X_PROPERTY(bool, SeismicLineVisible);
	X_PROPERTY(bool, SeismicLineUseObjColor);
	X_PROPERTY(QColor, SeismicLineColor);
	X_PROPERTY(int, SeismicLineWidth);
	
	X_PROPERTY(bool, TracePointVisible);
	X_PROPERTY(bool, TracePointUseObjColor);
	X_PROPERTY(QColor, TracePointColor);
	X_PROPERTY(int, TracePointSymbol);

	X_PROPERTY(bool, TickmarksVisible);
	X_PROPERTY(bool, TickmarksUseObjColor);
	X_PROPERTY(QColor, TickmarksColor);
	X_PROPERTY(QString, TickmarksFont);
	X_PROPERTY(int, TickmarksFontSize);
	X_PROPERTY(bool, InlineAnnotationOnBegin);
	X_PROPERTY(bool, InlineAnnotationOnEnd);
	X_PROPERTY(bool, XlineAnnotationOnBegin);
	X_PROPERTY(bool, XlineAnnotationOnEnd);
	
	X_PROPERTY(bool, SurveyNameVisible);
	X_PROPERTY(bool, SurveyNameUseObjColor);
	X_PROPERTY(QColor, SurveyNameColor);
	X_PROPERTY(QString, SurveyNameFont);
	X_PROPERTY(int, SurveyNameFontSize);
};

#endif // KEVIEWINFO3DSURVEY_H
