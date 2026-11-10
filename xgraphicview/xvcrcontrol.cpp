#include "xvcrcontrol.h"
#include "xglobal.h"

#include <QSlider>
#include <QToolBar>
#include <QMainWindow>
#include <QAction>
#include <QComboBox>
#include <QTimer>

#include "xsliderspinwidget.h"
#include "xwindow.h"

CXVCRControl::CXVCRControl(CXWindow* pWin)
	: QObject(pWin), m_pCurWindow(pWin), m_nTimerInterval(100)
	, m_dStepInterval(-1.), m_dCurValue(-1.), m_dStart(0.), m_dEnd(1.), m_dMinStep(-1.), m_dRatioFactor(1.)
{
}

void CXVCRControl::_InitSliderSpinWidget()
{
	m_pSliderSpinWidget = new CXSliderSpinWidget(m_pTBarVCR);
	m_pSliderSpinWidget->HideLabel(true) ;
	m_pSliderSpinWidget->setMinimumWidth(200);

	connect(m_pSliderSpinWidget, SIGNAL(EditingFinished()), this, SLOT(OnEditFinish()));
	connect(m_pSliderSpinWidget, SIGNAL(SliderReleased()), this, SLOT(OnEditFinish()));
	connect(m_pSliderSpinWidget, SIGNAL(ValueChanged(double)), this, SLOT(OnEditFinish()));
}

void CXVCRControl::_InitComboStepInterval()
{
	m_pComboStepInterval = new QComboBox(m_pTBarVCR);
	m_pComboStepInterval->setEditable(false);
	connect(m_pComboStepInterval, SIGNAL(activated(const QString &)), SLOT(slotStepIntervalChanged(const QString &))) ;
}

void CXVCRControl::_InitActions()
{
	m_pBtPlayToFirst  = m_pTBarVCR->addAction(QIcon(::GetIconPath() + "Play2First.png"), "Play to First", this, SLOT(slotPlayToFirst()));
	m_pBtPlayPageUp   = m_pTBarVCR->addAction(QIcon(::GetIconPath() + "PlayPageUp.png"), "Play PageUp", this, SLOT(slotPlayPageUp()));
	m_pBtPlayBackward = m_pTBarVCR->addAction(QIcon(::GetIconPath() + "PlayBackward.png"), "Play Backward", this, SLOT(slotPlayBackward()));
	m_pBtPlayStop     = m_pTBarVCR->addAction(QIcon(::GetIconPath() + "PlayStop.png"), "Stop Playing", this, SLOT(slotPlayerStop()));
	m_pBtPlayForward  = m_pTBarVCR->addAction(QIcon(::GetIconPath() + "PlayForward.png"), "Play Forward", this, SLOT(slotPlayForward()));
	m_pBtPlayPageDown = m_pTBarVCR->addAction(QIcon(::GetIconPath() + "PlayPageDown.png"), "Play PageDown", this, SLOT(slotPlayPageDown()));
	m_pBtPlayToLast   = m_pTBarVCR->addAction(QIcon(::GetIconPath() + "Play2Last.png"), "Play to Last", this, SLOT(slotPlayToLast()));
	
	m_pBtPlayBackward->setCheckable(true);
	m_pBtPlayForward ->setCheckable(true);
}

void CXVCRControl::CreateIt()
{
	m_pTBarVCR = new QToolBar(QString("Slice Index and Animation"), m_pCurWindow);
	m_pTBarVCR->setObjectName("VCRControlToolBar");
	m_pTBarVCR->hide();
	_InitSliderSpinWidget();
	m_pTBarVCR->addSeparator();
	m_pTBarVCR->addWidget(m_pSliderSpinWidget);
	m_pTBarVCR->addSeparator();
	m_pTBarVCR->setIconSize(QSize(16, 16)) ;
	_InitActions();
	m_pTBarVCR->addSeparator();
	_InitComboStepInterval();
	m_pTBarVCR->addWidget(m_pComboStepInterval);
	m_pTBarVCR->addSeparator();

	m_pCurWindow->addToolBar(Qt::BottomToolBarArea, m_pTBarVCR);
}

void CXVCRControl::SetVCRToolBarEnabled(bool bEnabled)
{
	if(m_pTBarVCR) m_pTBarVCR->setEnabled(bEnabled);
}

void CXVCRControl::InitData(double dStart, double dEnd, double dCur, double dMinStep, double dCurStep, int nDecimal)
{
	if (m_dStepInterval < 0)
	{
		m_dStepInterval = dCurStep;
	}

	if (!IsDivideExactly(m_dStepInterval, dCurStep))
	{
		m_dStepInterval = dCurStep;
	}

	m_dStart = dStart;
	m_dEnd = dEnd;
	m_dCurValue = dCur;

	if (nDecimal == -1)
	{
		nDecimal = GetSeisUnitDecimalNumber(dCurStep) ;
	}

	if (m_dMinStep != dMinStep)
	{
		m_dMinStep = dMinStep;
		m_pComboStepInterval->clear();
		for (int i = 1; i <= 10; i++) m_pComboStepInterval->addItem(vtos(m_dMinStep * i, nDecimal));
	}

	m_pComboStepInterval->setCurrentIndex(m_pComboStepInterval->findText(QString::number(m_dStepInterval))) ;

	if (dStart > dEnd)
	{
		m_dRatioFactor = -1.0 ;
	}
	else
	{
		m_dRatioFactor = 1.0 ;
	}

	int nCount = (int) (qAbs(m_dEnd - m_dStart) / m_dStepInterval + 1 + 0.5);

	m_pSliderSpinWidget->InitWidget(m_dStart, m_dEnd, m_dStepInterval, nCount, nDecimal) ;
	m_pSliderSpinWidget->SetValue(dCur) ;
	m_pSliderSpinWidget->SetSpinSingleStep(m_dStepInterval) ;

	m_bInited = true;
}

void CXVCRControl::SetSliderSpinValue(double dValue)
{
	m_pSliderSpinWidget->SetValue(dValue) ;
	m_dCurValue = dValue;
}
 
void CXVCRControl::OnEditFinish()
{
	if(m_dCurValue == m_pSliderSpinWidget->GetValue())
	{
		return;
	}

	m_dCurValue = m_pSliderSpinWidget->GetValue() ;

	emit CurrentSectionChanged(m_dCurValue) ;
}

void CXVCRControl::slotPlayForward  () 
{
	m_ePlayMode = ePlayForward ;
	_updateToolbarStates () ;

	if ( NULL == m_pTimer )
	{
		m_pTimer = new QTimer( this ) ;
		connect ( m_pTimer, SIGNAL ( timeout()) , this , SLOT ( slotOnTimer () ) ) ;
		m_pTimer->start ( m_nTimerInterval ) ;
	}

	_StopOtherVCRControl();

	if ( ! m_pTimer->isActive() )
		m_pTimer->start ( m_nTimerInterval ) ;

	
}

void CXVCRControl::slotPlayBackward ()
{
	m_ePlayMode = ePlayBackward ;
	_updateToolbarStates () ;

	if ( NULL == m_pTimer )
	{
		m_pTimer = new QTimer( this ) ;
		connect ( m_pTimer, SIGNAL ( timeout()) , this , SLOT ( slotOnTimer () ) ) ;
		m_pTimer->start ( m_nTimerInterval ) ;
	}

	_StopOtherVCRControl();

	if ( ! m_pTimer->isActive() )
		m_pTimer->start ( m_nTimerInterval ) ;
	
}

void CXVCRControl::_StopOtherVCRControl()
{
	/*CGmUiMainControl *pMainControl = dynamic_cast<CGmUiMainControl*>( ::GetMainControl() );
	if( pMainControl )
	{
		foreach( CGmWindow *pWindow,pMainControl->GetWindowManager()->GetWindowList() )
		{
			CGmOIVWindow *pOIVWindow = dynamic_cast<CGmOIVWindow *>( pWindow );
			if( pOIVWindow!= m_pCurWindow && pOIVWindow &&   pOIVWindow->GetVCRControl( false )  )
			{
				pOIVWindow->GetVCRControl( false )->StopTimer();
			}
		}
	}*/
}

void CXVCRControl::slotPlayPageUp   () 
{
	m_ePlayMode = ePlayPageUp ;
	_updateToolbarStates () ;

	if ( NULL != m_pTimer && m_pTimer->isActive() )	m_pTimer->stop() ;

	m_dCurValue -= m_dStepInterval * m_dRatioFactor  ;
	if ( m_dCurValue * m_dRatioFactor < m_dStart * m_dRatioFactor )
		m_dCurValue = m_dEnd ;

	m_pSliderSpinWidget->SetValue(m_dCurValue) ;
	emit CurrentSectionChanged(m_dCurValue);
}

void CXVCRControl::slotPlayPageDown () 
{
	m_ePlayMode = ePlayPageDown ;
	_updateToolbarStates () ;

	if ( NULL != m_pTimer && m_pTimer->isActive())	m_pTimer->stop() ;

	m_dCurValue    += m_dStepInterval * m_dRatioFactor  ;
	if ( m_dCurValue * m_dRatioFactor > m_dEnd * m_dRatioFactor)
		m_dCurValue = m_dStart ;

	m_pSliderSpinWidget->SetValue(m_dCurValue) ;
	emit CurrentSectionChanged(m_dCurValue);
}

void CXVCRControl::slotPlayToFirst  () 
{
	m_ePlayMode = ePlayToFirst ;
	_updateToolbarStates () ;

	if ( NULL != m_pTimer && m_pTimer->isActive())
		m_pTimer->stop() ;
	m_dCurValue = m_dStart;

	m_pSliderSpinWidget->SetValue(m_dCurValue) ;
	emit CurrentSectionChanged(m_dCurValue);
}

void CXVCRControl::slotPlayToLast  () 
{
	m_ePlayMode = ePlayToLast ;
	_updateToolbarStates () ;

	if ( NULL != m_pTimer && m_pTimer->isActive())
		m_pTimer->stop() ;
	m_dCurValue = m_dEnd;

	m_pSliderSpinWidget->SetValue(m_dCurValue) ;
	emit CurrentSectionChanged(m_dCurValue);
}

void CXVCRControl::slotPlayerStop   () 
{
	m_ePlayMode = ePlayerStop ;
	_updateToolbarStates () ;

	if ( NULL != m_pTimer && m_pTimer->isActive())
		m_pTimer->stop() ;
}

void CXVCRControl::slotOnTimer ()
{

	if ( ePlayForward == m_ePlayMode )	
	{
		m_dCurValue += m_dStepInterval * m_dRatioFactor ;
		if ( m_dCurValue * m_dRatioFactor > m_dEnd * m_dRatioFactor )
			m_dCurValue = m_dStart ;

		m_pSliderSpinWidget->SetValue(m_dCurValue) ;
		emit CurrentSectionChanged(m_dCurValue);
	}
	else if ( ePlayBackward == m_ePlayMode )
	{
		m_dCurValue -= m_dStepInterval * m_dRatioFactor ;
		if ( m_dCurValue * m_dRatioFactor < m_dStart * m_dRatioFactor )
			m_dCurValue = m_dEnd ;

		m_pSliderSpinWidget->SetValue(m_dCurValue) ;
		emit CurrentSectionChanged(m_dCurValue);
	}

}

void CXVCRControl::_updateToolbarStates ()
{
	m_pBtPlayForward->setChecked  ( ePlayForward == m_ePlayMode ) ;
	m_pBtPlayBackward->setChecked ( ePlayBackward == m_ePlayMode ) ;

	switch( m_ePlayMode ) 
	{
	case ePlayForward :
	case ePlayBackward :		
		{
			m_pBtPlayToFirst->setEnabled  ( false ) ;
			m_pBtPlayPageUp->setEnabled   ( false ) ;
			m_pBtPlayBackward->setEnabled ( true ) ;
			m_pBtPlayStop->setEnabled     ( true ) ;
			m_pBtPlayForward->setEnabled  ( true ) ;
			m_pBtPlayPageDown->setEnabled ( false ) ;
			m_pBtPlayToLast->setEnabled   ( false ) ;			
		}
		break ;

	case ePlayToFirst :
	case ePlayPageUp:
	case ePlayPageDown :
	case ePlayToLast :
	case ePlayerStop :
	case ePlayNone :
	default:
		{
			m_pBtPlayToFirst->setEnabled  ( true ) ;
			m_pBtPlayPageUp->setEnabled   ( true ) ;
			m_pBtPlayBackward->setEnabled ( true ) ;
			m_pBtPlayStop->setEnabled     ( false ) ;
			m_pBtPlayForward->setEnabled  ( true ) ;
			m_pBtPlayPageDown->setEnabled ( true ) ;
			m_pBtPlayToLast->setEnabled   ( true ) ;
		}
		break ;
	}
}

void CXVCRControl::slotStepIntervalChanged ( const QString & str )
{
	m_dStepInterval = str.toDouble() ;
	m_pSliderSpinWidget->SetSpinSingleStep( m_dStepInterval );
}

void CXVCRControl::ShowMe(bool bVisible)
{
	if (m_pCurWindow == nullptr) return;
	
	if (bVisible)
	{
		m_pTBarVCR->show();
	}
	else
	{
		slotPlayerStop();
		m_pTBarVCR->hide();
	}

    m_bVisible = bVisible;
}

void CXVCRControl::SetToolBarTitle(const QString& strToolbarName)
{
	if(m_pTBarVCR!=NULL)
	{
		m_pTBarVCR->setWindowTitle(strToolbarName);
		m_pTBarVCR->setObjectName(strToolbarName);
	}
}
void CXVCRControl::SetStepComboboxDisabled(bool b)
{
	m_pComboStepInterval->setDisabled(b);
}

void CXVCRControl::StopTimer()
{
	m_pBtPlayStop->trigger();
}