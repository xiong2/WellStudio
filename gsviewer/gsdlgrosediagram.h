#ifndef GSDLGROSEDIAGRAM_H
#define GSDLGROSEDIAGRAM_H

#include <QDialog>
#include "ui_gsdlgrosediagram.h"

class GSStressMap;
class GSBMItemDefineRose;

class gsdlgrosediagram : public QDialog
{
	Q_OBJECT

public:
	gsdlgrosediagram(GSStressMap *, GSBMItemDefineRose *, QWidget *parent = 0);
	~gsdlgrosediagram();

	void accept() override;
	void reject() override;

private slots:
	void slotChangeRadius(int);
	void slotUseWell();
	void slotSelectWell(const QString &);

private:
	Ui::gsdlgrosediagram ui;

	GSStressMap*			m_pMap;
	GSBMItemDefineRose*		m_pItem;
};

#endif // GSDLGROSEDIAGRAM_H
