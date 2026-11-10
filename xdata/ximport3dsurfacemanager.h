#ifndef XIMPORT3DSURFACEMANAGER_H
#define XIMPORT3DSURFACEMANAGER_H

#include "xdata_global.h"
#include <vector>
#include "xdef.h"
#include <QStringList>
#include "xdelimiter.h"
#include "xmathmacro.h"

class CXUTMTool;
class CX3DSurface;
class QWidget;

/**
* @class CXImportSurfacePara in the file "rlimport3dsurfacemanager.h"
* @brief The class provides the parameters during importing surface, the class can only used by "CXImport3DSurfaceManager".
* 
* @author Yong Shu 
* @date 4/10/2014
*/
class XDATA_EXPORT CXImportSurfacePara
{
public:
	///@brief Constructor and destructor
	CXImportSurfacePara();
	~CXImportSurfacePara();

	///@brief Calculate the increment of the inline or crossline 
	void CalculateLineIncrement();

	///@brief Parse a string list to the meaningful data 
	inline bool ParseOneLineData(const QStringList& strList, float* pZ, double fInvalidEPS);

	///@brief Set the initial value for min or max data
	void ResetMinMaxValues();

	///@brief Release the memory
	void ClearDataBuffer();

public:
	// Grid size
	int m_nI;
	int m_nJ;	

	// Horizon number
	int m_nHorizonCount;

	// Invalid data
	double m_fInvalidData;

	// Import line range
	int m_iFirstLineNum;
	int m_iLastLineNum;

	// Column index
	int m_nInlineIndex;     
	int m_nCrosslineIndex;  
	int m_nXIndex;         
	int  m_nYIndex;
	int m_nIIndex;
	int m_nJIndex;
	std::vector<int> m_vecDataIndex;   		

	// Column data
	std::vector<int> m_vecInline;
	std::vector<int> m_vecXline;
	std::vector<int> m_vecI;
	std::vector<int> m_vecJ;
	std::vector<double> m_vecX;
	std::vector<double> m_vecY;
	std::vector<std::vector<float> > m_vecVecZ;

	// Inline/crossline range
	int m_nInlineMin;
	int m_nInlineMax;
	int m_nInlineInc;
	int m_nXlineMin;
	int m_nXlineMax;
	int m_nXlineInc;

	// Min and Max values for X, Y and Z
	double m_dXMin;
	double m_dXMax;
	double m_dYMin;
	double m_dYMax;
	std::vector<double> m_vecZMin;
	std::vector<double> m_vecZMax;

	std::vector<unsigned int> m_vecTemplateID;

	// The Type of the horizons (Z coordinates or attribute values) only for the horizon picks
	// -1: invalid value; 0: all Z; 1: all attributes; 2: one Z and attribute(s)
	int m_nHorizonType;
};

/**
* @class CXImport3DSurfaceManager in the file "rlimport3dsurfacemanager.h"
* @brief The class provides methods for importing 3-D surfaces
* 
* @author Yong Shu 
* @date 4/10/2014
*/	

class XDATA_EXPORT  CXImport3DSurfaceManager
{
public:
	enum DataFormat
	{
		e_H_Line, // Horizon, have inline/xline
		e_H_Line_XY, // Horizon, have line/xline, X/Y
		e_H_IJ_XY, // Horizon, have I/J, X/Y
		e_H_XY, // Horizon, have X/Y	
		e_H,  // Horizon, only have data
		e_S_Line_XY, // Surface, have inline/crossline, X/Y
		e_S_IJ_XY, // Surface, have I/J, X/Y
		e_S // Surface, only have data		
	};
public:
	///@brief Constructor and destructor
	CXImport3DSurfaceManager(const QString& strFileName, EImportFileType eFileType);
	~CXImport3DSurfaceManager();

	/**
	* @brief Verify the file according to the individual format
	* @param[in] listColumnNames and fInvalid only for the format of "Horizon Picks"
	*/
	bool VerifyFileFormat(const CXDelimiter& delimiter = CXDelimiter(), const QStringList& listColumnNames=QStringList(), int iFirstLineNum=0, int iLastLineNum=0, double fInvalid = M_FINVALID);
	
	void WipeStripNumber();

	///@brief Import data
	bool ImportData();	

	///@brief Guess UTM from the data of inline, crossline, x and y.
	bool GuessUTMTool(CXUTMTool* pUTM, bool bWithoutZone = true);

	///@brief Calculate the UTM from a regular grid.
	bool GetRegularUTMTool(CXUTMTool* pUTM, bool bWithoutZone = true); 	

	/**
	* @brief Convert the column data to surface
	* @param[in] pSurface : target surface
	* @param[in] pUTM : target UTM
	* @param[in] index : which horizon (can have multiple surfaces)
	* @param[in] nType : 2: inline/crossline; 1: only x/y; 0: no inline/crossline and no x/y
	*/
	void ConvertColumnDataToSurface(CX3DSurface* pSurface, CXUTMTool* pDataUTM, int index, int nType);

	///@brief Tell if there is data for inline, crossline, x, y, I and J
	void GetDataFlag(bool& bInline, bool& bXline, bool& bX, bool& bY, bool& bI, bool& bJ);

	///@brief Get the range for inline and crossline
	void GetLineRange(int& iInlineMin, int& iInlineMax, int& iInlineInc, int& iXlineMin, int& iXlineMax, int& iXlineInc);

	///@brief Copy parametes
	void CopyPara(CXImport3DSurfaceManager* pOther);

	///@brief Get the horizon type (Z or attribute horizons)
	int GetHorizonType() { return m_ImPara.m_nHorizonType; }

	///@brief Get min and max for x, y and z
	void GetXYZMinMax(int index, double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dzMax);

	///@brief Get the number of horizons
	int GetHorizonNum() { return m_ImPara.m_nHorizonCount; } 
	///@brief Get the name list for horizons
	QStringList GetHorizonListName() { return m_strListHorizonName; }
	///@brief Set the name for the specific horizon
	void SetHorizonName(int index, const QString& strName);

	///@brief Get the invalid data
	double GetInvalidData() { return m_ImPara.m_fInvalidData; }

	///@brief Get templates
	std::vector<unsigned int> GetVecTemplateID() {return m_ImPara.m_vecTemplateID;}

	///@brief Set unit conversion ratios
	void SetUnitConversionRatios(float fXRatio, float fYRatio, float fZRatio);
private:
	bool _VerifyHorizonPicks(const CXDelimiter& delimiter, const QStringList& listColumnNames, int iFirstLineNum, int iLastLineNum, double fInvalid);
	bool _VerifyZMapGridASCII();	
	
	// Import different surfaces
	bool _ImportGeneralColumnHorizonData();
	bool _ImportGeneralSurfaceData();

private:
	QString m_sFileName;
	EImportFileType m_eFileType; 
	QStringList m_strListHorizonName;

	int m_nHeadSize;
	bool m_bAbort;

private:
	// Parameter
	CXImportSurfacePara m_ImPara;

	QString m_strAllPotentialColumnName;

	CXDelimiter m_Delimiter;	
};


#endif // RLIMPORT3DSURFACEMANAGER_H
