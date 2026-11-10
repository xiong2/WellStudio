#ifndef XBUTTONCOLOREDIT_H_
#define XBUTTONCOLOREDIT_H_

#include "xbasicui_global.h"
#include <QPushButton>
#include <QFrame>
#include <QPointer>

class QVBoxLayout;
class CXColorPalette;

class CXColorBlock : public QFrame
{
	Q_OBJECT
public:
	CXColorBlock(QWidget* parent = 0);
	virtual ~CXColorBlock();

protected:
	virtual void mouseReleaseEvent(QMouseEvent *e);
	virtual void enterEvent(QEvent * e);
	virtual void leaveEvent(QEvent * e);

signals:
	void ColorSelected(const QColor& c);
};


class CXColorPalette : public QFrame
{
	Q_OBJECT
public:
	CXColorPalette(QWidget* parent = 0, Qt::WindowFlags f = Qt::Popup);
	virtual ~CXColorPalette();

	QVBoxLayout* GetTopLayout() { return m_topLayout; }
	
signals:
	void ColorSelected(const QColor& c);
	void OtherButtonClicked();

private:
	QVBoxLayout *m_topLayout;
};

class XBASICUI_EXPORT CXButtonColorEdit : public QPushButton
{
	Q_OBJECT
public:
	enum EColorType{ SelectColor, ObjColor, ObjColorMap, DiscreteContour, Texture };

	CXButtonColorEdit(QWidget* parent = 0, QColor c = qRgb(0, 255, 0), const char* name = 0);
	virtual ~CXButtonColorEdit();

	const QColor& GetColor() const;

	int ColorType();
	void SetColorType(int nColorType);

	bool AddButton(const QString& strName, const QColor& color);
	void SetButtonColor(const QString& strName, const QColor& color);
	void SetButtonColor(int nColorType, const QColor& color);
	void GetButtonColor(int &nColorType, QColor& color);
	/**
	* @brief Get button's color with specified text
	* @param strName the button text
	* @return the button's color
	* @date 5/5/2010
	* @see
	*/
	QColor GetButtonColor(const QString& strName);

	/**
	* @brief Set both color and type for the control
	* @param nColorType the color type
	* @param c the button color
	* @return
	* @date 4/23/2010
	* @see SetColorType
	*/
	void SetColor(int nColorType, const QColor& c);

	/**
	* @brief Replace color for specified button
	* @param strName the text in the button
	* @param color the button color
	* @return
	* @date 4/26/2010
	* @see AddButton
	*/
	void ReplaceButtonColor(const QString& strName, const QColor& color);
	void AddObjectColorButton(const QColor& objColor);
	void AddColormapButton();
	bool IsObjectColor();
protected:
	virtual void _InitColorPalette(CXColorPalette* pColorPalette);
	virtual void paintEvent(QPaintEvent*);
	void drawButton(QPainter*);
public slots:
	virtual void onEditor();
	virtual void   SetColor(const QColor& c);
	void OnOtherButtonClicked();
	void OnSpecialButtonClicked();
	void slotObjectColorChanged(const QColor& color);
signals:
	void ColorSelected(const QColor& c);
	void ColorTypeChanged(int type);
private:
	QIcon _buildIcon(const QColor&);
protected:
	int m_nColorType;
private:
	QColor  m_Color;
	QPointer<CXColorPalette> m_pColorPalette;
protected:
	QList<QColor> m_lstBtnColors;
	QStringList   m_lstBtnTexts;
};

#endif // KEBUTTONCOLOREDIT_H_