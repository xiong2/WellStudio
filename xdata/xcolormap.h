#ifndef CXCOLORMAP_H
#define CXCOLORMAP_H

#include <qstringlist.h>
#include <qcolor.h>
#include <qmap.h>
#include "xdata_global.h"
#include <qpixmap.h>

/*!
* @class	CXColormap provided in the file "kecolormap.h"
* @brief	Used to represent colormap.
* @author	pezy
* @date		2016-01-26
* @see		
*/

class XDATA_EXPORT CXColormap
{
public:
	static bool InitializeColormapsFromFile();
    static bool InitializeColormapsFromTemplateDB();
    static bool InitializeColormapsFromJason(const QString& jasonColorScalesDir);
	static bool InitializeColormapsFromProjectDB();

    static bool WriteColormapsToTemplateDB();
    static bool WriteColormapsToFile();

	static bool ImportColormapFromFile(const QString& strFilePath);
    
	static QStringList GetAllColormapsName();
    
	static CXColormap* GetColormap(const QString& sName);
	static CXColormap* GetColormap(unsigned int iIDX);
	static CXColormap* GetCustomizedColormap(CXColormap* pBaseColormap);

	static QPixmap GeneratePixmap(const QString& name);

public:
    // copy
    CXColormap(const CXColormap& colormap);
    CXColormap& operator=(const CXColormap& colormap);

	QColor GetColorAt(unsigned char iIDX);
	const QColor& ColorAt(int index) const;
    QRgb GetRgbAt(int index) const;
    QString GetName() const;
    QList<int> GetControlPointsIndex() const;
    int GetColorNum() const;
	const QMap<int, QRgb>& GetGeologicMask() const;
	const QMap<int, uchar>& GetAlphaMap() const;
	bool IsCustomized() const;

    bool SaveAs(const QString& strFilePath);
	bool SaveToProjectDB();

    void SetControlPointRgb(int index, const QRgb& rgb);
    void DeleteControlPoint(int index);
    void UpdateControlPoint(int oldIndex, int newIndex, const QRgb& newRgb);
	void SetGeologicMask(int index, const QRgb& rgb);
	bool DeleteGeologicMask(int index);
	void UpdateGeologicMask(int oldIndex, int newIndex, const QRgb& newRgb);
	void ClearAlpha();
	void DeleteOpacityPoint(int index);
	void SetAlpha(int index, uchar alpha);
    void Flip();
	const QColor& GetInvalidColor() const;
	void SetInvalidColor(const QColor& color);

private:
	CXColormap(const QString& sName, const QMap<int, QRgb>& mapRgb, const QMap<int, uchar>& mapAlpha, int colNum = 256, QColor invalidCol = QColor(Qt::white));
    CXColormap(const QString& fileName, const QString& jsonText);
	CXColormap(QString sPalFile, int iType);

    void _UpdateColormap();
	void _UpdateGeologicMask();
	void _WriteToJson(QByteArray& data, bool bFormat = false);

    QString m_strName;
    int m_colorNum;

    QMap<int, QRgb> m_mapControlPointsRgb;
	QMap<int, QRgb> m_mapGeologicMask;
    QMap<int, uchar> m_mapControlPointsAlpah;

    QColor m_listColor[256];
	const int cInvalidColorIndex = 255;

	static QList<CXColormap> m_stdListColormap;
};

#endif // CXCOLORMAP_H
