#ifndef XPAGEMAKEFAULTSTICKSBYSEISMICSECTIONFROMPOINTS_H
#define XPAGEMAKEFAULTSTICKSBYSEISMICSECTIONFROMPOINTS_H

#include <QDialog>
#include "ui_xpagemakefaultsticksbysurveyfrompoints.h"
#include "xgui_global.h"

class CX3DPoints;
class CXSeismicUTMTool;

/**
@class provided CXPageMakeFaultSticksBySeismicSectionFromPoints in the xpagemakefaultsticksbyseismicsectionfrompoints.h
@brief The class provides the dialog of making fault sticks by survey from points
@author pezy
@date 2017-08-22
@sa
*/
class XGUI_EXPORT CXPageMakeFaultSticksBySurveyFromPoints : public QDialog
{
	Q_OBJECT

public:
	CXPageMakeFaultSticksBySurveyFromPoints(CX3DPoints* pPoints, QWidget *parent = 0);
	~CXPageMakeFaultSticksBySurveyFromPoints();

private:
	void _Init();
	void _MappingData();
	void _OnSurveyChanged(int index);
	void _OnGenerate();

	Ui::CXPageMakeFaultSticksBySurveyFromPoints ui;

	CX3DPoints* m_pPoints = nullptr;
	CXSeismicUTMTool* m_pSelectedUTM = nullptr;
	std::map<int, std::map<int, std::vector<std::tuple<double, double, double>>>> m_mapTrace2Points;
};

#endif // XPAGEMAKEFAULTSTICKSBYSEISMICSECTIONFROMPOINTS_H
