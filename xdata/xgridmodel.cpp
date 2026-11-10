#include <QFile>
#include "xgridcell.h"
#include "xgridmodel.h"
#include "xobjectfactory.h"
#include "xglobal.h"  

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXGridModel)
EXGridModel
END_REGISTER_OBJECT_TO_FACTORY(CXGridModel)

CXGridModel::CXGridModel()
{
}

CXGridModel::CXGridModel(unsigned int nI, unsigned int nJ, unsigned int nK, unsigned int nSegment)
{
	SetObjectType(EXGridModel);
	SetIconName("ResGeometryModel.png");

	m_nI			= nI;
	m_nJ			= nJ;
	m_nK			= nK;
	m_nValidCells	= 0;
	m_nSegment		= (unsigned char) nSegment;
}

CXGridModel::~CXGridModel()
{
	_freeMemory();
}

QStringList CXGridModel::GetDescription()
{
	QStringList strListDesc;
		
	GetValidCellNumber();
	strListDesc<<GetTr(" I 方向网格数目")<<QString::number(m_nI);
	strListDesc<<GetTr(" J 方向网格数目")<<QString::number(m_nJ);
	strListDesc<<GetTr(" K 方向网格数目")<<QString::number(m_nK);
	strListDesc<<GetTr("总网格数目")<<QString::number(m_nK * m_nI * m_nJ);
	strListDesc<<GetTr("有效网格数目")<<QString::number(m_nValidCells);
	strListDesc<<GetTr("有效网格比例（%）")<<QString::number(m_nValidCells * 100 / (m_nK * m_nI * m_nJ));

	return strListDesc;
}
unsigned int CXGridModel::GetValidCellNumber()
{
	if(m_nValidCells == 0)
	{
		if(m_listCells.size() == 0)
			LoadData();

		m_nValidCells = m_listCells.size();
	}

	return m_nValidCells;
}

QList<CXGridCell *>& CXGridModel::GetAllCells()
{
	if(m_listCells.size() == 0)
		LoadData();

	return m_listCells;
}

bool CXGridModel::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar<<m_nI;
		ar<<m_nJ;
		ar<<m_nK;
		ar<<m_nValidCells;
		ar<<m_nSegment;

		double dim[6];
		GetDimension(dim[0], dim[1], dim[2], dim[3], dim[4], dim[5]);
		for (int i=0; i<6; ++i)
			ar<<dim[i];
	}
	else
	{
		ar>>m_nI;
		ar>>m_nJ;
		ar>>m_nK;
		ar>>m_nValidCells;
		ar>>m_nSegment;

		double dim[6];
		for (int i=0; i<6; ++i)
			ar>>dim[i];
		_SetDimension(dim[0], dim[1], dim[2], dim[3], dim[4], dim[5]);
	}

	return true;
}

void CXGridModel::_WriteData()
{
	if(m_listCells.size() == 0)
		return;

	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return;

	//	Allocate continuous memory, copy data into the memtory, and write it into file.
	qint64 iCellSize = sizeof(CXGridCell);
	qint64 iBuffSize = m_listCells.size() * iCellSize;
	char *pBuff = new char[iBuffSize];

	int i = 0;
	foreach(CXGridCell *pCell, m_listCells)
	{
		memcpy(pBuff + i * iCellSize, pCell, iCellSize);
		i++;
	}

	//	Write a slice data into the file!
	qFile.write(pBuff, iBuffSize);

	delete []pBuff;
	qFile.close();
}

void CXGridModel::_ReadData()
{
	if(m_nValidCells == 0)
		return;

	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::ReadOnly))
		return;

	//	Free the memory used before.
	_freeMemory();

	//	Allocate continuous memory, copy data into the memtory, and write it into file.
	qint64 iCellSize = sizeof(CXGridCell);
	qint64 iBuffSize = m_nValidCells * iCellSize;
	char *pBuff = new char[iBuffSize];

	qFile.read((char *)pBuff, iBuffSize);

	for(int i = 0; i < m_nValidCells; i++)
	{
		CXGridCell *pCell = (CXGridCell *)(pBuff + iCellSize * i);
		m_listCells<<pCell;
	}

	qFile.close();
}

void CXGridModel::_freeMemory()
{
	if(m_listCells.size() > 1)
	{
		int iOffset = m_listCells[1] - m_listCells[0];
		if(iOffset > 1)
		{
			//	Not continuous memory.
			foreach(CXGridCell *pCell, m_listCells)
			{
				delete pCell;
			}
		}
		else
		{
			//	Continuous memory, delete the 1st element is OK.
			delete m_listCells[0];
		}
	}
	else if(m_listCells.size() == 1)
		delete m_listCells[0];

	m_listCells.clear();
}

void CXGridModel::SetDimension(double dXMin, double dXMax, double dYMin, double dYMax, double dZMin, double dZMax)
{
	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);

	if(m_nValidCells < m_listCells.size())
		m_nValidCells = m_listCells.size();
}

