#ifndef XSUBGRIDSETTING_H
#define XSUBGRIDSETTING_H

/**
* @class CXSubGridSetting in the file "kesubgridsetting.h "
* @brief The class is a GUI dialog for setting Sub-Grid model geometry.
* 
* @author PEZY
* @date Nov. 26, 2014
* @see CX3DGridModelBuilder and CX3DScene
*/

#include <QDialog>
namespace Ui { class CXSubGridSetting; };

class CX3DWindow;
class CXGridModel;
class CXViewInfo3DGridModel;

class CXSubGridSetting : public QDialog
{
	Q_OBJECT

public:
	CXSubGridSetting(QWidget *parent, CX3DWindow *curWin);
	~CXSubGridSetting();

private:
	void _Init();

private slots:
	void slotSetMinILimit(int value);
	void slotSetMinJLimit(int value);
	void slotSetMinKLimit(int value);

	void slotSetMinI(int value);
	void slotSetMinJ(int value);
	void slotSetMinK(int value);
	void slotSetMaxI(int value);
	void slotSetMaxJ(int value);
	void slotSetMaxK(int value);

	void slotReset();

private:
	Ui::CXSubGridSetting *ui;
	CX3DWindow *m_curWin;
	CXGridModel *m_obj;
	CXViewInfo3DGridModel *m_viewInfo;
};

#endif // RLSUBGRIDSETTING_H
