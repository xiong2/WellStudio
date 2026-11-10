#ifndef CXKDTree3D_H_H
#define CXKDTree3D_H_H

#include "xbasic_global.h"  

class TreeData  
{  
public:
	long long pos[3];  
	int id;  
};

class XBASIC_EXPORT CXKDTree3D
{
public:
    CXKDTree3D(int dim, double* x, double* y, double* z, int num);
    ~CXKDTree3D();

    void query(int L, int R);
    void build(int L, int R);
    int nearest(int numofpoint, double x, double y, double z, int* pIndex);

    TreeData data[60000];
    TreeData op;
    TreeData point;

    bool use[60000];
    long long ans;
    long long id;
    double var[10];
    int now;
    int n;
    int demension;
    int m_numOfTreeNode;
};




#endif