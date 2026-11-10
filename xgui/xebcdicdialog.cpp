#include "xebcdicdialog.h"

#include <QGridLayout>

#include "xglobal.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QApplication>

/*
 *  Constructs a CXEBCDICDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
CXEBCDICDialog::CXEBCDICDialog( QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl )
    : QDialog( parent, fl )
{
	setWindowIcon(QIcon(QString::fromUtf8(":/icon/Product.png")));
	this->setObjectName(QString::fromUtf8("CXEBCDICDialog"));
    this->resize(QSize(594, 440).expandedTo(this->minimumSizeHint()));
    this->setSizeGripEnabled(true);
    //this->setModal(true);
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(5);
    gridLayout->setMargin(5);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    table = new QTableWidget(this);
	table->horizontalHeader()->setHidden(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	table->horizontalHeader()->setStretchLastSection(true);
	table->verticalHeader()->setHidden(true);
    table->setObjectName(QString::fromUtf8("table"));
    table->setFrameShape(QFrame::WinPanel);
    table->setFrameShadow(QFrame::Sunken);
    table->setLineWidth(3);
    table->setRowCount(40);
    table->setColumnCount(1);
    table->setShowGrid(true);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QTableWidgetItem *pTableItem = NULL;
	for(int i=0;i<40;i++)
	{	
		pTableItem = new QTableWidgetItem();
		table->setItem(i,0,pTableItem);
	}
	table->setShowGrid(false);
    gridLayout->addWidget(table, 0, 0, 1, 1);
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    okButton = new QPushButton(this);
    okButton->setObjectName(QString::fromUtf8("okButton"));
    hboxLayout->addWidget(okButton);

    gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);
	QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(OnOk()));

    languageChange();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CXEBCDICDialog::~CXEBCDICDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CXEBCDICDialog::languageChange()
{
    setWindowTitle(QApplication::translate("CXEBCDICDialog", "EBCDIC Header", nullptr));
    okButton->setText(QApplication::translate("CXEBCDICDialog", "Close", nullptr));
}

void CXEBCDICDialog::SetEBCDIC(char *pReelEBCDIC)
{
	if(pReelEBCDIC == NULL) return;
	memcpy(m_pReelEBCDIC,pReelEBCDIC,3200);
	QString tempStr = "";
	QTableWidgetItem *pTableItem = NULL;
	int i;
	for (i=0;i<40;i++)
	{
		tempStr = QString::fromLatin1(pReelEBCDIC+i*80, 80);
		pTableItem = table->item(i,0);
		pTableItem->setText(tempStr);
	}
}

void CXEBCDICDialog::OnOk()
{
	int i,j;
	QString tempStr = "";
	QString str;
	memset(m_pReelEBCDIC,'\0',3200);
	QTableWidgetItem *pTableItem = NULL;
	for(i=0;i<40;i++)
	{
		
		pTableItem = table->item(i,0);
		tempStr = pTableItem->text();
		if(tempStr.size()<80) 
		{
			for(j=0;j<80-tempStr.size();j++) str.append(' ');
			tempStr.insert(tempStr.size(),str);
		}
		else
			tempStr.truncate(80);
		str.clear();
		memcpy(m_pReelEBCDIC+i*80,(char *)tempStr.toLatin1().constData(),80);
	}
	QDialog::accept();
}
