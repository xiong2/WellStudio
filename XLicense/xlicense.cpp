#include "xlicense.h"
#include <QSettings>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QDebug>
#include <QKeyEvent>
#include <QClipboard>
#include <QTextStream>

#include "xlicensechecker.h"
#include "xsimplecrypt.h"
#include "xversion.h"
#include "xrandomgenerator.h"

CXLicense::CXLicense(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	_Init();
	_Load();

	ui.edit_Username->installEventFilter(this);
}

CXLicense::~CXLicense()
{
	_Save();
}

bool CXLicense::eventFilter(QObject * o, QEvent * e)
{
	Q_ASSERT(ui.edit_Username == o);

	if (e->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);
		if (keyEvent->modifiers() == Qt::ControlModifier && keyEvent->matches(QKeySequence::Paste))
		{
			QClipboard *pClipboard = QApplication::clipboard();
			_ParseClipboard(pClipboard->text());
			return true;
		}
	}

	return false;
}

void CXLicense::_Init()
{
	ui.groupBoxApp->setLayout(_InitAppLayout());
	ui.edit_Username->setText(CXLicenseChecker::GetLocalUsername());
	ui.edit_PC->setText(CXLicenseChecker::GetLocalHostname());
	ui.edit_MAC->setText(CXLicenseChecker::GetLocalMACAddress().front());
	ui.dateEdit_Start->setDate(QDate::currentDate());
	ui.dateEdit_End->setDate(QDate::currentDate().addMonths(6));

	connect(ui.btn_Test, &QPushButton::pressed, this, &CXLicense::slotTest);
	connect(ui.btn_Generate, &QPushButton::pressed, this, &CXLicense::slotGenerate);
	connect(ui.btn_GenerateOld, &QPushButton::pressed, this, &CXLicense::slotGenerateOld);
	connect(ui.btn_Local, &QPushButton::pressed, this, &CXLicense::slotLocal);
}

void CXLicense::_Load()
{
	QSettings cache("XStudio", "License");
	if (cache.allKeys().isEmpty())
		return;

	ui.edit_Username->setText(cache.value("username").toString());
	ui.edit_PC->setText(cache.value("pc_name").toString());
	ui.edit_MAC->setText(cache.value("pc_mac").toString());
}

void CXLicense::_Save()
{
	QSettings cache("XStudio", "License");
	cache.setValue("username", ui.edit_Username->text());
	cache.setValue("pc_name", ui.edit_PC->text());
	cache.setValue("pc_mac", ui.edit_MAC->text());
}

QLayout * CXLicense::_InitAppLayout()
{
	auto pLayout = new QGridLayout(this);
	QList<SVersion> listVersion = CXVersion::Instance().GetAllVersions();

	for (int i = 0; i != listVersion.size(); ++i)
	{
		auto pChkb = new QCheckBox(this);
		pChkb->setText(listVersion[i].m_strVerName);
		pChkb->setChecked(true);
		pLayout->addWidget(pChkb, i / 4, i % 4);
	}

	return pLayout;
}

QStringList CXLicense::_FetchCheckedApps()
{
	QStringList listChecked;
	for (auto&& pObj : ui.groupBoxApp->children())
	{
		auto pCheckBox = dynamic_cast<QCheckBox*>(pObj);

		if (pCheckBox && pCheckBox->isChecked())
			listChecked << pCheckBox->text();
	}
	return listChecked;
}

void CXLicense::_AddedRandomPerturbation(QJsonObject& obj)
{
	// Get random number between 50 ~ 100;
	CXRandomGenerator rand;
	int nNum = 50 + rand.GetValue() * 50;

	auto _GetRandomStr = [](int n)
	{
		QString ret(n, '*');
		for (auto &c : ret)
		{
			CXRandomGenerator ran;
			c = static_cast<char>(ran.GetValue() * 254);
		}
		return ret;
	};

	while (nNum --> 0)
	{
		obj["random" + QString::number(nNum)] = _GetRandomStr(nNum);
	}
}

void CXLicense::_AddedNoLimitsMark(QJsonObject& obj)
{
	if (!ui.chkb_NoLimits->isChecked())
		return;

	// write a great book name.
	obj["privilege"] = CXLicenseChecker::LICENSE_PRIVILEGE;
}

void CXLicense::_ParseClipboard(QString &text)
{
	QTextStream stream(&text);
	QString line;
	while (stream.readLineInto(&line))
	{
		QString k = line.section(": ", 0, 0);
		QString v = line.section(": ", 1);
		if (v.isEmpty())
		{
			ui.edit_Username->setText(line.trimmed());
			continue;
		}

		if ("username" == k.toLower())
			ui.edit_Username->setText(v.trimmed());
		else if ("pc name" == k.toLower())
			ui.edit_PC->setText(v.trimmed());
		else if ("mac address" == k.toLower())
			ui.edit_MAC->setText(v.trimmed());
	}
}

void CXLicense::slotTest()
{
	QString filename = QFileDialog::getOpenFileName(this, "Test License", CXLicenseChecker::LICENSE_FILE_NAME, "*.lic");
	if (filename.isEmpty()) return;

	QString strError;
	CXLicenseChecker::LicenseInfo info = CXLicenseChecker::DecryptoToInfo(filename, strError);
	if (!strError.isEmpty())
	{
		QMessageBox::warning(this, "Error", strError);
		return;
	}

	auto _GetPassedInfo = [](const CXLicenseChecker::LicenseInfo& info)
	{
		QString strApps;
		for (auto&& app : info.apps)
			strApps += app + ",";
		strApps.chop(1);

		return QString("Apps: %1\nUsername: %2\nPC Name: %3\nMAC: %4\nFrom: %5\nTo: %6\nPrivilege: %7")
			.arg(strApps)
			.arg(info.username)
			.arg(info.pcname)
			.arg(info.mac)
			.arg(info.begin.toString(Qt::ISODate))
			.arg(info.end.toString(Qt::ISODate))
			.arg(info.privilege.isEmpty() ? "No" : "Yes");
	};

	if (QMessageBox::Ok == QMessageBox::information(this, "Passed", _GetPassedInfo(info)))
	{
		for (auto&& pObj : ui.groupBoxApp->children())
		{
			auto pCheckBox = dynamic_cast<QCheckBox*>(pObj);
			if (!pCheckBox) continue;
			pCheckBox->setChecked(info.apps.contains(pCheckBox->text()));
		}

		ui.edit_Username->setText(info.username);
		ui.edit_PC->setText(info.pcname);
		ui.edit_MAC->setText(info.mac);
		ui.chkb_NoLimits->setChecked(!info.privilege.isEmpty());
	}
}

void CXLicense::slotGenerate()
{
	if (_FetchCheckedApps().isEmpty())
	{
		QMessageBox::warning(this, "Tips", "You should at least selected one application.");
		return;
	}

	auto _Encrypt = [&](const QString version, qint64 key)
	{
		QJsonObject info;
		info["version"] = version;
		info["apps"] = QJsonArray::fromStringList(_FetchCheckedApps());
		info["username"] = ui.edit_Username->text();
		info["pcname"] = ui.edit_PC->text();
		info["mac"] = ui.edit_MAC->text();
		info["from"] = ui.dateEdit_Start->date().toString(Qt::ISODate);
		info["to"] = ui.dateEdit_End->date().toString(Qt::ISODate);

		_AddedNoLimitsMark(info);
		_AddedRandomPerturbation(info);

		QJsonDocument doc(info);
		SimpleCrypt sc(key);
		//qDebug() << doc.toJson(QJsonDocument::Compact);
		return sc.encryptToString(doc.toJson(QJsonDocument::Compact));
	};

	QString filename = QFileDialog::getSaveFileName(this, "Generate License", CXLicenseChecker::LICENSE_FILE_NAME, "*.lic");
	if (filename.isEmpty()) return;

	QFile file(filename);
	if (!file.open(QFile::WriteOnly))
	{
		QMessageBox::warning(this, "Failed", "Cannot saved.");
		return;
	}

	QDataStream ds(&file);
	ds << _Encrypt(CXLicenseChecker::LICENSE_VERSION0, CXLicenseChecker::KEY0)
	   << _Encrypt(CXLicenseChecker::LICENSE_VERSION1, CXLicenseChecker::KEY1);
}

void CXLicense::slotGenerateOld()
{
	auto _Encrypt = [&](const QString type, qint64 key)
	{
		QJsonObject info;
		info["type"] = type;
		info["showname"] = ui.edit_Username->text();
		info["pcname"] = ui.edit_PC->text();
		info["pcmac"] = ui.edit_MAC->text();
		info["timefrom"] = ui.dateEdit_Start->date().toString(Qt::ISODate);
		info["timeend"] = ui.dateEdit_End->date().toString(Qt::ISODate);

		_AddedNoLimitsMark(info);
		_AddedRandomPerturbation(info);

		QJsonDocument doc(info);
		SimpleCrypt sc(key);
		//qDebug() << doc.toJson(QJsonDocument::Compact);
		return sc.encryptToString(doc.toJson(QJsonDocument::Compact));
	};

	QString filename = QFileDialog::getSaveFileName(this, "Generate License", "rocklab.lic", "*.lic");
	if (filename.isEmpty()) return;

	QFile file(filename);
	if (!file.open(QFile::WriteOnly))
	{
		QMessageBox::warning(this, "Failed", "Cannot saved.");
		return;
	}

	QDataStream ds(&file);
	ds << _Encrypt("CDlgLicOnCompute1", CXLicenseChecker::KEY0)
		<< _Encrypt("CDlgLicOnCompute2", CXLicenseChecker::KEY1);
}

void CXLicense::slotLocal()
{
	ui.edit_Username->setText(CXLicenseChecker::GetLocalUsername());
	ui.edit_PC->setText(CXLicenseChecker::GetLocalHostname());
	ui.edit_MAC->setText(CXLicenseChecker::GetLocalMACAddress().front());
}
