#ifndef _CXGEOBODY_H__
#define _CXGEOBODY_H__

#include <QFile>
#include "xdata_global.h"
#include "xobject.h"
#include "xsortondisk.h"
#include "xseismicutmtool.h"

class CXParametersGeobodyDetection;
class CX3DSurface;

/**
*@brief		This class used to offer a large dataset by a fragment each time.
*@author	Xiong Xiong
*@date		Aug, 2015
*/
template<class T>
class CXBufferFile
{
public:
	CXBufferFile(QString strFileName) : m_File(strFileName)
	{
		m_bFileOpen = m_File.open(QIODevice::ReadOnly);

	}
	T *GetBuffer(qint64 nNeedReadBufferSize, qint64& nReallyReadBufferSize)
	{
		if (!m_bFileOpen) return NULL;

		m_vData.resize(nNeedReadBufferSize * sizeof(T));
		nReallyReadBufferSize = m_File.read((char*)(&m_vData[0]), nNeedReadBufferSize * sizeof(T));
		nReallyReadBufferSize /= sizeof(T);
		if (nReallyReadBufferSize>0)
		{
			return &m_vData[0];
		}
		return NULL;
	}
    ~CXBufferFile()
	{
		m_File.close();
	}
private:
	QFile m_File;
	bool m_bFileOpen;
	std::vector<T> m_vData;
};

/**
*@brief		It represent geobody.
*@author	Xiong Xiong
*@date		Aug, 2015
*@see		See UML diagram "geobody.uml" to find the relationship with other classes.
*/
class XDATA_EXPORT CXGeobody: public CXObject
{
public:
	CXGeobody();
	CXGeobody(CXSeismicUTMTool *, float fSZ, float fEZ, float fZInc, bool bWhole = false);
	~CXGeobody();

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	virtual QString GetTypeString() { return "Geobody"; }

	///	Is a whole geobody?
	bool IsMerged()
	{
		return m_bMerged;
	}

	///	Get the number of cells.
	unsigned int GetTotalCellNumber()
	{
		return m_iTotalCellNumber;
	}

	///	Get the number of cells.
	unsigned int GetSkinCellNumber()
	{
		return m_iSkinCellNumber;
	}

	///	Get the central position of a specific cell.
	void GetCellCentralPosition(qint64 iCellIndex, double& x, double& y, double& z);

	void PopulateData(QString sFile, unsigned int iSkinCellNumber);

	///	Get all the skin cells, do not delte the return pointer!
	qint64* GetAllCells(unsigned int& iNumberCell);

	void Unite(CXGeobody *pOtherGeobody);

	CXSeismicUTMTool& GetUTM()
	{
		return m_utm;
	}

	float GetZByK(int K);
	int GetNZ();

	///@brief Overwrite the basic implement to offer more info.
	QStringList GetDescription();

	CXParametersGeobodyDetection *	GetDetectParameter();

	//	Get the top and bottom surface of the geobody.
	bool GetTopBottomSurface(CX3DSurface *pTopSurface, CX3DSurface *pBottomSurface);

	float GetZInc()
	{
		return m_fZInc;
	}

	void GetZRange(float& fSZ, float& fEZ)
	{
		fSZ = m_fStartZ;
		fEZ = m_fEndZ;
	}

	void SetDimension(double dXMin, double dXMax, double dYMin, double dYMax, double dZMin, double dZMax);

protected:
	CXSeismicUTMTool		m_utm;

	bool m_bMerged;			//	Is the whole geobody or only an individual one.

	unsigned int			m_iTotalCellNumber;		//	Total cells' amount.
	unsigned int			m_iSkinCellNumber;		//	Skin cells' amount.
	qint64*					m_pCells;				//	All cells.

	float m_fStartZ;
	float m_fEndZ;
	float m_fZInc;

	virtual void _findSelfLimit();

	void indexToIJK(qint64 iIndex, int &i, int &j, int &k);

	virtual void _ReadData();
};

#endif