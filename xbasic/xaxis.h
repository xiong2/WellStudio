#pragma once
#include "xbasic_global.h"

#include <QRect>

class XBASIC_EXPORT CXAxis
{
public:
	enum AxisType
	{
		XAxis,
		YAxis
	};
public:
    CXAxis(double dBegin, double dEnd, const QRect& sceneRect = QRect(), int nStepUnit = 10);
    virtual ~CXAxis();
public:
    /**
     * @brief get tick count
     */
    int GetTickCount();
    /**
     * @brief get tick interval in ground, e.g. 0.1, 10, 100
     */
    double GetGroundTickInterval();
    /**
     * @brief get tick interval in ground, unit is pixel
     */
    int GetSceneTickInterval();
    /**
     * @brief get graduation value in ground by index
     */
    double GetGroundGradValue(int nIndex);
    /**
     * @brief value mapping from ground to scene
     */
    int MapGroundToScene(double dGroundValue, bool bReverse = false);
    /**
     * @brief value mapping from scene to ground
     */
    double MapSceneToGround(int nValue, bool bReverse = false);
    /**
     * @brief judge if the tick is a major tick
     */
    bool IsMainTick(double dGroundValue);
    /**
     * @brief synchronize position, used for scrolling
     */
    void SychonizePosition(const CXAxis* pRuler);
	/**
     * @brief synchronize scale, used for scale
     */
    void SychonizeScale(const CXAxis* pRuler);
    /**
     * @brief zoom the ruler by a given range
     */
    void Zoom(double dValueRange);
public:
	bool GroundChanged()
	{
		return m_bGroundChanged;
	}
    /**
     * @brief get begin value in ground
     */
    double GetBegin() const {return m_dBegin;}
    /**
     * @brief set begin value in ground
     */
    void SetBegin(double dBegin) 
	{
		m_dBegin = dBegin;
		m_bGroundChanged = true;
	}
    /**
     * @brief get end value in ground
     */
    double GetEnd() const {return m_dEnd;}
    /**
     * @brief set end value in ground
     */
    void SetEnd(double dEnd) 
	{
		m_dEnd = dEnd;
		m_bGroundChanged = true;
	}
    /**
     * @brief get value range in ground
     */
    double GetValueRange() const {return m_dEnd-m_dBegin;}
    /**
     * @brief get step unit
     */
    int GetStepUnit() const {return m_nStepUnit;}
    
    /**
     * @brief set step unit
     */
    void SetStepUnit(int nStepUnit) {m_nStepUnit = nStepUnit;}
    /**
     * @brief get scene rect
     */
    QRect GetSceneRect() const {return m_sceneRect;}
    /**
     * @brief set scene rect
     */
    void SetSceneRect(const QRect& sceneRect) 
	{
		m_sceneRect = sceneRect;
	}
	//Calculator ground tick interval
	double calculatorGroundTickInterval();
	static double GetBaseNum(double dValue, double dBase = 5);
	static double _Round(double dValue, double dInterval);
	static double _Round(double dValue, int nPrecision);
	void SetAxisType(AxisType eType)
	{
		m_eType = eType;
	}
private:
    // begin value in ground
    double m_dBegin;
    // end value in ground
    double m_dEnd;
    // step unit, 10 by default
    int m_nStepUnit;
    // scene rect
    QRect m_sceneRect;
    // minimum tick interval in scene, 2 pixels by default
    static const int m_nMinTickInterval = 2;
	// Ground Tick Interval
	double m_dGroundTickInterval;
	bool m_bGroundChanged;
	AxisType m_eType;
};