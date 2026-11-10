#include "gsutilities.h"

QColor GSUtil::GetKellyColor(int index)
{
    // theory: https://eleanormaclure.files.wordpress.com/2011/03/colour-coding.pdf (page 5)
    // kelly's colors: http://artshacker.com/wp-content/uploads/2014/12/Kellys-22-colour-chart.jpg
    // remove the white and black.

    index %= 19;

    return QList<QColor>{
        QColor("pink"),
        QColor("olive"),
        QColor("magenta"),
        QColor("crimson"),
        QColor("gold"),
        QColor("teal"),
        QColor("saddlebrown"),
        QColor("rosybrown"),
        QColor("darkblue"),
        QColor("mediumslateblue"),
        QColor("darkturquoise"),
        QColor("darkslategray"),
        QColor("darkkhaki"),
        QColor("mediumvioletred"),
        QColor("green"),
        QColor("darkorchid"),
        QColor("tomato"),
        QColor("purple"),
        QColor("cyan"),
        QColor("dodgerblue")
    }
        .at(index);
}

XVec2d GSUtil::ToVec(const QPointF& p)
{
    return XVec2d(p.x(), p.y());
}

QPointF GSUtil::ToPoint(const XVec3d& vec)
{
	return QPointF(vec.x(), vec.y());
}

XLine2d GSUtil::MakeLine(const QPointF& p1, const QPointF& p2)
{
    return XLine2d(p1.x(), p1.y(), p2.x(), p2.y());
}
