#include "xprogressbar.h"
#include <QCoreApplication>


CXProgressBar::CXProgressBar(const QString& strWindowName, const QString& strTaskName, qint64 nTotalNum)
	:QProgressDialog(strTaskName, "Abort", 0, 0)
{
	setWindowModality(Qt::WindowModal);
	setWindowTitle(strWindowName);

	m_nStep = qMax(1, static_cast<int>(nTotalNum / 100));
	m_iCurrent = 0;
	int nTotal = static_cast<int>(nTotalNum / m_nStep);

	setRange(0, nTotal);

	setMinimumDuration(1000);
	setMinimumWidth(400);
}

CXProgressBar::~CXProgressBar()
{

}

void CXProgressBar::SetValue(qint64 iValue)
{
	int iCurrent = static_cast<int>(iValue / m_nStep);
	if (iCurrent > m_iCurrent)
	{
		++m_iCurrent;
		setValue(m_iCurrent);
	}	
}

bool CXProgressBar::IsAborted()
{
	return this->wasCanceled();
}