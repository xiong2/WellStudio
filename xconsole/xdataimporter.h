#ifndef _CXDATAIMPORTER_H__
#define	_CRLDATAIMPORTER_H__

#include "xconsole_global.h"

#include <qstringlist.h>
#include "xdef.h"

class CXObject;

///@brief	Used to offer a standard data importer API.
///@author	Xiong Xiong
///@date	Apr, 2013
///@see		
class XCONSOLE_EXPORT CXDataImporter
{
public:
	///	The 1st API to import files.
	bool ImportData(EImportFileType, CXObject* = NULL);

private:
	bool importWellASCIIHeaderFiles(QStringList);
	bool importWellASCIIPathFiles(QStringList);
	bool importWellLasDlisFiles(QStringList, bool bLAS, bool bNoTemplate = false);
	bool importWellWISFiles(QStringList);
	bool importWellXTFFiles(QStringList);
	bool importWellASCIILogFiles(QStringList);
	bool importWellCheckShotFiles(QStringList);
	bool importWellASCIITopsFiles(QStringList);
	bool importMicroSeismicFiles(QStringList, CXObject *);
	bool importPointsASCIIFiles(QStringList);
	bool importFaultSticksASCIIFiles(const QString& strNameFilter, const QStringList& strListFileName);
	bool import3DSurfaceFiles(const QString& strNameFilter, const QStringList& strListFileName);
	bool importSegyFile(const QString& strNameFilter, const QStringList& strListFileName);
	bool improt3DSegyFile(QStringList);
	bool improt2DPostStackSegyFile(QStringList);
	bool importReservoirFile(QStringList);
	bool importFABFile(QStringList);
};

#endif