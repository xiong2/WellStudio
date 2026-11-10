#ifndef XBASEDIALOG_H
#define XBASEDIALOG_H

#include <QDialog>
#include "xgui_global.h"

class QGridLayout;
class QDialogButtonBox;

class XGUI_EXPORT CXBaseDialog : public QDialog {
    Q_OBJECT
public:
    CXBaseDialog(QWidget* parent);
    ~CXBaseDialog(void);

    QGridLayout* GetMainLayout() { return m_pMainLayout; }

    virtual void OnOK()
    {};

    void SetOKEnabled(bool bEnabled);
private slots:
    void slotCancelClicked();
    void slotOKClicked();
private:
    QGridLayout* m_pMainLayout;
    QDialogButtonBox* m_pButtonBox;
};

#endif // KEBASEDIALOG_H
