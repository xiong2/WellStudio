#ifndef GSBASEMAPVIEW_H
#define GSBASEMAPVIEW_H

#include <QGraphicsView>

class GSBasemapView : public QGraphicsView
{
	Q_OBJECT

public:
	GSBasemapView(QWidget *parent = Q_NULLPTR);
	~GSBasemapView();

signals:
	void ShowPositionInfo(const QPoint& pos, QGraphicsItem* pItem);

protected:
	void wheelEvent(QWheelEvent *) override;
	void mouseMoveEvent(QMouseEvent *) override;

private:
};

#endif // GSBASEMAPVIEW_H
