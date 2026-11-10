#ifndef XTHREADPROPMODINCISION_H
#define XTHREADPROPMODINCISION_H

#include "xbasethread.h"
#include "xalgorithm_global.h"
#include <vector>
#include <QMap>
#include <QPair>

/**
 * @class CXThreadModelIntersection provided in the file "rlthreadmodelintersection.h"
 * @brief The Class provides a thread to convert a trace file to a slice file
 * 
 * @author Pezy
 * @date 3/11/2015
 * @see 
 */

class CXParameterModelIntersection;
class CXGridModel;
class CXIntersectionGrid;

class XALGORITHM_EXPORT CXThreadModelIntersection : public CXBaseThread
{
public:
	CXThreadModelIntersection(CXGridModel *pModel, CXParameterModelIntersection *pPara);
	virtual ~CXThreadModelIntersection();

	const std::vector<CXIntersectionGrid *>& GetOutputIntersection() { return m_vecOutput; }

protected:
	/// Reimplementation of run()
	virtual void RunThread() override;

private:
	void _InitLock();
	void _CreateObj();
	bool _IncisedGrid(const std::vector<double>& vecX, const std::vector<double>& vecY);

	void _Indices2Lines(std::vector<int>::const_iterator, std::vector<int>::const_iterator, QSet<QPair<int, int> >&);
	bool _CheckIntersectionFaceClosure(std::vector<std::pair<unsigned, unsigned> >&, std::vector<unsigned>&);

	CXGridModel *m_pModel;
	CXParameterModelIntersection *m_pPara;

	QMap<unsigned char, QList<unsigned> >	m_mapTriangeStrips;
	QMap<unsigned char, QList<unsigned> >	m_mapLineStrips;

	// output (divided to at least two parts.)
	std::vector<CXIntersectionGrid *> m_vecOutput;

private:
	//progress bar
	qint64 m_nTotalStep, m_iCurrent;
};

#endif // RLTHREADPROPMODINCISION_H
