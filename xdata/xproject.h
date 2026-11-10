#ifndef XPROJECT_H
#define XPROJECT_H

#include "xobject.h"
#include "xdata_global.h"

#include <qfont.h>
#include <qmap.h>
#include <qtimer.h>

class CXDBIO;

class CXAutoSave : public QObject
{
	Q_OBJECT
		public slots:
	static void onTimeOut();
};

class XDATA_EXPORT CXProject : public CXObject
{
public:
	CXProject();
	CXProject(QString sName, QString sDir, bool bMetricUnit, QString sComments);
	CXProject(const CXProject& other) = delete;
	CXProject& operator=(const CXProject& other) = delete;
	~CXProject();

	bool UsingMetricUnit()
	{
		return m_bMetricUnit;
	}

	///@brief Get the project path
	QString GetProjectPath();

	///@brief Get the project data path
	QString GetProjectDataPath(bool bTemporary = false);

	///@breif Serialize function
	virtual bool Serialize(bool bSave);

	virtual bool SerializeData(CXArchive& ar) override;

	///@breif Create a new project
	bool InitNewProject();

	///@brief Save and load the whole project
	void Save();
	void Load(const QString& strProjectName);

	///@brief Get the DB IO of the project
	CXDBIO* GetDBIO() {return m_pDBIO;}

	///@brief Add deleted object
	void AddDeletedObjectID(const QUuid& objID);

	///@brief Set and get window manager ID
	void SetWindowManagerID(const QUuid& winManagerID) {m_uuidWinManager = winManagerID;}
	QUuid GetWindowManagerID() {return m_uuidWinManager;}

    void LoadDefaultSetting();
    bool IsAutoSave() const { return m_bAutoSave; }
    void EnableAutoSave(bool bAutoSave) { m_bAutoSave = bAutoSave; }

	int GetSaveInterval() const;
	void SetSaveInterval(int iSaveInterval);

	QFont GetFont() const { return m_font; }
	void SetFont(QFont font) { m_font = font; }

	///@brief For curve alias
	QMap<QString, QStringList>& GetCurveAlias() { return m_mapCurveAlias; }
	void SetCurveAlias(const QMap<QString, QStringList>& map);

	///@brief For Well Intervals select
	QStringList GetLastIntervalsPath(){ return m_LastIntervalsPath; }
	void AddLastIntervalsPath(QString);

	///@brief For Well select
	QStringList GetLastWellNames(){ return m_LastWellNames; }
	void AddLastWellName(QString);

	///@brief Set and get parameter manager ID
	void SetParaManagerID(const QUuid& uuidParaManagerID) { m_uuidParaManager = uuidParaManagerID; }
	QUuid GetParaManagerID() { return m_uuidParaManager; }

	float GetCellSize()
	{
		return 250.;
	}

	int GetBaseSHDirection()
	{
		return 0;
	}

	float GetReplacementVelocity()
	{
		return 2000.;
	}

private:
	void _InitFont();
	void _DeleteUnusedFiles();

private:
	bool		m_bMetricUnit;		//	Use metric unit or imperial unit system.
	QString		m_sDirectory;		//	Directory to store data.
	QString		m_sComments;		//	Any comments offered by user.	
    bool		m_bAutoSave;		//  Whether automatically save current project.
    int			m_iSaveInterval;	//  how long between two auto-saving.(minutes)
	QFont		m_font;				//  The font of application.

	QUuid		m_uuidParaManager;

	// DB IO of the project
	CXDBIO* m_pDBIO;

	// Deleted objects
	QList<QUuid> m_listDeletedObjID;

	// window manager ID
	QUuid m_uuidWinManager;

	// for curve alias
	QMap<QString, QStringList> m_mapCurveAlias;

	// for well
	QStringList m_LastIntervalsPath;
	QStringList m_LastWellNames;
		
	// for auto save.
	QTimer m_timerSave;
	CXAutoSave	m_autoSave;
};

#endif // RLPROJECT_H
