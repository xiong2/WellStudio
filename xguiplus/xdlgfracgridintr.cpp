#include "xdlgfracgridintr.h"
#include "xfracturepatch.h"
#include "xglobal.h"
#include "xproject.h"
#include "xreservoirmodel.h"
#include "xgridmodel.h"
#include "xgridcell.h"
#include "xpropertymodel.h"
#include "xintersecthextri.h"
#include <iostream>

CXDlgFracGridIntr::CXDlgFracGridIntr(CXObject *pObj, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_pObj = dynamic_cast<CXFracturePatch *>(pObj);

	QStringList sListProp = m_pObj->GetProperties();
	ui.comboBoxProp->addItems(sListProp);

	QList<CXObject *> listObj = ::GetProject()->GetChildren(EXReservoirModel);
	QStringList sList;
	foreach(CXObject *pObj, listObj)
		sList << pObj->GetObjectName();

	ui.comboBoxGrid->addItems(sList);
}

CXDlgFracGridIntr::~CXDlgFracGridIntr()
{
}

void CXDlgFracGridIntr::accept()
{
	QStringList sListProp = m_pObj->GetProperties();
	unsigned int i, j, iFracDataSize, nProp = sListProp.size(), iPatchSize = (sListProp.size() + 12);
	double *pFracData = m_pObj->GetData(iFracDataSize);
	unsigned int nPatch = iFracDataSize / iPatchSize;

	QList<CXObject *> listObj = ::GetProject()->GetChildren(EXReservoirModel);
	CXObject *pRModel = listObj[ui.comboBoxGrid->currentIndex()];
	CXGridModel *pGrid = dynamic_cast<CXGridModel *>(pRModel->GetChildren(EXGridModel).at(0));
	if (!pGrid)
		return;
	QList<CXGridCell *>& listCells = pGrid->GetAllCells();
	unsigned int nCells = listCells.size();
	double *pBuff = new double[nCells];
	memset(pBuff, 0, sizeof(double) * nCells);

	qDebug() << "Total patches number: " << nPatch;
	int nPer = 0, nCent = nPatch / 100;
	for (i = 0; i < nPatch; i++)
	{
		Triangle tri;
		tri.v0 = { pFracData[i * iPatchSize + nProp], pFracData[i * iPatchSize + 1 + nProp], pFracData[i * iPatchSize + 2 + nProp] };
		tri.v1 = { pFracData[i * iPatchSize + 3 + nProp], pFracData[i * iPatchSize + 4 + nProp], pFracData[i * iPatchSize + 5 + nProp] };
		tri.v2 = { pFracData[i * iPatchSize + 6 + nProp], pFracData[i * iPatchSize + 7 + nProp], pFracData[i * iPatchSize + 8 + nProp] };

		double dX = XMAX(XMAX(XABS(tri.v0.x - tri.v1.x), XABS(tri.v1.x - tri.v2.x)), XABS(tri.v0.x - tri.v2.x));
		double dY = XMAX(XMAX(XABS(tri.v0.y - tri.v1.y), XABS(tri.v1.y - tri.v2.y)), XABS(tri.v0.y - tri.v2.y));
		double dZ = XMAX(XMAX(XABS(tri.v0.z - tri.v1.z), XABS(tri.v1.z - tri.v2.z)), XABS(tri.v0.z - tri.v2.z));
		double dS = XMAX(XMAX(dX, dY), dZ);
		dS *= 3;

		Triangle tri2;
		tri2.v0 = { pFracData[i * iPatchSize + nProp], pFracData[i * iPatchSize + 1 + nProp], pFracData[i * iPatchSize + 2 + nProp] };
		tri2.v1 = { pFracData[i * iPatchSize + 6 + nProp], pFracData[i * iPatchSize + 7 + nProp], pFracData[i * iPatchSize + 8 + nProp] };
		tri2.v2 = { pFracData[i * iPatchSize + 9 + nProp], pFracData[i * iPatchSize + 10 + nProp], pFracData[i * iPatchSize + 11 + nProp] };

		//int sum1 = 0, sum2 = 0;
		for (j = 0; j < nCells; j++)
		{
			//bool bTooFar = false;
			double *pVertex = listCells[j]->GetVertex();

			if (tooFar(tri, dS, pVertex[0], pVertex[1], pVertex[2]))
			{
				//bTooFar = true;
				continue;
			}
			//else
			//	sum1++;

			Hexahedron hex = 
			{
				Vec3{pVertex[0], pVertex[1], pVertex[2]},
				Vec3{pVertex[3], pVertex[4], pVertex[5]},
				Vec3{pVertex[6], pVertex[7], pVertex[8]},
				Vec3{pVertex[9], pVertex[10], pVertex[11]},
				Vec3{pVertex[12], pVertex[13], pVertex[14]},
				Vec3{pVertex[15], pVertex[16], pVertex[17]},
				Vec3{pVertex[18], pVertex[19], pVertex[20]},
				Vec3{pVertex[21], pVertex[22], pVertex[23]}
			};

			if (triangleIntersectsHexahedron(tri, hex) || triangleIntersectsHexahedron(tri2, hex))
			{
				pBuff[j] = pFracData[i * iPatchSize + ui.comboBoxProp->currentIndex()];

				//sum2++;
				//if (bTooFar)
				//	qDebug() << "Wrong!";
			}
		}

		//qDebug() << "sum1 is " << sum1 << ", sum2 is " << sum2;
		if (nCent > 0 && i / nCent != nPer)
		{
			nPer++;
			qDebug() << "Finished " << nPer << "%";
		}
	}

	QString sName = pRModel->GetUnallocatedName(sListProp[ui.comboBoxProp->currentIndex()]);
	CXPropertyModel* pPropMod = new CXPropertyModel(sName);
	pPropMod->ResetData(nCells, pBuff);
	listObj[ui.comboBoxGrid->currentIndex()]->AddChild(pPropMod);
	::AddObjectEvent(pRModel);

	QDialog::accept();
}