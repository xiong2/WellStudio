#ifndef _GSSECTIONVIEW_H__
#define _GSSECTIONVIEW_H__

#include <QGraphicsView>

class GSSectionView : public QGraphicsView
{
	Q_OBJECT
public:
	GSSectionView(QWidget *parent = Q_NULLPTR);
	~GSSectionView();

protected:
	//void wheelEvent(QWheelEvent *) override;
	void mouseMoveEvent(QMouseEvent *) override;
};

#endif