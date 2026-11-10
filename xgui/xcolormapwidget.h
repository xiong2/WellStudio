#ifndef _CXCOLORMAPWIDGET_H__
#define _CXCOLORMAPWIDGET_H__

#include "xgui_global.h"
#include <qwidget.h>

class XGUI_EXPORT CXColormapWidget : public QWidget
{
    Q_OBJECT

public:

	CXColormapWidget(QWidget* parent = 0);
	CXColormapWidget(QString strColormapName, QWidget* parent = 0, Qt::WindowFlags f = 0);

    virtual QSize sizeHint() const;

    void SetDisplayRange(qreal dMin, qreal dMax);
    void SetColormapName(const QString& name);

	QString GetColormapName() const { return m_strName; }

signals:
    void OpenColormapEditingDialog();
	void signalChangedColormap(const QString&);

protected:
	void paintEvent(QPaintEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
	void slotTableMenuRequest(const QPoint &);
	void slotChangeColormap();

    QString         m_strName;
	qreal			m_dMin;
	qreal			m_dMax;

private:
	void _Init();

private:
    const int m_margin = 10;
    const int m_rainbowWidth = 30;
    const int m_scaleWidth = 5;

    int m_textHeight = 0;
    int m_textWidth = 0;
};

#endif