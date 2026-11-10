#include "xdlgrruger.h"
#include "xwidgetrccurve.h"
#include "xwidget3dsurface.h"
#include "xnummethod.h"
#include <cmath>
#include "xmathmacro.h"
#include "xfunctiontemplate.h"

CXDlgRruger::CXDlgRruger(QWidget *parent)
	: QDialog(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	m_ui.setupUi(this);
	_Init();
	_ConnectSignals();
}

CXDlgRruger::~CXDlgRruger()
{
	//delete m_pWidgetCurve;
	delete m_pWidget3DSurface;
}

void CXDlgRruger::slotRun()
{
	QList<int> oldKeys = m_mapPara.keys();

	_GetParameter();
	_GetRangePara();

	if (m_pWidgetCurve.isNull())
	{
		m_pWidgetCurve = new CXWidgetRCCurve(this);
		m_pWidgetCurve->setWindowTitle("AvAz");
		m_pWidgetCurve->show();
	}

	for (auto iter = m_mapPara.cbegin(); iter != m_mapPara.cend(); ++iter)
	{
		vector<double> vecAziX, vecIncX, vecAziLine, vecIncLine;
		vector<vector<double>> vecAziYs, vecIncYs;
		_GenerateDataForCurvesAlongAzi(iter.key(), vecAziX, vecAziLine, vecAziYs);
		_GenerateDataForCurvesAlongInc(iter.key(), vecIncX, vecIncLine, vecIncYs);

		if (vecAziX.empty() || vecIncX.empty() || vecAziLine.empty() || vecIncLine.empty())
			continue;

		m_pWidgetCurve->AddCurve(iter.key(), 0, vecAziX, vecAziLine, vecAziYs);
		m_pWidgetCurve->AddCurve(iter.key(), 1, vecIncX, vecIncLine, vecIncYs);
		m_pWidgetCurve->SetVisibility(iter.key(), true);
	}

	if (m_pWidget3DSurface.isNull())
	{
		m_pWidget3DSurface = new CXWidget3DSurface("3D-AvAz");
		m_pWidget3DSurface->show();
	}

	QList<int> listIndex = m_mapPara.keys();
	if (listIndex.isEmpty())
		return;

	for (int i = 0; i < listIndex.size(); ++i)
	{
		float* pData(nullptr);
		int m, n;
		_GenerataDataForSurface(listIndex[i], pData, m, n);
		if (!pData)
			continue;

		m_pWidget3DSurface->ADDOneSurface(listIndex[i], pData, m, n);
		delete[]pData;
	}

	for (int i = 0; i < listIndex.size(); ++i)
		oldKeys.removeAll(listIndex[i]);

	for (int i = 0; i < oldKeys.size(); ++i)
	{
		m_pWidget3DSurface->SetVisibility(oldKeys[i], false);
		m_pWidgetCurve->SetVisibility(oldKeys[i], false);
	}
}

void CXDlgRruger::slotUpdate(int, int)
{
	_GetParameter();
	_GetRangePara();

	auto pTable = dynamic_cast<QTableWidget*>(sender());
	int index = m_listTables.indexOf(pTable);

	if (index == -1)
		return;

	if (0 <= index && index < 3)
	{
		vector<double> vecAziX, vecIncX, vecAziLine, vecIncLine;
		vector<vector<double>> vecAziYs, vecIncYs;
		_GenerateDataForCurvesAlongAzi(index, vecAziX, vecAziLine, vecAziYs);
		_GenerateDataForCurvesAlongInc(index, vecIncX, vecIncLine, vecIncYs);

		if (!m_pWidgetCurve.isNull())
		{
			m_pWidgetCurve->AddCurve(index, 0, vecAziX, vecAziLine, vecAziYs);
			m_pWidgetCurve->AddCurve(index, 1, vecIncX, vecIncLine, vecIncYs);
		}

		float* pData(nullptr);
		int m, n;
		_GenerataDataForSurface(index, pData, m, n);
		if (!pData)
			return;

		if (!m_pWidget3DSurface.isNull())
		{
			m_pWidget3DSurface->Update(index, pData, m, n);
		}
		
		delete[]pData;
	}
	else
	{
		for (auto iter = m_mapPara.cbegin(); iter != m_mapPara.cend(); ++iter)
		{
			vector<double> vecAziX, vecIncX, vecAziLine, vecIncLine;
			vector<vector<double>> vecAziYs, vecIncYs;
			_GenerateDataForCurvesAlongAzi(iter.key(), vecAziX, vecAziLine, vecAziYs);
			_GenerateDataForCurvesAlongInc(iter.key(), vecIncX, vecIncLine, vecIncYs);

			if (vecAziX.empty() || vecIncX.empty() || vecAziLine.empty() || vecIncLine.empty())
				continue;

			if (!m_pWidgetCurve.isNull())
			{
				m_pWidgetCurve->AddCurve(iter.key(), 0, vecAziX, vecAziLine, vecAziYs);
				m_pWidgetCurve->AddCurve(iter.key(), 1, vecIncX, vecIncLine, vecIncYs);
				m_pWidgetCurve->SetVisibility(iter.key(), true);
			}
			
		}
	}
}

void CXDlgRruger::slotVisible(bool bVisible)
{
	auto pBox = dynamic_cast<QGroupBox*>(sender());
	int index = m_listBox.indexOf(pBox);

	if (index == -1)
		return;

	if (!m_pWidget3DSurface.isNull())
		m_pWidget3DSurface->SetVisibility(index, bVisible);

	if (!m_pWidgetCurve.isNull())
		m_pWidgetCurve->SetVisibility(index, bVisible);
}

void CXDlgRruger::slotDefaultSize()
{
	adjustSize();
}

void CXDlgRruger::_Init()
{
	m_ui.m_pBoxTable1->setVisible(false);
	m_ui.m_pBoxTable2->setVisible(false);
	m_ui.m_pBtnLess->setVisible(false);

	adjustSize();

	m_listTables << m_ui.m_pTable0 << m_ui.m_pTable1 << m_ui.m_pTable2 << m_ui.m_pTableAzimuth << m_ui.m_pTableIncident;
	m_listBox << m_ui.m_pBoxTable0 << m_ui.m_pBoxTable1 << m_ui.m_pBoxTable2;
}

void CXDlgRruger::_ConnectSignals()
{
	connect(m_ui.m_pBtnClose, &QPushButton::clicked, this, &CXDlgRruger::close);
	connect(m_ui.m_pBtnRun, &QPushButton::clicked, this, &CXDlgRruger::slotRun);
	connect(m_ui.m_pBoxTable0, &QGroupBox::toggled, this, &CXDlgRruger::slotVisible);
	connect(m_ui.m_pBoxTable1, &QGroupBox::toggled, this, &CXDlgRruger::slotVisible);
	connect(m_ui.m_pBoxTable2, &QGroupBox::toggled, this, &CXDlgRruger::slotVisible);
	connect(m_ui.m_pTable0, &QTableWidget::cellChanged, this, &CXDlgRruger::slotUpdate);
	connect(m_ui.m_pTable1, &QTableWidget::cellChanged, this, &CXDlgRruger::slotUpdate);
	connect(m_ui.m_pTable2, &QTableWidget::cellChanged, this, &CXDlgRruger::slotUpdate);
	connect(m_ui.m_pTableAzimuth, &QTableWidget::cellChanged, this, &CXDlgRruger::slotUpdate);
	connect(m_ui.m_pTableIncident, &QTableWidget::cellChanged, this, &CXDlgRruger::slotUpdate);
	connect(m_ui.m_pBtnLess, &QPushButton::clicked, this, &CXDlgRruger::slotDefaultSize);
}

void CXDlgRruger::_GetParameter()
{
	m_mapPara.clear();

	for (int i = 0; i != m_listBox.size(); ++i)
	{
		if (m_listBox.at(i)->isChecked())
		{
			vector<double> vecPara = _GetTableDataSet(m_listTables.at(i));
			if (!vecPara.empty())
				m_mapPara.insert(i, _GetTableDataSet(m_listTables.at(i)));
		}
	}
}

void CXDlgRruger::_GetRangePara()
{
	// azimuth
	m_rangeAzi = { m_ui.m_pTableAzimuth->item(0, 0)->text().toDouble(),
		m_ui.m_pTableAzimuth->item(0, 1)->text().toDouble(),
		m_ui.m_pTableAzimuth->item(0, 2)->text().toDouble(),
		m_ui.m_pTableAzimuth->item(1, 0)->text().toDouble(),
		m_ui.m_pTableAzimuth->item(1, 1)->text().toDouble(),
		m_ui.m_pTableAzimuth->item(1, 2)->text().toDouble() 
	};

	// Incident
	m_rangeInc = { m_ui.m_pTableIncident->item(1, 0)->text().toDouble(),
		m_ui.m_pTableIncident->item(1, 1)->text().toDouble(),
		m_ui.m_pTableIncident->item(1, 2)->text().toDouble(),
		m_ui.m_pTableIncident->item(0, 0)->text().toDouble(),
		m_ui.m_pTableIncident->item(0, 1)->text().toDouble(),
		m_ui.m_pTableIncident->item(0, 2)->text().toDouble()
	};
}

void CXDlgRruger::_GenerataDataForSurface(int iIndex, float *& pData, int & m, int & n)
{
	/*
	float xymin = -0.6;
	float xymax = 0.6;
	int nStepNum = 100;

	m = nStepNum;
	n = nStepNum;
	pData = new float[3 * m*n];

	float fdx = (xymax - xymin) / nStepNum;
	float fdy = fdx;

	std::vector<double> vecPara = m_mapPara.value(iIndex);
	double para[12];
	std::copy(vecPara.begin(), vecPara.end(), para);
	float x, y, theta, azi, rc;
	int index = 0;
	for (int ix = 0; ix < nStepNum; ++ix)
	{
		x = xymin + ix*fdx;
		for (int iy = 0; iy < nStepNum; ++iy)
		{
			y = xymin + iy*fdy;
			theta = sqrtf(SQR(x)+SQR(y))*M_DEG;
			azi = atan2(x, y)*M_DEG;

			rc = NXNumMethod::PP_coefficient2(para, theta, azi);
			pData[3 * index] = x;
			pData[3 * index+1] = y;
			pData[3 * index+2] = rc;
			++index;
		}
	}
	*/

	m = 60;
	n = 360;

	pData = new float[3 * m*n];

	std::vector<double> vecPara = m_mapPara.value(iIndex);
	double para[12];
	std::copy(vecPara.begin(), vecPara.end(), para);

	float theta, azi, rc;
	int index = 0;
	for (int i = 0; i < m; ++i)
	{
		theta = i;
		for (int j = 0; j < 360; ++j)
		{
			azi = j;
			rc = NXNumMethod::PP_coefficient2(para, theta, azi);

			pData[3 * index] = theta*M_RAD;
			pData[3 * index + 1] = azi*M_RAD;
			pData[3 * index + 2] = rc;
			++index;
		}
	}

	// polar
	if (!m_pWidget3DSurface.isNull())
	{
		m_pWidget3DSurface->SetPolar(true);
	}
}

void CXDlgRruger::_GenerateDataForCurvesAlongAzi(int iIndex, vector<double>& vecAzi, vector<double>& vecInc, vector<vector<double>>& vecRC)
{
	std::vector<double> vecPara = m_mapPara.value(iIndex);
	double para[12];
	std::copy(vecPara.cbegin(), vecPara.cend(), para);

	vecAzi.clear();
	for (double dAzi = m_rangeAzi.dAziStart; dAzi <= m_rangeAzi.dAziEnd; dAzi += m_rangeAzi.dAziInterval)
		vecAzi.push_back(dAzi);

	for (double dInc = m_rangeAzi.dIncStart; dInc <= m_rangeAzi.dIncEnd; dInc += m_rangeAzi.dIncInterval)
		vecInc.push_back(dInc);

	vecRC.resize(vecInc.size());
	for (int i = 0; i < vecRC.size(); ++i)
	{
		for (auto dAzi : vecAzi)
		{
			double rc = NXNumMethod::PP_coefficient2(para, vecInc[i], dAzi);
			vecRC[i].push_back(rc);
		}
	}
}

void CXDlgRruger::_GenerateDataForCurvesAlongInc(int iIndex, vector<double>& vecInc, vector<double>& vecAzi, vector<vector<double>>& vecRC)
{
	std::vector<double> vecPara = m_mapPara.value(iIndex);
	double para[12];
	std::copy(vecPara.cbegin(), vecPara.cend(), para);

	for (double dAzi = m_rangeInc.dAziStart; dAzi <= m_rangeInc.dAziEnd; dAzi += m_rangeInc.dAziInterval)
		vecAzi.push_back(dAzi);

	vecInc.clear();
	for (double dInc = m_rangeInc.dIncStart; dInc <= m_rangeInc.dIncEnd; dInc += m_rangeInc.dIncInterval)
		vecInc.push_back(dInc);

	vecRC.resize(vecAzi.size());
	for (int i = 0; i < vecRC.size(); ++i)
	{
		for (auto dInc : vecInc)
		{
			double rc = NXNumMethod::PP_coefficient2(para, dInc, vecAzi[i]);
			vecRC[i].push_back(rc);
		}
	}
}

std::vector<double> CXDlgRruger::_GetTableDataSet(QTableWidget * pTable)
{
	std::vector<double> vecPara;
	for (int i = 0; i != pTable->rowCount(); ++i)
	{
		for (int j = 0; j != pTable->columnCount(); ++j)
		{
			if (pTable->item(i, j) == nullptr)
				return vector<double>();

			vecPara.push_back(pTable->item(i, j)->text().toFloat());
		}
	}
	return vecPara;
}