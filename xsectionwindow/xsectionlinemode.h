#ifndef XSECTIONLINEMODE_H
#define XSECTIONLINEMODE_H

#include "xabstractitem.h"

class CXSectionLineMode : public QObject, public CXAbstractItem
{
    Q_OBJECT

public:
    CXSectionLineMode(CX2DSectionWindow* pWindow, QGraphicsItem* parent = 0);
    ~CXSectionLineMode(void);
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    void SynSectionNumber(QPointF pos);
public slots:
    void slotSceneChanged();
protected:
    virtual void _UpdateData();
    QPainterPath m_Path;
private:
    QPen m_Pen;
};

#endif // KESECTIONLINEMODE_H