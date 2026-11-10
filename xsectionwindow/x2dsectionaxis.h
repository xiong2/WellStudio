#ifndef X2DSECTIONAXIS_H
#define X2DSECTIONAXIS_H

#include <QWidget>
#include <QVector3D>
#include <vector>

using std::vector;

class CXObject;
class CXWell;
class QGridLayout;
class CXSectionScene;
class CXWindowInfoSection;
class CX2DSectionWindow;
class CX2DAxisHelper;

class CX2DSectionAxis : public QWidget
{
public:
	CX2DSectionAxis(QWidget* parent);
	~CX2DSectionAxis(void) {}

	CX2DAxisHelper* GetXAxis() const { return m_pAxisX; }
	CX2DAxisHelper* GetYAxis() const { return m_pAxisY; }

	void SetDisplaySection(CXObject *);
	void AddWidget(QWidget* pWidget);
	void AddWellName(QPair<CXWell*, double> wellName);
	void RemoveWellName(CXWell* pWell);


protected:
	virtual void paintEvent(QPaintEvent* event) override;

private:
	enum EDraw2DType
	{
		eProfile = 0,
		eSectionPoststack,
		eSectionPrestack,
		eRandomPrestack,
		eRandomPostack,
		e2DLine
	};

private:
	void _SetDataTypeandResetDrawData();
	void _Draw(QPainter* painter);
	void _DrawY(QPainter* painter);


	void _SetSectionPrestack();
	void _SetSectionPostStack();
	void _SetRandomPrestack();
	void _SetRandomPoststack();
	void _Set2DLine();

	void _SetXYAxis();

	void _DrawIndexedXAxis(QPainter* painter);
	void _DrawContinuousXAxis(QPainter* painter);

private:
	CXObject* m_pObject = nullptr;

	EDraw2DType m_eType;
	CX2DAxisHelper* m_pAxisX = nullptr;
	CX2DAxisHelper* m_pAxisY = nullptr;
	vector<double> m_vecXValue;
	vector<double> m_vecYValue;
	vector<vector<double> > m_vec2DCoord;
	QStringList m_listXAxisName;


	QList<QPair<CXWell*, double>> m_displayedWellList;
	QGridLayout* m_pLayout = nullptr;

	CX2DSectionWindow* m_pWindow;
	CXSectionScene *m_pScene;
	CXWindowInfoSection* m_pWindowInfo;
};

#endif // KE2DSECTIONAXIS_H