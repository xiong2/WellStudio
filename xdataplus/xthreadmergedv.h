#pragma once

#include "xbasethread.h"
#include "xdataplus_global.h"
#include "xbaseparameter.h"

class XDATAPLUS_EXPORT CXParameterMergeDV : public CXBaseParameter
{
public:
	X_PROPERTY(QUuid, BaseDV);
	X_PROPERTY(QString, NewDVName);
	X_PROPERTY(std::vector<QUuid>, VecSubDV);
	X_PROPERTY(std::vector<float>, VecWeight);
};

class XDATAPLUS_EXPORT XThreadMergeDV : public CXBaseThread
{
public:
	XThreadMergeDV(CXParameterMergeDV *);

protected:
	virtual void RunThread() override;

private:
	void cal();

	CXParameterMergeDV*	m_pPara;
};