#include "xcreateseisworkarea.h"
#include "x3dsurvey.h"
#include "xseismicutmtool.h"
#include "xglobal.h"
#include "xproject.h"
#include "xtree.h"
#include <QMessageBox>
#include <QFileDialog>
#include <algorithm>
#include <QVector2D>
#include <QtMath>
#include <qvalidator.h>

CXCreateSeisWorkArea::CXCreateSeisWorkArea(QWidget*parent) :CXBaseDialog(parent)
{
	m_Ui.setupUi(this);
	this->GetMainLayout()->addLayout(m_Ui.gridLayout_4, 0, 0, 1, 2);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("Create Seismic Work Area");

	connect(m_Ui.btn_save, &QPushButton::pressed, this, &CXCreateSeisWorkArea::slotSave);
	connect(m_Ui.btn_load, &QPushButton::pressed, this, &CXCreateSeisWorkArea::slotLoad);
	connect(m_Ui.m_pBtnPreview, SIGNAL(clicked()), this, SLOT(slotPreView()));

	// set input data validator
	QDoubleValidator *pDoubleValidator = new QDoubleValidator(this);
	QIntValidator *pIntValidator = new QIntValidator(this);
	//Point 1
	m_Ui.m_EdtInlinePoint1->setValidator(pIntValidator);
	m_Ui.m_EdtCrossLinePoint1->setValidator(pIntValidator);
	m_Ui.m_EdtXPoint1->setValidator(pDoubleValidator);
	m_Ui.m_EdtYPoint1->setValidator(pDoubleValidator);

	//Point 2
	m_Ui.m_EdtInlinePoint2->setValidator(pIntValidator);
	m_Ui.m_EdtCrossLinePoint2->setValidator(pIntValidator);
	m_Ui.m_EdtXPoint2->setValidator(pDoubleValidator);
	m_Ui.m_EdtYPoint2->setValidator(pDoubleValidator);

	//Point 3
	m_Ui.m_EdtInlinePoint3->setValidator(pIntValidator);
	m_Ui.m_EdtCrossLinePoint3->setValidator(pIntValidator);
	m_Ui.m_EdtXPoint3->setValidator(pDoubleValidator);
	m_Ui.m_EdtYPoint3->setValidator(pDoubleValidator);

	//Grid information

	m_Ui.m_EdtFirstInline->setValidator(pIntValidator);
	m_Ui.m_EdtInlineNumber->setValidator(pIntValidator);
	m_Ui.m_EdtFirstCrossLine->setValidator(pIntValidator);
	m_Ui.m_EdtCrosslineNumber->setValidator(pIntValidator);
	m_Ui.m_EdtInlineSpace->setValidator(pDoubleValidator);
	m_Ui.m_EdtInlineSpace->setValidator(pDoubleValidator);

	m_Ui.m_EdtInLineInc->setValidator(pIntValidator);
	m_Ui.m_pEdtCrossLineInc->setValidator(pIntValidator);

	connect(m_Ui.m_EdtInlinePoint1, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));
	connect(m_Ui.m_EdtInlinePoint2, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));
	connect(m_Ui.m_EdtInlinePoint3, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));
	connect(m_Ui.m_EdtInLineInc, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));
	connect(m_Ui.m_pEdtCrossLineInc, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));
	connect(m_Ui.m_EdtCrossLinePoint1, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));
	connect(m_Ui.m_EdtCrossLinePoint2, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));
	connect(m_Ui.m_EdtCrossLinePoint3, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));

	connect(m_Ui.m_EdtXPoint1, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));
	connect(m_Ui.m_EdtXPoint2, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));
	connect(m_Ui.m_EdtXPoint3, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));
	connect(m_Ui.m_EdtYPoint1, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));
	connect(m_Ui.m_EdtYPoint2, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));
	connect(m_Ui.m_EdtYPoint3, SIGNAL(textChanged(const QString &)), this, SLOT(slotPreViewEnabled()));

	SetOKEnabled(false);
}

CXCreateSeisWorkArea::~CXCreateSeisWorkArea(void)
{
}

void CXCreateSeisWorkArea::OnOK()
{
	//	Get an unique name first.
	QString strSurveyName = m_Ui.m_pEdtSurveyName->text();
	CXProject *pProject = ::GetProject();
	strSurveyName = pProject->GetUnallocatedName(strSurveyName);

	CX3DSurvey *pSurvey = new CX3DSurvey(m_utm, strSurveyName);
	pProject->AddChild(pSurvey);

	::AddObjectEvent(pSurvey);
}

void CXCreateSeisWorkArea::slotPreViewEnabled()
{
	bool  bDisabled = (m_Ui.m_EdtInlinePoint1->text().isEmpty() ||
		m_Ui.m_EdtCrossLinePoint1->text().isEmpty() ||
		m_Ui.m_EdtXPoint1->text().isEmpty() ||
		m_Ui.m_EdtYPoint1->text().isEmpty() ||
		m_Ui.m_EdtInlinePoint2->text().isEmpty() ||
		m_Ui.m_EdtCrossLinePoint2->text().isEmpty() ||
		m_Ui.m_EdtXPoint2->text().isEmpty() ||
		m_Ui.m_EdtYPoint2->text().isEmpty() ||
		m_Ui.m_EdtInlinePoint3->text().isEmpty() ||
		m_Ui.m_EdtCrossLinePoint3->text().isEmpty() ||
		m_Ui.m_EdtXPoint3->text().isEmpty() ||
		m_Ui.m_EdtYPoint3->text().isEmpty() ||
		m_Ui.m_EdtInLineInc->text().isEmpty() ||
		m_Ui.m_pEdtCrossLineInc->text().isEmpty());

	m_Ui.m_pBtnPreview->setEnabled(!bDisabled);
}

void CXCreateSeisWorkArea::slotSave()
{
	QString strName = QFileDialog::getSaveFileName(this);
	QFile file(strName);
	if (!file.open(QFile::WriteOnly))
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(), tr("Cannot write file %1:\n%2.").arg(QDir::toNativeSeparators(strName), file.errorString()));
		return;
	}

	QDataStream out(&file);

	out << (quint32)0xF1E2D3C4;
	out << (qint32)100;

	out << m_Ui.m_EdtInlinePoint1->text();
	out << m_Ui.m_EdtCrossLinePoint1->text();
	out << m_Ui.m_EdtXPoint1->text();
	out << m_Ui.m_EdtYPoint1->text();
	out << m_Ui.m_EdtInlinePoint2->text();
	out << m_Ui.m_EdtCrossLinePoint2->text();
	out << m_Ui.m_EdtXPoint2->text();
	out << m_Ui.m_EdtYPoint2->text();
	out << m_Ui.m_EdtInlinePoint3->text();
	out << m_Ui.m_EdtCrossLinePoint3->text();
	out << m_Ui.m_EdtXPoint3->text();
	out << m_Ui.m_EdtYPoint3->text();
	out << m_Ui.m_EdtInLineInc->text();
	out << m_Ui.m_pEdtCrossLineInc->text();
}

void CXCreateSeisWorkArea::slotLoad()
{
	QString strName = QFileDialog::getOpenFileName(this);
	QFile file(strName);
	if (!file.open(QFile::ReadOnly))
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(), tr("Cannot open file %1:\n%2.").arg(QDir::toNativeSeparators(strName), file.errorString()));
		return;
	}

	QDataStream in(&file);

	quint32 mask;
	in >> mask;
	if (mask != 0xF1E2D3C4)
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(), tr("Bad File Formation"));
		return;
	}

	qint32 version;
	in >> version;
	if (version < 100)
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(), tr("Bad File: Too Old"));
		return;
	}
	if (version > 100)
	{
		QMessageBox::warning(this, QGuiApplication::applicationDisplayName(), tr("Bad File: Too New"));
		return;
	}

	auto _SetLineEditText = [&in](QLineEdit* pLineEdit)
	{
		QString str;
		in >> str;
		pLineEdit->setText(str);
	};

	_SetLineEditText(m_Ui.m_EdtInlinePoint1);
	_SetLineEditText(m_Ui.m_EdtCrossLinePoint1);
	_SetLineEditText(m_Ui.m_EdtXPoint1);
	_SetLineEditText(m_Ui.m_EdtYPoint1);
	_SetLineEditText(m_Ui.m_EdtInlinePoint2);
	_SetLineEditText(m_Ui.m_EdtCrossLinePoint2);
	_SetLineEditText(m_Ui.m_EdtXPoint2);
	_SetLineEditText(m_Ui.m_EdtYPoint2);
	_SetLineEditText(m_Ui.m_EdtInlinePoint3);
	_SetLineEditText(m_Ui.m_EdtCrossLinePoint3);
	_SetLineEditText(m_Ui.m_EdtXPoint3);
	_SetLineEditText(m_Ui.m_EdtYPoint3);
	_SetLineEditText(m_Ui.m_EdtInLineInc);
	_SetLineEditText(m_Ui.m_pEdtCrossLineInc);
}

void CXCreateSeisWorkArea::slotPreView()
{
	int iInlineInc = m_Ui.m_EdtInLineInc->text().toInt();
	int iCrosslineInc = m_Ui.m_pEdtCrossLineInc->text().toInt();
	if (iInlineInc < 1 || iCrosslineInc < 1)
	{
		QMessageBox::information(this, "Create Seismic Survey", "The Inline /Crossline increment must be greater than 0");
		return;
	}

	int iInline0 = m_Ui.m_EdtInlinePoint1->text().toInt();
	int iInline1 = m_Ui.m_EdtInlinePoint2->text().toInt();
	int iInline2 = m_Ui.m_EdtInlinePoint3->text().toInt();

	auto rangeInline = std::minmax({ iInline0, iInline1, iInline2 });
	int iNumInline = (rangeInline.second - rangeInline.first) / iInlineInc + 1;

	int iXline0 = m_Ui.m_EdtCrossLinePoint1->text().toInt();
	int iXline1 = m_Ui.m_EdtCrossLinePoint2->text().toInt();
	int iXline2 = m_Ui.m_EdtCrossLinePoint3->text().toInt();

	auto rangeXline = std::minmax({ iXline0, iXline1, iXline2 });
	int iNumCrossline = (rangeXline.second - rangeXline.first) / iCrosslineInc + 1;

	double x0 = m_Ui.m_EdtXPoint1->text().toDouble();
	double y0 = m_Ui.m_EdtYPoint1->text().toDouble();
	double x1 = m_Ui.m_EdtXPoint2->text().toDouble();
	double y1 = m_Ui.m_EdtYPoint2->text().toDouble();
	double x2 = m_Ui.m_EdtXPoint3->text().toDouble();
	double y2 = m_Ui.m_EdtYPoint3->text().toDouble();

	if (!m_utm.InitSize(rangeInline.first, iNumInline, iInlineInc, rangeXline.first, iNumCrossline, iCrosslineInc))
	{
		QMessageBox::information(this, "Create Seismic Survey", "UTM initialize failed, wrong line or trace number!");
		return;
	}

	if (!m_utm.InitCoordinates(iInline0, iXline0, x0, y0, iInline1, iXline1, x1, y1, iInline2, iXline2, x2, y2))
	{
		QMessageBox::information(this, "Create Seismic Survey", "UTM initialize failed, wrong coordinates!");
		return;
	}

	SetOKEnabled(true);

	int nXLine = m_utm.GetCrosslineNum();
	int nInline = m_utm.GetInlineNum();

	double  p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y;
	m_utm.IJToXY(0, 0, p1x, p1y);
	m_utm.IJToXY(0, nXLine - 1, p2x, p2y);
	m_utm.IJToXY(nInline - 1, 0, p3x, p3y);
	m_utm.IJToXY(nInline - 1, nXLine - 1, p4x, p4y);

	std::vector<QPointF> vec;
	vec.push_back(QPointF(p1x, p1y));
	vec.push_back(QPointF(p2x, p2y));
	vec.push_back(QPointF(p3x, p3y));
	vec.push_back(QPointF(p4x, p4y));

	auto _GetIndex = [rangeInline, rangeXline](int iInline, int iXline)
	{
		if (iInline == rangeInline.first && iXline == rangeXline.first) return 0;
		if (iInline == rangeInline.first && iXline == rangeXline.second) return 1;
		if (iInline == rangeInline.second && iXline == rangeXline.first) return 2;
		return 3;
	};

	std::vector<int> vecIndex(4, -1);
	vecIndex.at(_GetIndex(iInline0, iXline0)) = 1;
	vecIndex.at(_GetIndex(iInline1, iXline1)) = 2;
	vecIndex.at(_GetIndex(iInline2, iXline2)) = 3;
	std::replace(vecIndex.begin(), vecIndex.end(), -1, 4);

	m_Ui.m_UtmToolView->SetPoints(vec, vecIndex);
	m_Ui.m_UtmToolView->update();

	//Grid information
	m_Ui.m_EdtFirstInline->setText(QString::number(m_utm.GetFirstInline()));
	m_Ui.m_EdtInlineNumber->setText(QString::number(m_utm.GetInlineNum()));
	m_Ui.m_EdtFirstCrossLine->setText(QString::number(m_utm.GetFirstCrossline()));
	m_Ui.m_EdtCrosslineNumber->setText(QString::number(m_utm.GetCrosslineNum()));
	m_Ui.m_EdtInlineSpace->setText(vtos(m_utm.GetInlineInterval(), 4));
	m_Ui.m_EdtCrossSpace->setText(vtos(m_utm.GetCrosslineInterval(), 4));

	auto _GetNeighbor = [](int i)
	{
		if (i == 0 || i == 3) return std::make_pair(1, 2);
		else return std::make_pair(0, 3);
	};

	auto index0 = _GetIndex(iInline0, iXline0);
	auto neighbor = _GetNeighbor(index0);

	QVector2D vec0(vec[neighbor.first] - vec[index0]);
	QVector2D vec1(vec[neighbor.second] - vec[index0]);
	qreal angle = qRadiansToDegrees(qAcos(QVector2D::dotProduct(vec0, vec1) / (vec0.length() * vec1.length())));
	m_Ui.lineEditAngleP1->setText(vtos(angle, 2));
}