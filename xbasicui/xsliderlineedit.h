#ifndef XSLIDERLINEEDIT_H
#define XSLIDERLINEEDIT_H

/*!
 *  @brief  custom control that combined QSlider and QLineEdit
 *  @author pezy
 *  @date   2015-12-30
 *  @see    
 */

//       +--------+                  _
// Title |LineEdit| MinValue -------|_|----------- MaxValue
//       +--------+

#include "xbasicui_global.h"
#include <QWidget>
#include <QFrame>

class QVBoxLayout;
class QLineEdit;
class QLabel;
class QSlider;

struct CXSliderLineEditInfo
{
    QString m_title;
    int m_iBeg;
    int m_iEnd;
    int m_iStep = 1;
};

class CXSliderLineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit CXSliderLineEdit(CXSliderLineEditInfo info, QWidget *parent = nullptr);
    ~CXSliderLineEdit();

    int GetValue() const;
    void SetValue(int value);

    int GetMinValue() const;
    int GetMaxValue() const;

    void SetFixedTitleWidth(int width);
    void SetFixedLineEditWidth(int width);

    const CXSliderLineEditInfo& GetInfo() const { return m_info; }

signals:
    void ValueChanged(int);
    void SliderReleased();

private:
    void _BlockSignals(bool bBlock);
    int _GetCorrectValue(int value);

    CXSliderLineEditInfo m_info;

    QLineEdit*  m_pLineEdit;
    QSlider*    m_pSlider;
    QLabel*     m_pLabelTitle;
    QLabel*     m_pLabelMin;
    QLabel*     m_pLabelMax;

private slots:
    void slotLineEditChanged();
    void slotSliderValueChanged(int);
};

class CXRangeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CXRangeWidget(CXSliderLineEditInfo info, QWidget *parent = nullptr);
    ~CXRangeWidget();

    CXSliderLineEdit* GetSliderLineEidt1() const;
    CXSliderLineEdit* GetSliderLineEidt2() const;

signals:
    void ValueChanged(int iStart, int iEnd);

private slots:
    void slotBegValueChanged(int);
    void slotEndValueChanged(int);
    void slotValueChanged();

private:
    void _BlockSignals(bool bBlock);

    CXSliderLineEditInfo m_info;

    CXSliderLineEdit* m_sliderLineEdit1;
    CXSliderLineEdit* m_sliderLineEdit2;
};

class XBASICUI_EXPORT CXRangeFrame : public QFrame
{
    Q_OBJECT
public:
    explicit CXRangeFrame(QWidget * parent = nullptr, Qt::WindowFlags f = 0);
    ~CXRangeFrame();

    void AddOneLine(QString title, int iBegin, int iEnd, int iStep, bool bPair = true);
    void SetDisabled(int index, bool bDisable = true);
    void SetVisible(int index, bool bVisible = true);

    int GetValueAt(int index) const;
    void SetValueAt(int index, int value);

private:
    void _FormatWidth();

    QVBoxLayout *m_pVBoxLayout;
    QList<CXSliderLineEdit*> m_listSliderLineEdit;
};

#endif // KESLIDERLINEEDIT_H
