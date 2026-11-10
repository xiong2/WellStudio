#ifndef _CXOBJCALCULATOR_H__
#define _CXOBJCALCULATOR_H__

#include "xdata_global.h"
#include "xobject.h"

/**
*@class		CXObjCalculator
*@brief		This class offer a general calculator to CXObject.
*@author	Xiong Xiong
*@date		Oct, 2013
*/
class XDATA_EXPORT CXObjCalculator
{
public:
    CXObjCalculator(QUuid objID);

    virtual ~CXObjCalculator(){}

	///@brief	Calculate a complex expression.
	///@param[in]	str:	The input expression.
	///@param[out]  fVal:	A returned double value of the expression.
	///@return	The result object created by the calculation.
	virtual CXObject* Calculate(QString str, double& fVal);

	///@brief	Get the help tips of the calculator.
	QString GetHelpTips();

	void SetDegreeType(int nDegType)
	{
		m_nDegType = nDegType;
	}

	void SetOutputTemplate(QString sTemplateName)
	{
		m_sTemplateName = sTemplateName;
	}

protected:
	QUuid							m_objID;			//	The object the calculaotr works on (on which RBM popup.)
	QUuid							m_refObjID;			//	The object used to initialize the output object.

	unsigned int					m_iDataSize;		//	Size of each the object data.
	unsigned short					m_count;
	std::vector<double *>			m_vecPData;			//	Hold all interim data.
	QString							m_strNewObjName;
	QString							m_sTemplateName;	//	Name of output template.
	double							m_fInvalid;
	int								m_nDegType;

	bool							m_bObj;				//	Result must be an object?
	bool*							m_pBoolArray[20];	//	To store some tmp result through functions.

	bool*							m_pBValid;			//	To remember each value whether valid, length is m_iDataSize.

	//	pre-process the input string.
	bool _preProcess(QString& str);

	//	Parse the string and find out the variable.
	//	Return 0 means the result is a figure stored in d.
	//	Return 1 means the result is a log stored in pObj.
	// Return -1 means wrong expression
	short _findOutVar(QString str, short position, bool bBackWard, short& pos2, double& d, double*& pBuff);

	//	Calculate a simple expression.
	//	Return 0 means the result is a figure stored in d.
	//	Return 1 means the result is an object stored in pBuff.
	//	Return -1 means wrong expression
	short _simpleCal(QString& str, double& d, double *& pBuff);

	//	Calculate a if(...) expression.
	//	Return 1 means the result is an object stored in pBuff.
	//	Return -1 means wrong expression
	short _ifCal(QString& str, double *& pBuff);

	//	Process the condition of if(...And...Or...).
	//	The result is an array of boolean with the same size of the attribute points.
	bool* _processCondition(QString str);

	//	Process the multiple conditions without brackets.
	//	The result is an array of boolean with the same size of the attribute points.
	bool* _processMultipleCondition(QString str);

	//	Process the single condition without And/Or.
	//	The result is an array of boolean with the same size of the attribute points.
	bool* _processSingleCondition(QString str);

	//	Single compare the first argu with the second one, the third is the operator.
	bool _singleCompare(double left, double right, int oper);

	//	Find the inner most bracket string from the source string and calculate the value.
	bool _calInnerMostExp(QString& str);

	//	Applied the function represented by chFlag on the object.
	double* _funcOnAttribute(QChar chFlag, double *, double& factor);

	static bool _ObjectCompareByLengthDescend( CXObject *p1, CXObject *p2 );// sort object by object name string length descend
	static bool _StringCompareByLengthDescend( const QString&str1, const QString& str2 );// sort string by string length descend

	//	Get the common help tips for all kinds of calculator.
	QString _getBasicHelpTips();

	//---------	Below functions relevant to detail object type.------------------

	//	Process the input expression, find out all objects and replace them with key word.
	virtual QString _findOutObjects(QString);

	//	Generate the result object.
	virtual CXObject* _createResultObject(double *);

	//	Get the special help tips depend on a specific object.
	virtual QString _getSpecialHelpTips();
};

#endif