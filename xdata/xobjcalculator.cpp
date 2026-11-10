#include <QMessageBox>
#include <cmath>
#include "xmathmacro.h"
#include "xobjcalculator.h"
#include "xwell.h"
#include "xwellcurve.h"
#include "x3dsurface.h"
#include "x3dhorizon.h"
#include "xutmtool.h"
#include "xglobal.h"
#include "xtemplate.h"

CXObjCalculator::CXObjCalculator(QUuid objID)
{
	m_objID			= objID;
	m_refObjID		= QUuid();
	m_bObj			= false;
	m_fInvalid		= g_dInvalidData;
	m_iDataSize		= 0;
	m_count			= 65;
	m_strNewObjName = "New Object";
	m_sTemplateName	= "GENERAL";
	m_nDegType		= 0;

	for(int i = 0; i < 20; i++) 
		m_pBoolArray[i] = NULL;
}

//	pre-process the input string.
bool CXObjCalculator::_preProcess(QString& str)
{
	int i, pos, cur;

	//	Replace "else_if" by "el_if" so it's easy to locate the last else.
	str.replace("else_if", "el_f", Qt::CaseInsensitive);
	str.replace("else if", "el_f", Qt::CaseInsensitive);

	//	Repalce "if", "IF" by "If"
	str.replace("if(", "If(", Qt::CaseInsensitive);
	str.replace("if (", "If(", Qt::CaseInsensitive);

	//	Find out the "=" first.
	cur = str.indexOf("If(");
	if(cur == -1) cur = 10000;
	pos = str.indexOf("=");
	m_bObj = false;
	if(pos != -1 && pos < cur)
	{
		m_bObj = true;
		m_strNewObjName = str.left(pos);
		str = str.right(str.length()-pos-1);
	}

	//	Process the object.
	str = _findOutObjects(str);
	if(str == "XXX")
		return false;

	//	To deal all rand or randn
	//while(str.indexOf("Rand") != -1)
	//{
	//	short iPos = str.indexOf("Rand");
	//	short iLen = 4;
	//	bool bUniform = true;
	//	if(str.indexOf("Randn") == iPos)
	//	{
	//		bUniform = false;
	//		iLen = 5;
	//	}

	//	CGmRandomNumGenerator random(bUniform);

	//	QString tmpStr;
	//	if(!m_bObj)
	//	{
	//		//	The result is not an object, so only one figure is enough.
	//		tmpStr = QString::number(random.GetValue());
	//		str.replace(iPos, iLen, tmpStr);
	//	}
	//	else
	//	{
	//		//	The result is an object, so repalce it by an array of random value.
	//		double *pBuff = new double[m_iDataSize];
	//		for(i = 0; i < m_iDataSize; i++)
	//			pBuff[i] = random.GetValue();

	//		//	Save the array.
	//		m_vecPData.push_back(pBuff);

	//		tmpStr = "$";
	//		tmpStr += QChar(m_count);
	//		tmpStr += "$";
	//		str.replace(iPos, iLen, tmpStr);
	//		m_count++;
	//	}
	//}

	//	Eliminate all space.
	str = str.simplified();

	//	Are the brackets OK?
	pos = str.count("(");
	cur = str.count(")");
	if(pos != cur) 
		return false;

	pos = str.count("{");
	cur = str.count("}");
	if(pos != cur) 
		return false;

	//	Process the "-" then.
	pos = 1;
	while((cur = str.indexOf("-", pos)) != -1)
	{
		QString tmpStr = str.mid(cur-1, 1);
		if(tmpStr != "(") 
			str.replace(cur, 1, "~");
		pos = cur+1;
	}

	//	We use '=' rather than '=='.
	str.replace("==", "=");

	//	Process the functions.
	QStringList funcList, symbolList;
	funcList <<"Actan"<<"Ctan"<<"Asin"<<"ACos"<<"Atan"<< "Abs" << "Sin" << "Cos" << "Tan" << "Log" << "ln" << "Exp" << "Round" << "Sqrt" << "Int" << "Pow"<<"Std"<<"Min"<<"Max"<<"Mean"<<"Sum"<<"Num";
	symbolList <<"P#"<<"L#"<<"M#"<<"N#"<<"O#"<< "A#" << "B#" << "C#" << "D#" << "E#" << "F#" << "G#" << "H#" << "I#" << "J#" << "K#"<<"R#"<<"S#"<<"T#"<<"U#"<<"V#"<<"W#";

	for(i = 0; i < funcList.size(); i++)
	{
		str.replace(funcList.at(i), symbolList.at(i), Qt::CaseInsensitive);
	}

	//	Process N/A.
	str = str.replace("Inv", "("+QString::number(m_fInvalid)+")");

	str = str.remove(" ");

	return true;
}

//	Parse the string and indexOf out the variable.
//	Return 0 means the result is a figure stored in d.
//	Return 1 means the result is an object stored in pObject.
// Return -1 means wrong expression
short CXObjCalculator::_findOutVar(QString str, short position, bool bBackWard, short& pos2, double& d, double*& pBuff)
{
	short p1, p2, p3, p4;
	QString strVar;
	bool bOK;

	if(bBackWard)
	{
		if(position <= 0) return -1;

		//	an object?
		if(str.at(position-1) == '$')
		{
			QChar ch = str.at(position-2);
			unsigned short us = ch.unicode();
			us -= 65;
			pBuff = m_vecPData.at(us);
			pos2 = position-3;
			return 1;
		}

		//	A figure.
		p1 = str.lastIndexOf("+", position-1);
		p2 = str.lastIndexOf("~", position-1);
		p3 = str.lastIndexOf("*", position-1);
		p4 = str.lastIndexOf("/", position-1);

		p1 = p1>p2?p1:p2;
		p1 = p1>p3?p1:p3;
		p1 = p1>p4?p1:p4;

		if(p1 >= position) return -1;
		pos2 = p1+1;
		strVar = str.mid(p1+1, position-p1-1);
		d = strVar.toFloat(&bOK);
		if(!bOK) return -1;
		
		return 0;
	}
	else
	{
		//	an object?
		if(str.at(position+1) == '$')
		{
			QChar ch = str.at(position+2);
			unsigned short us = ch.unicode();
			us -= 65;
			pBuff = m_vecPData.at(us);
			pos2 = position+3;
			return 1;
		}

		//	A figure.
		p1 = str.indexOf("+", position+1);
		p2 = str.indexOf("~", position+1);
		p3 = str.indexOf("*", position+1);
		p4 = str.indexOf("/", position+1);

		short len = str.length();
		p1 = p1==(-1)?len:p1;
		p2 = p2==(-1)?len:p2;
		p3 = p3==(-1)?len:p3;
		p4 = p4==(-1)?len:p4;

		p1 = p1<p2?p1:p2;
		p1 = p1<p3?p1:p3;
		p1 = p1<p4?p1:p4;

		pos2 = p1 -1;
		strVar = str.mid(position+1, p1-position-1);
		d = strVar.toFloat(&bOK);
		if(!bOK) return -1;
		
		return 0;
	}
}

//	Calculate a "if(...)" expression.
//	Return 1 means the result is a object and data stored in pBuff.
// Return -1 means wrong expression
short CXObjCalculator::_ifCal(QString& str, double *& pBuff)
{
	//	Should have object involved.
	if(m_vecPData.size() <= 0) return -1;

	short s;
	int i, j;
	double res;

	//	We use the number of "{" to find the number of cases.
	unsigned short numCases = str.count("{");

	//	At lease if(){}else{} so the number must greater than 1.
	if(numCases <= 1)
		return -1;

	//	Buff to save the tmp result.
	bool **pBoolArray = new bool*[numCases - 1];
	double**pFloatResult = new double*[numCases];
	for(i = 0; i < numCases; i++)
		pFloatResult[i] = NULL;

	//	For convenient.
	str.replace("If", "el_f");

	//	Process each condition.
	int pos1, pos2, cur = 0;
	for(i = 0; i < numCases - 1; i++)
	{
		pBoolArray[i] = NULL;
		pos1 = str.indexOf("el_f", cur);
		pos2 = str.indexOf("{", pos1);

		pBoolArray[i] = _processCondition(str.mid(pos1+5, pos2 - pos1 - 6));
		if(!pBoolArray[i])
		{
			for(j = 0; j < i; j++)
				delete []pBoolArray[j];

			delete []pBoolArray;
			delete []pFloatResult;

			return -1;
		}

		cur = pos2+1;
	}

	//	Then the cases.
    res = -999.;
	cur = 0;
	QList<double *> listFBuff;
	for(i = 0; i < numCases; i++)
	{
		pos1 = str.indexOf("{", cur);
		pos2 = str.indexOf("}", pos1);
		
		QString strVal = str.mid(pos1+1, pos2-pos1-1);
		int loopTime = 0;
		while(_calInnerMostExp(strVal))
		{
			//	To avoid dead loop
			if(loopTime > 100) 
				return -1;
			loopTime++;
		}

		s = _simpleCal(strVal, res, pFloatResult[i]);

		if(s == 0)
		{
			//	It means the 'if' part is a constant, we should create the buff and fill it with this constant.
			pFloatResult[i] = new double[m_iDataSize];
			for(j = 0; j < m_iDataSize; j++)
				pFloatResult[i][j] = res;
			listFBuff.append(pFloatResult[i]);
		}
		if(s == -1)
		{
			for(j = 0; j < i; j++)
			{
				delete []pBoolArray[j];
			}

			while(!listFBuff.empty())
			{
				double *pFirstBuff = listFBuff.takeFirst();
                delete[] pFirstBuff;
			}

			delete []pBoolArray;
			delete []pFloatResult;

			return -1;
		}

		cur = pos2 + 1;
	}

	//	Now combine the result!
	pBuff = new double[m_iDataSize];
	for(i = 0; i < m_iDataSize; i++)
	{
		pBuff[i] = pFloatResult[numCases-1][i];
		for(j = 0; j < numCases - 1; j++)
		{
			if(pBoolArray[j][i])
			{
				pBuff[i] = pFloatResult[j][i];
				break;
			}
		}
	}

	m_vecPData.push_back(pBuff);

	str = "$";
	str += QChar(m_count);
	str += "$";
	m_count++;

	for(i = 0; i < numCases - 1; i++)
	{
		delete []pBoolArray[i];
	}

	while(!listFBuff.empty())
	{
		double *pFirstBuff = listFBuff.takeFirst();
        delete[] pFirstBuff;
	}

	delete []pBoolArray;
	delete []pFloatResult;

	return 1;
}

//	Process the condition of if(...And...Or...).
//	The result is an array of boolean with the same size of the object.
bool* CXObjCalculator::_processCondition(QString str)
{
	int pos, pos1, pos2;

	int i, ind = 0;

	str.replace("And", "Ad");
	str.replace("&&", "Ad");
	str.replace("||", "Or");

	//	Process the brackets.
	while(1)
	{
		pos1 = str.lastIndexOf("Ad(");
		pos2 = str.lastIndexOf("Or(");
		pos = pos1>pos2?pos1:pos2;

		//	No brackets yet.
		if(pos == -1) break;

		//	To find out the right bracket.
		int tcount = 1;
		int len = str.length();
		for(i = pos+3; i < len; i++)
		{
			if(str[i] == '(') tcount++;
			if(str[i] == ')') tcount--;
			if(tcount == 0) break;
		}

		//	Something wrong.
		if(i >= len) 
			return NULL;

		QString tmpstr = str.mid(pos+3, i-pos-3);

		m_pBoolArray[ind] = _processMultipleCondition(tmpstr);
		QString sss = "@"+QString::number(ind);
		str.replace(pos+2, i-pos-1, sss);
		ind++;
	}
	
	//	No need to begin with a bracket.
	if(str[0] == '(')
	{
		pos = 1;
		for(i = 1; i < str.length(); i++)
		{
			if(str[i] == ')') pos--;
			if(str[i] == '(') pos++;
			if(pos == 0) break;
		}

		if(i >= str.length())
		{
			//	Something wrong
			return NULL;
		}

		str.remove(i, 1);
		str.remove(0, 1);
	}

	return _processMultipleCondition(str);
}

//	Process the multiple conditions without brackets.
//	The result is an array of boolean with the same size of the object.
bool* CXObjCalculator::_processMultipleCondition(QString str)
{
	bool* pBool;
	bool bAnd;

	int pos, pos1, pos2;
	pos1 = str.indexOf("Ad");
	if(pos1 == -1) 
		pos1 = 10000;
	pos2 = str.indexOf("Or");
	if(pos2 == -1) 
		pos2 = 10000;

	if(pos1 > pos2)
	{
		pos = pos2;
		bAnd = false;
	}
	else
	{
		pos = pos1;
		bAnd = true;
	}

	//	No 'Ad' or 'Or' at all.
	if(pos == 10000) 
		return _processSingleCondition(str);

	QString tmpstr = str.left(pos);
	pBool = _processSingleCondition(tmpstr);
	if(!pBool) 
		return NULL;

	str = str.right(str.length()-pos-2);
	while(1)
	{
		pos1 = str.indexOf("Ad");
		if(pos1 == -1) 
			pos1 = 10000;
		pos2 = str.indexOf("Or");
		if(pos2 == -1) 
			pos2 = 10000;
		pos = pos1>pos2?pos2:pos1;

		if(pos == 10000) 
			tmpstr = str;
		else 
			tmpstr = str.left(pos);

		bool *pTmpBool = _processSingleCondition(tmpstr);
		if(!pTmpBool)
		{
			//	Something wrong.
			delete[] pBool;
			return NULL;
		}

		//	Combine the result.
		if(bAnd)
			for(int i = 0; i < m_iDataSize; i++) 
				pBool[i] &= pTmpBool[i];
		else
			for(int i = 0; i < m_iDataSize; i++) 
				pBool[i] |= pTmpBool[i];
		
		//	Free the memory.
		delete[] pTmpBool;

		if(pos == 10000)  
			return pBool;
		bAnd = pos1>pos2?false:true;
		str = str.right(str.length()-pos-2);
	}
}

//	Process the single condition without And/Or.
//	The result is an array of boolean with the same size of the object.
bool* CXObjCalculator::_processSingleCondition(QString str)
{
	bool* pBool = NULL;
	QString leftStr, rightStr;
	int pos, oper(0);

	pos = str.indexOf("@");
	if(pos != -1)
	{
		QString rr = str.mid(pos+1);
		pos = rr.toInt();
		if(pos >= 20 || pos < 0) return NULL;
		return m_pBoolArray[pos];
	}

	//	Let's find the oper now.
	if(str.indexOf("<=") != -1)
	{
		pos = str.indexOf("<=");
		oper = 0;
		leftStr = str.left(pos);
		rightStr = str.right(str.length()-pos-2);
	}
	else if(str.indexOf(">=") != -1)
	{
		pos = str.indexOf(">=");
		oper = 1;
		leftStr = str.left(pos);
		rightStr = str.right(str.length()-pos-2);
	}
	else if(str.indexOf("<>") != -1)
	{
		pos = str.indexOf("<>");
		oper = 2;
		leftStr = str.left(pos);
		rightStr = str.right(str.length()-pos-2);
	}
	else if(str.indexOf("<") != -1)
	{
		pos = str.indexOf("<");
		oper = 3;
		leftStr = str.left(pos);
		rightStr = str.right(str.length()-pos-1);
	}
	else if(str.indexOf(">") != -1)
	{
		pos = str.indexOf(">");
		oper = 4;
		leftStr = str.left(pos);
		rightStr = str.right(str.length()-pos-1);
	}
	else if(str.indexOf("=") != -1)
	{
		pos = str.indexOf("=");
		oper = 5;
		leftStr = str.left(pos);
		rightStr = str.right(str.length()-pos-1);
	}

	//	The left part.
	int loopTime = 0;
	while(_calInnerMostExp(leftStr))
	{
		//	To avoid dead loop
		if(loopTime > 100) 
			return pBool;
		loopTime++;
	}

	double resl;
	double *pLeftSur = NULL;
	short sl = _simpleCal(leftStr, resl, pLeftSur);
	if(sl == -1) 
		return pBool;

	//	The right part.
	loopTime = 0;
	while(_calInnerMostExp(rightStr))
	{
		//	To avoid dead loop
		if(loopTime > 100) 
			return pBool;
		loopTime++;
	}

	double resr;
	double *pRightSur = NULL;
	short sr = _simpleCal(rightStr, resr, pRightSur);
	if(sr == -1) 
		return pBool;

	//	Now do the comparision.  First at least there's a object involved.
	if(sl == 0 && sr == 0) 
		return pBool;
	else 
	{
		double ll, rr;
		pBool = new bool[m_iDataSize];

		if(sl == 0)
		{
			//	Left is double, that means right is a object.
			for(int i = 0; i < m_iDataSize; i++)
			{
				rr = pRightSur[i];
				if( rr == m_fInvalid) 
					pBool[i] = false;
				else 
					pBool[i] = _singleCompare(resl, rr, oper);
			}
		}
		else if(sr == 0)
		{
			for(int i = 0; i < m_iDataSize; i++)
			{
				ll = pLeftSur[i];
				if(ll == m_fInvalid) 
					pBool[i] = false;
				else 
					pBool[i] = _singleCompare(ll, resr, oper);
			}
		}
		else
		{	
			//	Both are attributes.
			for(int i = 0; i < m_iDataSize; i++)
			{
				ll = pLeftSur[i];
				rr = pRightSur[i];
				if(ll == m_fInvalid || rr == m_fInvalid) 
					pBool[i] = false;
				else 
					pBool[i] = _singleCompare(ll, rr, oper);
			}
		}
	}

	return pBool;
}

//	Single compare the first argu with the second one, the third is the operator.
bool CXObjCalculator::_singleCompare(double left, double right, int oper)
{
	switch(oper)
	{
	case 0:
		return left <= right;
	case 1:
		return left >= right;
	case 2:
		return fabs(left-right) > 0.1;
	case 3:
		return left < right;
	case 4:
		return left > right;
	case 5:
		return fabs(left-right) < 0.1;
	default:
		return false;
	}
}

//	Calculate a simple expression.
//	Return 0 means the result is a figure stored in d.
//	Return 1 means the result is an object stored in pObject.
// Return -1 means wrong expression
short CXObjCalculator::_simpleCal(QString& str, double &dou, double *& pBuff)
{
	double lvar, rvar;
	QString strVar1, strVar2;
	bool bOK;
	short s1 = 2, s2 = 2;
	double *pObject1 = NULL, *pObject2 = NULL;

	//	Let's process * and / first.
	short lb, rb;
	short d = str.indexOf("/");
	short m = str.indexOf("*");
	if(d == -1) d = 999;
	if(m == -1) m = 999;

	while(d != 999 || m != 999)
	{
		if(d < m)
		{
			s1 = _findOutVar(str, d, true, lb, lvar, pObject1);
			s2 = _findOutVar(str, d, false, rb, rvar, pObject2);

			if(s1 == -1 || s2 == -1) 
				return -1;
			if(s1 == 0 && s2 == 0)
			{
				//	both are figures.
				if(rvar == 0.)
				{
					return -1;
				}

				if(lvar == m_fInvalid || rvar == m_fInvalid)
					dou = m_fInvalid;
				else
					dou = lvar/rvar;
				strVar1 = QString::number(dou, 'f');
				str.replace(lb, rb-lb+1, strVar1);
			}
			else
			{
				//	at least one variable is an object.
				pBuff = new double[m_iDataSize];

				if(s1 == 0)
				{
					//	left is figure, right is object
					for(int i = 0; i < m_iDataSize; i++)
					{
						if(qAbs(pObject2[i]) > 0.000001 && pObject2[i] != m_fInvalid && lvar != m_fInvalid)
							pBuff[i] = lvar/pObject2[i];
						else
							pBuff[i] = m_fInvalid;
					}
				}
				else if(s2 == 0)
				{
					//	left is object, right is figure
					for(int i = 0; i < m_iDataSize; i++)
					{
						if(pObject1[i] != m_fInvalid && rvar != m_fInvalid && rvar != 0)
							pBuff[i] = pObject1[i]/rvar;
						else
							pBuff[i] = m_fInvalid;
					}
				}
				else
				{
					//	both are attributes
					for(int i = 0; i < m_iDataSize; i++)
					{
						if(pObject1[i] != m_fInvalid && pObject2[i] != m_fInvalid && pObject2[i] != 0)
							pBuff[i] = pObject1[i]/pObject2[i];
						else
							pBuff[i] = m_fInvalid;
					}
				}

				m_vecPData.push_back(pBuff);

				QString tmpStr = "$";
				tmpStr += QChar(m_count);
				tmpStr += "$";
				str.replace(lb, rb-lb+1,tmpStr);
				m_count++;
			}

			d = str.indexOf("/");
			m = str.indexOf("*");
			if(d == -1) d = 999;
			if(m == -1) m = 999;
		}
		else
		{
			s1 = _findOutVar(str, m, true, lb, lvar, pObject1);
			s2 = _findOutVar(str, m, false, rb, rvar, pObject2);

			if(s1 == -1 || s2 == -1) 
				return -1;
			if(s1 == 0 && s2 == 0)
			{
				//	both are figures.
				if(lvar == m_fInvalid || rvar == m_fInvalid)
					dou = m_fInvalid;
				else
					dou = lvar*rvar;
				strVar1 = QString::number(dou, 'f');
				str.replace(lb, rb-lb+1, strVar1);
			}
			else
			{
				//	at least one variable is a object.
				pBuff = new double[m_iDataSize];

				if(s1 == 0)
				{
					//	left is figure, right is object
					for(int i = 0; i < m_iDataSize; i++)
					{
						if(pObject2[i] != m_fInvalid && lvar != m_fInvalid)
							pBuff[i] = lvar * pObject2[i];
						else
							pBuff[i] = m_fInvalid;
					}
				}
				else if(s2 == 0)
				{
					//	left is object, right is figure
					for(int i = 0; i < m_iDataSize; i++)
					{
						if(pObject1[i] != m_fInvalid && rvar != m_fInvalid)
							pBuff[i] = rvar * pObject1[i];
						else
							pBuff[i] = m_fInvalid;
					}
				}
				else
				{
					//	both are logs
					for(int i = 0; i < m_iDataSize; i++)
					{
						if(pObject1[i] != m_fInvalid && pObject2[i] != m_fInvalid)
							pBuff[i] = pObject1[i] * pObject2[i];
						else
							pBuff[i] = m_fInvalid;
					}
				}

				m_vecPData.push_back(pBuff);

				QString tmpStr = "$";
				tmpStr += QChar(m_count);
				tmpStr += "$";
				str.replace(lb, rb-lb+1,tmpStr);
				m_count++;
			}

			d = str.indexOf("/");
			m = str.indexOf("*");
			if(d == -1) d = 999;
			if(m == -1) m = 999;
		}
	}

	//	Now process + and -
	d = str.indexOf("~");
	m = str.indexOf("+");
	if(d == -1 || d == 0) d = 999;
	if(m == -1) m = 999;

	while(d != 999 || m != 999)
	{
		if(d < m)
		{
			s1 = _findOutVar(str, d, true, lb, lvar, pObject1);
			s2 = _findOutVar(str, d, false, rb, rvar, pObject2);

			if(s1 == -1 || s2 == -1) 
				return -1;

			if(s1 == 0 && s2 == 0)
			{
				//	both are figures.
				if(lvar == m_fInvalid || rvar == m_fInvalid)
					dou = m_fInvalid;
				else
					dou = lvar-rvar;
				strVar1 = QString::number(dou, 'f');
				str.replace(lb, rb-lb+1, strVar1);
			}
			else
			{
				//	at least one variable is a object.
				pBuff = new double[m_iDataSize];

				if(s1 == 0)
				{
					//	left is figure, right is object
					for(int i = 0; i < m_iDataSize; i++)
					{
						if(pObject2[i] != m_fInvalid && lvar != m_fInvalid)
							pBuff[i] = lvar - pObject2[i];
						else
							pBuff[i] = m_fInvalid;
					}
				}
				else if(s2 == 0)
				{
					//	left is object, right is figure
					for(int i = 0; i < m_iDataSize; i++)
					{
						if(pObject1[i] != m_fInvalid && rvar != m_fInvalid)
							pBuff[i] = pObject1[i] - rvar;
						else
							pBuff[i] = m_fInvalid;
					}
				}
				else
				{
					//	both are logs
					for(int i = 0; i < m_iDataSize; i++)
					{
						if(pObject1[i] != m_fInvalid && pObject2[i] != m_fInvalid)
							pBuff[i] = pObject1[i] - pObject2[i];
						else
							pBuff[i] = m_fInvalid;
					}
				}

				m_vecPData.push_back(pBuff);

				QString tmpStr = "$";
				tmpStr += QChar(m_count);
				tmpStr += "$";
				str.replace(lb, rb-lb+1,tmpStr);
				m_count++;
			}

			d = str.indexOf("~");
			m = str.indexOf("+");
			if(d == -1) d = 999;
			if(m == -1) m = 999;
		}
		else
		{
			s1 = _findOutVar(str, m, true, lb, lvar, pObject1);
			s2 = _findOutVar(str, m, false, rb, rvar, pObject2);

			if(s1 == -1 || s2 == -1) 
				return -1;

			if(s1 == 0 && s2 == 0)
			{
				//	both are figures.
				if(lvar == m_fInvalid || rvar == m_fInvalid)
					dou = m_fInvalid;
				else
					dou = lvar+rvar;
				strVar1 = QString::number(dou, 'f');
				str.replace(lb, rb-lb+1, strVar1);
			}
			else
			{
				//	at least one variable is a object.
				pBuff = new double[m_iDataSize];

				if(s1 == 0)
				{
					//	left is figure, right is object
					for(int i = 0; i < m_iDataSize; i++)
					{
						if(pObject2[i] != m_fInvalid && lvar != m_fInvalid)
							pBuff[i] = lvar + pObject2[i];
						else
							pBuff[i] = m_fInvalid;
					}
				}
				else if(s2 == 0)
				{
					//	left is object, right is figure
					for(int i = 0; i < m_iDataSize; i++)
					{
						if(pObject1[i] != m_fInvalid && rvar != m_fInvalid)
							pBuff[i] = pObject1[i] + rvar;
						else
							pBuff[i] = m_fInvalid;
					}
				}
				else
				{
					//	both are logs
					for(int i = 0; i < m_iDataSize; i++)
					{
						if(pObject1[i] != m_fInvalid && pObject2[i] != m_fInvalid)
							pBuff[i] = pObject1[i] + pObject2[i];
						else
							pBuff[i] = m_fInvalid;
					}
				}

				m_vecPData.push_back(pBuff);

				QString tmpStr = "$";
				tmpStr += QChar(m_count);
				tmpStr += "$";
				str.replace(lb, rb-lb+1,tmpStr);
				m_count++;
			}

			d = str.indexOf("~");
			m = str.indexOf("+");
			if(d == -1) d = 999;
			if(m == -1) m = 999;
		}
	}
	
	if(s1 == 2 && s2 == 2)
	{
		//	No +-*/ operator at all.
		int pos = str.count("$");
		if(pos > 2)
		{
			return -1;
		}

		//	Since no +-*/, only $X$.
		if(pos > 0 && (str.indexOf('$') != 0 || str.lastIndexOf('$') < str.length() - 1))
			return -1;

		pos = str.indexOf('$');
		if(pos != -1)
		{
			QChar ch = str.at(pos+1);
			unsigned short us = ch.unicode();
			us -= 65;
			pBuff = m_vecPData.at(us);

			return 1;
		}

		str.replace("~", "-");
		dou = str.toFloat(&bOK);
		if(!bOK) 
			return -1;

		return 0;
	}
		
	return s1>s2?s1:s2;
}

//	indexOf the inner most bracket string from the source string and calculate the value.
bool CXObjCalculator::_calInnerMostExp(QString& str)
{
	short left = str.lastIndexOf("(");
	short right = str.indexOf(")", left);
	if(left < 0 || right < 0 || left >= right)
	{
		return false;
	}
	
	QString resStr = str.mid(left+1, right-left-1);
	QString tmpStr;
	int i;
	double res, rightRes(0);
	double *pObject = NULL, *pObject2;

	//	Process Pow(A, B) first, it's the only function need 2 parameters.
	if(left >=2 &&  str.at(left-2) == 'K')
	{
		//	There should be one comma in it.
		short comma = resStr.indexOf(",");
		if(comma < 1 || comma >= resStr.length()-1)
			return false;

		//	The second parameter should be a figure.
		QString rightStr = resStr.right(resStr.length()-comma-1);
		i = _simpleCal(rightStr, rightRes, pObject);
		if(i != 0)
			return false;

		resStr = resStr.left(comma);
	}	
	
	i = _simpleCal(resStr, res, pObject);
	if(i == -1) 
		return false;

	if(left <=  1 || str.at(left-1) != '#')
	{
		if(i == 0)
		{
			tmpStr = QString::number(res, 'f');
			str.replace(left, right-left+1, tmpStr);
		}
		else if(i == 1)
		{
			str.replace(left, right-left+1, resStr);
		}
	}
	else
	{
		//	Sepcial function, such as "Sin", "Cos" and so on...
		QChar symbol = str.at(left-2);

		if(i == 1)
		{
			//	Function on object.
			double dVal = rightRes;
			pObject2 = this->_funcOnAttribute(symbol, pObject, dVal);

			if(pObject2)
			{
				//	The result still be an object.
				m_vecPData.push_back(pObject2);

				tmpStr = "$";
				tmpStr += QChar(m_count);
				tmpStr += "$";
				m_count++;

				str.replace(left-2, right-left+3, tmpStr);
			}
			else
			{
				//	The result be a figure.
				tmpStr = QString::number(dVal, 'd');
				str.replace(left-2, right-left+3, tmpStr);
			}
		}
		else if(i == 0)
		{
			//	Function on a figure.
			switch(symbol.toLatin1())
			{
				case 'A':
					res = fabs(res);
					break;
				case 'B':
					if(m_nDegType == 0)
						res = sin(res*M_RAD);
					else if(m_nDegType == 1)
						res = sin(res);
					else
						res = sin(res * 0.9 * M_RAD);
					break;
				case 'C':
					if(m_nDegType == 0)
						res = cos(res*M_RAD);
					else if(m_nDegType == 1)
						res = cos(res);
					else
						res = cos(res * 0.9 * M_RAD);
					break;
				case 'D':
					if(m_nDegType == 0)
						res = tan(res*M_RAD);
					else if(m_nDegType == 1)
						res = tan(res);
					else
						res = tan(res * 0.9 * M_RAD);
					break;
				case 'E':
					res = log10(res);
					break;
				case 'F':
					res = log(res);
					break;
				case 'G':
					res = exp(res);
					break;
				case 'H':
					i = (int)(res+0.5);
					res = (double)i;
					break;
				case 'I':
					res = sqrt(res);
					break;
				case 'J':
					i = (int)(res);
					res = (double)i;
					break;
				case 'K':
					res = pow(res, rightRes);
					break;
				case 'L':
					{
						if(m_nDegType == 0)
							res = tan(res*M_RAD);
						else if(m_nDegType == 1)
							res = tan(res);
						else
							res = tan(res * 0.9 * M_RAD);
						if (res != 0.)
							res = 1/res;
					}
					break;
				case 'M':
					if(m_nDegType == 0)
						res = asin(res)*M_DEG;
					else if(m_nDegType == 1)
						res = asin(res);
					else
						res = asin(res)*M_DEG/0.9;
					break;
				case 'N':
					if(m_nDegType == 0)
						res = acos(res)*M_DEG;
					else if(m_nDegType == 1)
						res = acos(res);
					else
						res = acos(res)*M_DEG/0.9;
					break;
				case 'O':
					if(m_nDegType == 0)
						res = atan(res)*M_DEG;
					else if(m_nDegType == 1)
						res = atan(res);
					else
						res = atan(res)*M_DEG/0.9;
					break;
				case 'P':
					{
						if(m_nDegType == 0)
						{
							if (res == 0.)
								res = 90;
							else
								res = atan(1/res)*M_DEG;
						}
						else if(m_nDegType == 1)
						{
							if (res == 0.)
								res = M_PI_2;
							else
								res = atan(1/res);
						}
						else
						{
							if (res == 0.)
								res = 100;
							else
								res = atan(1/res)*M_DEG/0.9;
						}
					}
					break;
				case 'R':
					//	Std on one figure should be 0.
					res = 0.;
					break;
				case 'S':
				case 'T':
				case 'U':
				case 'V':
					//	Above 4 statistic function on one figure has no meaning.
					break;
				case 'W':
					//	Statistic the variables number.
					res = 1;
					break;
				default:
					return false;
			}

			tmpStr = QString::number(res, 'f');
			str.replace(left-2, right-left+3, tmpStr);
		}
	}

	return true;
}

//	Calculate a complex expression.
CXObject* CXObjCalculator::Calculate(QString str, double& fVal)
{
	int i;
	double res;
	m_strNewObjName = "New Object";
	fVal = g_dInvalidData;

	for(i = 0; i < 20; i++)
	{
		if(m_pBoolArray[i] != NULL) delete m_pBoolArray[i];
		m_pBoolArray[i] = NULL;
	}

	//	Pre-process.
	if(!_preProcess(str))
	{
		QMessageBox::critical(NULL, "Calculator Error", "Invalid Expression!");
		return NULL;
	}

	//	Process all the "if" expression.
	while(str.contains("If("))
	{
		//	Extract the "if(...){...}else if(...){...}else{...}" expression.
		int len = str.length();
		int tcount = 1;
		int pos1 = str.indexOf("If(");
		int pos2 = str.indexOf("else");
		for(i = pos2+5; i < len; i++)
		{
			if(str[i] == '{') tcount++;
			if(str[i] == '}') tcount--;
			if(tcount == 0) break;
		}

		if(i >= len) 
		{
			QMessageBox::critical(NULL, "Calculator Error", "Invalid Expression!");
			return NULL;
		}

		//	The tmpstr is the expression.
		QString tmpstr = str.mid(pos1, i-pos1+1);

		double *pObject = NULL;
		short tres = _ifCal(tmpstr, pObject); 
		if(tres == -1)
		{
			QMessageBox::critical(NULL, "Calculator Error", "Invalid Expression!");
			return NULL;
		}
		else
		{
			str.replace(pos1, i-pos1+1, tmpstr);
		}
	}


	int loopTime = 0;
	while(_calInnerMostExp(str))
	{
		//	To avoid dead loop
		if(loopTime > 100)
		{
			QMessageBox::critical(NULL, "Calculator Error", "Invalid Expression!");
			return NULL;
		}
		loopTime++;
	}

	double *pObject = NULL;
	short s = _simpleCal(str, res, pObject);

	for(i = 65; i < m_count-1; i++)
	{
		double *pData = m_vecPData.at(i-65);
		delete []pData;
	}

	for(i = 0; i < 20; i++)
	{
		if(m_pBoolArray[i] != NULL) delete m_pBoolArray[i];
		m_pBoolArray[i] = NULL;
	}

	if(s == 0)
	{
		//	The result is a figure.
		if(m_bObj)
		{
			//	Result must be an object, with the constant value.
			pObject = new double[m_iDataSize];
			for(i = 0; i < m_iDataSize; i++)
				pObject[i] = res;

			return _createResultObject(pObject);
		}
		else
		{
			//	Simply a figure.
			if(fabs(res) < 0.0000000001)
				res = 0;

			fVal = res;
		}
	}
	else if(s == 1)
	{
		//	The result is an object, add it on tree.
		return _createResultObject(pObject);
	}
	else if(s == -1)
	{
		QMessageBox::critical(NULL, "Calculator Error", "Invalid Expression!");
		return NULL;
	}

	return NULL;
}

//	Applied the function represented by chFlag on the object.
double* CXObjCalculator::_funcOnAttribute(QChar chFlag, double *pOriData, double& factor)
{
	if(!pOriData) 
		return NULL;

	int i;
	double *pNewData = NULL;

	double fRAD = M_RAD;
	double fDEG = M_DEG;
	if(m_nDegType == 1)
	{
		fRAD = 1.;
		fDEG = 1.;
	}
	else if(m_nDegType == 2)
	{
		fRAD = M_RAD * 0.9;
		fDEG = M_DEG / 0.9;
	}

	switch(chFlag.toLatin1())
	{
	case 'A':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				pNewData[i] = fabs(pOriData[i]);
			}
		}
		break;
	case 'B':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				pNewData[i] = sin(pOriData[i] * fRAD);
			}
		}
		break;
	case 'C':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				pNewData[i] = cos(pOriData[i]*fRAD);
			}
		}
		break;
	case 'D':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				pNewData[i] = tan(pOriData[i]*fRAD);
			}
		}
		break;
	case 'E':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}

				if(pOriData[i] <= 0)
					pNewData[i] = 0;
				else
					pNewData[i] = log10(pOriData[i]);
			}
		}
		break;
	case 'F':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}

				if(pOriData[i] <= 0)
					pNewData[i] = 0;
				else
					pNewData[i] = log(pOriData[i]);
			}
		}
		break;
	case 'G':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				pNewData[i] = exp(pOriData[i]);
			}
		}
		break;
	case 'H':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				pNewData[i] = (double)((int)(pOriData[i]+0.5));
			}
		}
		break;
	case 'I':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				if(pOriData[i] <= 0)
					pNewData[i] = 0;
				else
					pNewData[i] = sqrt(pOriData[i]);
			}
		}
		break;
	case 'J':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				pNewData[i] = (double)((int)(pOriData[i]));
			}
		}
		break;
	case 'K':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				pNewData[i] =  pow(pOriData[i], (double)factor);
			}
		}
		break;
	case 'L':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				pNewData[i] = tan(pOriData[i]*fRAD);
				if (pNewData[i] != 0.)
					pNewData[i] = 1/pNewData[i];
			}
		}
		break;
	case 'M':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				pNewData[i] = asin(pNewData[i])*fDEG;
			}
		}
		break;
	case 'N':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				pNewData[i] = acos(pNewData[i])*fDEG;
			}
		}
		break;
	case 'O':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				pNewData[i] = atan(pNewData[i])*fDEG;
			}
		}
		break;
	case 'P':
		{
			pNewData = new double[m_iDataSize];
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					pNewData[i] = m_fInvalid;
					continue;
				}
				if (pNewData[i] == 0.)
				{
					if(m_nDegType == 0)
						pNewData[i] = 90;
					else if(m_nDegType == 1)
						pNewData[i] = M_PI_2;
					else
						pNewData[i] = 100;
				}
				else
					pNewData[i] = atan(1/pNewData[i])*fDEG;
			}
		}
		break;
	case 'R':
		{
			//	Std.
			int nCount = 0;
			double dSum = 0.;

			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] != m_fInvalid)
				{
					++nCount;
					dSum += pOriData[i];
				}
			}
			if (nCount < 2)
				factor = 0.;
			else
			{
				double dMean =  dSum/nCount;
				dSum = 0.;
				for(i=0; i < m_iDataSize; i++)
				{
					if (pOriData[i] != m_fInvalid)
					{
						dSum += qAbs(pOriData[i] - dMean) * qAbs(pOriData[i] - dMean);
					}
				}
				factor = sqrt(dSum/(nCount-1));
			}
		}
		break;
	case 'S':
		{
			//	Min.
			factor = m_fInvalid;
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					continue;
				}

				if(factor == m_fInvalid)
					factor = pOriData[i];
				else if(factor > pOriData[i])
					factor = pOriData[i];
			}
		}
		break;
	case 'T':
		{
			//	Max.
			factor = m_fInvalid;
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					continue;
				}

				if(factor == m_fInvalid)
					factor = pOriData[i];
				else if(factor < pOriData[i])
					factor = pOriData[i];
			}
		}
		break;
	case 'U':
		{
			//	Mean.
			factor = 0.;
			int iCount = 0;
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					continue;
				}
					
				factor += pOriData[i];
				iCount++;
			}

			if(iCount > 0)
				factor /= iCount;
		}
		break;
	case 'V':
		{
			//	Sum.
			factor = 0.;
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					continue;
				}
					
				factor += pOriData[i];
			}
		}
		break;
	case 'W':
		{
			//	Number.
			int iCount = 0;
			for(i=0; i < m_iDataSize; i++)
			{
				if(pOriData[i] == m_fInvalid)
				{
					continue;
				}
					
				iCount++;
			}

			factor = iCount;
		}
		break;
	default:
		break;
	}

	return pNewData;
}
 
bool CXObjCalculator::_ObjectCompareByLengthDescend( CXObject *p1, CXObject *p2)
{
	if( p1 && p2 )
	{
		return p1->GetObjectName().length() > p2->GetObjectName().length();
	}
	return true;
}

bool CXObjCalculator::_StringCompareByLengthDescend( const QString&str1, const QString&str2 )
{
	return str1.length() > str2.length();
}

//	Process the input expression, find out all objects and replace them with key word.
QString CXObjCalculator::_findOutObjects(QString str)
{
	int i, j;
	m_count = 65;
	m_vecPData.clear();
	m_pBValid = NULL;

	CXObject *pObj = ::GetObjectByID(m_objID);
	if(!pObj)
		return str;

	EXObjectType eObjType = pObj->GetObjectType();
	EXObjectType eChildType = EXBegin;

	if(eObjType == EXWell)
		eChildType = EXWellCurve;
	else if (eObjType == EXSurfaceFolder)
		eChildType = EX3DSurface;
	else if (eObjType == EXHorizonFolder)
		eChildType = EX3DHorizon;

	QList<CXObject *> listChildern = pObj->GetChildren(eChildType);
	QList<CXObject *> listObj;

	//	In case this object has no child at all.
	if(listChildern.size() == 0)
		return str;

	//	Initialize.
	m_count = 65;
	m_vecPData.clear();

	//	We should search log name from long to short, so sort the log name first.
	//std::sort(vecChildren.begin(), vecChildren.end(), _ObjectCompareByLengthDescend);
	std::sort(listChildern.begin(), listChildern.end(), [](CXObject* p1, CXObject* p2) {
		return p1->GetObjectName().length() > p2->GetObjectName().length();
	});

	for(i = 0; i < listChildern.size(); i++)
	{
		QString strLogName = listChildern[i]->GetObjectName();
		if(str.indexOf(strLogName) != -1)
		{
			//	Deal with the object's name has only one character.
			if(strLogName.size() == 1)
			{
				int ind = str.indexOf(strLogName);
				if(ind > 0 && ind < str.size() - 1)
				{
					if(str.at(ind - 1) == '$' && str.at(ind + 1) == '$')
						continue;
				}
			}

			QString strTmpName = "$";
			strTmpName += QChar(m_count);
			strTmpName += "$";
			str.replace(strLogName, strTmpName);
			m_count++;

			listObj.append(listChildern.at(i));
		}
	}

	if(eObjType == EXWell)
	{
		CXWell *pWell = (CXWell *)pObj;

		double dStart, dStop, dStep;
		pWell->GetDepthRange(dStart, dStop);
		dStep = pWell->GetWellStep();
		m_iDataSize = (int)((dStop - dStart) / dStep + 1.99);

		for(i = 0; i < listObj.size(); i++)
		{
			CXWellCurve *pCurve = (CXWellCurve *)listObj.at(i);
			double *pData = new double[m_iDataSize];
			pCurve->GetData(pData, dStart, m_iDataSize);
			m_vecPData.push_back(pData);
		}
	}
	else if (eObjType == EXSurfaceFolder || eObjType == EXHorizonFolder)
	{
		CX3DSurface *pSurf;
		if(!listObj.empty())
			pSurf = (CX3DSurface *)listObj.at(0);
		else
		{
			QList<CXObject *> listAllObj;
			if (pObj->GetObjectType() == EXSurfaceFolder)
				listAllObj = pObj->GetChildren(EX3DSurface);
			else
				listAllObj = pObj->GetChildren(EX3DHorizon);

			if (!listAllObj.empty())
				pSurf = (CX3DSurface *)listAllObj.at(0);
			else
				return str;
		}

		CXUTMTool& utm = pSurf->GetUTM();
		m_iDataSize = utm.GetNI() * utm.GetNJ();
		m_refObjID = pSurf->GetObjectID();

		for(i = 0; i < listObj.size(); i++)
		{
			pSurf = (CX3DSurface *)listObj.at(i);
			double *pData = new double[m_iDataSize];
			float *pFData = pSurf->GetData();

			for(j = 0; j < m_iDataSize; j++)
				pData[j] = (double)pFData[j];

			m_vecPData.push_back(pData);
		}
	}

	return str;
}

//	Generate the result object.
CXObject* CXObjCalculator::_createResultObject(double *pBuff)
{
	CXObject *pObj = ::GetObjectByID(m_objID);
	if(pObj->GetObjectType() == EXWell)
	{
		CXWell *pWell = dynamic_cast<CXWell *>(::GetObjectByID(m_objID));
		if(!pWell)
			return NULL;

		double dStart, dStop, dStep;
		pWell->GetDepthRange(dStart, dStop);
		dStep = pWell->GetWellStep();

		CXWellCurve *pCurve = new CXWellCurve(pWell->GetUnallocatedName(m_strNewObjName));
		pCurve->ResetData(dStart, dStep, m_iDataSize, pBuff);
		CXTemplate *pTemplate = CXTemplate::GetTemplate(m_sTemplateName);
		pCurve->SetTemplateID(pTemplate->GetID());
		pWell->AddChild(pCurve);

		return pCurve;
	}
	else if(pObj->GetObjectType() == EXSurfaceFolder 
		|| pObj->GetObjectType() == EXHorizonFolder)
	{
		//	Use the 1st surface under the folder to get the UTM.
		CX3DSurface *pSurf = NULL;
		if(!m_refObjID.isNull())
			pSurf = dynamic_cast<CX3DSurface *>(::GetObjectByID(m_refObjID));

		if(!pSurf)
		{
			QList<CXObject *> listObj;
			if(pObj->GetObjectType() == EXSurfaceFolder)
				listObj = pObj->GetChildren(EX3DSurface);
			else
				listObj = pObj->GetChildren(EX3DHorizon);

			if (listObj.empty())
				return NULL;

			pSurf = (CX3DSurface *)listObj.at(0);
		}

		float *pData = new float[m_iDataSize];
		for(int i = 0; i < m_iDataSize; i++)
			pData[i] = (float)pBuff[i];

		if (pObj->GetObjectType() == EXSurfaceFolder)
		{
			CX3DSurface *pNewSurf = new CX3DSurface(pSurf->GetUTM(), pObj->GetUnallocatedName(m_strNewObjName));
			pNewSurf->SetData(pData);
			pObj->AddChild(pNewSurf);
			delete []pData;

			return pNewSurf;
		}
		else
		{
			CX3DHorizon *pHorizon = dynamic_cast<CX3DHorizon *>(pSurf);
			if (!pHorizon)
			{
				delete[]pData;
				return NULL; 
			}

			CX3DHorizon *pNewSurf = new CX3DHorizon(pHorizon->GetSurveyID(), pHorizon->GetUTM(), pObj->GetUnallocatedName(m_strNewObjName));
			pNewSurf->SetData(pData);
			pObj->AddChild(pNewSurf);
			delete[]pData;

			return pNewSurf;
		}
	}
	else
	{
		return NULL;
	}
}

QString CXObjCalculator::GetHelpTips()
{
	return _getBasicHelpTips() + _getSpecialHelpTips();
}

QString CXObjCalculator::_getBasicHelpTips()
{
	QString str = "The useful tips:\n\n"
		                   "1. The variable name has to be different from any of keywords. Otherwise, the calculator may\n"
						   "     not parse the expression.\n\n"
						   "2. The operator \"If\" is used with \"else\", and \"else if\" is optional. Here are examples with two\n "
						   "     or three curves,\n\n"
						   "     If (Log A > curve B) {curve A} else { curve B}\n"
						   "     If (curve A > curve B) {curve A} else if (curve B > curve C) {curve B}else {curve C} \n\n"
						   "3. \"Inv\" represents an invalid number. Any operation between a number and  \"Inv\" results in  \"Inv\".";


	return str;
}

QString CXObjCalculator::_getSpecialHelpTips()
{
	QString str;

	return str;
}