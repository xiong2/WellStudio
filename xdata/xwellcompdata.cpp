
#include "xwellcompdata.h"
#include "xobjectfactory.h"
#include "xwellcurve.h"
#include <math.h>
#ifndef MAX
#define	MAX(x,y) ((x) > (y) ? (x) : (y))
#endif
#ifndef MIN
#define	MIN(x,y) ((x) < (y) ? (x) : (y))
#endif

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellCompData)
EXWellCompData
END_REGISTER_OBJECT_TO_FACTORY(CXWellCompData)

QList<CXWellCompData*> CXWellCompData::g_lstAllData;
CXWellCompData::CXWellCompData()
{
	g_lstAllData.append(this);
	m_id = NULL;
	m_type = -1;
	SetObjectType(EXWellCompData);
	SetObjectName("Well CompData");
	m_nSamplingNum = 0;
	m_pCompData = NULL;

	SetNodeFlag(false);
// 	if (m_pWellLog && m_pWellLog->m_lstTrack.count() >0)
// 	{
// 		CreateDataByTrack(m_pWellLog->m_lstTrack.at(0));
// 	}

	QColor cr = Qt::red;
	for (int i = 0 ; i< 12; i++)
	{
		m_lstColor.append(cr);
	}
}

CXWellCompData::~CXWellCompData()
{
	g_lstAllData.removeOne(this);
	if (m_pCompData)
	{
		delete []m_pCompData;
	}
	m_pCompData = NULL;
}

void CXWellCompData::SetID(void* id)
{
	m_id = id;
}

void* CXWellCompData::GetID() {
	return m_id;
}

bool   CXWellCompData::CreateDataByTrack(CXWellCurve* pTrack)//由相对应的pTrack创建原始数据
{
	if (!pTrack)
	{
		return false;
	}
	m_nCount = pTrack->GetCount();
	if (m_pCompData)
	{
		delete []m_pCompData;
	}
	m_pCompData = new int[m_nCount];
	for (int i = 0 ; i< m_nCount ; i++)
	{
		m_pCompData[i] = 0;
	}
	pTrack->GetDepthRange(m_start, m_stop);
	m_step = pTrack->GetStep();
	this->SetModifiedFlag();
	return true;
}
void  CXWellCompData::SetChooseDepth(double Dst,double Ded,int choose)//设置一段范围为选定
{
	if (Ded< m_start || Dst > m_stop		 )
	{
		return;
	}
	if (!m_pCompData)
	{
		return;
	}
	Dst = (Dst<m_start )? m_start: Dst;
	Ded = (Ded>m_stop  )? m_stop : Ded;
	int i,ist,ied;
	ist = MAX(GetIndex(Dst),0);
	ied = MIN(GetIndex(Ded),m_nCount-1);
	for(i = ist ; i<= ied ;i++)
	{
		m_pCompData[i] = choose;
	}
	
}

void CXWellCompData::SetColor(QColor cr,int index )//index<12,设置颜色,如果没有定义index,则默认添加新颜色
{
	if (index <12 )
	{
		m_lstColor[index] = cr;
	}
}

QColor CXWellCompData::GetColor(int index)//返回相对应的颜色
{
	if (index <12 )
	{
		return m_lstColor[index] ;
	}
	return Qt::black;	
}

int CXWellCompData::GetColorCount()
{
	return m_lstColor.count();
}

double  CXWellCompData::GetDepth(int index)//返回当前的depth
{
	double dep;
	dep=m_start+m_step*(double)index;
	return dep;
}

int    CXWellCompData::GetIndex(double depth)//由深度返回index
{
	if(m_start-depth>0.01 || depth-(double)m_nCount* m_step - m_start>0.01) 
		return -1;	
	int   index=(depth-m_start)*1000.f/(m_step*1000.f);	
	double dep,amin,temp,ix;
	for(int i=index-1;i<=index+1;i++)
	{
		dep=GetDepth(i);
		if(i==index-1)
		{
			amin=fabs(depth-dep);
			ix=i;
		}
		else
		{
			temp=fabs(depth-dep);
			if(temp<amin)
			{
				amin=temp;
				ix=i;
			}
		}	
	}	
	return ix;
}

int* CXWellCompData::GetData()
{
	return m_pCompData;	
}

int CXWellCompData::GetData(int index)
{
	return m_pCompData[index];
}

int    CXWellCompData::GetCount()
{
	return m_nCount;
}

bool CXWellCompData::SerializeData(CXArchive& ar)
{
	int i = 0 ;
	int size = 0 ;
	if(ar.IsSaving()==false)
	{		
		ar>> size;
		if (size == 20160830)
		{
		}
		else if (size == 20100325)
		{
			ar>> m_start >> m_stop >> m_step; 
			ar>> size;		
			if (m_pCompData)
			{
				if (m_nCount != size)
				{
					delete []m_pCompData;
					m_nCount = size;
					m_pCompData = new int[m_nCount];	
				}
			}
			else{
				m_nCount = size;
				m_pCompData = new int[m_nCount];	
			}
			ar.readRawData((char*)m_pCompData,m_nCount*sizeof(int));

			//除了曲线窗口上选择数据以外,其余全部为空
			for (i = 0 ; i < m_nCount ;i++)
			{
				if (m_pCompData[i] > 1)
				{
					m_pCompData[i] = 0;
				}
			}

			ar>> m_lstColor;
			ar>> i;//保留字
		}
		else{
			return false;
		}
	}
	else{
		ar << 20160830;

		//ar<< 20100325;
		//ar<< m_start << m_stop << m_step; 
		//ar<< m_nCount;		
		//ar.writeRawData((char*)m_pCompData,m_nCount*sizeof(int));	
		//ar<< m_lstColor;
		//ar<< 20100316;
	}
	return true;
}
