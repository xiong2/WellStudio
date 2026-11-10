#ifndef XLICENSE_H
#define XLICENSE_H

#include <QtWidgets/QDialog>
#include "ui_xlicense.h"

class QLayout;

class CXLicense : public QDialog
{
	Q_OBJECT

public:
	CXLicense(QWidget *parent = 0);
	~CXLicense();

protected:
	bool eventFilter(QObject *o, QEvent *e) override;

private:
	void _Init();
	void _Load();
	void _Save();

	QLayout* _InitAppLayout();
	QStringList _FetchCheckedApps();
	void _AddedRandomPerturbation(QJsonObject& obj);
	void _AddedNoLimitsMark(QJsonObject& obj);
	void _ParseClipboard(QString &text);

private slots:
	void slotTest();
	void slotGenerate();
	void slotGenerateOld();
	void slotLocal();

private:
	Ui::CXLicenseClass ui;
};

#endif // KELICENSE_H
