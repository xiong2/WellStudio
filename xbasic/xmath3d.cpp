#include "xmath3d.h"
#include <qvector3d.h>

void NXMath3D::QVector2Array(const QVector3D& vec, double (&v)[3])
{
	v[0] = vec.x();
	v[1] = vec.y();
	v[2] = vec.z();
}