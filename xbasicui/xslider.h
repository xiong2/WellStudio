#ifndef XSLIDER_H
#define XSLIDER_H

#include <QSlider>
#include "xbasicui_global.h"

class CXSliderPrivate;
/**
* @brief CXSlider provides two sliders within one widget
*/
class XBASICUI_EXPORT CXSlider : public QSlider
{
	Q_OBJECT
public:
	explicit CXSlider(QWidget* parent = 0);
	explicit CXSlider(Qt::Orientation orientation, QWidget* parent = 0);
	virtual ~CXSlider();

	enum HandleMovementMode
	{
		FreeMovement,
		NoCrossing,
		NoOverlapping
	};

	enum RangeHandle
	{
		NoHandle,
		MinHandle,
		MaxHandle
	};

	HandleMovementMode handleMovementMode() const;
	void setHandleMovementMode(HandleMovementMode mode);

	int minValue() const;
	int maxValue() const;

public slots:
	void setMinValue(int min);
	void setMaxValue(int max);
	void SetRange(int min, int max);
	void setMinPosition(int min);
	void setMaxPosition(int max);

private slots:
	void slotMovePressedHandle();
	
signals:
	void minValueChanged(int min);
	void maxValueChanged(int max);

	void minPositionChanged(int min);
	void maxPositionChanged(int max);

	void sliderPressed(RangeHandle handle);

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);
	int minPosition() const;
	int maxPosition() const;
private:
	CXSliderPrivate* m_pSliderPrivate;
	friend class CXSliderPrivate;

};

#endif // KESLIDER_H
