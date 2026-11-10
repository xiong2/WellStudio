#ifndef X2DSECTIONVIEW_H
#define X2DSECTIONVIEW_H

#include "xgraphicsview.h"
#include "xsectionwindow_global.h"

class QOpenGLWidget;
class CX2DSectionWindow;
class CXSectionDigitizingItem;
class CXSectionLineMode;
class CXTimeSliceItem;
class CXSectionScene;

class XSECTIONWINDOW_EXPORT CX2DSectionView : public CXGraphicsView 
{
public:
	CX2DSectionView(QGraphicsScene* scene, EXWindowType eWindowType, QWidget* parent = 0);
    ~CX2DSectionView();
    QOpenGLWidget* GetGLWidget() const;

protected:
    virtual void resizeEvent(QResizeEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
	void _InitGLWidget();

    CX2DSectionWindow* m_pMainWindow;
	CXSectionScene*	m_pScene;

    CXSectionDigitizingItem* m_pDigitizingItem;
    CXSectionLineMode* m_pSectionLineItem;
    CXTimeSliceItem* m_pSectionTimeSlice;

	QOpenGLWidget* m_pGLWidget;
};

#endif // RL2DSECTIONVIEW_H
