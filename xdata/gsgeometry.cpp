#include "gsgeometry.h"
#include "xgeometry.h"
#include "xmathmacro.h"

QPolygonF GSGeom::CreateCapsule(QPointF p0, QPointF p1, double dMaxRadius, double dLengthToWidth)
{
    QPolygonF polygon;

    double delta_ang = 2 * M_PI / 32.0;

    XVec2d v0(p0.x(), p0.y());
    XVec2d v1(p1.x(), p1.y());

    XLine2d line(v0, v1);
    double t0 = line.TforXY(v0.x(), v0.y());
    double t1 = line.TforXY(v1.x(), v1.y());
    if (t0 > t1)
        std::swap(t0, t1);

	double r = qMin(fabs(t1 - t0) / dLengthToWidth, dMaxRadius);

    XVec2d cp0 = line.PforT(t0 + r);
    XVec2d ep0 = line.PointPerp(t0 + r, -r);

    for (double ang = 0.0; ang <= M_PI + delta_ang / 2; ang += delta_ang)
    {
        XVec2d rp = XGeom::RotateAbout(cp0, ang, ep0);
        polygon << QPointF(rp.x(), rp.y());
    }

    XVec2d cp1 = line.PforT(t1 - r);
    XVec2d ep1 = line.PointPerp(t1 - r, r);

    for (double ang = 0.0; ang <= M_PI + delta_ang / 2; ang += delta_ang)
    {
        XVec2d rp = XGeom::RotateAbout(cp1, ang, ep1);
        polygon << QPointF(rp.x(), rp.y());
    }

    polygon << polygon.front();
    return polygon;
}

double GSGeom::PolygonArea(const QPolygonF& polygon)
{
    int count = polygon.size();

    if (polygon.isClosed())
        --count;

    double dArea = 0.0;
    for (int i = 0; i < count; ++i)
    {
        int j = (i + 1) % count;
        dArea += polygon.at(i).x() * polygon.at(j).y();
        dArea -= polygon.at(i).y() * polygon.at(j).x();
    }

    dArea /= 2;

    return dArea;
}

QPointF GSGeom::PolygonCentroid(const QPolygonF& polygon)
{
	// https://www.seas.upenn.edu/~ese502/lab-content/extra_materials/Polygon%20Area%20and%20Centroid.pdf
	// X = SUM[(Xi + Xi+1)(Xi * Yi+1 - Xi+1 * Yi)] / 6 / A
	// Y = SUM[(Yi + Yi+1)(Xi * Yi+1 - Xi+1 * Yi)] / 6 / A

	int count = polygon.size();

	if (polygon.isClosed())
		--count;

	double dA = PolygonArea(polygon);

	QPointF centroid;
	for (int i = 0; i < count; ++i) {
		int j = i + 1;
		if (j >= count) j = 0;
		centroid.rx() += (polygon.at(i).x() + polygon.at(j).x()) * (polygon.at(i).x() * polygon.at(j).y() - polygon.at(j).x() * polygon.at(i).y());
		centroid.ry() += (polygon.at(i).y() + polygon.at(j).y()) * (polygon.at(i).x() * polygon.at(j).y() - polygon.at(j).x() * polygon.at(i).y());
	}

	centroid.rx() /= (6 * dA);
	centroid.ry() /= (6 * dA);

    return centroid;
}

QPolygonF GSGeom::CreateMarker(EMarkerType type, QPointF center, double dSize, double dAngleDegress)
{
    QPolygonF polygon;

    switch (type)
    {
    case eAnticline:
        polygon << QPointF(0.0, 0.5) << QPointF(0.25, 0.0) << QPointF(0.0, -0.5) << QPointF(-0.25, 0.0) << QPointF(0.0, 0.5);
        break;
    case eSyncline:
        polygon << QPointF(0, 0) << QPointF(-0.25, 0.5) << QPointF(0.25, 0.5) << QPointF(0.0, 0.0) << QPointF(0.25, -0.5) << QPointF(-0.25, -0.5) << QPointF(0.0, 0.0);
        break;
    case eStressArrow:
        polygon << QPointF(0, 0) << QPointF(0.1, 0.1) << QPointF(0.1, 0.05) << QPointF(0.5, 0.05) << QPointF(0.5, -0.05) << QPointF(0.1, -0.05) << QPointF(0.1, -0.1) << QPointF(0, 0);
        break;
    default:
        Q_ASSERT(!"Error");
    }

    for (auto& p : polygon)
    {
        double x = p.x() * dSize;
        double y = p.y() * dSize;

        XVec2d rp = XGeom::RotateAbout(XVec2d(0, 0), dAngleDegress / 180 * M_PI, XVec2d(x, y));

        p.setX(center.x() + rp.x());
        p.setY(center.y() + rp.y());
    }

    return polygon;
}

QPolygonF GSGeom::ConvexHull(const QVector<QPointF>& points)
{
	std::vector<XVec2d> vecPoints;
	for (const auto& p : points)
	{
		vecPoints.emplace_back(p.x(), p.y());
	}
	const std::vector<XVec2d>& sortedP = XGeom::ConvexHull2D(vecPoints);
	QPolygonF ret;
	for (const auto& p : sortedP)
	{
		ret.append(QPointF(p.x(), p.y()));
	}
	return ret;
}
