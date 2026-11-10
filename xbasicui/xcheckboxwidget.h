#ifndef XCHECKBOXWIDGET_H
#define XCHECKBOXWIDGET_H

#include "xbasicui_global.h"
#include <QWidget>

class QCheckBox;

class XBASICUI_EXPORT CXCheckBoxWidget : public QWidget
{
	Q_OBJECT

public:
	CXCheckBoxWidget(QWidget *parent = Q_NULLPTR);
	~CXCheckBoxWidget();

	bool IsChecked() const;
	void SetChecked(bool bChecked);

signals:
	void StateChanged(int state);

private:
	QCheckBox* m_pCheckBox = nullptr;
};

#endif // XCHECKBOXWIDGET_H
