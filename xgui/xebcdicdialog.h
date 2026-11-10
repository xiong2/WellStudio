/****************************************************************************
** Form interface generated from reading m_ui file '.\gmebcdicdialog.m_ui'
**
** Created: Sun Jun 26 19:24:57 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.1   edited Nov 24 13:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef __RLEBCDICDIALOG_H__
#define __RLEBCDICDIALOG_H__
#include <QDialog>

class QTableWidget;
class QSpacerItem;
class QGridLayout;
class QHBoxLayout;

class  CXEBCDICDialog : public QDialog
{
    Q_OBJECT

public:
    CXEBCDICDialog( QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0 );
    ~CXEBCDICDialog();

    QTableWidget *table;
    QSpacerItem *spacerItem;
    QPushButton *okButton;

	char m_pReelEBCDIC[3200];
	void SetEBCDIC(char *pReelEBCDIC);

protected:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
protected slots:
    virtual void languageChange();
	void OnOk();
};

#endif // __RLEBCDICDIALOG_H__
