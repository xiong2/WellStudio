#include "xprocess.h"
#include "xbasethread.h"

IKEProcess::IKEProcess (void) :
m_pThread (NULL)
, m_pParentObject (NULL)
, m_pPara (NULL)
{
}

IKEProcess::~IKEProcess (void)
{
	if (m_pThread != NULL)
	{
		delete m_pThread;
		m_pThread = NULL;		
	}
}

void IKEProcess::Recalculate(CXObject* pTargetObj, CXBaseParameter* pPara)
{
}

void IKEProcess::Calculate (CXObject* pTargetObj, std::vector<CXBaseParameter*> vecPara)
{
}

void IKEProcess::slotFinishedComputing (void)
{
}
