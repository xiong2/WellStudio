#ifndef _CXDATACONVERTOR_H__
#define _CXDATACONVERTOR_H__

#include "xbasic_global.h"

//	Below function come from "gmutl.h"
XBASIC_EXPORT void flipFloat(unsigned char *buffer, int numpts);

//	Below functions come from "segypar.h"
#define MSK_MANT_IBM 0xffffff
#define MSK_EXP_IBM  0x7f000000
#define MSK_SIGN_IBM 0x80000000
#define MSK_NORM_IEEE 0x800000

#define MSK_MANT_IEEE 0x7fffff
#define MSK_EXP_IEEE  0x7f800000
#define MSK_SIGN_IEEE 0x80000000

XBASIC_EXPORT extern void flip(unsigned char *buffer, int numpts);
XBASIC_EXPORT extern void decode_lineInt(int numpts, int *buff, int *data);
XBASIC_EXPORT extern void decode_lineShortInt(int numpts, short int *buff, short int *data);
XBASIC_EXPORT extern void flip_shortInt(unsigned char *buffer, int numpts);
//
/////////////////////////////
XBASIC_EXPORT extern void decode_lineFloat(int numpts, float *buff, float *data);
XBASIC_EXPORT extern void decode_line_Int(int numpts, int *buff, int *data);
//
XBASIC_EXPORT extern void FloatIee_Ibm(int numpts, long *ibm_fpn, long *ieee_fpn);
XBASIC_EXPORT extern void IntIee_Ibm(int numpts, int *buff, int *data);
XBASIC_EXPORT extern void ShortIntIee_Ibm(int numpts, short int *buff, short int *data);
XBASIC_EXPORT extern void ASCII_EBCDIC(char *p,int n);
XBASIC_EXPORT extern void EBCDIC_ASCII(char *p,int n);
XBASIC_EXPORT extern void Ibm_IeeShortInt(short *pInt);
XBASIC_EXPORT extern void Ibm_IeeInt(int *pInt);
XBASIC_EXPORT extern float FloatfromIBM(long ibm);
XBASIC_EXPORT extern long IEEEfromIBM(long ibm);
XBASIC_EXPORT extern float FloatfromIEEE(long ieee);
XBASIC_EXPORT extern long LongfromIeeeFloat(float *f);

//	Below functions come from "gmreverse.h"
XBASIC_EXPORT void Reverse(char *pChar, int nChar);
XBASIC_EXPORT void Reverse(int &n);
XBASIC_EXPORT void Reverse(short &n);
XBASIC_EXPORT void Reverse(long &n);
XBASIC_EXPORT void Reverse(float &n);
XBASIC_EXPORT void Reverse(unsigned short &n);
XBASIC_EXPORT void Reverse(double &n);

XBASIC_EXPORT void ConvertOneTrace(float* pDstData, char* pOriData, int iDataType, unsigned short iSampleNumber, bool bFlip);

//	Below functions come from "gmsegygroup.h"
XBASIC_EXPORT void IBMToIEEE(int* ibm_fpn, int* ieee_fpn, int num);

XBASIC_EXPORT void IEEEToIBM(int* ieee_fpn, int* ibm_fpn, int num);

#endif