#ifndef XDEF_H
#define XDEF_H

#include <quuid.h>
#include <qmetatype.h>
#include <vector>
#include <qvariant.h>

///@brief KE property with member
//#define X_PROPERTY(type, name) \
//	private: type m_##name; \
//	public: type Get##name() const { return property(#name).value<type>(); } \
//	void Set##name(const type& v) { setProperty(#name, QVariant::fromValue<type>(v)); m_##name = v; }

///@brief Define KE property
#define X_PROPERTY(type,name) type Get##name() const{return property(#name).value<type>();}; void Set##name(const type& v){setProperty(#name,QVariant::fromValue<type>(v));}

///@brief Define a few custom types that can convert from and to QVariant
Q_DECLARE_METATYPE(std::vector<int>)
Q_DECLARE_METATYPE(std::vector<unsigned int>)
Q_DECLARE_METATYPE(std::vector<float>)
Q_DECLARE_METATYPE(std::vector<double>)
Q_DECLARE_METATYPE(std::vector<bool>)
Q_DECLARE_METATYPE(std::vector<QUuid>)
Q_DECLARE_METATYPE(std::vector<qint64>)
Q_DECLARE_METATYPE(QUuid)	


enum EEventType
{
	EInfoChanged,		//	Information, such as name, icon, template, viewinfo, and so on, changed.
	EDataChanged,				//	Data changed.
	EColormapChanged,           // Colormap changed
	EDeleted,					//	The whole object be deleted.
	EAdded,	                    // new object added to the tree
	EPartialDataChanged,
	EActivate,					// Active				
	EDeactivate,				// Deactive	
	EWindowSizeChanged,			// the window's size changed.
	EChairmode,
	ELightToggle
};

enum EXWindowType
{
	eNoWindow,
	eLogViewWindow,
	eCrossplotWindow,
	eHistogramWindow,
	e3DWindow,
	eSectionWindowBlank,
	eSectionWindow,
	e3DBaseMap,
	eGSSectionWindow,
	eGSBaseMap,
	eGSPDGWindow,
	eGSFRGWindow
};

enum EImportFileType
{
	eGeneralASCII,

	e3DPointsASCII,

	eFaultPolygonASCII,
	eFaultSticksASCII,

	eWellHeaderASCII,
	eWellPathASCII,
	eWellLAS,
	eWellLAS_NoTemplate,
	eWellWIS,
	eWellXTF,
	eWellDLIS,
	eWellASCIILog,
	eWellCheckShot,
	eWellTopsASCII,
	eMicroSeismicASCII,

	// 3-D Surface
	eZMapASCII,
	e3DHorizonPicks,
	eGeoquestCardImage7,

	//segy file
	e3DSEGY,
	e2DSEGY,
	e2DLineNavigate,

	//	Reservoir file.
	eReservoir,

	eFracturePatches,
};

enum EDomainType
{
	eNull,
	eTimeDomain,
	eDepthDomain
};

enum EXSectionType
{
	eInlineSection,
	eCrosslineSection,
	eRandomSection,
	eTimeSlice,
	eInlineProfile,			//	Inline with profile from a picture.
	e2DSection,
};

#endif // RLDEF_H