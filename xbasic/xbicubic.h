#pragma once

/*
Java class to implement a bicubic interpolator
      by Ken Perlin @ NYU, 1998.

You have my permission to use freely, as long as you keep the attribution. - Ken Perlin

Note: this Bicubic.html file also works as a legal Bicubic.java file. If you save the source under that name, you can just run javac on it.
Why does this class exist?

    I created this class because I needed to evaluate a fairly expensive function over x,y many times. It turned out that I was able to rewrite the function as a sum of a "low frequency" part that only varied slowly, and a much less expensive "high frequency" part that just contained the details.
    I used the bicubic patches as follows: First I presampled the low frequency part on a coarse grid. During the inner loop of the evaluation, I used this bicubic approximation, and then added in the high frequency part. Through this approach I was able to speed up the computation by a large factor. 

What does the class do?

    If you provide a 4x4 grid of values (ie: all the corners in a 3x3 arrangement of square tiles), this class creates an object that will interpolate a Catmull-Rom spline to give you the value within any point of the center tile.
    If you want to create a spline surface, you can make a two dimensional array of such objects, arranged so that adjoining objects overlap by one grid point. 

The class provides a constructor and a method:

    Bicubic(double[][] G)
        Given 16 values on the grid [-1,0,1,2] X [-1,0,1,2], calculate bicubic coefficients. 

    double eval(double x, double y)
        Given a point in the square [0,1] X [0,1], return a value. 

Algorithm:

    f(x,y) = X * M * G * MT * YT , where:

        X = (x3 x2 x 1) ,
        Y = (y3 y2 y 1) ,
        M is the Catmull-Rom basis matrix. 

    The constructor Bicubic() calculates the matrix C = M * G * MT

    The method eval(x,y) calculates the value X * C * YT 

*/

#include "xbasic_global.h"
#include <array>

/**
@class  CXBicubic provided in the file "xbicubic.h"
@brief  The class provides a bicubic interpolator from above Java Code.
@author pezy
@date   2018-03-27
@sa
*/
class XBASIC_EXPORT CXBicubic
{
public:
    CXBicubic(const std::array<std::array<double, 4>, 4>& G);

	double Eval(double x, double y) const;

private:
	std::array<std::array<double, 4>, 4> C; // coefficients matrix
    const std::array<std::array<double, 4>, 4> M = { { { -0.5,  1.5, -1.5,  0.5 }, // Catmull-Rom basis matrix
													   {    1, -2.5,    2, -0.5 },
													   { -0.5,    0,  0.5,    0 },
													   {    0,    1,    0,    0 } } };
};

class XBASIC_EXPORT CXBilinear
{
public:
	CXBilinear(const std::array<std::array<double, 2>, 2>& g);

	double Eval(double u, double v) const;

private:
	std::array<std::array<double, 2>, 2> m_z;
};