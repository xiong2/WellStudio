#ifndef XSECTIONVIEWSCENE_H
#define XSECTIONVIEWSCENE_H

#include "xscene.h"
#include "xdef.h"
#include <QOpenGLFunctions>
#include <QVector4D>
#include "xsectionwindow_global.h"

/*!
 *  @class  CXSectionScene in kesectionscene.h 
 *  @brief  Show section items on scene.
 *  @author pezy
 *  @date   2015-11-03
 *  @see    CX2DSectionWindow
 */

class CXWindowInfoSection;
class QMouseEvent;
class CXObject;
class CX2DSectionWindow;
class CXSeismicObject;
class CXAbstractItem;
class CXSectionBuilder;
class CXSectionProjector;
struct SKETraceInfo;
class CXSecRectZoomItem;
class CXOrthoSectionItem;

struct CXSectionData
{
	CXSectionData()
	{
		m_nTraceQty = 0;
		m_nSamplingQty = 0;
		m_pAttObj = NULL;
		m_pGeoObj = NULL;
		m_pData = NULL;
		m_pTraceInfo = NULL;
	}

    CXSeismicObject*	m_pAttObj;
	CXObject*			m_pGeoObj;
    float*				m_pData;
    int					m_nTraceQty;
    int					m_nSamplingQty;
    double				m_dMin;
    double				m_dMax;
	SKETraceInfo*		m_pTraceInfo;
};

class CXSectionScene : public CXScene
{
    Q_OBJECT

public:
    explicit CXSectionScene(CXWindow* pWindow, QObject *parent = nullptr);
    ~CXSectionScene();

	virtual bool CreateItem(QUuid objectID, CXViewInfoObject *pViewInfo) override;
	virtual bool DeleteItem(QUuid objectID) override;
	virtual void UpdateView(const CXEventParameter& eventPara) override;

    bool SetForeData(CXSeismicObject* pAttObj, CXObject *pGeoObj);
    bool SetBackData(CXSeismicObject* pAttObj, CXObject *pGeoObj);

	void UpdateItems(EEventType);
	void UpdateROI(float fLeft, float fRight, float fBottom, float fTop);

	const QMap<QUuid, CXAbstractItem*>& GetItemMap() const { return m_mapItem; }

	//	Report the information of given postion, x is CDP and y is time/depth.
	void ShowPositionInfo(QMouseEvent *);

	void InitOpenGLBuilder();

	EDomainType GetDomainType();

	///	Get the background section/2d line or data volume/2d section.
	CXObject* GetBackgroundSection(bool bGeometry = true);

	CXSectionProjector* GetProjector()
	{
		return m_pProjector;
	}
	
	void SetEditMode(EXSectionEditMode eMode)
	{
		m_eEditMode = eMode;
	}

	EXSectionEditMode GetEditMode()
	{
		return m_eEditMode;
	}

	void SetActiveItem(QUuid objID);

	void DeactiveItem();

	CXAbstractItem* GetActiveItem()
	{
		return m_pActiveItem;
	}

	CXAbstractItem* FindItem(QUuid objID);

	QList<CXAbstractItem *> FindAllAbsItems(EXObjectType);

	///	Get the dimension information of current section, as trace * ms.
	void GetSectionSize(float& fTraceNumber, float& fMS);

	void DeleteAllItems();

	void HandleMouseEvent(QMouseEvent* event, EXMouseEventType);

	//	Fault picking relevant.
	void FaultStickAssign(QUuid sourceFaultID, QUuid destFaultID);

	SKETraceInfo* GetTraceInfo(int& iNumTraceInfo)
	{
		iNumTraceInfo = m_backData.m_nTraceQty;
		return m_backData.m_pTraceInfo;
	}

	void SwitchRectZoom(bool);

	void ShowOrthoSections(bool);

	void GetXYByTraceNumber(double& dX, double& dY, double dTrace);

	///@brief Get window
	CX2DSectionWindow* GetWindow() { return m_pSectionWindow; }

	///@brief Get dimension of the section
	void GetSectionDimension(int& nJ, int& nK);

	///@brief Update section data
	void UpdateSectionData();
	

protected:
	virtual void drawBackground(QPainter * painter, const QRectF & rect) override;
	virtual void drawForeground(QPainter * painter, const QRectF & rect) override;

	CXAbstractItem* _CreateItemByObj(CXObject* pObject) const;

	bool _ResetData(CXSeismicObject* pAttObj, CXObject *pGeoObj, CXSectionData &data) const;
	static void _ClearData(CXSectionData &data);

	static bool _readData(CXSectionData &data);

    void _SetTexData(const CXSectionData& data, CXSectionBuilder* pBuilder) const;
    void _SetWiggleData(const CXSectionData& data, CXSectionBuilder* pBuilder) const;
	void _SetAreaData(const CXSectionData& data, CXSectionBuilder* pBuilder, std::vector<int>& vecCount);

	void _CalcWiggleData(float* pData, const CXSectionData& data) const;
    void _CalcAreaData(float* pData, const CXSectionData& data, std::vector<int>& vecCount) const;

	void _CreateItemOfOtherSection(CXObject* pSection);
	void _RemoveItemOfOtherSection(CXObject* pSection);

    void _UpdateDisplayRange(CXSectionData& data) const;

	void _UpdateAllItems(EEventType);
	void _UpdateWellItems();

	CX2DSectionWindow*		m_pSectionWindow;
	CXWindowInfoSection*		m_pViewInfo;
    QMap<QUuid, CXAbstractItem*> m_mapItem;

	CXSectionData			m_backData;	
	CXSectionData			m_foreData;

    CXSectionBuilder*		m_pBackgroundBuilder;
    CXSectionBuilder*		m_pForegroundBuilder;

    std::vector<int>		m_vecBackCount;
	std::vector<int>		m_vecForeCount;

	EXSectionEditMode		m_eEditMode;
	CXAbstractItem*		m_pActiveItem;		//	Current active item.

	CXSecRectZoomItem*		m_pRectZoomItem;
	CXOrthoSectionItem*	m_pOrthoSectionItem;

	CXSectionProjector*	m_pProjector;
};

#endif // KESECTIONVIEWSCENE_H
