#ifndef XPROCESS3TERMAVOINVERSION_H
#define XPROCESS3TERMAVOINVERSION_H


#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXSeismicDataVolume;

/**
* @class CXProcess3TermAVOInversion in the file "keprocess3termavoinversion.h"
* @brief The class provides a process to make AVO inversion
*
* @author Yong Shu
* @date 12/15/2015
* @see
*/
class XALGORITHM_EXPORT CXProcess3TermAVOInversion : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcess3TermAVOInversion();
	virtual ~CXProcess3TermAVOInversion();

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

private:
	std::vector<CXSeismicDataVolume*> m_vecDV;

};

#endif // KEPROCESS3TERMAVOINVERSION_H
