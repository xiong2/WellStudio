/*! @file rlmathmacro.h
* @brief The file defines the macro used for math in the XModel
*
* @date 2013-10
* @author Xiong
*/

#ifndef __RLMATHMACRO_H__
#define __RLMATHMACRO_H__

/* Definitions of useful mathematical constants
 * M_E        - e
 * M_LOG2E    - log2(e)
 * M_LOG10E   - log10(e)
 * M_LN2      - ln(2)
 * M_LN10     - ln(10)
 * M_PI       - pi
 * M_2XPI     - pi*2
 * M_PI_2     - pi/2
 * M_PI_4     - pi/4
 * M_1_PI     - 1/pi
 * M_2_PI     - 2/pi
 * M_RAD      - pi/180
 * M_DEG      - 180/pi
 * M_2_SQRTPI - 2/sqrt(pi)
 * M_SQRT2    - sqrt(2)
 * M_SQRT1_2  - 1/sqrt(2)

 * M_FEPS 5.0E-7
 *	M_DEPS 1.0E-12
 * M_TINY 1.0E-35
 *	M_FLT_MAX 1.0E+35
 * M_FLT_NEGATIVEMAX -1.0E+35
 * M_FINVALID -99999.99
 */

#ifndef M_E
#  define M_E        2.71828182845904523536
#endif

#ifndef M_LOG2E
#  define M_LOG2E    1.44269504088896340736
#endif

#ifndef M_LOG10E
#  define M_LOG10E   0.434294481903251827651
#endif

#ifndef M_LN2
#  define M_LN2      0.693147180559945309417
#endif

#ifndef M_LN10
#  define M_LN10     2.30258509299404568402
#endif

#ifndef M_PI
#  define M_PI       3.14159265358979323846
#endif

#ifndef M_2XPI
#  define M_2XPI     6.28318530717958647692
#endif

#ifndef M_PI_2
#  define M_PI_2     1.57079632679489661923
#endif

#ifndef M_PI_4
#  define M_PI_4     0.785398163397448309616
#endif

#ifndef M_1_PI
#  define M_1_PI     0.318309886183790671538
#endif

#ifndef M_2_PI
#  define M_2_PI     0.636619772367581343076
#endif

#ifndef M_RAD
#  define M_RAD      0.017453292519943295769
#endif

#ifndef M_DEG
#  define M_DEG      57.295779513082320876846
#endif

#ifndef M_SQRTPI
#  define M_SQRTPI   1.77245385090551602730
#endif

#ifndef M_SQRT2XPI
#  define M_SQRT2XPI 2.50662827463100050241
#endif

#ifndef M_2_SQRTPI
#  define M_2_SQRTPI 1.12837916709551257390
#endif

#ifndef M_SQRT2
#  define M_SQRT2    1.41421356237309504880
#endif

#ifndef M_SQRT1_2
#  define M_SQRT1_2  0.707106781186547524401
#endif

#ifndef  M_FEPS 
#	define  M_FEPS 2.0E-7
#endif

#ifndef  FLT_EPSILON
#   define  FLT_EPSILON M_FEPS
#endif

#ifndef M_TOL_SAMEPOINT
#define M_TOL_SAMEPOINT 0.1e-3
#endif // !M_TOL_SAMEPOINT

#ifndef M_TOL_DOUBLE
#	define	M_TOL_DOUBLE 1e-6
#endif // !M_TOL_DOUBLE

#ifndef M_ZERO_TEST
#	define M_ZERO_TEST	1.0e-08
#endif // !M_ZERO_TEST

#ifndef  M_DEPS 
#	define  M_DEPS 1.0E-15
#endif

#ifndef  M_TINY 
#	define  M_TINY 1.0E-35
#endif

#ifndef  M_FLT_MAX 
#	define  M_FLT_MAX 1.0E+35
#endif

#ifndef  FLT_MAX
#   define  FLT_MAX M_FLT_MAX
#endif

#ifndef  M_FLT_NEGATIVEMAX 
#	define  M_FLT_NEGATIVEMAX -1.0E+35
#endif

#ifndef M_FINVALID 
# define M_FINVALID -999.25
#endif 

/**
* @brief this value if for translating QColor to SbColor, it means 1.0f/255.0f
* @return M_FCOLORFACTOR
* @see
*/


#endif // __RLMATHMACRO_H__