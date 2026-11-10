#include "xdlgcalculator.h"

#include <qfiledialog.h>
#include <qmessagebox.h>
#include <QClipboard>
#include <QSettings>
#include <QTextStream>

#include "xglobal.h"
#include "xobject.h"
#include "xtemplate.h"
#include "xobjcalculator.h"
#include "xdvcalculator.h"
#include "xtree.h"
#include "xbaseconsole.h"
#include "xseismicdatavolume.h"

CXDlgCalculator::CXDlgCalculator(QUuid objectID, QWidget *parent): QDialog(parent)
{
	ui.setupUi(this);
	m_objectID = objectID;
	CXObject  *pObj = ::GetObjectByID(m_objectID);

	if (pObj->GetObjectType() == EXSeismicDataVolume)
		m_pCalculator = new CXDVCalculator(objectID);
	else
		m_pCalculator = new CXObjCalculator(objectID);

	initTextMap();
	connectTbnSignal();
	initVariableTree();
	setWindowIcon(QIcon(::GetIconPath() + "Calculator.png"));

	ui.comboBox->addItems(CXTemplate::GetAllTemplates());

	ui.m_VaribleTree->header()->setHidden(true);
	ui.m_VaribleTree->setMouseTracking(true);
	ui.m_VaribleTree->header()->setStretchLastSection(false);
    ui.m_VaribleTree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

	m_strDisplaySelectedText = "";
	m_nCurPos = -1;
	m_nStartPos = -1;
	this->setAttribute(Qt::WA_DeleteOnClose);
	QString strPath = ::GetIconPath();
	QString strHelpTips = m_pCalculator->GetHelpTips();
	ui.m_LblHelp->setPixmap(QPixmap(strPath +"Question4.png"));
	ui.m_LblHelp->setToolTip(strHelpTips);
	_readHistory();
}

CXDlgCalculator::~CXDlgCalculator()
{
	delete m_pCalculator;
}

void CXDlgCalculator::connectTbnSignal()
{
	QList<QToolButton*>listToolButton =  m_MapToText.keys();
	foreach(QToolButton* pTbn,listToolButton)
	{
		connect(pTbn,SIGNAL(clicked()),this,SLOT(slotTbnClicked()));
	}
	connect(ui.m_TbnEnter,SIGNAL(clicked()),this,SLOT(slotEnterClicked()));
	connect(ui.m_TbnClear,SIGNAL(clicked()),this,SLOT(slotClearClicked()));
	connect(ui.m_TbnBackSpace,SIGNAL(clicked()),this,SLOT(slotBackspace()));
	connect(ui.m_TbnBrowse,SIGNAL(clicked()),this,SLOT(slotBrowseClicked()));
	connect(ui.m_TbnCopy,SIGNAL(clicked()),this,SLOT(slotCopyClicked()));
	connect(ui.m_TbnClearShowView,SIGNAL(clicked()),this,SLOT(slotLsClearClicked()));
	connect(ui.m_VaribleTree,SIGNAL(itemClicked(QTreeWidgetItem *, int)),this,SLOT(slotVariableItemClicked( QTreeWidgetItem *)));
	connect(ui.m_VaribleTree,SIGNAL(itemEntered(QTreeWidgetItem *, int)),this,SLOT(slotVariableItemEntered()));
	connect(ui.m_EdtFunctionDisplay,SIGNAL(cursorPositionChanged (int, int)),this,SLOT(slotDisplayCorPosChanged()));

	connect(ui.m_TbnDeg,SIGNAL(clicked()),this,SLOT(slotDegTypeClicked()));
	connect(ui.m_RdoRad,SIGNAL(clicked()),this,SLOT(slotDegTypeClicked()));
	connect(ui.m_RdoGrad,SIGNAL(clicked()),this,SLOT(slotDegTypeClicked()));
	
	connect(ui.m_LsResultShow,SIGNAL(itemDoubleClicked ( QListWidgetItem *)),this,SLOT(slotResultItemClicked(QListWidgetItem * )));

	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetOutputTemplate(int)));
}
void CXDlgCalculator:: slotDegTypeClicked()
{
	QRadioButton *pRdo = (QRadioButton*)sender();
	if(pRdo->text() == "Degrees")
	{
		m_pCalculator->SetDegreeType(0);
	}
	else if(pRdo->text() == "Radians")
	{
		m_pCalculator->SetDegreeType(1);
	}
	else 
	{
		m_pCalculator->SetDegreeType(2);
	}
}

void CXDlgCalculator::slotSetOutputTemplate(int)
{
	m_pCalculator->SetOutputTemplate(ui.comboBox->currentText());
}

void CXDlgCalculator::slotDisplayCorPosChanged()
{	
	m_strDisplaySelectedText = ui.m_EdtFunctionDisplay->selectedText();
	m_nCurPos = ui.m_EdtFunctionDisplay->cursorPosition();
	m_nStartPos = ui.m_EdtFunctionDisplay->selectionStart();
}

void CXDlgCalculator::addAnItemToVaribleTree(QUuid objID)
{
	CXObject *pObj = ::GetObjectByID(objID);
	if(!pObj)
		return;

	QTreeWidgetItem * item = new QTreeWidgetItem(ui.m_VaribleTree);
	item->setText(0, pObj->GetObjectName());
	item->setIcon(0, QPixmap(::GetIconPath() + pObj->GetIconName()));
	item->setData(0, Qt::UserRole, QVariant(objID));
}

void CXDlgCalculator::initVariableTree()
{
	QList<CXObject *> listObj;
	CXObject  *pObj = ::GetObjectByID(m_objectID);
	if(pObj->GetObjectType() == EXWell)
	{
		listObj = pObj->GetChildren(EXWellCurve);
	}
	else if (pObj->GetObjectType() == EXSeismicDataVolume)
	{
		CXSeismicDataVolume *pDV = (CXSeismicDataVolume *)pObj;
		pDV->GetAllDVWithSameSize(listObj);
	}
	else
	{
		listObj = pObj->GetChildrenList();
	}

	for(int i = 0; i < listObj.size(); i++)
	{
		addAnItemToVaribleTree(listObj[i]->GetObjectID());
	}
}

void CXDlgCalculator::slotVariableItemEntered()
{
	m_strDisplaySelectedText = ui.m_EdtFunctionDisplay->selectedText();
	m_nCurPos = ui.m_EdtFunctionDisplay->cursorPosition();
	m_nStartPos = ui.m_EdtFunctionDisplay->selectionStart();
}

void CXDlgCalculator::slotVariableItemClicked( QTreeWidgetItem * pItem)
{
	if(!pItem->isSelected())
		return;
	int nSetPos;
	QString strItemText = pItem->text(0);
	QString strDisplayText = ui.m_EdtFunctionDisplay->text();
	if(!m_strDisplaySelectedText.isEmpty())
	{
		int nMin = qMin(m_nStartPos,m_nCurPos);
		strDisplayText = strDisplayText.remove(nMin,m_strDisplaySelectedText.length());
		strDisplayText = strDisplayText.insert(nMin,strItemText);
		nSetPos = nMin+strItemText.length();	
	}
	else
	{
		strDisplayText = strDisplayText.insert(m_nCurPos,strItemText);
		nSetPos = m_nCurPos+strItemText.length();
	}

	ui.m_EdtFunctionDisplay->setText(strDisplayText);//back space all select text
	ui.m_EdtFunctionDisplay->setCursorPosition(nSetPos);//set corsor position
	m_nStartPos = -1;
	m_nCurPos = nSetPos;
	ui.m_EdtFunctionDisplay->setFocus();//restore focus
}

void CXDlgCalculator::slotLsClearClicked()
{
	//m_ui.m_LsResultShow->clear();
	//EGmObjectType eCalType = m_pNode->GetCGmObject()->GetObjType();
	//QString strFileName = ::GetDBEngine()->GetDBTreeEngine()->GetObjTypeName(eCalType)+".txt";
	//QString strProPath = ::GetProjectPath();
	//QDir proDir(strProPath);
	//if(proDir.exists(strFileName))
	//{
	//	QFile file(strProPath+"\\"+strFileName);
	//	file.open(QIODevice::WriteOnly|QIODevice::Truncate | QIODevice::Text);
	//}

}
void CXDlgCalculator::slotClearClicked()
{
	ui.m_EdtFunctionDisplay->clear();
}

void CXDlgCalculator::slotCopyClicked()
{
	QClipboard *clipboard = QApplication::clipboard();
	if(ui.m_LsResultShow->currentItem() != NULL)
	{
		clipboard->setText(ui.m_LsResultShow->currentItem()->text());
	}
}

void CXDlgCalculator::slotResultItemClicked(QListWidgetItem *  pItem)
{
	ui.m_EdtFunctionDisplay->clear();
	ui.m_EdtFunctionDisplay->setText( pItem->text());
	ui.m_EdtFunctionDisplay->setFocus();
}

void CXDlgCalculator::slotBrowseClicked()
{
	QString strFilePath ;
	QSettings settings("XStudio", "Last Used Dir" );
	settings.beginGroup("Calculator");
	strFilePath = settings.value("From Dir").toString();
	if(strFilePath.isEmpty())
	{
		strFilePath = QFileDialog::getOpenFileName(this,"Open file","","XStudio macro file (*.txt)");
	}
	else
	{
		QFileInfo fileInfo(strFilePath);
		strFilePath = fileInfo.absoluteDir().absolutePath();
		strFilePath = QFileDialog::getOpenFileName(this,"Open file",strFilePath,"XStudio macro file (*.txt)");
	}
	if(!strFilePath.isEmpty())
	{	
		strFilePath = QDir::toNativeSeparators(strFilePath);
		QFile qFile(strFilePath);
		if(!qFile.open(QIODevice::ReadOnly))
		{
			QMessageBox::critical(NULL, "Calculator Error", "Can not open the selected file!");
			return;
		}

		QByteArray qBA = qFile.readAll();
		QString strExp(qBA);
		ui.m_EdtFunctionDisplay->setText(strExp);

		qFile.close();
	}
	settings.setValue("From Dir",strFilePath);
	settings.endGroup();
}

void CXDlgCalculator::slotBackspace()
{	
	int nCurPos = ui.m_EdtFunctionDisplay->cursorPosition();
	QString strDisplayText = ui.m_EdtFunctionDisplay->text();
	if(ui.m_EdtFunctionDisplay->hasSelectedText())
	{
		int nStartPos = ui.m_EdtFunctionDisplay->selectionStart();
		QString strSelectText = ui.m_EdtFunctionDisplay->selectedText();
		int nMin = qMin(nStartPos,nCurPos);
		strDisplayText = strDisplayText.remove(nMin,strSelectText.length());
		nCurPos = nMin;
	}
	else
	{		
		nCurPos = nCurPos-1;
		if(nCurPos >=0)
		{
			strDisplayText = strDisplayText.remove(nCurPos,1);
		}
	}
	ui.m_EdtFunctionDisplay->setText(strDisplayText);//back space all select text
	ui.m_EdtFunctionDisplay->setCursorPosition(nCurPos);//set corsor position
	m_nStartPos = -1;
	m_nCurPos = nCurPos;
	ui.m_EdtFunctionDisplay->setFocus();//restore focus
}
void CXDlgCalculator::_setDisplayFocus(QString strTbnText)
{
    QString strSelectText = ui.m_EdtFunctionDisplay->selectedText();
	QString strDisplayText = ui.m_EdtFunctionDisplay->text();
	int nCurPos =ui.m_EdtFunctionDisplay->cursorPosition();
	if(!strSelectText.isEmpty())
	{
		int nStartPos = ui.m_EdtFunctionDisplay->selectionStart();
		int nMin = qMin(nStartPos,nCurPos);
		strDisplayText = strDisplayText.remove(nMin,strSelectText.length());
		strDisplayText = strDisplayText.insert(nMin,strTbnText);
		nCurPos = nMin;	
	}
	else
	{
		strDisplayText = strDisplayText.insert(nCurPos,strTbnText);
	}
	if(strTbnText.contains(QChar('(')))
	{
		 nCurPos = nCurPos+strTbnText.lastIndexOf(QChar('('))+1;
	}
	else
	{
		nCurPos = nCurPos+strTbnText.length();
	}
	ui.m_EdtFunctionDisplay->setText(strDisplayText);//set display text
	ui.m_EdtFunctionDisplay->setCursorPosition(nCurPos);//set corsor position
	m_nCurPos = nCurPos;
	m_nStartPos = -1;
	ui.m_EdtFunctionDisplay->setFocus();//restore focus

}
void CXDlgCalculator::slotTbnClicked()
{
	QToolButton* pClickedTbn = dynamic_cast<QToolButton*>(sender());
	QString strTbnText = m_MapToText.value(pClickedTbn);
	_setDisplayFocus(strTbnText);
}

void CXDlgCalculator::initTextMap()
{
	//digit button
	m_MapToText[ui.m_Tbn0] = "0";
	m_MapToText[ui.m_Tbn1] = "1";
	m_MapToText[ui.m_Tbn2] = "2";
	m_MapToText[ui.m_Tbn3] = "3";
	m_MapToText[ui.m_Tbn4] = "4";
	m_MapToText[ui.m_Tbn5] = "5";
	m_MapToText[ui.m_Tbn6] = "6";
	m_MapToText[ui.m_Tbn7] = "7";
	m_MapToText[ui.m_Tbn8] = "8";
	m_MapToText[ui.m_Tbn9] = "9";
	m_MapToText[ui.m_TbnDot] = ".";
	m_MapToText[ui.m_TbnU] = "Inv";
	m_MapToText[ui.m_TbnPi] = "3.1415926535898";
	
	m_MapToText[ui.m_TbnRand] = "Rand";
	m_MapToText[ui.m_TbnRandn] = "Randn";
	//math
	m_MapToText[ui.m_TbnRound] = "Round()";
	m_MapToText[ui.m_TbnSqrt] = "Sqrt()";
	m_MapToText[ui.m_TbnSin] = "Sin()";
	m_MapToText[ui.m_TbnAbs] = "Abs()";
	m_MapToText[ui.m_TbnInt] = "Int()";
	m_MapToText[ui.m_TbnCos] = "Cos()";
	m_MapToText[ui.m_TbnExp] = "Exp()";
	m_MapToText[ui.m_TbnLn] = "Ln()";
	m_MapToText[ui.m_TbnTan] = "Tan()";
	m_MapToText[ui.m_TbnCTan] = "Ctan()";
	m_MapToText[ui.m_TbnPow] = "Pow(,)";
	m_MapToText[ui.m_TbnLog] = "Log()";
	m_MapToText[ui.m_TbnIf] = "If(){ } else { }";
	m_MapToText[ui.m_TbnAnd] = "And";
	m_MapToText[ui.m_TbnOr] = "Or";
	
	m_MapToText[ui.m_TbnASin] = "Asin()";
	m_MapToText[ui.m_TbnACos] = "Acos()";
	m_MapToText[ui.m_TbnATan] = "Atan()";
	m_MapToText[ui.m_TbnAcTan] = "Actan()";
	//Statistic
	m_MapToText[ui.m_TbnNum] = "Num()";
	m_MapToText[ui.m_TbnSum] = "Sum()";
	m_MapToText[ui.m_TbnStd] = "Std()";
	m_MapToText[ui.m_TbnMin] = "Min()";
	m_MapToText[ui.m_TbnMax] = "Max()";
	m_MapToText[ui.m_TbnMean] = "Mean()";
	//maker symbol
	m_MapToText[ui.m_TbnDivide] = "/";
	m_MapToText[ui.m_TbnMultiply] = "*";
	m_MapToText[ui.m_TbnSubtract] = "-";
	m_MapToText[ui.m_TbnAddition] = "+";
	m_MapToText[ui.m_TbnLbracket] = "(";
	m_MapToText[ui.m_TbnLessthan] = "<";
	m_MapToText[ui.m_TbnMorethan] = ">";
	m_MapToText[ui.m_TbnCast] = "<>";
	m_MapToText[ui.m_TbnRbracket] = ")";
	m_MapToText[ui.m_TbnLessAndEqual] = "<=";
	m_MapToText[ui.m_TbnMoreAndEqual] = ">=";
	m_MapToText[ui.m_TbnEqual] = "=";
}

void CXDlgCalculator::slotEnterClicked()
{
	QString strExp = ui.m_EdtFunctionDisplay->text();
	double fVal = -1; 
	CXObject *pResObj = m_pCalculator->Calculate(strExp, fVal);

	if(pResObj)
	{
		::AddObjectEvent(pResObj);
		ui.m_LsResultShow->addItem(strExp);
		strExp = "";
		addAnItemToVaribleTree(pResObj->GetObjectID());
	}
	else if(fVal != g_dInvalidData)
	{
		ui.m_LsResultShow->addItem(strExp);
		strExp = QString::number(fVal);
	}
	else
	{
	}

	ui.m_EdtFunctionDisplay->setText(strExp);	
	ui.m_EdtFunctionDisplay->setSelection(0,ui.m_EdtFunctionDisplay->maxLength());
}

void  CXDlgCalculator::closeEvent(QCloseEvent * pEvent)
{
	_writeHistory();

	CXBaseConsole *pConsole = (CXBaseConsole *)(::GetConsole());
	pConsole->CloseCalculator(m_objectID);

	QDialog::closeEvent(pEvent);
}

void CXDlgCalculator::_writeHistory()
{
	QString strFileName = ::GetProjectPath() + "/calculatorHistory.txt";
	QFile file(strFileName);
	if(file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		for(int i = 0 ;i < ui.m_LsResultShow->count() ; ++i)
		{
            QListWidgetItem *pItem = ui.m_LsResultShow->item(i);
			QString strText = pItem->text() + "\n";
			file.write(strText.toLatin1().constData());
		}

		file.close();
	}
}

void CXDlgCalculator::_readHistory()
{
	QString strFileName = ::GetProjectPath() + "/calculatorHistory.txt";
	QFile file(strFileName);
	if(file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in(&file);
		while (!in.atEnd()) 
		{
			QString strline = in.readLine();
			ui.m_LsResultShow->addItem(strline);
		}

		file.close();
	}
}