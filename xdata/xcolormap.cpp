#include "xcolormap.h"
#include <qdir.h>
#include <qrgb.h>
#include <vector>
#include <QtSql>
#include <QVector3D>
#include <QMessageBox>
#include <qpainter.h>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

#include "xlog.h"
#include "xdbio.h"
#include "xsaveload.h"
#include "xglobal.h"

QList<CXColormap> CXColormap::m_stdListColormap;

bool CXColormap::InitializeColormapsFromFile()
{
	QString colormapDir = CXDBIO::GetColormapFilePath();
	QDir qDir(colormapDir);
    if (!qDir.exists())
    {
        CXLog::AddLog("Can not find the colormap directory at " + colormapDir + "!");
        return false;
    }

    QStringList sListFilter;
    sListFilter << "*.colormap.json";
    QStringList sListFiles = qDir.entryList(sListFilter, QDir::Files);

    if (sListFiles.isEmpty())
    {
        CXLog::AddLog("No colormap files found at " + colormapDir + "!");
        return false;
    }

    for (const auto& fileName : sListFiles)
    {
        QString fileDir = colormapDir + QDir::separator() + fileName;

        QFileInfo fileInfo(fileDir);

        // open file
        QFile file(fileDir);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            Q_ASSERT(false);
        }

        QTextStream stream(&file);
        stream.skipWhiteSpace();
        
        CXColormap colormap(fileInfo.baseName(), stream.readAll());
        m_stdListColormap << colormap;
    }

    return true;
}

bool CXColormap::InitializeColormapsFromTemplateDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(CXDBIO::GetDefaultDBFileName());

    if (!db.open())
    {
        CXLog::AddLog("Open DB error: " + CXDBIO::GetDefaultDBFileName());
        qDebug() << db.lastError();
        return false;
    }

    QSqlQueryModel model;
    model.setQuery("Select * from Colormap");
    for (int i = 0; i < model.rowCount(); ++i)
    {
        QString colormapName = model.record(i).value("ColormapName").toString();
        QString colormapContent = model.record(i).value("ColormapData").toString();
        CXColormap colormap(colormapName, colormapContent);
        m_stdListColormap << colormap;
    }

    return true;
}

bool CXColormap::InitializeColormapsFromJason(const QString& jasonColorScalesDir)
{
    QDir qDir(jasonColorScalesDir);
    if (!qDir.exists())
    {
        CXLog::AddLog("Can not find the jason 8.4 colormap directory at " + jasonColorScalesDir + "!");
        return false;
    }

    QStringList sListFilter;
    sListFilter << "*.shs";
    QStringList sListFiles = qDir.entryList(sListFilter, QDir::Files);
    
    if (sListFiles.isEmpty())
    {
        CXLog::AddLog("No colormap files found at " + jasonColorScalesDir + "!");
        return false;
    }

    for (const auto& fileName : sListFiles)
    {
        QString fileDir = jasonColorScalesDir + QDir::separator() + fileName;

        QFileInfo fileInfo(fileDir);

        // open file
        QFile file(fileDir);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            Q_ASSERT(false);
        }

        // read control points
        bool bRgb = false;
        bool bAlpha = false;
        QMap<int, QRgb> mapRgb;
        QMap<int, uchar> mapAlpha;

        int numCol = 0;
        qreal pos, r, g, b, a;

        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            QString line = stream.readLine();

            if (line.section(':', 0, 0) == "number_of_colors")
            {
                numCol = line.section('=', 1).remove(';').trimmed().toInt();
            }

            if (line.section(':', 0, 0) == "rgb_control_points") // rgb begin
            {
                bRgb = true;
            }
            else if (line.section(':', 0, 0) == "alpha_control_points") // alpha begin
            {
                bAlpha = true;
            }
            else if (line == ";")
            {
                bRgb = false;
                bAlpha = false;
            }

            if (bRgb)
            {
                if (line.contains("fraction:real"))
                {
                    pos = line.section('=', 1).remove(';').trimmed().toDouble();
                }
                else if (line.contains("red:real"))
                {
                    r = line.section('=', 1).remove(';').trimmed().toDouble();
                }
                else if (line.contains("green:real"))
                {
                    g = line.section('=', 1).remove(';').trimmed().toDouble();
                }
                else if (line.contains("blue:real"))
                {
                    b = line.section('=', 1).remove(';').trimmed().toDouble();

                    QColor color(qRound(r / 100 * 255), qRound(g / 100 * 255), qRound(b / 100 * 255));
                    mapRgb.insert(qRound(pos * (numCol - 1)), color.rgb());
                }
            }
            
            if (bAlpha)
            {
                if (line.contains("fraction:real"))
                {
                    pos = line.section('=', 1).remove(';').trimmed().toDouble();
                }
                else if (line.contains("alpha:real"))
                {
                    a = line.section('=', 1).remove(';').trimmed().toDouble();

                    mapAlpha.insert(qRound(pos * (numCol - 1)), qBound((uchar)0, (uchar)(a / 100 * 255), (uchar)255));
                }
            }
        }
       
        CXColormap colormap(fileInfo.baseName(), mapRgb, mapAlpha, numCol);
        m_stdListColormap << colormap;
    }

    return true;
}

bool CXColormap::InitializeColormapsFromProjectDB()
{
	if (!::GetProject() || !::GetDBIO())
	{
		QMessageBox::warning(nullptr, "project or db error!", "Cannot find current project or connect rdb failed.", QMessageBox::Ok);
		return false;
	}

	if (!::GetDBIO()->GetDB()->isOpen())
	{
		QMessageBox::warning(nullptr, "rdb error!", "Connected rdb failed.", QMessageBox::Ok);
		return false;
	}

	QSqlQueryModel model;
	model.setQuery("Select * from Colormap", *::GetDBIO()->GetDB());
	for (int i = 0; i < model.rowCount(); ++i)
	{
		QString colormapName = model.record(i).value("ColormapName").toString();
		QString colormapContent = model.record(i).value("ColormapData").toString();
		CXColormap colormap(colormapName, colormapContent);
		m_stdListColormap << colormap;
	}

	if (m_stdListColormap.isEmpty() || m_stdListColormap.first().IsCustomized()) // old project don't have template colormap.
	{
		InitializeColormapsFromTemplateDB();
	}

	//	LandMark colormap.
	CXColormap lColormap(CXDBIO::GetColormapFile("Landmark.CLM"), 0);
	m_stdListColormap << lColormap;

	//	Now to add spectial colormap for GSM
	CXColormap colormap(CXDBIO::GetColormapFile("stressmap.pal"), 1);
	m_stdListColormap << colormap;

	Q_ASSERT(!m_stdListColormap.isEmpty());

	return true;
}

bool CXColormap::WriteColormapsToTemplateDB()
{
    CXDBIO db;
    if (!db.ConnectDB(CXDBIO::GetDefaultDBFileName()))
        return false;

    QStringList listName = CXColormap::GetAllColormapsName();
    QStringList listField{ "ColormapName", "ColormapData" };

    db.Transaction();
    for (int i = 0; i < listName.size(); ++i)
    {
        QList<QVariant> vtList;

        CXColormap *pColormap = CXColormap::GetColormap(listName.at(i));

		QByteArray outData;
		pColormap->_WriteToJson(outData);

        vtList.append(listName.at(i));
		vtList.append(outData);

        db.Insert("Colormap", listField, vtList);
    }
    db.Commit();

    return true;
}

bool CXColormap::WriteColormapsToFile()
{
    for (const QString& fileName : CXColormap::GetAllColormapsName())
    {
        CXColormap *pColormap = CXColormap::GetColormap(fileName);
        pColormap->SaveAs(QDir::currentPath() + QDir::separator() + "Colormap");
    }

    return true;
}

bool CXColormap::ImportColormapFromFile(const QString& strFilePath)
{
	QFileInfo fileInfo(strFilePath);

	// open file
	QFile file(strFilePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return false;
	}

	QTextStream stream(&file);
	stream.skipWhiteSpace();

	CXColormap colormap(fileInfo.baseName(), stream.readAll());
	m_stdListColormap << colormap;

	return true;
}

QStringList CXColormap::GetAllColormapsName()
{
	QStringList strListName;

	for(int i = 0; i< m_stdListColormap.size(); i++)
	{
		strListName<<m_stdListColormap[i].GetName();
	}

	return strListName;
}

CXColormap* CXColormap::GetColormap(const QString& strName)
{
	for(int i = 0; i< m_stdListColormap.size(); i++)
	{
		if(m_stdListColormap[i].GetName() == strName)
			return &(m_stdListColormap[i]);
	}

	return NULL;
}

CXColormap* CXColormap::GetColormap(unsigned int iIDX)
{
	if(iIDX >= m_stdListColormap.size())
		return NULL;
	else
		return &(m_stdListColormap[iIDX]);
}

CXColormap* CXColormap::GetCustomizedColormap(CXColormap* pBaseColormap)
{
	QStringList listColormapName = GetAllColormapsName();

	int customIndex = listColormapName.indexOf("customized");
	if (customIndex != -1)
	{
		Q_ASSERT(m_stdListColormap[customIndex].GetName() == "customized");
		m_stdListColormap[customIndex] = *pBaseColormap;
		m_stdListColormap[customIndex].m_mapGeologicMask.clear();
		m_stdListColormap[customIndex].m_strName = "customized";
		return &m_stdListColormap[customIndex];
	}
	else
	{
		m_stdListColormap.push_back(*pBaseColormap);
		m_stdListColormap.last().m_strName = "customized";
		return &m_stdListColormap.last();
	}
}

QPixmap CXColormap::GeneratePixmap(const QString & name)
{
	QSize iconSize(55, 10);
	QPixmap pixmap(iconSize);
	QPainter painter(&pixmap);

	CXColormap *colormap = CXColormap::GetColormap(name);
	QLinearGradient gradient(0, iconSize.height() / 2, iconSize.width(), iconSize.height() / 2);

	for (int i = 0; i != colormap->GetColorNum(); ++i)
	{
		gradient.setColorAt(i * 1.0 / (colormap->GetColorNum() - 1), colormap->ColorAt(i));
	}

	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(QBrush(gradient), iconSize.height()));
	painter.drawLine(0, iconSize.height() / 2, iconSize.width(), iconSize.height() / 2);

	return pixmap;
}

QColor CXColormap::GetColorAt(unsigned char iIDX)
{
	// assume that always have 255 color. (for compatible)
	Q_ASSERT(0 <= iIDX && iIDX < 256);

	if (iIDX == 255)
	{
		iIDX = 254; // last color for invalid color.
	}

	int realIndex = qRound(iIDX * 1.0 / 254 * (m_colorNum - 1));
	return m_listColor[realIndex];
}

const QColor& CXColormap::ColorAt(int index) const
{
    Q_ASSERT(0 <= index && index < m_colorNum);

    return m_listColor[index];
}

QRgb CXColormap::GetRgbAt(int index) const
{
    Q_ASSERT(0 <= index && index < m_colorNum);

    return m_listColor[index].rgb();
}

QString CXColormap::GetName() const
{
    return m_strName;
}

QList<int> CXColormap::GetControlPointsIndex() const
{
    return m_mapControlPointsRgb.keys();
}

int CXColormap::GetColorNum() const
{
    return m_colorNum;
}

const QMap<int, QRgb>& CXColormap::GetGeologicMask() const
{
	return m_mapGeologicMask;
}

const QMap<int, uchar>& CXColormap::GetAlphaMap() const
{
	return m_mapControlPointsAlpah;
}

bool CXColormap::IsCustomized() const
{
	return m_strName == "customized";
}

bool CXColormap::SaveAs(const QString& strFilePath)
{
    QFile saveFile(strFilePath);
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
        return false;
    }

	QByteArray outData;
	_WriteToJson(outData, true);
	saveFile.write(outData);

    return true;
}

bool CXColormap::SaveToProjectDB()
{
	QStringList listName = CXColormap::GetAllColormapsName();
	QStringList listField{ "ColormapName", "ColormapData" };

	QByteArray outData;
	_WriteToJson(outData);

	QList<QVariant> vtList;
	vtList.append(m_strName);
	vtList.append(outData);

	QStringList keyName{ "ColormapName" };
	QStringList key{ m_strName };

	return ::GetDBIO()->UpdateInsert("Colormap", listField, vtList, keyName, key);
}

void CXColormap::SetControlPointRgb(int index, const QRgb& rgb)
{
    m_mapControlPointsRgb[index] = rgb;

    _UpdateColormap();
}

void CXColormap::DeleteControlPoint(int index)
{
    m_mapControlPointsRgb.remove(index);

	if (m_mapControlPointsRgb.empty())
		return;

    _UpdateColormap();
}

void CXColormap::UpdateControlPoint(int oldIndex, int newIndex, const QRgb& newRgb)
{
    if (newIndex == oldIndex)
        return;

    m_mapControlPointsRgb.insert(newIndex, newRgb);
    m_mapControlPointsRgb.remove(oldIndex);

    _UpdateColormap();
}

void CXColormap::SetGeologicMask(int index, const QRgb& rgb)
{
	m_mapGeologicMask.insert(index, rgb);

	int offset = m_colorNum / 100;
	int maskBeg = qMax(0, index - offset);
	int maskEnd = qMin(m_colorNum - 1, index + offset);

	for (int i = maskBeg; i <= maskEnd; ++i)
	{
		m_listColor[i] = rgb;
	}
}

bool CXColormap::DeleteGeologicMask(int index)
{
	if (!m_mapGeologicMask.contains(index))
		return false;

	m_mapGeologicMask.remove(index);
	_UpdateColormap();
	return true;
}

void CXColormap::UpdateGeologicMask(int oldIndex, int newIndex, const QRgb& newRgb)
{
	if (oldIndex == newIndex)
		return;

	DeleteGeologicMask(oldIndex);
	SetGeologicMask(newIndex, newRgb);
}

void CXColormap::ClearAlpha()
{
	m_mapControlPointsAlpah.clear();

	for (int i = 0; i != m_colorNum; ++i)
	{
		m_listColor[i].setAlpha(255);
	}
}

void CXColormap::DeleteOpacityPoint(int index)
{
	m_mapControlPointsAlpah.remove(index);

	m_listColor[index].setAlpha(255);
}

void CXColormap::SetAlpha(int index, uchar alpha)
{
	m_mapControlPointsAlpah.insert(index, alpha);

	m_listColor[index].setAlpha(alpha);
}

void CXColormap::Flip()
{
    QList<int> indices = m_mapControlPointsRgb.keys();
    QList<QRgb> rgbs = m_mapControlPointsRgb.values();

    m_mapControlPointsRgb.clear();

    for (auto i = 0; i != indices.size(); ++i)
    {
        m_mapControlPointsRgb.insert(m_colorNum - indices.at(i) - 1, rgbs.at(i));
    }

    indices = m_mapControlPointsAlpah.keys();
    QList<uchar> alphas = m_mapControlPointsAlpah.values();

    m_mapControlPointsAlpah.clear();

    for (auto i = 0; i != indices.size(); ++i)
    {
        m_mapControlPointsAlpah.insert(m_colorNum - indices.at(i) - 1, alphas.at(i));
    }

    _UpdateColormap();
}

const QColor& CXColormap::GetInvalidColor() const
{
	return m_listColor[cInvalidColorIndex];
}

void CXColormap::SetInvalidColor(const QColor& color)
{
	m_listColor[cInvalidColorIndex] = color;
}

CXColormap::CXColormap(const QString& sName, const QMap<int, QRgb>& mapRgb, const QMap<int, uchar>& mapAlpha, int colNum, QColor invalidCol)
    :m_strName(sName)
{
    if (mapRgb.size() < 2)
        throw "At least have two control points.";

    m_mapControlPointsRgb = mapRgb;
    m_mapControlPointsAlpah = mapAlpha;
    m_colorNum = colNum;
	m_listColor[cInvalidColorIndex] = invalidCol;

    _UpdateColormap();
}

CXColormap::CXColormap(const QString& fileName, const QString& jsonText)
    : m_strName(fileName)
{
    rapidjson::Document jsonDoc;
    jsonDoc.Parse(jsonText.toUtf8().constData());

    if (!jsonDoc.HasMember("number") || !jsonDoc.HasMember("invalid_point") || !jsonDoc.HasMember("rgb_control_points") || !jsonDoc.HasMember("alpha_control_points"))
        return;

    m_colorNum = jsonDoc["number"].GetInt();

	m_listColor[cInvalidColorIndex].setRed(jsonDoc["invalid_point"]["red"].GetInt());
	m_listColor[cInvalidColorIndex].setGreen(jsonDoc["invalid_point"]["green"].GetInt());
	m_listColor[cInvalidColorIndex].setBlue(jsonDoc["invalid_point"]["blue"].GetInt());
	m_listColor[cInvalidColorIndex].setAlpha(jsonDoc["invalid_point"]["alpha"].GetInt());

    const rapidjson::Value& rgbPoints = jsonDoc["rgb_control_points"];
    for (rapidjson::SizeType i = 0; i != rgbPoints.Size(); ++i)
    {
        m_mapControlPointsRgb.insert(rgbPoints[i]["position"].GetInt(), qRgb(rgbPoints[i]["red"].GetInt(), rgbPoints[i]["green"].GetInt(), rgbPoints[i]["blue"].GetInt()));
    }

    const rapidjson::Value& alphaPoints = jsonDoc["alpha_control_points"];
    for (rapidjson::SizeType i = 0; i != alphaPoints.Size(); ++i)
    {
        m_mapControlPointsAlpah.insert(alphaPoints[i]["position"].GetInt(), alphaPoints[i]["alpha"].GetInt());
    }

    _UpdateColormap();
}

CXColormap::CXColormap(QString sPalFile, int iType)
{
	QFileInfo qFI(sPalFile);
	m_strName = qFI.baseName();

	// open file
	QFile qFile(sPalFile);
	if (!qFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		assert(false);
	}

	bool bDiscrete = false;
	QString strLine;
	QStringList strListLine;
	std::vector<unsigned char> vecA, vecR, vecG, vecB;
	int iInd = 0;
	QList<QString> m_listStates;

	if (iType == 1)
	{
		// read head
		while (!qFile.atEnd())
		{
			strLine = qFile.readLine();
			if (strLine.contains("Discrete = 1"))
			{
				bDiscrete = true;
				continue;
			}

			if (bDiscrete && strLine.contains("ColorState"))
			{
				strLine.remove("ColorState", Qt::CaseInsensitive);
				strLine.remove("=", Qt::CaseInsensitive);
				m_listStates << strLine.simplified();
				continue;
			}

			if (strLine.contains("<ColorMap>"))
				break;
		}

		// read data
		while (!qFile.atEnd())
		{
			strLine = qFile.readLine();
			if (strLine.contains("</ColorMap>"))
				break;

			strLine.remove("Color", Qt::CaseInsensitive);
			strLine.remove("=", Qt::CaseInsensitive);
			strLine = strLine.simplified();
			strListLine = strLine.split(',', QString::SkipEmptyParts);
			if (strListLine.size() < 4)
				break;

			vecA.push_back(strListLine[0].toShort());
			vecR.push_back(strListLine[1].toShort());
			vecG.push_back(strListLine[2].toShort());
			vecB.push_back(strListLine[3].toShort());

			m_listColor[iInd].setRgb(strListLine[1].toShort(), strListLine[2].toShort(), strListLine[3].toShort());
			iInd++;
			if (iInd >= 256)
				break;
		}
	}
	else if (iType == 0)
	{
		while (!qFile.atEnd())
		{
			strLine = qFile.readLine();
			strLine = strLine.simplified();
			strListLine = strLine.split(' ', QString::SkipEmptyParts);
			if (strListLine.size() != 3)
				continue;

			vecR.push_back(strListLine[0].toShort());
			vecG.push_back(strListLine[1].toShort());
			vecB.push_back(strListLine[2].toShort());

			m_listColor[iInd].setRgb(strListLine[0].toShort(), strListLine[1].toShort(), strListLine[2].toShort());
			iInd++;
			if (iInd >= 256)
				break;
		}
	}

	qFile.close();
	m_colorNum = 256;
	int iRed[256], iGreen[256], iBlue[256];
	if (!bDiscrete)
	{
		int i, nSize = (int)vecR.size();
		int IInterval = 256 / nSize;
		for (i = 0; i < nSize; ++i)
		{
			//iAlpha[i*IInterval] = vecA[i];
			iRed[i*IInterval] = vecR[i];
			iGreen[i*IInterval] = vecG[i];
			iBlue[i*IInterval] = vecB[i];

			if (i < nSize - 1)
			{
				for (int j = i * IInterval + 1; j < (i + 1)*IInterval; ++j)
				{
					float fFactor = (j - i * IInterval)*1.f / IInterval;
					//iAlpha[j] = vecA[i] * (1.f - fFactor) + vecA[i + 1] * fFactor;
					iRed[j] = vecR[i] * (1.f - fFactor) + vecR[i + 1] * fFactor;
					iGreen[j] = vecG[i] * (1.f - fFactor) + vecG[i + 1] * fFactor;
					iBlue[j] = vecB[i] * (1.f - fFactor) + vecB[i + 1] * fFactor;
				}

			}
		}

		//iAlpha[255] = iAlpha[254];
		iRed[255] = iRed[254];
		iGreen[255] = iGreen[254];
		iBlue[255] = iBlue[254];

		for (i = 0; i < 256; i++)
		{
			m_listColor[i].setRgb(iRed[i], iGreen[i], iBlue[i]);
		}
	}
	else
	{
		//m_nDiscreteNum = vecA.size();
		//memcpy(m_iAlpha, &vecA[0], sizeof(unsigned char) * vecA.size());
		//memcpy(m_iRed, &vecR[0], sizeof(unsigned char) * vecR.size());
		//memcpy(m_iGreen, &vecG[0], sizeof(unsigned char) * vecG.size());
		//memcpy(m_iBlue, &vecB[0], sizeof(unsigned char) * vecB.size());
	}
}

CXColormap::CXColormap(const CXColormap& colormap)
    : m_strName(colormap.m_strName)
    , m_mapControlPointsRgb(colormap.m_mapControlPointsRgb)
    , m_mapControlPointsAlpah(colormap.m_mapControlPointsAlpah)
    , m_colorNum(colormap.m_colorNum)
{
    for (auto i = 0; i != m_colorNum; ++i)
    {
        m_listColor[i] = colormap.ColorAt(i);
    }

	m_listColor[cInvalidColorIndex] = colormap.GetInvalidColor();
}

CXColormap& CXColormap::operator = (const CXColormap& colormap)
{
    m_strName = colormap.m_strName;
    m_mapControlPointsRgb = colormap.m_mapControlPointsRgb;
    m_mapControlPointsAlpah = colormap.m_mapControlPointsAlpah;
    m_colorNum = colormap.m_colorNum;

    for (auto i = 0; i != m_colorNum; ++i)
    {
        m_listColor[i] = colormap.ColorAt(i);
    }

	m_listColor[cInvalidColorIndex] = colormap.GetInvalidColor();

    return *this;
}

void CXColormap::_UpdateColormap()
{
    if (m_mapControlPointsRgb.firstKey() != 0)
    {
        for (auto i = 0; i != m_mapControlPointsRgb.firstKey(); ++i)
        {
            m_listColor[i] = m_mapControlPointsRgb.first();
        }
    }

    // interpolation
    for (auto iter = m_mapControlPointsRgb.cbegin(); iter != m_mapControlPointsRgb.cend(); ++iter)
    {
        if (std::next(iter) == m_mapControlPointsRgb.cend())
            break;

        for (auto i = iter.key(); i != std::next(iter).key(); ++i)
        {
            float factor = (i - iter.key()) * 1.0f / (std::next(iter).key() - iter.key());

            m_listColor[i].setRed(qRed(iter.value()) + qRound((qRed(std::next(iter).value()) - qRed(iter.value())) * factor));
            m_listColor[i].setGreen(qGreen(iter.value()) + qRound((qGreen(std::next(iter).value()) - qGreen(iter.value())) * factor));
            m_listColor[i].setBlue(qBlue(iter.value()) + qRound((qBlue(std::next(iter).value()) - qBlue(iter.value())) * factor));
        }
    }

    if (m_mapControlPointsRgb.lastKey() != m_colorNum - 1)
    {
        for (auto i = m_mapControlPointsRgb.lastKey(); i != m_colorNum; ++i)
        {
            m_listColor[i] = m_mapControlPointsRgb.last();
        }
    }
    else
    {
        m_listColor[m_colorNum - 1] = m_mapControlPointsRgb.last();
    }

    // alpha
    for (auto iter = m_mapControlPointsAlpah.cbegin(); iter != m_mapControlPointsAlpah.cend(); ++iter)
    {
        m_listColor[iter.key()].setAlpha(iter.value());
    }

	_UpdateGeologicMask();
}

void CXColormap::_UpdateGeologicMask()
{
	int offset = m_colorNum / 100;

	for (auto iter = m_mapGeologicMask.cbegin(); iter != m_mapGeologicMask.cend(); ++iter)
	{
		int maskBeg = qMax(0, iter.key() - offset);
		int maskEnd = qMin(m_colorNum - 1, iter.key() + offset);

		for (int i = maskBeg; i <= maskEnd; ++i)
		{
			m_listColor[i] = iter.value();
		}
	}
}

void CXColormap::_WriteToJson(QByteArray& data, bool bFormat)
{
	rapidjson::Document colormapDoc;

	colormapDoc.SetObject();
	rapidjson::Document::AllocatorType& allocator = colormapDoc.GetAllocator();
    
	colormapDoc.AddMember("number", m_colorNum, allocator);

    rapidjson::Value invalidColor(rapidjson::kObjectType);
	invalidColor.AddMember("red", m_listColor[cInvalidColorIndex].red(), allocator);
	invalidColor.AddMember("green", m_listColor[cInvalidColorIndex].green(), allocator);
	invalidColor.AddMember("blue", m_listColor[cInvalidColorIndex].blue(), allocator);
	invalidColor.AddMember("alpha", m_listColor[cInvalidColorIndex].alpha(), allocator);

	colormapDoc.AddMember("invalid_point", invalidColor, allocator);

    rapidjson::Value rgbControlPoint(rapidjson::kArrayType);

    for (auto iter = m_mapControlPointsRgb.cbegin(); iter != m_mapControlPointsRgb.cend(); ++iter)
    {
        rapidjson::Value posColor(rapidjson::kObjectType);
        posColor.AddMember("position", iter.key(), allocator);
        posColor.AddMember("red", qRed(iter.value()), allocator);
        posColor.AddMember("green", qGreen(iter.value()), allocator);
        posColor.AddMember("blue", qBlue(iter.value()), allocator);

        rgbControlPoint.PushBack(posColor, allocator);
    }

	colormapDoc.AddMember("rgb_control_points", rgbControlPoint, allocator);

    rapidjson::Value alphaControlPoint(rapidjson::kArrayType);

    for (auto iter = m_mapControlPointsAlpah.cbegin(); iter != m_mapControlPointsAlpah.cend(); ++iter)
    {
        rapidjson::Value posAlpha(rapidjson::kObjectType);
        posAlpha.AddMember("position", iter.key(), allocator);
        posAlpha.AddMember("alpha", iter.value(), allocator);

        alphaControlPoint.PushBack(posAlpha, allocator);
    }

	colormapDoc.AddMember("alpha_control_points", alphaControlPoint, allocator);

	rapidjson::StringBuffer buffer;

	if (bFormat)
	{
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		colormapDoc.Accept(writer);
	}
	else
	{
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		colormapDoc.Accept(writer);
	}

	data.append(buffer.GetString());
}
