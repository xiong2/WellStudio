#ifndef _CXDVCALCULATOR_H__
#define _CXDVCALCULATOR_H__

#include "xdataplus_global.h"
#include "xobjcalculator.h"

class CXSeismicDataVolume;
template<typename T> class CXRegularDataWriter;

/**
*@class		CXDVCalculator
*@brief		This class offer a calculator for seismic data volume.
*@author	Xiong Xiong
*@date		Dec, 2015
*/
class XDATAPLUS_EXPORT CXDVCalculator : public CXObjCalculator
{
public:
	CXDVCalculator(QUuid objID);

	virtual CXObject* Calculate(QString str, double& fVal);

protected:
	//	Process the input expression, find out all objects and replace them with key word.
	virtual QString _findOutObjects(QString);

	virtual void _updateData(unsigned int iLineIDX);

	QList<CXSeismicDataVolume *>	m_listDV;
	CXSeismicDataVolume*			m_pOutputDV;
	CXRegularDataWriter<float>*	m_pWriter;
	float *m_pFloatBuff;
};

#endif