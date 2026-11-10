#include "xproject.h"

#include <QFile>
#include <qfileinfo.h>
#include <qstack.h>
#include <QSqlQuery>
#include <qmessagebox.h>
#include <qdir.h>
#include <QSettings>
#include <QApplication>

#include "xglobal.h"
#include "xobjectfactory.h"
#include "xdbio.h"
#include "xwaitcursor.h"
#include "xparametermanager.h"
#include "xviewinfomanager.h"
#include "xbaseparameter.h"
#include "xbasethread.h"
#include "xbaseconsole.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXProject)
EXProject
END_REGISTER_OBJECT_TO_FACTORY(CXProject)

void CXAutoSave::onTimeOut()
{
	auto pCurrProject = ::GetProject();
	auto pConsole = reinterpret_cast<CXBaseConsole*>(::GetConsole());
	if (pCurrProject && pCurrProject->IsAutoSave() && pConsole)
		if (CXBaseThreadManager::Instance().GetActiveThreadNum() == 0)
			pConsole->SaveProject();
}

CXProject::CXProject():CXObject()
{
	m_pDBIO = new CXDBIO;
	SetObjectType(EXProject);
	g_mapIDToObject.insert(this->GetObjectID(), this);
	_InitFont();

	QObject::connect(&m_timerSave, SIGNAL(timeout()), &m_autoSave, SLOT(onTimeOut()));
}

CXProject::CXProject(QString sName, QString sDir, bool bMetricUnit, QString sComments)
:CXObject(sName)
{
	m_pDBIO = new CXDBIO;

	SetObjectType(EXProject);

	m_sDirectory	= sDir;
	m_bMetricUnit	= bMetricUnit;
	m_sComments		= sComments;

	g_mapIDToObject.insert(this->GetObjectID(), this);
	_InitFont();

	QObject::connect(&m_timerSave, SIGNAL(timeout()), &m_autoSave, SLOT(onTimeOut()));
}

CXProject::~CXProject()
{	
	m_timerSave.stop();

	delete m_pDBIO;
	m_pDBIO = NULL;
}

QString CXProject::GetProjectPath()
{
	return m_sDirectory + QDir::separator();
}

QString CXProject::GetProjectDataPath(bool bTemporary)
{
	if (bTemporary)
	{
		return GetProjectPath() + this->GetObjectName() + QDir::separator() + QString("tmp") + QDir::separator();
	}
	else
	{
		return GetProjectPath() + this->GetObjectName() + QDir::separator();
	}
}


 bool CXProject::Serialize(bool bSave)
{
	// base object
	if (!CXObject::Serialize(bSave))
		return false;

	QString strTable = "rlproject";

	// save
	if (bSave)
	{
		QStringList strFieldList;
		strFieldList<<"ID";	
		strFieldList<<"Unit";
		strFieldList<<"Directory";
		strFieldList<<"Comments";
		strFieldList<<"WinManagerID";
		strFieldList<<"CurveAlias";
		strFieldList <<"IntervalPath";
		strFieldList <<"WellGroup";
		strFieldList << "ParaManagerID";

		QList<QVariant> vtList;

		vtList.append(GetObjectID().toString());
		vtList.append(m_bMetricUnit);

		vtList.append(m_sDirectory);
		vtList.append(m_sComments);
		vtList.append(m_uuidWinManager.toString());

		// curve alias
		QStringList listAlias;
		for (auto it = m_mapCurveAlias.begin(); it != m_mapCurveAlias.end(); ++it)
		{
			listAlias.append(it.key());
			listAlias.append(it.value().join('\v'));
		}
		vtList.append(listAlias.join('\r'));

		// interval
		vtList.append(m_LastIntervalsPath.join('\r'));

		// well group
		vtList.append(m_LastWellNames.join('\r'));

		// parameter manager ID
		vtList.append(m_uuidParaManager.toString());
		

		return ::GetDBIO()->UpdateInsert(strTable, strFieldList, vtList, GetObjectID().toString());
	}
	else
	{
		QStringList strFieldList;
		strFieldList<<"Unit";
		strFieldList<<"Directory";
		strFieldList<<"Comments";
		strFieldList<<"WinManagerID";
		strFieldList<<"CurveAlias";
		strFieldList << "IntervalPath";
		strFieldList << "WellGroup";
		strFieldList << "ParaManagerID";

        QSqlQuery query = ::GetDBIO()->Select(strTable, strFieldList, this->GetObjectID().toString());

		if( query.first() )
		{
			int nIndex = -1;

			m_bMetricUnit = query.value(++nIndex).toBool();
			QString sDirectoryTmp = query.value(++nIndex).toString();
			m_sComments = query.value(++nIndex).toString();
			m_uuidWinManager = query.value(++nIndex).toString();

			QString strAlias = query.value(++nIndex).toString();
			QStringList strListAlias = strAlias.split("\r");
			m_mapCurveAlias.clear();
			for (int i = 0; i < strListAlias.size() / 2; ++i)
			{
				QString strKey = strListAlias[2*i];
				QStringList strListValue = strListAlias[2 * i + 1].split('\v');
				m_mapCurveAlias.insert(strKey, strListValue);
			}

			QString strIntervalPath = query.value(++nIndex).toString();
			m_LastIntervalsPath = strIntervalPath.split("\r");

			QString strWellGroup = query.value(++nIndex).toString();
			m_LastWellNames = strWellGroup.split("\r");

			m_uuidParaManager = query.value(++nIndex).toString();
		}

		return true;
	}
}

bool CXProject::InitNewProject()
 {
	 QApplication::setFont(m_font);
	 QString strDefaultDBFileName = CXDBIO::GetDefaultDBFileName();

	 if (!QFile::exists(strDefaultDBFileName))
		 return false;
	 
	 QString strProjectFileName = GetProjectPath() + this->GetObjectName() + ".rdb";

	 if (QFile::exists(strProjectFileName))
	 {
		 QString strMsg = "The selected project file already exists. Please choose a different name.";
		 QMessageBox::warning(NULL, "Warning", strMsg);
		 return false;
	 }
	 else
	 {
		 QFile::remove(strProjectFileName);
	 }		 

	 // make new project file and the directory
	 QFile::copy(strDefaultDBFileName, strProjectFileName);

	 QDir dir(m_sDirectory);
	 dir.mkdir(this->GetObjectName());

	 m_pDBIO->ConnectDB(strProjectFileName);

	 m_timerSave.start(GetSaveInterval() * 60 * 1000);

	 return true;
 }

 void CXProject::Save()
 {
	 CXWaitCursor waitCursor;

	 ::GetDBIO()->Transaction();

	 QStack<CXObject*> stack;
	 stack.push(this);	 

	 while(!stack.empty())
	 {
		 CXObject* pObj = stack.pop();

		 pObj->Serialize(true);		

		 QList<CXObject*> listChildren = pObj->GetChildrenList();

		 for (int i=listChildren.size()-1; i>=0; --i)
		 {
			 stack.push(listChildren.at(i));
		 }
	 }	

	 // delete objects
	 QDir dir(GetProjectDataPath());
	 QStringList listFileName = dir.entryList(QDir::Files);
	 for (int i=0; i<m_listDeletedObjID.size(); ++i)
	 {
		 // delete from database
		 ::GetDBIO()->Delete(m_listDeletedObjID.at(i).toString());

		 // delete from disk
		 QString strFileNamePrefix =  m_listDeletedObjID.at(i).toString();		 
		 for (int j=0; j<listFileName.size(); ++j)
		 {
			 if (listFileName.at(j).contains(strFileNamePrefix))
			 {
				 QString strFileName = GetProjectDataPath() + listFileName.at(j);
				 QFile::remove(strFileName);
			 }
		 }
	 }
	 m_listDeletedObjID.clear();

	 ::GetDBIO()->Commit();

	 _DeleteUnusedFiles();

	 ::SetProjectDirty(false);
 }

 void CXProject::_DeleteUnusedFiles()
 {
	 QString strDataFilePath = GetProjectDataPath();
	 QDir dir(strDataFilePath);
	 QStringList listFileName = dir.entryList(QDir::Files);
	 for (int i = 0; i < listFileName.size(); ++i)
	 {
		 QString strAbsFileName = strDataFilePath + listFileName.at(i);
		 QFileInfo fileInfo(strAbsFileName);
		 QUuid uuid(fileInfo.baseName());
		 if (!uuid.isNull() && !g_mapIDToObject.contains(uuid))
		 {
			 QFile::remove(strAbsFileName);
		 }
	 }
 }

 void CXProject::Load(const QString& strProjectName)
 {
	 CXWaitCursor waitCursor;

	 ::GetDBIO()->Transaction();


	 // load project
	 QString projectID =  ::GetDBIO()->GetProjectID();
	 this->SetObjectID(projectID);
	 this->SetObjectType(EXProject);

	 this->Serialize(false);
	 g_mapIDToObject.insert(this->GetObjectID(), this);

	 // modify project name from outside
	 if (strProjectName != this->GetObjectName())
	 {
		 this->SetObjectName(strProjectName);
	 }

	 // load the rest
	 QStack<CXObject*> stack;
	 stack.push(this);

	 while(!stack.empty())
	 {
		 CXObject* pParentObj = stack.pop();

		 QStringList childrenIDs =::GetDBIO()->GetChildrenIDs(pParentObj->GetObjectID().toString());

		 for (int i=0; i<childrenIDs.size(); ++i)
		 {
			 EXObjectType eObjType = ::GetDBIO()->GetObjectTypeFromID(childrenIDs.at(i));

			 CXObject* pObj = dynamic_cast<CXObject*>(CXObjectFactory::Instance().CreateObject(eObjType));

			 if (!pObj)
				 continue;

			 pObj->SetObjectID(childrenIDs.at(i));

			 pObj->Serialize(false);

			 pParentObj->AddChild(pObj);

			 stack.push(pObj);
		 }
	 }
	 
	 QApplication::setFont(m_font);

	 ::GetDBIO()->Commit();

	 _DeleteUnusedFiles();

	 m_timerSave.start(GetSaveInterval() * 60 * 1000);
 }

 void CXProject::AddDeletedObjectID(const QUuid& objID)
 {
	 m_listDeletedObjID.append(objID);

	 // Add associated parameter to the ID list that will be deleted.
	 CXBaseParameter* pPara = CXParameterManager::Instance().GetParameterByID(objID);
	 if (pPara)
	 {
		 //m_listDeletedObjID.append(pPara->GetObjectID());
		 CXParameterManager::Instance().RemoveOneParameter(objID);
	 }

	 // Add associated view info to the ID list that will be deleted.
	 CXViewInfoManager::Instance().RemoveOneViewInfo(objID);
 }

void CXProject::LoadDefaultSetting()
{
    QSettings settings("XStudio", "AppSetting");
    if (!settings.contains("AutoSave"))
    {
        settings.setValue("AutoSave", true);
        settings.setValue("SaveInterval", 10);
    }

    EnableAutoSave(settings.value("AutoSave").toBool());
    SetSaveInterval(settings.value("SaveInterval").toInt());
}

bool CXProject::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_bAutoSave << m_iSaveInterval << m_font.family() << m_font.pointSize() << m_font.bold() << m_font.italic();
	}
	else
	{
		QString fontFamily;
		int fontSize;
		bool bBold, bItalic;
		
		ar >> m_bAutoSave >> m_iSaveInterval >> fontFamily >> fontSize >> bBold >> bItalic;
		
		m_font.setFamily(fontFamily);
		m_font.setPointSize(fontSize);
		m_font.setBold(bBold);
		m_font.setItalic(bItalic);
	}

	return true;
}

void CXProject::_InitFont()
{
	m_font.setFamily("arial");
	m_font.setPointSize(9);
}

int CXProject::GetSaveInterval() const
{
	if (m_iSaveInterval == 0)
		return 10;

	return m_iSaveInterval;		
}

void CXProject::SetSaveInterval(int iSaveInterval)
{
	m_iSaveInterval = iSaveInterval;

	m_timerSave.start(m_iSaveInterval * 60 * 1000);
}

void CXProject::SetCurveAlias(const QMap<QString, QStringList>& map)
{
	m_mapCurveAlias = map;
	SetModifiedFlag();
}


void CXProject::AddLastIntervalsPath(QString str0)
{
	m_LastIntervalsPath.prepend(str0);
	m_LastIntervalsPath.removeDuplicates();
	while (m_LastIntervalsPath.count()>20)
	{
		m_LastIntervalsPath.removeLast();
	}
	SetModifiedFlag();
}

void CXProject::AddLastWellName(QString str0)
{
	m_LastWellNames.prepend(str0);
	m_LastWellNames.removeDuplicates();
	while (m_LastWellNames.count() > 20)
	{
		m_LastWellNames.removeLast();
	}
	SetModifiedFlag();
}