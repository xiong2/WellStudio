#include <cstring>
#include "xkdtreet.h"

#ifndef M_FCOLORFACTOR 
# define M_FCOLORFACTOR 0.003921568627f
#endif 

#ifndef INT_INF
#define INT_INF 0x3fffffff  
#endif 

#ifndef LL_INF
#define LL_INF 0x3fffffffffffffff  
#endif

#ifndef EPS
#define EPS 1e-12  
#endif

#ifndef MOD
#define MOD 1000000007  
#endif

#ifndef PI
#define PI 3.141592653579798  
#endif 
//#define N 60000  
CXKDTree3D::CXKDTree3D(int dim,double *x,double *y,double *z,int num)
{
	demension=dim;
	for(int i=1;i<=num;i++)
	{
		TreeData oneData;
		//for(int j=0;j<dim;j++)
		oneData.pos[0]=(x)[i-1];
		oneData.pos[1]=(y)[i-1];
		oneData.pos[2]=(z)[i-1];
		oneData.id=i;
		data[i]=(oneData);
	}
	m_numOfTreeNode=num;
}
CXKDTree3D::~CXKDTree3D()
{
	;
}
int split[60000];
int now;
bool treecmp(TreeData a,TreeData b)  
{  
	return a.pos[split[now]]<b.pos[split[now]];  
}  

void CXKDTree3D::build(int L,int R)  
{  
	if(L>R) return;  

	int mid=(L+R)>>1;  

	//求出 每一维 上面的方差  
	for(int pos=0;pos<demension;pos++)  
	{  
		double ave=var[pos]=0.0;  
		for(int i=L;i<=R;i++)  
			ave+=data[i].pos[pos];  
		ave/=(R-L+1);  
		for(int i=L;i<=R;i++)  
			var[pos]+=(data[i].pos[pos]-ave)*(data[i].pos[pos]-ave);  
		var[pos]/=(R-L+1);  
	}  

	//找到方差最大的那一维，用它来作为当前区间的 split_method  
	split[now=mid]=0;  
	for(int i=1;i<demension;i++)  
		if(var[split[mid]]<var[i]) split[mid]=i;  

	//对区间排排序，找到中间点  
	std::nth_element(data+L,data+mid,data+R+1,treecmp);  

	build(L,mid-1);  
	build(mid+1,R);  
}  

void CXKDTree3D::query(int L,int R)  
{  
	if(L>R) return;  
	int mid=(L+R)>>1;  

	//求出目标点 op 到现在的根节点的距离  
	long long dis=0;  
	for(int i=0;i<demension;i++)  
		dis+=(op.pos[i]-data[mid].pos[i])*(op.pos[i]-data[mid].pos[i]);  

	//如果当前区间的根节点能够用来更新最近距离，并且 dis 小于已经求得的 ans  
	if(!use[data[mid].id] && dis<ans)  
	{  
		ans=dis;  //更新最近距离  
		point=data[mid];  //更新取得最近距离下的点  
		id=data[mid].id;  //更新取得最近距离的点的 id  
	}  

	//计算 op 到分裂平面的距离  
	long long radius=(op.pos[split[mid]]-data[mid].pos[split[mid]])*(op.pos[split[mid]]-data[mid].pos[split[mid]]);  

	//对子区间进行查询  
	if(op.pos[split[mid]]<data[mid].pos[split[mid]])  
	{  
		query(L,mid-1);  
		if(radius<=ans) query(mid+1,R);  
	}  
	else  
	{  
		query(mid+1,R);  
		if(radius<=ans) query(L,mid-1);  
	}  
}  

int CXKDTree3D::nearest(int numofpoint,double x,double y,double z,int *pIndex)
{
	  
		memset(use,0,sizeof(use));  
		for(int i=0;i<numofpoint;i++)  
		{  
			ans=(((long long)INT_INF)*INT_INF);  
			op.pos[0]=x;
			op.pos[1]=y;
			op.pos[2]=z;
			query(1,m_numOfTreeNode);  
			//for(int i=0;i<demension;i++)  
			//{  
				//printf("%I64d",point.pos[i]);  
				//if(i==demension-1) printf("\n");  
				//else printf(" ");  
				//nearPoints.push_back(point);
			(pIndex)[i]=(id-1);
			//}  
			use[id]=1;  
		}  
		return 1;
		//}	
}
