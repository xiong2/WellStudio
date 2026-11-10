#ifndef _CXIMPORTRESERVOIRTHREAD_H__
#define _CXIMPORTRESERVOIRTHREAD_H__

#include "xdata_global.h"
#include "xbasethread.h"
#include <qtextstream.h>

class CXEclipseObject;
class CXGridModel;
class CXPropertyModel;

/**
*@brief		This class is a thread that scan .grdecl file to import a reservoir.
*@author	Xiong Xiong
*@date		Nov, 2014
*/
class XDATA_EXPORT CXImportReservoirThread: public CXBaseThread
{
public:
	 ///@brief Constructor
    CXImportReservoirThread(QString sFileName);

     ///@brief Destructor
	virtual ~CXImportReservoirThread();

	CXEclipseObject*			m_pEObj;
	CXGridModel*				m_pGridModel;
	QList<CXPropertyModel *>	m_listProps;
	double						m_dInvalid;

protected:
	///@brief Reimplementation of run()
	virtual void RunThread();

	QString				m_sFileName;

	bool _readPCoord(QTextStream&);							//	Read pillar coordinates.
	bool _readZCoord(QTextStream&);							//	Read Z coordinates.
	bool _readActCell(QTextStream&);						//	Read valid cell flag.
	bool _calcCellCoord();									//	Calculate each cells' coordinate.
	bool _readProperty(QString sPorpName, QTextStream&);	//	Read one property.
};

#endif