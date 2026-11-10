#include <cstring>
#include "xdataconvertor.h"

XBASIC_EXPORT void flipFloat(unsigned char *buffer, int numpts)
{
	int i,j;
	unsigned char val;

	for(i=0;i<numpts;i++)
	{
		j=i*4;
		val=buffer[j+0];
		buffer[j+0]=buffer[j+3];
		buffer[j+3]=val;
		val=buffer[j+1];
		buffer[j+1]=buffer[j+2];
		buffer[j+2]=val;
	}
}

XBASIC_EXPORT void Ibm_IeeInt(int *pInt)
{
	char *v=(char*)pInt;
    char mv=*v;
	*v = *(v+3);
	*(v+3) = mv;
    mv=*(v+1);
	*(v+1) = *(v+2);
	*(v+2) = mv;
}

XBASIC_EXPORT void Ibm_IeeShortInt(short *pInt)
{
	if(!pInt)
	{
		return;
	}

	char *v=(char*)pInt;
    char mv=*v;
	*v = *(v+1);
	*(v+1) = mv;
}

XBASIC_EXPORT void Iee_IbmInt(int *pInt)
{
	char *v=(char*)pInt;
    char mv=*v;
	*v = *(v+3);
	*(v+3) = mv;
    mv=*(v+1);
	*(v+1) = *(v+2);
	*(v+2) = mv;
}

XBASIC_EXPORT void Iee_IbmShortInt(short int *pInt)
{
	char *v=(char*)pInt;
    char mv=*v;
	*v = *(v+1);
	*(v+1) = mv;
}

XBASIC_EXPORT void EBCDIC_ASCII(char *p,int n)

{
      static unsigned char ASCII_Table[256] = {

//    0      1   2      3   4      5   6      7   8    9    A    B    C    D    E      F

      0X00, 0X01, 0X02, 0X03, 0X9C, 0X09, 0X86, 0X7F, 0X97, 0X8D, 0X8E, 0X0B, 0X0C, 0X0D, 0X0E, 0X0F, //0

      0X10, 0X11, 0X12, 0X13, 0X9D, 0X85, 0X08, 0X87, 0X18, 0X19, 0X92, 0X8F, 0X1C, 0X1D, 0X1E, 0X1F, //1

      0X80, 0X81, 0X82, 0X83, 0X84, 0X0A, 0X17, 0X1B, 0X88, 0X89, 0X8A, 0X8B, 0X8C, 0X05, 0X06, 0X07, //2

      0X90, 0X91, 0X16, 0X93, 0X94, 0X95, 0X96, 0X04, 0X98, 0X99, 0X9A, 0X9B, 0X14, 0X15, 0X9E, 0X1A, //3

      0X20, 0XA0, 0XA1, 0XA2, 0XA3, 0XA4, 0XA5, 0XA6, 0XA7, 0XA8, 0XD5, 0X2E, 0X3C, 0X28, 0X2B, 0X7C, //4

      0X26, 0XA9, 0XAA, 0XAB, 0XAC, 0XAD, 0XAE, 0XAF, 0XB0, 0XB1, 0X21, 0X24, 0X2A, 0X29, 0X3B, 0X5E, //5

      0X2D, 0X2F, 0XB2, 0XB3, 0XB4, 0XB5, 0XB6, 0XB7, 0XB8, 0XB9, 0XE5, 0X2C, 0X25, 0X5F, 0X3E, 0X3F, //6

      0XBA, 0XBB, 0XBC, 0XBD, 0XBE, 0XBF, 0XC0, 0XC1, 0XC2, 0X60, 0X3A, 0X23, 0X40, 0X27, 0X3D, 0X22, //7

      0XC3, 0X61, 0X62, 0X63, 0X64, 0X65, 0X66, 0X67, 0X68, 0X69, 0XC4, 0XC5, 0XC6, 0XC7, 0XC8, 0XC9, //8    .abcdefghi......

      0XCA, 0X6A, 0X6B, 0X6C, 0X6D, 0X6E, 0X6F, 0X70, 0X71, 0X72, 0XCB, 0XCC, 0XCD, 0XCE, 0XCF, 0XD0, //9    .jklmnopqr......

      0XD1, 0X7E, 0X73, 0X74, 0X75, 0X76, 0X77, 0X78, 0X79, 0X7A, 0XD2, 0XD3, 0XD4, 0X5B, 0XD6, 0XD7, //A    .~stuvwxyz...[..

      0XD8, 0XD9, 0XDA, 0XDB, 0XDC, 0XDD, 0XDE, 0XDF, 0XE0, 0XE1, 0XE2, 0XE3, 0XE4, 0X5D, 0XE6, 0XE7, //B    .............]..

      0X7B, 0X41, 0X42, 0X43, 0X44, 0X45, 0X46, 0X47, 0X48, 0X49, 0XE8, 0XE9, 0XEA, 0XEB, 0XEC, 0XED, //C    {ABCDEFGHI......

      0X7D, 0X4A, 0X4B, 0X4C, 0X4D, 0X4E, 0X4F, 0X50, 0X51, 0X52, 0XEE, 0XEF, 0XF0, 0XF1, 0XF2, 0XF3, //D    }JKLMNOPQR......

      0X5C, 0X9F, 0X53, 0X54, 0X55, 0X56, 0X57, 0X58, 0X59, 0X5A, 0XF4, 0XF5, 0XF6, 0XF7, 0XF8, 0XF9, //E    \.STUVWXYZ......

      0X30, 0X31, 0X32, 0X33, 0X34, 0X35, 0X36, 0X37, 0X38, 0X39, 0XFA, 0XFB, 0XFC, 0XFD, 0XFE, 0XFF};//F    0123456789......

      int i;

      for(i=0;i<n;i++)
      {
            *(p+i) = ASCII_Table[(unsigned char)*(p+i)];
      }
}

 

XBASIC_EXPORT void ASCII_EBCDIC(char *p,int n)

{
      static unsigned char EBCDIC_Table[256] = {

//    0      1   2      3   4      5   6      7   8    9    A    B    C    D    E      F

      0X00, 0X01, 0X02, 0X03, 0X37, 0X2D, 0X2E, 0X2F, 0X16, 0X05, 0X25, 0X0B, 0X0C, 0X0D, 0X0E, 0X0F, //0

      0X10, 0X11, 0X12, 0X13, 0X3C, 0X3D, 0X32, 0X26, 0X18, 0X19, 0X3F, 0X27, 0X1C, 0X1D, 0X1E, 0X1F, //1

      0X40, 0X5A, 0X7F, 0X7B, 0X5B, 0X6C, 0X50, 0X7D, 0X4D, 0X5D, 0X5C, 0X4E, 0X6B, 0X60, 0X4B, 0X61, //2

      0XF0, 0XF1, 0XF2, 0XF3, 0XF4, 0XF5, 0XF6, 0XF7, 0XF8, 0XF9, 0X7A, 0X5E, 0X4C, 0X7E, 0X6E, 0X6F, //3

      0X7C, 0XC1, 0XC2, 0XC3, 0XC4, 0XC5, 0XC6, 0XC7, 0XC8, 0XC9, 0XD1, 0XD2, 0XD3, 0XD4, 0XD5, 0XD6, //4

      0XD7, 0XD8, 0XD9, 0XE2, 0XE3, 0XE4, 0XE5, 0XE6, 0XE7, 0XE8, 0XE9, 0XAD, 0XE0, 0XBD, 0X5F, 0X6D, //5

      0X79, 0X81, 0X82, 0X83, 0X84, 0X85, 0X86, 0X87, 0X88, 0X89, 0X91, 0X92, 0X93, 0X94, 0X95, 0X96, //6

      0X97, 0X98, 0X99, 0XA2, 0XA3, 0XA4, 0XA5, 0XA6, 0XA7, 0XA8, 0XA9, 0XC0, 0X4F, 0XD0, 0XA1, 0X07, //7

      0X20, 0X21, 0X22, 0X23, 0X24, 0X15, 0X06, 0X17, 0X28, 0X29, 0X2A, 0X2B, 0X2C, 0X09, 0X0A, 0X1B, //8

      0X30, 0X31, 0X1A, 0X33, 0X34, 0X35, 0X36, 0X08, 0X38, 0X39, 0X3A, 0X3B, 0X04, 0X14, 0X3E, 0XE1, //9

      0X41, 0X42, 0X43, 0X44, 0X45, 0X46, 0X47, 0X48, 0X49, 0X51, 0X52, 0X53, 0X54, 0X55, 0X56, 0X57, //A

      0X58, 0X59, 0X62, 0X63, 0X64, 0X65, 0X66, 0X67, 0X68, 0X69, 0X70, 0X71, 0X72, 0X73, 0X74, 0X75, //B

      0X76, 0X77, 0X78, 0X80, 0X8A, 0X8B, 0X8C, 0X8D, 0X8E, 0X8F, 0X90, 0X9A, 0X9B, 0X9C, 0X9D, 0X9E, //C

      0X9F, 0XA0, 0XAA, 0XAB, 0XAC, 0X4A, 0XAE, 0XAF, 0XB0, 0XB1, 0XB2, 0XB3, 0XB4, 0XB5, 0XB6, 0XB7, //D

      0XB8, 0XB9, 0XBA, 0XBB, 0XBC, 0X6A, 0XBE, 0XBF, 0XCA, 0XCB, 0XCC, 0XCD, 0XCE, 0XCF, 0XDA, 0XdB, //E

      0XDC, 0XDD, 0XDE, 0XDF, 0XEA, 0XEB, 0XEC, 0XED, 0XEE, 0XEF, 0XFA, 0XFB, 0XFC, 0XFD, 0XFE, 0XFF};//F

      int i;
      for(i=0;i<n;i++)
      {
            *(p+i) = EBCDIC_Table[(unsigned char)*(p+i)];
      }
}

XBASIC_EXPORT void decode_lineFloat(int numpts, float *buff, float *data)
{
	flip((unsigned char *)buff, numpts);
	IBMToIEEE((int*)buff, (int*)data, numpts);
}

XBASIC_EXPORT void decode_line_Int(int numpts, int *buff, int *data)
{
	flip((unsigned char *)buff, numpts);
	memmove(data, buff, numpts*sizeof(int));
}

XBASIC_EXPORT void decode_lineShortInt(int numpts, short int *buff, short int *data)
{
	flip_shortInt((unsigned char *)buff, numpts);
	memmove(data, buff, numpts*sizeof(short int));
}

/**************************************************************************
**	Flip a 4 bytes number (float or int) high bits and low bits
**************************************************************************/
XBASIC_EXPORT void flip(unsigned char *buffer, int numpts)
{
	int i,j;
	unsigned char val;

    j=0;
	for(i=0;i<numpts;i++)
	{
        val=buffer[j+0];
		buffer[j+0]=buffer[j+3];
		buffer[j+3]=val;
		val=buffer[j+1];
		buffer[j+1]=buffer[j+2];
		buffer[j+2]=val;
        j+=4;
	}
}

XBASIC_EXPORT void flip_shortInt(unsigned char *buffer, int numpts)
{
	int i,j;
	unsigned char val;

	for(i=0;i<numpts;i++)
	{
		j=i*2;
		val=buffer[j+0];
		buffer[j+0]=buffer[j+1];
		buffer[j+1]=val;
	}
}

XBASIC_EXPORT void FloatIee_Ibm(int numpts, int *ibm_fpn, int *ieee_fpn)
{
	int i;
	int exponent,mantissa,sign;

	for(i=0;i<numpts;i++)
	{
		if(ieee_fpn[i]==0)
			ibm_fpn[i]=0;
		else
		{
			mantissa=(ieee_fpn[i]&MSK_MANT_IEEE)|0x800000;
			exponent=((ieee_fpn[i]&MSK_EXP_IEEE)>>23)-126;
			sign=(ieee_fpn[i]&MSK_SIGN_IEEE);
			while((exponent&0x03)!=0)
			{
				exponent++;
				mantissa>>=1;
			}
			exponent=((exponent>>2)+64)<<24;
			ibm_fpn[i]=sign|exponent|mantissa;
		}
	}
}

XBASIC_EXPORT void IntIee_Ibm(int numpts, int *buff, int *data)
{
	memmove(buff, data, numpts*sizeof(int));
	flip((unsigned char *)buff, numpts);
}

XBASIC_EXPORT void ShortIntIee_Ibm(int numpts, short int *buff, short int *data)
{
	memmove(buff, data, numpts*sizeof(short int));
	flip_shortInt((unsigned char *)buff, numpts);
}

XBASIC_EXPORT void decode_lineInt(int numpts, int *buff, int *data)
{
	flipFloat((unsigned char *)buff, numpts);
	memmove(data, buff, numpts*sizeof(int));
}

XBASIC_EXPORT float FloatfromIBM(long ibm)
{
	int ieee = IEEEfromIBM(ibm);
	float *ff = (float*)(&ieee);
	return *ff;
}

XBASIC_EXPORT long IEEEfromIBM(long ibm)
{
	if ((ibm & MSK_MANT_IBM) == 0)
	{
		return 0;
	}
	else
	{
		int mantissa = (ibm & MSK_MANT_IBM); /* get mantissa */
		int exponent = ((((ibm & MSK_EXP_IBM) >> 24) - 64) << 2 ); 
			/* get exponent */
		int sign     = (ibm & MSK_SIGN_IBM); /* get sign */
		while ((mantissa & MSK_NORM_IEEE) == 0) 
		{
			mantissa <<= 1;  /* normalize */
			exponent-- ;
		}
		mantissa = mantissa & 0x7fffff;    /* shift understood one out */
		exponent += 126;
		if (( exponent < 0 ) || (exponent > 255))
		{
			printf ("IBM floating point exponent out of range \n");
			sign=mantissa=exponent = 0;
		}
		exponent <<= 23;
		return (sign | exponent | mantissa);
	}
}

XBASIC_EXPORT float FloatfromIEEE(long ieee)
{
	float *ff = (float*)(&ieee);
	return *ff;
}

XBASIC_EXPORT long LongfromIeeeFloat(float *f)
{
	if(fabs(*f)<1e-6) return 0;
	unsigned char *ieee = (unsigned char *)f;
// in pointor *ieee: h1h0 h3h2 h5h4 h7h6 (low -> hi), "flipped"
//					 0	  1	   2	3

// IEEE float format:
//			  s[0]	     s[1]		s[2]	   s[3]
//			  f[3]		 f[2]	    f[1]	   f[0]
//			h7	 h6  | h5	h4  | h3   h2  | h1	  h0
//	bit:	FEDC BA98| 7654 3210| FEDC BA98| 7654 3210
//			||_________||____________________________|
//	IEEE  sign exp(8bits)	mantissa (23bits)
//			|________| ||____________________________|
//	MS	  exp(8bits)  sign	mantissa (23bits)

/*
 Microsoft/IEEE Float binary:                                       
 +--------------------------------------------------------------------+
 |bit |F E D C|B A 9 8|7 6 5 4|3 2 1 0|F E D C|B A 9 8|7 6 5 4|3 2 1 0|
 +====+=+=============+=+=============================================+
 |IEEE|s| exponent      |                mantissa                     |
 +----+-+-------------+-+---------------------------------------------+
 |MKS |   exponent    |s|                mantissa                     |
 +----+---------------+-+---------------------------------------------|
*/
/*
	char s[4][3]; // hex string, hi -> low
	for(int i=0;i<4;i++) sprintf(s[3-i],"%02x",ieee[i]);
*/
/*
	unsigned int f0 = UlFromSzHex(s[3]); //bit 07-04 03-00, h1h0
	unsigned int f1 = UlFromSzHex(s[2]); //    15-12 11-08, h3h2
	unsigned int f2 = UlFromSzHex(s[1]); //    23-20 19-16, h5h4
	unsigned int f3 = UlFromSzHex(s[0]); //    31-28 27-24, h7h6
//	unsigned int ul = f0*pow(2,0) + f1*pow(2,8) + f2*pow(2,16) + f3*pow(2,24);
	unsigned int ul = f0		   + f1*256		 + f2*65536		+ f3*16777216;
*/
	//					2^24			2^16			2^8			2^0
	long l = ieee[3]*16777216 + ieee[2]*65536 + ieee[1]*256 + ieee[0];
/*
	int sign = f3>>7;
	int l = ul;
	if(sign==1) l = ul*-1;
*/	
	return l;
}

XBASIC_EXPORT void Reverse(char *pChar, int nChar)
{
	int nHalf=nChar/2;
	char c;
	for(int i=0;i<nHalf;i++)
    {
		c=pChar[i];
		pChar[i]=pChar[nChar-i-1];
		pChar[nChar-i-1]=c;
	}
}

XBASIC_EXPORT void Reverse(int &n)
{
	char *pChar=(char*)(&n);
	Reverse(pChar,sizeof(int));
}

XBASIC_EXPORT void Reverse(short &n)
{
	char *pChar=(char*)(&n);
	Reverse(pChar,sizeof(short));
}

XBASIC_EXPORT void Reverse(long &n)
{
	char *pChar=(char*)(&n);
	Reverse(pChar,sizeof(long));
}

XBASIC_EXPORT void Reverse(float &n)
{
	char *pChar=(char*)(&n);
	Reverse(pChar,sizeof(float));	
}

XBASIC_EXPORT void Reverse(unsigned short &n)
{
	char *pChar=(char*)(&n);
	Reverse(pChar,sizeof(unsigned short));	
}

XBASIC_EXPORT void Reverse(double &n)
{
	char *pChar=(char*)(&n);
	Reverse(pChar,sizeof(double));	
}

#define MSK_MANT_IBM 0xffffff
#define MSK_EXP_IBM  0x7f000000
#define MSK_SIGN_IBM 0x80000000
#define MSK_NORM_IEEE 0x800000

#define MSK_MANT_IEEE 0x7fffff
#define MSK_EXP_IEEE  0x7f800000
#define MSK_SIGN_IEEE 0x80000000

XBASIC_EXPORT void ConvertOneTrace(float* pDstData, char* pOriData, int iDataType, unsigned short iSampleNumber, bool bFlip)
{
	int i;

	if(iDataType >= 0 && iDataType <= 2)
	{
		//	float or integer, need flip?  Notes IBM float always need flip.
		if(bFlip || iDataType == 1)
		{
			float *pData = (float *)pOriData;
			for(i = 0; i < iSampleNumber; i++)
			{
				Reverse(pData[i]);
			}
		}

		if(iDataType == 0)
		{
			memcpy(pDstData, pOriData, iSampleNumber * sizeof(float));
		}
		else if(iDataType == 1)
		{
			IBMToIEEE((int *)pOriData, (int *)pDstData, iSampleNumber);
		}
		else if(iDataType == 2)
		{
			int *pData = (int *)pOriData;
			for(i = 0; i < iSampleNumber; i++)
			{
				pDstData[i] = (float)pData[i];
			}
		}
	}
	else if(iDataType == 3)
	{
		//	2-bit short.
		short *pData = (short *)pOriData;
		if(bFlip)
		{
			for(i = 0; i < iSampleNumber; i++)
			{
				Reverse(pData[i]);
			}
		}

		for(i = 0; i < iSampleNumber; i++)
		{
			pDstData[i] = (float)pData[i];
		}
	}
	else if(iDataType == 4)
	{
		//	1-bit char.
		char *pData = (char *)pOriData;
		for(i = 0; i < iSampleNumber; i++)
		{
			pDstData[i] = (float)pData[i];
		}
	}
}

XBASIC_EXPORT void IBMToIEEE(int  *ibm_fpn, int *ieee_fpn, int numpts)
{
    int i;
    int exponent;
    int mantissa;
    int sign;


    for(i=0;i<numpts;i++)
    {
        if ((ibm_fpn[i] & MSK_MANT_IBM) == 0)
        {
            ieee_fpn[i] = 0;
        }
        else
        {
            mantissa = (ibm_fpn[i] & MSK_MANT_IBM); /* get mantissa */
            exponent = ((((ibm_fpn[i] & MSK_EXP_IBM) >> 24) - 64) << 2 ); 
            /* get exponent */
            sign     = (ibm_fpn[i] & MSK_SIGN_IBM); /* get sign */
            while ((mantissa & MSK_NORM_IEEE) == 0) 
            {
                mantissa <<= 1;  /* normalize */
                exponent-- ;
            }
            mantissa = mantissa & 0x7fffff;    /* shift understood one out */
            exponent += 126;
            if (( exponent < 0 ) || (exponent > 255))
            {
                //				printf ("IBM floating point exponent out of range \n");
                sign=mantissa=exponent = 0;
            }
            exponent <<= 23;
            ieee_fpn[i] =  sign | exponent | mantissa;
        }
    }
}

XBASIC_EXPORT void IEEEToIBM(int *ieee_fpn, int *ibm_fpn, int num)
{
    int i;
    int exponent,mantissa,sign;

    for(i=0;i<num;i++)
    {
        if(ieee_fpn[i]==0)
            ibm_fpn[i]=0;
        else
        {
            mantissa=(ieee_fpn[i]&MSK_MANT_IEEE)|0x800000;
            exponent=((ieee_fpn[i]&MSK_EXP_IEEE)>>23)-126;
            sign=(ieee_fpn[i]&MSK_SIGN_IEEE);
            while((exponent&0x03)!=0)
            {
                exponent++;
                mantissa>>=1;
            }
            exponent=((exponent>>2)+64)<<24;
            ibm_fpn[i]=sign|exponent|mantissa;
        }
    }
}
