#ifndef XCOLORMAPEDITOR_H
#define XCOLORMAPEDITOR_H

#include <QWidget>
#include <QMap>
#include "xbasicui_global.h"

/*!
 * \class CXColormapEditor
 *
 * \brief widget of color map editor, include histogram, rainbow and axis.
 *
 * \author PEZY
 * \date Sept. 2014
 */

class CXObject;
class CXAxis;
class CXColormap;
class QMenu;
class CXButtonColorEdit;

class XBASICUI_EXPORT CXColormapViewer : public QWidget
{
	Q_OBJECT

public:
	explicit CXColormapViewer(QWidget *parent = 0);
	~CXColormapViewer();

	//! users should set following parameters.
	void SetDisplayedObject(CXObject* pObj);
	void SetDisplayedRange(double dMin, double dMax);
	void SetColormap(QString colormapName);
	void SetStatic(bool bStatic = true);

	void Update();

signals:
	void DisplayedRangeChanged(double dMin, double dMax);

protected:
	virtual void paintEvent(QPaintEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *) override;

public slots:
	void slotDisplayMinChanged(const QString& strMin);
	void slotDisplayMaxChanged(const QString& strMax);
	void slotTemplateChanged(int index);
	void slotReverse(int state);
	void slotReset();

private slots:
	void slotColorEdited(const QColor& c);

private:
	void _drawXAxis(QPainter *pDC,QRect rect);
	void _drawYAxis(QPainter *pDC,QRect rect);
	void _drawHistogram(QPainter* pDC,QRect rect);
	bool _hasInMarkMap(QMap<double, QColor>::iterator iBeg, QMap<double, QColor>::iterator iEnd, QMap<double, QColor>::iterator& it);
	QColor _getCustomColor(int pos) const;

private:
	CXObject *m_pObj = nullptr;			/**< The object which is painted.*/
	CXAxis *m_XAxis = nullptr;
	CXAxis *m_YAxis = nullptr;
	QRect m_rect;
	CXColormap *m_curColormap = nullptr;	/**< Current colormap template. */

	double m_dDisplayMinValue = 0.0;	/**< display colormap's min value */
	double m_dDisplayMaxValue = 0.0;	/**< display colormap's max value */

	bool m_draggingLeft = false;		/**< state of the left cursor. */
	bool m_draggingRight = false;		/**< state of the right cursor. */

	bool m_bReverse = false;			/**< state whether reverse. */
	QMap<double, QColor> m_mapColorMark;	/**< custom color list by user. */

	QMenu *m_menuEditColor;		/**< menu to change the color */
	CXButtonColorEdit *m_colorEdit;	/**< color edit widget */
	QMap<double, QColor>::iterator m_iterCurrentEdit;	/**< current editing color */
	bool m_bCustom = false;
	bool m_bStatic = false;
};

#endif // RLCOLORMAPEDITOR_H
