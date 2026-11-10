#ifndef XCOLORMAPEDITOR_H
#define XCOLORMAPEDITOR_H

/*!
*  @class  CXColormapEditor in kecolormapeditor.h
*  @brief  widget for editing color map.
*  @author pezy
*  @date   2016-02-05
*/

#include <QWidget>
#include <QMenu>
#include "xbasicui_global.h"

class CXColormap;

class XBASICUI_EXPORT CXColormapEditor : public QWidget
{
    Q_OBJECT

public:
    CXColormapEditor(QWidget *parent = 0);
    ~CXColormapEditor();

	void SetColormap(const QString& colormapName);
	void SetHistogram(const QMap<double, double>& mapPercent);

signals:
    void ShowMsg(const QString& msg);
	void ColormapChanged();
	void MinValueChanged(double dMin);
	void MaxValueChanged(double dMax);

public slots:
    void slotReset();
    void slotFlip();
	void slotSetOpacityFreeDrawing(bool bChecked);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
	void slotAddControlPoint();
	void slotAddGeologicMask();
	void slotDeleteControlPointOrMask();
	void slotAllOpaque();
	void slotDeleteOpacityPoint();
	void slotAddOpacityPoint();
	void slotSetAsMin();
	void slotSetAsMax();

private:
    QPointF _ColorIndexToControlPos(int index);
	QPointF _IndexAlphaToOpacityPos(int index, int alpha);
    int _PosToColorIndex(const QPointF& pos);
	int _PosToAlpha(const QPointF& pos);
	int _PosToHistogramIndex(const QPointF& pos);

    void _DrawControlPoint(int index);
    void _DrawGeologicMask();
	void _DrawOpacityPoint();
    void _OpenControlMenu(QMenu& menu, const QPoint& pos);
	void _OpenOpacityMenu(QMenu& menu, const QPoint& pos);
    bool _IsInControlPoint(const QPoint& pos, int& controlIndex);
    bool _IsInGeologicMask(const QPoint& pos, int& maskIndex, QRgb& maskRgb);
	bool _IsInOpacityPoint(const QPoint& pos, int& controlIndex, int& alpha);

    void _ShowMenu(const QPoint& position, const QPoint& cursorPos);
    void _SetControlPointColor(const QPoint& position);
	void _SetGeologicMaskColor(const QPoint& position);
    void _ShowColorInfo(const QPoint& position);
	void _ShowHistogramDataRange(const QPoint& position);
    void _SelectControlPointOrMask(const QPoint& pos);
	void _BeginFreeDrawing(const QPoint& pos);

	void _SendChangeInfoAndUpdate();
	void _TransformToCustom();

private:
    const qreal m_controlRectHeight = 15.0;

    CXColormap* m_pColormap = nullptr;
	QString m_templateName;

    QRectF m_colorBarRect;
    QRectF m_controlRect;

    qreal m_singleColorBarWidth = 0.0;

    int m_selectedColorIndex = -1;
	int m_selectedHistogramIndex = -1;

    // change control point position
    bool m_bControlIndexChanged = false;
    QRgb m_selectedControlPointRgb = 0u;
    QList<int> m_listFixedControlPoints;

    // geologic mask
    bool m_bGeologicMaskChanged = false;
    QRgb m_selectedMaskRgb = 0u;
    QList<int> m_listFixedMask;

	// opacity
	int m_selectedAlpha = 255;
	bool m_bFreeDrawing = false;
	bool m_bDrawingStart = false;

	QMap<double, double> m_mapPercent;
	double m_maxPercent;
	qreal m_singleHistogramBarWidth = 0.0;
};

#endif // KECOLORMAPEDITOR_H
