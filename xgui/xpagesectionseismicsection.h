#ifndef XPAGESECTIONSEISMICSECTION_H
#define XPAGESECTIONSEISMICSECTION_H

#include "xbasepropertypage.h"
#include "ui_xpagesectionseismicsection.h"

class CXSeismicSection;
class CXObject;
class CXPageSectionSeismicSection : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPageSectionSeismicSection(QWidget *parent, CXObject *pObj);
	~CXPageSectionSeismicSection();

	virtual void Apply() override;

private:
	void _Init();
	void _InitBySectionType();

private:
	Ui::CXPageSectionSeismicSection m_ui;
	CXSeismicSection* m_pSection;
};

#endif // KEPAGESECTIONSEISMICSECTION_H
