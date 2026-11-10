#include "xpagemakefaultsticksbysurveyfrompoints.h"
#include <QFile>
#include <QMessageBox>
#include <QProcess>
#include "x3dpoints.h"
#include "xglobal.h"
#include "xproject.h"
#include "xseismicutmtool.h"
#include "x3dsurvey.h"
#include "xbaseconsole.h"

CXPageMakeFaultSticksBySurveyFromPoints::CXPageMakeFaultSticksBySurveyFromPoints(CX3DPoints* pPoints, QWidget *parent)
	: QDialog(parent), m_pPoints(pPoints)
{
	ui.setupUi(this);
	_Init();
}

CXPageMakeFaultSticksBySurveyFromPoints::~CXPageMakeFaultSticksBySurveyFromPoints()
{

}

void CXPageMakeFaultSticksBySurveyFromPoints::_Init()
{
	for (auto surveyObj : ::GetProject()->GetChildren(EX3DSurvey))
		ui.comboBox_survey->addItem(surveyObj->GetObjectName(), surveyObj->GetObjectID());

	_OnSurveyChanged(0);
	
	connect(ui.comboBox_survey, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CXPageMakeFaultSticksBySurveyFromPoints::_OnSurveyChanged);
	connect(ui.pushButton_generate, &QPushButton::clicked, this, &CXPageMakeFaultSticksBySurveyFromPoints::_OnGenerate);
	connect(ui.lineEdit_output, &QLineEdit::editingFinished, [this]() {
		if (ui.lineEdit_output->text().isEmpty())
			if (QMessageBox::Ok == QMessageBox::warning(this, "error", "The output file need a name."))
				ui.lineEdit_output->setFocus();
	});
	connect(ui.checkBox_alsoCrossline, &QCheckBox::stateChanged, [this](int state) {
		QString fileName = ui.lineEdit_output->text();
		int nTail = fileName.lastIndexOf('x');
		if (nTail == -1) return;
		fileName.chop(fileName.size() - nTail - 1);
		fileName.push_back(QString::number(state ? ui.spinBox_inlineStep->value() : 1));
		ui.lineEdit_output->setText(fileName);
	});
}

void CXPageMakeFaultSticksBySurveyFromPoints::_MappingData()
{
	m_mapTrace2Points.clear();

	uint n = 0;
	double* pData = m_pPoints->GetData(n);

	for (uint i = 0; i < n; i += 3)
	{
		int iInline, iXline;
		m_pSelectedUTM->XYToLine(pData[i], pData[i + 1], iInline, iXline);
		m_mapTrace2Points[iInline][iXline].emplace_back(pData[i], pData[i + 1], pData[i + 2]);
	}
}

void CXPageMakeFaultSticksBySurveyFromPoints::_OnSurveyChanged(int index)
{
	if (m_pSelectedUTM) { delete m_pSelectedUTM; m_pSelectedUTM = nullptr; }

	CX3DSurvey* p3DSurvey = dynamic_cast<CX3DSurvey*>(::GetObjectByID(ui.comboBox_survey->itemData(index).toUuid()));
	if (p3DSurvey) {
		m_pSelectedUTM = new CXSeismicUTMTool(p3DSurvey->GetUTM());

		_MappingData();
		
		ui.spinBox_firstInline->setRange(m_mapTrace2Points.begin()->first, m_mapTrace2Points.rbegin()->first);
		ui.spinBox_lastInline->setRange(m_mapTrace2Points.begin()->first, m_mapTrace2Points.rbegin()->first);
		ui.spinBox_inlineStep->setMinimum(m_pSelectedUTM->GetInlineIncrement());

		ui.spinBox_firstInline->setValue(m_mapTrace2Points.begin()->first);
		ui.spinBox_lastInline->setValue(m_mapTrace2Points.rbegin()->first);
		ui.spinBox_inlineStep->setValue(m_pSelectedUTM->GetInlineIncrement() * 5);

		ui.lineEdit_output->setText(m_pPoints->GetObjectName() + "_" + QString::number(m_pSelectedUTM->GetInlineIncrement() * 5) + "x1");
	}
}

void CXPageMakeFaultSticksBySurveyFromPoints::_OnGenerate()
{
	int iFirstInline = ui.spinBox_firstInline->value();
	int iLastInline = ui.spinBox_lastInline->value();
	int iInlineStep = ui.spinBox_inlineStep->value();
	int iXlineStep = ui.checkBox_alsoCrossline->isChecked() ? iInlineStep : 1;

	QString filename = ::GetProjectPath() + ui.lineEdit_output->text();
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly)) return;

	QTextStream stream(&file);

	for (int i = iFirstInline, no = 0; i <= iLastInline; i += iInlineStep)
	{
		if (m_mapTrace2Points.find(i) == m_mapTrace2Points.end()) continue;

		auto& mapXl2P = m_mapTrace2Points[i];
		for (auto iterXline = mapXl2P.begin(); iterXline != mapXl2P.end(); std::advance(iterXline, iXlineStep))
		{
			for (auto&& point : iterXline->second)
				stream << QString("%1 %2 %3 %4 %5 %6\r\n").arg(QString::number(std::get<0>(point), 'f'), -16, '0')
				.arg(QString::number(std::get<1>(point), 'f'), -16, '0')
				.arg(QString::number(std::get<2>(point), 'f'), -16, '0')
				.arg(i).arg(iterXline->first).arg(no);

			if (std::distance(iterXline, mapXl2P.end()) < iXlineStep)
				break;
		}
			
		++no;
	}

	QProcess* pProcess = new QProcess(this);
	pProcess->start("notepad.exe", { filename });
}
