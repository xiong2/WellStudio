#include "xunit.h"
#include "xlog.h"

CXUnit::CXUnit(EXUnitType eType, QString sName, QString sFullName, double dRatio)
{
	m_eUnitType = eType;
	m_sName		= sName;
	m_dRatio	= dRatio;
	m_listSAlias<<m_sName;

	//	If not given full name, set it the same as name.
	if(sFullName == "")
		m_sFullName = sName;
	else
	{
		m_sFullName = sFullName;
		m_listSAlias<<m_sFullName;
	}
}

//	Get the name of unit types.
QStringList CXUnit::GetAllUnitType()
{
	QStringList sListType;
	sListType<<"None"<<"Time"<<"Length"<<"Area"<<"Volume"<<"Weight"<<"Gamma Ray"<<"Potential"<<"Density"<<"Photo Electric"
		<<"Transit Time"<<"Resistivity"<<"Gamma Ray Spectral"<<"Angle";
	
	return sListType;
}

//	Get the standard unit name of the oriName, if not found return "".
QString CXUnit::GetStandardName(QString sOriName)
{
	std::vector<CXUnit> vecUnit = getUnitVector();
	int iSize = vecUnit.size();

	for(int i = 0; i < iSize; i++)
	{
		if(vecUnit[i].m_listSAlias.contains(sOriName, Qt::CaseInsensitive))
			return vecUnit[i].m_sName;
	}

	return "";
}

//	Get the type of the special unit.
EXUnitType CXUnit::GetUnitType(QString sName)
{
	std::vector<CXUnit> vecUnit = getUnitVector();
	int iSize = vecUnit.size();

	for(int i = 0; i < iSize; i++)
	{
		if(vecUnit[i].m_listSAlias.contains(sName, Qt::CaseInsensitive))
			return vecUnit[i].m_eUnitType;
	}

	return eVoid;
}

//	Get the convert ratio
double CXUnit::GetConvertRatio(QString sSoruceUnit, QString sDestinateUnit)
{
	int i, iS = -1, iD = -1;
	std::vector<CXUnit> vecUnit = getUnitVector();
	int iSize = vecUnit.size();

	for(i = 0; i < iSize; i++)
	{
		//	Find source unit.
		if(vecUnit[i].m_listSAlias.contains(sSoruceUnit, Qt::CaseInsensitive))
		{
			iS = i;
			if(iD != -1)
				break;
		}

		//	Find destinate unit.
		if(vecUnit[i].m_listSAlias.contains(sDestinateUnit, Qt::CaseInsensitive))
		{
			iD = i;
			if(iS != -1)
				break;
		}
	}

	if(iS == -1 || iD == -1)
	{
		//	At least one unit does not found!
		if(iS == -1)
			CXLog::AddLog("Unit: " + sSoruceUnit + " is not supported!");
		if(iD == -1)
			CXLog::AddLog("Unit: " + sDestinateUnit + " is not supported!");
		return 1.;
	}

	if(vecUnit[iS].m_eUnitType != vecUnit[iD].m_eUnitType)
	{
		//	Two units are not the same type, can not convert!
		CXLog::AddLog(sSoruceUnit + " and " + sDestinateUnit + " are not the same UNIT TYPE!");
		return 1.;
	}

	return vecUnit[iS].m_dRatio / vecUnit[iD].m_dRatio;
}

//	Get all available units of the specified type
QStringList CXUnit::GetAllUnits(EXUnitType eType)
{
	QStringList listSUnits;

	std::vector<CXUnit> vecUnit = getUnitVector();
	int iSize = vecUnit.size();

	for(int i = 0; i < iSize; i++)
	{
		if(vecUnit[i].m_eUnitType == eType)
			listSUnits<<vecUnit[i].m_sName;
	}

	return listSUnits;
}

//	Get the static unit vector.
std::vector<CXUnit>& CXUnit::getUnitVector()
{
	static std::vector<CXUnit> staVecUnit;

	//	If the vector already populated, directly return.
	if(staVecUnit.size() > 0)
		return staVecUnit;

	//	Time units.
	CXUnit msUnit(eTime, "ms", "millisecond");				//	Standard time unit.
	msUnit.m_listSAlias << "millisecond" << "msec";
	staVecUnit.push_back(msUnit);

	CXUnit sUnit(eTime, "s", "second", 1000);				
	sUnit.m_listSAlias << "second";
	staVecUnit.push_back(sUnit);

	CXUnit usUnit(eTime, "us", "microsecond", 0.001);
	usUnit.m_listSAlias << "microsecond" ;
	staVecUnit.push_back(usUnit);

	//	Length units.
	CXUnit mUnit(eLength, "m", "metre");				//	Standard length unit.
	mUnit.m_listSAlias<<"meter";
	staVecUnit.push_back(mUnit);

	CXUnit kmUnit(eLength, "km", "kilometre", 1000);
	kmUnit.m_listSAlias<<"kilometer";
	staVecUnit.push_back(kmUnit);

	CXUnit cmUnit(eLength, "cm", "centimetre", 0.01);
	cmUnit.m_listSAlias<<"centi metre"<<"centi-metre"<<"centimeter"<<"centi meter"<<"centi-meter";
	staVecUnit.push_back(cmUnit);

	CXUnit mmUnit(eLength, "mm", "millimetre", 0.001);
	mmUnit.m_listSAlias<<"milli meter"<<"milli-meter"<<"millimeter"<<"milli metre"<<"milli-metre";
	staVecUnit.push_back(mmUnit);
	
	CXUnit ftUnit(eLength, "ft", "foot", 0.3048);
	ftUnit.m_listSAlias<<"feet";
	staVecUnit.push_back(ftUnit);

	CXUnit inUnit(eLength, "in", "inch", 0.0254);
	staVecUnit.push_back(inUnit);

	CXUnit deciinUnit(eLength, "deciin", "0.1 inch", 0.00254);
	staVecUnit.push_back(deciinUnit);

	//	Area units.
	CXUnit m2Unit(eArea, "m2", "square metre");		//	Standard area unit.
	m2Unit.m_listSAlias<<"centiare"<<"sq.m."<<"m^2"<<"square meter";
	staVecUnit.push_back(m2Unit);

	CXUnit km2Unit(eArea, "km2", "square kilometre", 1000000);
	km2Unit.m_listSAlias<<"sq.km."<<"km^2"<<"square kilometer";
	staVecUnit.push_back(km2Unit);

	CXUnit cm2Unit(eArea, "cm2", "square centimetre", 0.0001);
	cm2Unit.m_listSAlias<<"sq.cm."<<"cm^2"<<"square centimetre";
	staVecUnit.push_back(cm2Unit);

	CXUnit ft2Unit(eArea, "ft2", "square foot", 0.09290304);
	ft2Unit.m_listSAlias<<"sq.ft."<<"sq ft"<<"ft^2"<<"square feet";
	staVecUnit.push_back(ft2Unit);

	CXUnit in2Unit(eArea, "in2", "square inch", 0.00064516);
	in2Unit.m_listSAlias<<"sq.in."<<"sq in"<<"in^2";
	staVecUnit.push_back(in2Unit);

	//	Volume units.
	CXUnit m3Unit(eVolume, "m3", "cubic metre");		//	Standard volume unit.
	m3Unit.m_listSAlias<<"stere"<<"cubic meter"<<"m^3";
	staVecUnit.push_back(m3Unit);

	CXUnit cm3Unit(eVolume, "cm3", "cubic centimetre", 0.000001);
	cm3Unit.m_listSAlias<<"cubic cm"<<"cm^3"<<"cubic centimeter"<<"cc"<<"milliliter"<<"ml";
	staVecUnit.push_back(cm3Unit);

	CXUnit ft3Unit(eVolume, "ft3", "cubic foot", 0.0283168);
	ft3Unit.m_listSAlias<<"cubic feet"<<"ft^3"<<"c.f."<<"cuft";
	staVecUnit.push_back(ft3Unit);

	CXUnit in3Unit(eVolume, "in3", "cubic inch", 0.000016387037037037);
	in3Unit.m_listSAlias<<"in^3"<<"cuin";
	staVecUnit.push_back(in3Unit);

	//	Weight units.
	CXUnit kgUnit(eWeight, "kg", "kilogram");		//	Standard weight unit.
	kgUnit.m_listSAlias<<"kilo";
	staVecUnit.push_back(kgUnit);

	CXUnit gUnit(eWeight, "g", "gram", 0.001);
	staVecUnit.push_back(gUnit);

	//	Gamma Ray
	CXUnit apiUnit(eGammaRay, "API", "GAPI");		//	Standard gamma ray unit.
	staVecUnit.push_back(apiUnit);

	//	Potential
	CXUnit mvUnit(ePotential, "mv", "millivolt");	//	Standard potential unit.
	staVecUnit.push_back(mvUnit);

	CXUnit vUnit(ePotential, "v", "volt", 1000);
	staVecUnit.push_back(vUnit);

	//	Porosity
	CXUnit poUnit(ePorosity, "%", "percent");	//	Standard porosity unit.
	poUnit.m_listSAlias<<"v/v";
	staVecUnit.push_back(poUnit);

	//	Density
	CXUnit kgm3Unit(eDensity, "kg/m3", "kilogram/cubic metre");	//	Standard density unit.
	kgm3Unit.m_listSAlias<<"kg/m^3";
	staVecUnit.push_back(kgm3Unit);

	CXUnit gccUnit(eDensity, "g/cc", "gram/cubic centimetre", 1000);
	gccUnit.m_listSAlias<<"g/cm^3"<<"g/cm3";
	staVecUnit.push_back(gccUnit);

	CXUnit baUnit(ePhotoelectric, "ba/e");			//	Standard photoelectric unit.
	staVecUnit.push_back(baUnit);

	CXUnit usmUnit(eTransitTime, "us/m");			//	Standard transit time unit.
	staVecUnit.push_back(usmUnit);

	CXUnit usfUnit(eTransitTime, "us/ft", "us/ft", 3.28084);
	staVecUnit.push_back(usfUnit);

	CXUnit smUnit(eTransitTime, "s/m", "s/m", 1000000);
	staVecUnit.push_back(smUnit);

	CXUnit sftUnit(eTransitTime, "s/ft", "s/ft", 3280840);
	staVecUnit.push_back(sftUnit);

	CXUnit ohmUnit(eTransitTime, "ohm.m");			//	Standard resistivity unit.
	ohmUnit.m_listSAlias<<"ohm*m"<<"ohmm";
	staVecUnit.push_back(ohmUnit);

	CXUnit ppmUnit(eGammaRaySpectral, "ppm");		//	Standard gamma ray spectral unit.
	staVecUnit.push_back(ppmUnit);

	CXUnit degUnit(eAngle, "deg", "degree");		//	Standard angle unit.
	staVecUnit.push_back(degUnit);

	return staVecUnit;
}