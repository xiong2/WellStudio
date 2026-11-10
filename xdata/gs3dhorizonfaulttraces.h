#ifndef GS3DHORIZONFAULTTRACES_H
#define GS3DHORIZONFAULTTRACES_H

#include <vector>
#include <iostream>
#include <QPolygonF>
#include "xobject.h"
#include "xdata_global.h"
#include "gsfaulttrace.h"

/**
@class  GS3DHorizonFaultTraces provided in the file "gs3dhorizonfaulttraces.h"
@brief  The class provides for represent traces between horizon and fault surface.
@author pezy
@date   2018-05-24
@sa
*/
class XDATA_EXPORT GS3DHorizonFaultTraces : public CXObject
{
public:
	GS3DHorizonFaultTraces(const QString& name = "");
	~GS3DHorizonFaultTraces();	

	bool SerializeData(CXArchive& ar) override;
	QStringList GetDescription() override;
	QString GetTypeString() override;

	void AddTrace(const GSFaultTrace& trace);
	void DelTrace(int iIndex);
	int TraceCount() const;
	GSFaultTrace* GetTrace(int iIndex);
	void Reduce(double dTol, bool bFixNonGenerated = true);
	double Length();
	double ReversePercent();
	double ThrowStdDevPoint(double dStdDev);
	int Dip();

	std::vector<GSFaultTrace>& GetTraces();
	double MaxThrow() const;

	friend std::ostream& operator<<(std::ostream& os, const GS3DHorizonFaultTraces& faultTraces);

	int GetStatus()
	{
		return m_iStatus;
	}

	void SetStatus(int iStatus)
	{
		if(iStatus < 0 || iStatus > 4)
			return;

		m_iStatus = iStatus;
	}

	bool IsActive()
	{
		return m_bActive;
	}

	void SetActive(bool bActive)
	{
		m_bActive = bActive;
	}

private:
	void _SetSelfDimension() override;

private:
	//	0 ~ 4 means normal, ss(l), ss(r), reverse, unset.
	int		m_iStatus = 4;		

	//	Only active fault should be used.
	bool	m_bActive = true;

	std::vector<GSFaultTrace> m_vecTraces;
};

#endif // GS3DHORIZONFAULTTRACES_H
