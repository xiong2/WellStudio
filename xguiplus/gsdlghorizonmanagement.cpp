#include "gs3dhorizonfaulttraces.h"
#include "gsdlghorizonmanagement.h"
#include "x3dhorizon.h"
#include "gscompressionpulse.h"
#include "xfaultsticks.h"
#include "gsfaultprocess.h"
#include "xcheckboxwidget.h"
#include "xgeneralfolder.h"
#include "xglobal.h"
#include "xproject.h"
#include "xtree.h"
#include "xutmtool.h"
#include "xgeometry.h"
#include "x3dsurvey.h"
#include "gsutilities.h"
#include <qfile.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qsettings.h>
#include <qtextstream.h>
#include <fstream>
#include <deque>

GSDlgHorizonManagement::GSDlgHorizonManagement(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	initialUI();
}

GSDlgHorizonManagement::~GSDlgHorizonManagement()
{
}

void GSDlgHorizonManagement::initialUI()
{
	QStringList sListSurvey;
	QList<CXObject*> listSurvey = ::GetProject()->GetChildren(EX3DSurvey);
	foreach(CXObject* pSurvey, listSurvey)
	{
		sListSurvey << pSurvey->GetObjectName();
	}
	ui.comboBox->addItems(sListSurvey);

	ui.tableWidget->setColumnWidth(0, 50);
	ui.tableWidget->setColumnWidth(1, 160);
	ui.tableWidget->setColumnWidth(2, 120);

	refreshTable(0);

	float dCellSize = ::GetProject()->GetCellSize();
	ui.lineEdit_FaultTolerance->setText(QString::number(dCellSize * 0.05f));

	connect(ui.comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &GSDlgHorizonManagement::refreshTable);
	connect(ui.pushButton, &QPushButton::clicked, this, &GSDlgHorizonManagement::readVolFile);
}

void GSDlgHorizonManagement::refreshTable(int iSurveyID)
{
	QStringList sListSurvey, sListType;
	QList<CXObject*> listSurvey = ::GetProject()->GetChildren(EX3DSurvey);
	QList<CXObject*> listH = listSurvey[iSurveyID]->GetChildren(EX3DHorizon, true);
	if (listH.empty())
		return;
	sListType << "Conformable"
		<< "Unconformable"
		<< "Erosional"
		<< "Basement";

	if (listH[0]->GetObjectName() == "SeaBed")
	{
		ui.checkBoxSeaBed->setChecked(false);
		ui.checkBoxSeaBed->setDisabled(true);
		listH.removeFirst();
	}
	else
		ui.checkBoxSeaBed->setDisabled(false);

	ui.tableWidget->setRowCount(listH.count());
	for (int i = 0; i < listH.count(); i++)
	{
		CX3DHorizon* pHor = (CX3DHorizon*)listH[i];

		//	1st column is the check box.
		CXCheckBoxWidget* pCheckBox1 = new CXCheckBoxWidget;
		pCheckBox1->SetChecked(true);
		ui.tableWidget->setCellWidget(i, 0, pCheckBox1);

		//	2nd column is the curve name.
		QTableWidgetItem* pWItem = new QTableWidgetItem(listH[i]->GetObjectName());
		pWItem->setIcon(QIcon(GetIconPath() + "Horizon.png"));
		ui.tableWidget->setItem(i, 1, pWItem);

		//	3rd column is the pulse.
		QComboBox* pCBPulse = new QComboBox;
		pCBPulse->addItems(GSCompressionPulse::GetAllPulses());
		pCBPulse->setCurrentIndex(pHor->GetPulse());
		ui.tableWidget->setCellWidget(i, 2, pCBPulse);

		//	4th column is the direction. 
		QString sDir = QString::number(pHor->GetBaseSHDirection());
		if (sDir == "-1")
		{
			sDir = QString::number(GetProject()->GetBaseSHDirection());
		}
		ui.tableWidget->setItem(i, 3, new QTableWidgetItem(sDir));

		//	5th column is the velocity.
		QString sVol = QString::number(pHor->GetIntervalVelocity());
		ui.tableWidget->setItem(i, 4, new QTableWidgetItem(sVol));

		//	6th column is the type
		QComboBox* pCBType = new QComboBox;
		pCBType->addItems(sListType);
		pCBType->setCurrentIndex(pHor->GetHorizonType());
		ui.tableWidget->setCellWidget(i, 5, pCBType);

		//	7th column is the check box.
		CXCheckBoxWidget* pCheckBox2 = new CXCheckBoxWidget;
		pCheckBox2->SetChecked(pHor->UsedByPP());
		ui.tableWidget->setCellWidget(i, 6, pCheckBox2);

		//	8th 9th, & 10th columns are the pore pressure, hydrostatic and lithostatic gradient.
		ui.tableWidget->setItem(i, 7, new QTableWidgetItem(QString::number(pHor->GetPorePressure())));
		ui.tableWidget->setItem(i, 8, new QTableWidgetItem(QString::number(pHor->GetHydroGradient())));
		ui.tableWidget->setItem(i, 9, new QTableWidgetItem(QString::number(pHor->GetLithoGradient())));
	}
}

void GSDlgHorizonManagement::readVolFile()
{
	int iHNum = ui.tableWidget->rowCount();
	if (iHNum == 0)
		return;

	QFileDialog dialog(NULL, "Reading Velocity File");
	dialog.setFileMode(QFileDialog::ExistingFiles);
	dialog.setNameFilter("*.asc");

	QSettings settings("GeoStress", "RecentDataDir");
	QString recentDataDir = settings.value("lastPath").toString();
	if (!recentDataDir.isEmpty())
		dialog.setDirectory(recentDataDir);

	QStringList sListFiles;
	QString strSelectedFilter;
	if (dialog.exec())
	{
		QDir currentDir = dialog.directory();
		settings.setValue("lastPath", currentDir.absolutePath());
		sListFiles = dialog.selectedFiles();
	}

	if (sListFiles.isEmpty())
		return;

	QFile qFile(sListFiles[0]);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		return;
	}

	ui.lineEdit->setText(sListFiles[0]);

	QString sLine;
	QStringList sList;
	QTextStream stream(&qFile);
	while (!stream.atEnd())
	{
		sLine = stream.readLine();
		if (sLine.startsWith("#"))
			continue;

		sList = sLine.split(",");
		if (sList.count() < 3)
			continue;

		QString sHName = sList[0].simplified();
		for (int i = 0; i < iHNum; i++)
		{
			if (ui.tableWidget->item(i, 1)->text() == sHName)
			{
				ui.tableWidget->item(i, 3)->setText(sList[2].simplified());
				QComboBox* pCB = (QComboBox*)ui.tableWidget->cellWidget(i, 2);
				pCB->setCurrentIndex(GSCompressionPulse::GetPulseIDByName(sList[1].simplified()));
				break;
			}
		}
	}

	qFile.close();
}

void GSDlgHorizonManagement::resampleHorizons(CX3DSurvey* pSurvey)
{
	CXObject *pSFolder = pSurvey->GetFolder(EXGSFolder);
	QList<CXObject*> listH = pSurvey->GetChildren(EX3DHorizon, true);

	int iHInuse = 0, iComp = -1, iHNum = ui.tableWidget->rowCount();
	for (int i = 0; i < iHNum; i++)
	{
		CXCheckBoxWidget* pCheckBox1 = (CXCheckBoxWidget*)(ui.tableWidget->cellWidget(i, 0));
		if (!pCheckBox1->IsChecked())
			continue;

		CX3DHorizon *pRawHorizon = dynamic_cast<CX3DHorizon*>(listH[i]);
		CXGeneralFolder *pHFolder = new CXGeneralFolder(pRawHorizon->GetObjectName(), EXGSFolderHorizon, "HorizonFolder.png");
		pSFolder->AddChild(pHFolder);

		CX3DHorizon* pTWTHorizon = new CX3DHorizon(pSurvey->GetObjectID(), pRawHorizon->GetUTM(), pRawHorizon->GetObjectName() + "(TWT)");
		float *pData = pTWTHorizon->GetData();
		memcpy(pData, pRawHorizon->GetData(), pRawHorizon->GetUTM().GetNI() * pRawHorizon->GetUTM().GetNJ() * 4);
		pTWTHorizon->SetObjectType(EXGS3DHorizonTWT);
		pTWTHorizon->SetModifiedFlag();
		pHFolder->AddChild(pTWTHorizon);
		CXSeismicUTMTool newUTM;
		newUTM.Copy(&pSurvey->GetUTM());
		newUTM.ChangeCellSize(GetProject()->GetCellSize());
		pTWTHorizon->Resample(&newUTM);

		QComboBox* pCB = (QComboBox*)ui.tableWidget->cellWidget(i, 2);
		pTWTHorizon->SetPulse(pCB->currentIndex());
		pTWTHorizon->SetColor(GSCompressionPulse::GetPulseColor(pCB->currentText()));

		pTWTHorizon->SetBaseSHDirection((int)(ui.tableWidget->item(i, 3)->text().toFloat()));
		pTWTHorizon->SetIntervalVelocity(ui.tableWidget->item(i, 4)->text().toFloat());
		pTWTHorizon->SetPorePressure(ui.tableWidget->item(i, 7)->text().toFloat());
		pTWTHorizon->SetHydroGradient(ui.tableWidget->item(i, 8)->text().toFloat());
		pTWTHorizon->SetLithoGradient(ui.tableWidget->item(i, 9)->text().toFloat());

		QComboBox* pCB2 = (QComboBox*)ui.tableWidget->cellWidget(i, 5);
		pTWTHorizon->SetHorizonType((EHorizonType)pCB2->currentIndex());

		CXCheckBoxWidget* pCheckBox2 = (CXCheckBoxWidget*)(ui.tableWidget->cellWidget(i, 6));
		pTWTHorizon->SetUsedByPP(pCheckBox2->IsChecked());
	}
}

void GSDlgHorizonManagement::updateHorizonsWithFaults(CX3DSurvey* pSurvey)
{
	auto getFaultsList = [this]()
	{
		QList<CXObject*> listFaultFolder = GetProject()->GetChildren(EXFaultFolder, true);
		if (listFaultFolder.isEmpty() || !ui.groupBox_UseFaults->isChecked())
			return QList<CXObject*>{};

		return listFaultFolder.at(0)->GetChildren(EXFaultSticks);
	};

	CXObject *pSFolder = pSurvey->GetFolder(EXGSFolder);
	QList<CXObject*> listHFolder = pSFolder->GetChildren(EXGSFolderHorizon);
	QList<CXObject*> listRawH = pSurvey->GetChildren(EX3DHorizon, true);
	float fFaultTol = ui.lineEdit_FaultTolerance->text().toFloat();

	for (int i = 0; i < listHFolder.count(); i++)
	{
		//	Use raw horizon to calculate, but result store in the resampled depth one.
		CX3DHorizon *pRawHorizon;
		foreach(CXObject *pObj, listRawH)
		{
			if (pObj->GetObjectName() == listHFolder[i]->GetObjectName())
			{
				pRawHorizon = dynamic_cast<CX3DHorizon*>(pObj);
				break;
			}
		}
		CX3DHorizon *pDepthHorizon = dynamic_cast<CX3DHorizon*>(listHFolder[i]->GetChildren(EXGS3DHorizonDepth).front());

		for (auto pObj : getFaultsList())
		{
			auto pFault = dynamic_cast<CXFaultSticks*>(pObj);
			auto pDepthtFaultTraces = new GS3DHorizonFaultTraces(pFault->GetObjectName());

			for (size_t i = 0; i < pFault->GetStickNum(); ++i)
			{
				CXFaultStick* pStick = pFault->GetStick(i);
				GSFaultInterpStick interpStick(pStick->begin(), pStick->end());
				GSHorizonFault horizonFault(pRawHorizon->GetUTM(), pRawHorizon->GetData(), interpStick);

				GSFaultTrace trace = horizonFault.GetFaultTrace(fFaultTol);
				if (trace.IsNull())
					continue;
				pDepthtFaultTraces->AddTrace(trace);
			}

			//	Avoid blank FT.
			if (pDepthtFaultTraces->TraceCount() == 0)
			{
				delete pDepthtFaultTraces;
				continue;
			}

			NGSFault::SortFaultTrace(&pDepthtFaultTraces->GetTraces());

			pDepthtFaultTraces->SetNodeFlag(false);
			pDepthHorizon->AddChild(pDepthtFaultTraces);
		}
	}
}

void GSDlgHorizonManagement::calculateIsoHorizonFaultTraces(CX3DSurvey* pSurvey)
{
	using GSUtil::ToVec;
	using GSUtil::MakeLine;
	double dBeginEndTol = GetProject()->GetCellSize() / 2.0;
	bool bFaultTypefromThick = ui.checkBox_UseThickForFaultType->isChecked();
	double dFaultTypefromThickTol = ui.lineEdit_ThickTolerance->text().toDouble();

	CXObject *pSFolder = pSurvey->GetFolder(EXGSFolder);
	QList<CXObject*> listHorizonFolder = pSFolder->GetChildren(EXGSFolderHorizon);

	auto getBelowTwt = [&listHorizonFolder](CXObject* pCurrent) -> CX3DHorizon*
	{
		auto currentIndex = listHorizonFolder.indexOf(pCurrent->GetParent());
		for (int i = currentIndex + 1; i < listHorizonFolder.size(); ++i)
		{
			auto pFolder = listHorizonFolder.at(i);
			auto listTWT = pFolder->GetChildren(EXGS3DHorizonDepth);
			if (!listTWT.isEmpty())
				return (CX3DHorizon *)listTWT[0];
		}
		return nullptr;
	};

	auto getAllFaultsName = [](CX3DHorizon* pUnder, CX3DHorizon* pBelow)
	{
		QStringList listFaultName;

		for (auto pFaultTracesObj : pUnder->GetChildren(EXGSFaultTraces))
		{
			listFaultName << pFaultTracesObj->GetObjectName();
		}

		for (auto pFaultTracesObj : pBelow->GetChildren(EXGSFaultTraces))
		{
			QString faultName = pFaultTracesObj->GetObjectName();
			if (!listFaultName.contains(faultName))
				listFaultName << faultName;
		}

		return listFaultName;
	};

	auto isReverseSegment = [](const GSFaultTrace& ft1, const GSFaultTrace& ft2)
	{
		if ((ft1.m_type == GSFaultTrace::eNormal || ft1.m_type == GSFaultTrace::eZero) && ft2.m_type != GSFaultTrace::eReverse)
			return false;

		if ((ft2.m_type == GSFaultTrace::eNormal || ft2.m_type == GSFaultTrace::eZero) && ft1.m_type != GSFaultTrace::eReverse)
			return false;

		return true;
	};

	auto lineIntersect = [isReverseSegment](const XVec2d& p1, const XVec2d& p2, GS3DHorizonFaultTraces* hft, GSFaultTrace* ft)
	{
		bool ret = false;

		// Centre of the line segment: we will pick the intersection segment that is closest to this point.
		XVec2d cp = XGeom::Lerp(p1, p2, 0.5f);
		const auto& faultTraces = hft->GetTraces();
		double prevd = std::numeric_limits<double>::max();
		for (auto ft1 = faultTraces.begin(), ft2 = std::next(faultTraces.begin()); ft2 != faultTraces.end(); ++ft1, ++ft2)
		{
			QPointF fp1 = ft1->CentrePoint();
			QPointF fp2 = ft2->CentrePoint();
			XVec2d ip;
			double u, v;

			if (XGeom::IntersectionTwoSegments(p1, p2, ToVec(fp1), ToVec(fp2), &ip, &u, &v))
			{
				double d = XGeom::Distance(ip, cp);
				if (d < prevd)
				{
					prevd = d;

					ft->m_p1 = XGeom::Lerp(ft1->m_p1, ft2->m_p1, u);
					ft->m_p2 = XGeom::Lerp(ft1->m_p2, ft2->m_p2, u);
					ft->m_type = isReverseSegment(*ft1, *ft2) ? GSFaultTrace::eReverse : GSFaultTrace::eNormal;

					ret = true;
				}
			}
		}

		return ret;
	};

	for (auto pFolder : listHorizonFolder)
	{
		const auto& horizonIsoList = pFolder->GetChildren(EXGS3DHorizonIso);
		if (horizonIsoList.empty())
			continue;

		auto pHorizonIso = dynamic_cast<CX3DHorizon*>(horizonIsoList.front());
		Q_ASSERT(pHorizonIso);

		auto pUnderTwt = dynamic_cast<CX3DHorizon*>(pFolder->GetChildren(EXGS3DHorizonDepth).front());
		auto pBelowTwt = getBelowTwt(pUnderTwt);
		Q_ASSERT(pBelowTwt);

		for (auto faultName : getAllFaultsName(pUnderTwt, pBelowTwt))
		{
			// 1 is under, 2 is below
			auto hft1 = dynamic_cast<GS3DHorizonFaultTraces*>(pUnderTwt->GetChild(faultName));
			auto hft2 = dynamic_cast<GS3DHorizonFaultTraces*>(pBelowTwt->GetChild(faultName));

			// Must have at least 2 points.
			if (hft1 && hft1->TraceCount() <= 2)
				hft1 = nullptr;
			if (hft2 && hft2->TraceCount() <= 2)
				hft2 = nullptr;

			GS3DHorizonFaultTraces* hft = nullptr;

			std::deque<QPointF> centrePoints;
			XLine2d line;
			double t1, t2;
			if (hft2) // copy points from below horizon fault traces.
			{
				for (auto&& trace : hft2->GetTraces())
				{
					centrePoints.emplace_back((trace.m_p1.x() + trace.m_p2.x()) / 2, (trace.m_p1.y() + trace.m_p2.y()) / 2);
				}

				// Set up the line between the start end fault points
				QPointF p1 = hft2->GetTrace(0)->CentrePoint();
				QPointF p2 = hft2->GetTrace(hft2->TraceCount() - 1)->CentrePoint();
				line = MakeLine(p1, p2);
				t1 = line.TforXY(p1.x(), p1.y());
				t2 = line.TforXY(p2.x(), p2.y());

				hft = new GS3DHorizonFaultTraces(hft2->GetObjectName());
			}

			if (hft1) // add points from the under horizon fault traces.
			{
				if (!hft)
					hft = new GS3DHorizonFaultTraces(hft1->GetObjectName());

				for (auto&& trace : hft1->GetTraces())
				{
					double x = (trace.m_p1.x() + trace.m_p2.x()) / 2;
					double y = (trace.m_p1.y() + trace.m_p2.y()) / 2;

					// If we have an intersection with the below surface only add points that extend the T range
					if (hft2)
					{
						double t = line.TforXY(x, y);
						if (t < t1 + dBeginEndTol)
						{
							centrePoints.emplace_front(x, y);
							t1 = t;
						}
						else if (t > t2 + dBeginEndTol)
						{
							centrePoints.emplace_back(x, y);
							t2 = t;
						}
					}
				}
			}

			if (centrePoints.size() < 2)
				continue;

			line = MakeLine(centrePoints.front(), centrePoints.back());
			QPointF p0, p1, p2;

			// Generate the fault trace points
			for (size_t i = 0; i != centrePoints.size(); ++i)
			{
				if (i == 0) // first segment
				{
					p1 = centrePoints.at(i);
					p2 = centrePoints.at(i + 1);
					line = MakeLine(p1, p2);
				}
				else if (i < centrePoints.size() - 1) // Middle segments (Split the angle and put the line through p1)
				{
					p0 = centrePoints.at(i - 1);
					p1 = centrePoints.at(i);
					p2 = centrePoints.at(i + 1);

					// Get the two segment lines
					XLine2d line1 = MakeLine(p0, p1);
					XLine2d line2 = MakeLine(p1, p2);

					// Split the angle
					XVec2d tp1 = line1.PforT(line1.TforXY(p1.x(), p1.y()) - 100.0);
					XVec2d tp2 = line2.PforT(line2.TforXY(p1.x(), p1.y()) + 100.0);

					// Make sure the line goes through p1
					line = XLine2d(ToVec(p1), tp2 - tp1);
				}
				else
				{
					p2 = centrePoints.at(i - 1);
					p1 = centrePoints.at(i);
					line = MakeLine(p2, p1);
				}

				double t = line.TforXY(p1.x(), p1.y());
				XVec2d secLeft = line.PointPerp(t, -5000);
				XVec2d secRight = line.PointPerp(t, 5000);
				XLine2d secLine(secLeft, secRight);

				GSFaultTrace ft1, ft2, ft;
				bool isFaultTraces1Define = hft1 && lineIntersect(secLeft, secRight, hft1, &ft1);
				bool isFaultTraces2Define = hft2 && lineIntersect(secLeft, secRight, hft2, &ft2);

				if (isFaultTraces1Define && isFaultTraces2Define)
				{
					double leftThick = ft2.m_p1.z() - ft1.m_p1.z();
					double rightThick = ft2.m_p2.z() - ft1.m_p2.z();

					ft.m_p1.rz() = 0.0;
					ft.m_p2.rz() = rightThick - leftThick;

					bool is1Left = secLine.TforXY(ft2.m_p2.x(), ft2.m_p2.y()) > secLine.TforXY(ft1.m_p2.x(), ft1.m_p2.y());
					if (is1Left)
					{
						ft.m_p1.rx() = ft1.m_p1.x();
						ft.m_p1.ry() = ft1.m_p1.y();
						ft.m_p2.rx() = ft2.m_p2.x();
						ft.m_p2.ry() = ft2.m_p2.y();
					}
					else
					{
						ft.m_p1.rx() = ft2.m_p1.x();
						ft.m_p1.ry() = ft2.m_p1.y();
						ft.m_p2.rx() = ft1.m_p2.x();
						ft.m_p2.ry() = ft1.m_p2.y();
					}

					if (bFaultTypefromThick && fabs(leftThick - rightThick) >= dFaultTypefromThickTol)
					{
						// There is a new method now(18-Jul-2011): for an ISO map(which is the case here), the fault is reverse
						// if the tinner side lies above the fault.

						if ((!is1Left && leftThick < rightThick) || (is1Left && leftThick >= rightThick))
							ft.m_type = GSFaultTrace::eReverse;
						else
							ft.m_type = GSFaultTrace::eNormal;
					}
					else
					{
						// Old method: set up fault type, if they are the same, use it. else use the value for the largest throw.
						ft.m_type = ft1.m_type;
						if (ft1.m_type != ft2.m_type)
						{
							ft.m_type = hft1->MaxThrow() > hft2->MaxThrow() ? ft1.m_type : ft2.m_type;
						}
					}
				}
				else if (isFaultTraces1Define)
				{
					// just deal with the under surface
					ft.m_p1 = ft1.m_p1;
					ft.m_p2 = ft1.m_p2;
					ft.m_p1.rz() = 0.0;
					ft.m_p2.rz() = ft1.m_p2.z() - ft1.m_p1.z();
					ft.m_type = ft1.m_type;
				}
				else if (isFaultTraces2Define)
				{
					// just deal with the below surface
					ft.m_p1 = ft2.m_p1;
					ft.m_p2 = ft2.m_p2;
					ft.m_p1.rz() = 0.0;
					ft.m_p2.rz() = ft2.m_p2.z() - ft2.m_p1.z();
					ft.m_type = ft2.m_type;
				}
				else
				{
					continue;
				}

				if (hft->TraceCount() > 0)
				{
					// make sure we don't overlap the traces.
					GSFaultTrace lastFt = hft->GetTraces().back();
					if (XGeom::IntersectionTwoSegments(ft.m_p1.ToVec2(), ft.m_p2.ToVec2(), lastFt.m_p1.ToVec2(), lastFt.m_p2.ToVec2()))
					{
						continue;
					}
				}

				hft->AddTrace(ft);
			}

			if (!hft || hft->TraceCount() < 2)
			{
				delete hft;
				continue;
			}

			NGSFault::SortFaultTrace(&hft->GetTraces());
			hft->SetNodeFlag(false);
			pHorizonIso->AddChild(hft);
		}

		//	Update the tree.
		CXTree::Instance().AddOneObject(pHorizonIso);
	}
}

void GSDlgHorizonManagement::accept()
{
	QStringList sListSurvey;
	QList<CXObject*> listSurvey = GetProject()->GetChildren(EX3DSurvey);
	CX3DSurvey *pSurvey = (CX3DSurvey *)listSurvey[ui.comboBox->currentIndex()];

	QDialog::accept();

	//	Now clear exist content.
	CXObject *pSFolder = pSurvey->GetFolder(EXGSFolder);
	QList<CXObject*> listChildren = pSFolder->GetChildrenList();
	for (int i = 0; i < listChildren.size(); ++i)
	{
		_DeleteObj(listChildren.at(i));
	}

	resampleHorizons(pSurvey);
	updateDepthHorizons(pSurvey);
	updateHorizonsWithFaults(pSurvey);
	if (ui.groupBox_UseFaults->isChecked())
	{
		calculateIsoHorizonFaultTraces(pSurvey);
	}
}

void GSDlgHorizonManagement::_DeleteObj(CXObject* pObj)
{
	if (!pObj)
		return;

	if (pObj->IsLocked())
		return;

	CXObject* pParentObj = pObj->GetParent();
	if (!pParentObj)
		return;

	QList<CXObject*> listChildren = pObj->GetChildrenList();
	for (int i = 0; i < listChildren.size(); ++i)
	{
		_DeleteObj(listChildren.at(i));
	}

	pParentObj->RemoveOneChild(pObj);
	{
		CXProcessEvent processEvent;
		pObj->AddEvent(EDeleted);
	}

	delete pObj;
}

void GSDlgHorizonManagement::updateDepthHorizons(CX3DSurvey* pSurvey)
{
	CXObject *pSFolder = pSurvey->GetFolder(EXGSFolder);
	QList<CXObject*> listHFolder = pSFolder->GetChildren(EXGSFolderHorizon);
	int iHNum = listHFolder.count();

	int i, j, m, iDataSize = 0;
	CX3DHorizon* pTopTH = NULL;
	CX3DHorizon* pTopDH = NULL;
	float fVol = GetProject()->GetReplacementVelocity() / 2000;

	//	First create the depth horizons.
	for (i = 0; i < iHNum; i++)
	{
		CX3DHorizon* pHor = (CX3DHorizon*)listHFolder[i]->GetChildren(EXGS3DHorizonTWT)[0];

		//	Now check the UTM size.
		if (iDataSize == 0)
		{
			iDataSize = pHor->GetUTM().GetNI() * pHor->GetUTM().GetNJ();
		}
		else
		{
			if (iDataSize != pHor->GetUTM().GetNI() * pHor->GetUTM().GetNJ())
			{
				QMessageBox::warning(NULL, "UTM size error", pHor->GetObjectName() + " has different data size with above horizon!");
				continue;
			}
		}

		//	Create the new depth horizon.
		QString sHName = pHor->GetObjectName();
		//CX3DHorizon* pDHorizon = new CX3DHorizon(pSurvey->GetObjectID(), pHor->GetUTM(), sHName.replace("TWT", "Depth"));
		CX3DHorizon* pDHorizon = new CX3DHorizon(*pHor);
		float* pData = pDHorizon->GetData();
		pDHorizon->SetObjectName(sHName.replace("TWT", "Depth"));
		pDHorizon->SetObjectType(EXGS3DHorizonDepth);
		pDHorizon->SetNeedCalcDimension();
		pDHorizon->SetModifiedFlag();
		listHFolder[i]->AddChild(pDHorizon);

		float* pTimeData = pHor->GetData();
		if (!pTopTH)
		{
			//	The first horizon.
			for (j = 0; j < iDataSize; j++)
			{
				if (pTimeData[j] == g_dInvalidData)
					pData[j] = g_dInvalidData;
				else
					pData[j] = pTimeData[j] * fVol;
			}
		}
		else
		{
			//	Not the first one, should based on top horizon.
			float* pTopTimeData = pTopTH->GetData();
			float* pTopDepthData = pTopDH->GetData();

			for (j = 0; j < iDataSize; j++)
			{
				if (pTimeData[j] == g_dInvalidData || pTopTimeData[j] == g_dInvalidData)
					pData[j] = g_dInvalidData;
				else
					pData[j] = pTopDepthData[j] + (pTimeData[j] - pTopTimeData[j]) * fVol;
			}
		}

		//	Update the velocity and top horizon.
		fVol = pHor->GetIntervalVelocity() / 2000;
		pTopTH = pHor;
		pTopDH = pDHorizon;
	}

	//	Now create the iso horizons.
	for (i = 0; i < iHNum - 1; i++)
	{
		//	Skip horizons not in using.
		CX3DHorizon* pTopHor = (CX3DHorizon*)listHFolder[i]->GetChildren(EXGS3DHorizonDepth)[0];
		if (!pTopHor)
			continue;

		CX3DHorizon* pBottomHor = NULL;
		for (m = i + 1; m < iHNum; m++)
		{
			pBottomHor = (CX3DHorizon*)listHFolder[m]->GetChildren(EXGS3DHorizonDepth)[0];
			if (pBottomHor)
				break;
		}

		if (!pBottomHor)
			break;

		//	Create the new iso horizon.
		QString sHName = pTopHor->GetObjectName();
		//CX3DHorizon* pIHorizon = new CX3DHorizon(pSurvey->GetObjectID(), pTopHor->GetUTM(), sHName.replace("Depth", "Iso"));
		CX3DHorizon* pIHorizon = new CX3DHorizon(*pTopHor);
		float* pData = pIHorizon->GetData();
		pIHorizon->SetObjectName(sHName.replace("Depth", "Iso"));
		pIHorizon->SetObjectType(EXGS3DHorizonIso);
		pIHorizon->SetNeedCalcDimension();
		pIHorizon->SetModifiedFlag();
		listHFolder[i]->AddChild(pIHorizon);

		float* pTopDData = pTopHor->GetData();
		float* pBotDData = pBottomHor->GetData();

		for (j = 0; j < iDataSize; j++)
		{
			if (pBotDData[j] == g_dInvalidData || pTopDData[j] == g_dInvalidData)
				pData[j] = g_dInvalidData;
			else
				pData[j] = pBotDData[j] - pTopDData[j];
		}
	}

	if (ui.checkBoxSeaBed->isChecked())
	{
		//	Create a sea bed horizon folder.
		CXGeneralFolder* pHorizonFolder = new CXGeneralFolder("SeaBed", EXGSFolderHorizon, "HorizonFolder.png");
		CX3DHorizon* pBotHor = (CX3DHorizon*)listHFolder[0]->GetChildren(EXGS3DHorizonDepth)[0];
		int iDataSize = pBotHor->GetUTM().GetNI() * pBotHor->GetUTM().GetNJ();

		CX3DHorizon* pTHorizon = new CX3DHorizon(pSurvey->GetObjectID(), pBotHor->GetUTM(), "SeaBed(TWT)");
		float* pData = pTHorizon->GetData();
		memset(pData, 0, sizeof(float) * iDataSize);
		pTHorizon->SetObjectType(EXGS3DHorizonTWT);
		pTHorizon->SetModifiedFlag();
		pHorizonFolder->AddChild(pTHorizon);

		CX3DHorizon* pDHorizon = new CX3DHorizon(pSurvey->GetObjectID(), pBotHor->GetUTM(), "SeaBed(Depth)");
		pData = pDHorizon->GetData();
		memset(pData, 0, sizeof(float) * iDataSize);
		pDHorizon->SetObjectType(EXGS3DHorizonDepth);
		pDHorizon->SetModifiedFlag();
		pHorizonFolder->AddChild(pDHorizon);

		CX3DHorizon* pIHorizon = new CX3DHorizon(pSurvey->GetObjectID(), pBotHor->GetUTM(), "SeaBed(Iso)");
		pHorizonFolder->AddChild(pIHorizon);
		pData = pIHorizon->GetData();
		float* pDData = pBotHor->GetData();
		memcpy(pData, pDData, sizeof(float) * iDataSize);
		pIHorizon->SetObjectType(EXGS3DHorizonIso);
		pIHorizon->SetModifiedFlag();
		pSFolder->InsertChild(pHorizonFolder, 0);
	}

	::AddObjectEvent(pSFolder);
}