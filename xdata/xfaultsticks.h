#ifndef _CXFaultStickS_H__
#define _CXFaultStickS_H__

#include "xdata_global.h"
#include "xobject.h"
#include "xdef.h"
#include "xvec.h"

class CXSeismicUTMTool;

enum EFaultStickType
{
	eFTRandom = 0,
	eFTInline = 1,
	eFTCrossline = 2,
	eFTTimeSlice = 3,
};

///@brief	The class used to represent a fault stick.
///@author	Xiong Xiong
///@date	Apr, 2014
///@see		
class XDATA_EXPORT CXFaultStick
{
public:
	CXFaultStick();
	~CXFaultStick();

	///	Populate the data.
	bool ResetData(double* pData, unsigned int iNumber, EFaultStickType eType = eFTRandom, QUuid lineID = QUuid(), int iSecNumber = -1, int* pTraceNumber = NULL);

	///	Use the given UTM and XYZ data to check and set the stick type.
	void CheckStickType(CXSeismicUTMTool *);

	unsigned int GetPointNumber()
	{
		return m_iNumPoint;
	}

	///	Get data
	double* GetXYZData(unsigned int&);

	EFaultStickType GetStickType()
	{
		return m_eFSType;
	}

	QUuid GetLineID()
	{
		return m_lineID;
	}

	int GetSecNumber()
	{
		return m_iSecNumber;
	}

	int* GetTraceNumber()
	{
		return m_pTraceNumber;
	}

	//	Add for GSM.
	// support for `range for`.
	std::vector<XPoint>::iterator begin();
	std::vector<XPoint>::const_iterator begin() const;
	std::vector<XPoint>::iterator end();
	std::vector<XPoint>::const_iterator end() const;

	// support for QDataStream
	friend QDataStream& operator<<(QDataStream& stream, const CXFaultStick& stick);
	friend QDataStream& operator>>(QDataStream& stream, CXFaultStick& stick);

	size_t PointsNum() const;
	void Clear();
	bool IsEmpty();
	const XPoint& First() const;
	const XPoint& Last() const;
	QPointF AvgXY() const;

private:
	EFaultStickType	m_eFSType;
	double*			m_pData;			//	Array of x, y, z, always exist, the length of m_pData.
	unsigned int	m_iNumPoint;		//	Number of points.
	QUuid			m_lineID;			//	Only valid for random section picked sticks.
	int				m_iSecNumber;		//	Line/CDP number of stick picked on Inline/Crossline.
	int*			m_pTraceNumber;		//	Trace number of each nodes, length is m_iNumPoint while picked on Inline/crossline, otherwise zero.

	std::vector<XPoint> m_vecPoints;
};

///@brief	The class used to represent a fault consist of sticks.
///@author	Xiong Xiong
///@date	Mar, 2014
///@see		
class XDATA_EXPORT CXFaultSticks: public CXObject
{
public:
	CXFaultSticks() { ; }
	CXFaultSticks(QString strName, QUuid surveyID);

	QList<CXFaultStick *>& GetAllSticks()
	{
		if (m_listSticks.isEmpty())
			LoadData();

		return m_listSticks;
	}

	///	Add one stick, if it not already exist.
	void AddOneStick(CXFaultStick *);

	///	Remove on stick, if it exists.
	void RemoveOneStick(CXFaultStick *);

	virtual QStringList GetDescription();
	virtual QString GetTypeString() { return "Fault Sticks"; }

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	///@brief Get all sticks belong to a specified section.
	void GetSticksOnSection(int iSectionNum, EXSectionType eSectionType, QList<CXFaultStick *>&);

	///@brief Get all sticks belong to a specified random section.
	void GetSticksOnSection(QUuid sectionID, QList<CXFaultStick *>&);

	///@brief Get all sticks intersect to a specified section.
	void GetSticksIntersectSection(int iSectionNum, EXSectionType eSectionType, QList<QPointF>&, QList<CXFaultStick *>&);

	QUuid GetSurveyID()
	{
		return m_surveyID;
	}

	//	Add for GSM
	CXFaultStick* GetStick(size_t index);
	size_t GetStickNum();

protected:
	virtual void _SetSelfDimension();

	//	Sort the sticks by their spatial location.
	virtual void sortSticks();

	QList<CXFaultStick *>		m_listSticks;
	QUuid	m_surveyID;

	virtual void _WriteData();
	virtual void _ReadData();
	virtual void _freeMemory();

};

#endif