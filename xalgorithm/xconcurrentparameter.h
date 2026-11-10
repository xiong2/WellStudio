#ifndef XCONCURRENTPARAMETER_H
#define XCONCURRENTPARAMETER_H

#include <QSemaphore>

/**
 * @class CXConcurrentParameter provided in the file "rlconcurrentparameter.h"
 * @brief The Class provides parameteters for threads synchronization
 * 
 * @author Yong Shu 
 * @date 5/27/2014
 * @see 
 * @bug	No Known bugs so far
 */

class CXConcurrentParameter
{
public:
	///@brief Constructor
    CXConcurrentParameter();
    ///@brief  Destructor
    ~CXConcurrentParameter();

    /// Keep only one slice or LDM conversion thread running
    static QSemaphore m_semaphoreSliceLDMConversion;

	///@brief  Semaphore for complete threadlets
	QSemaphore m_semaphoreThreadletCompleteOneCycle;	

	///@brief  Semaphore for complete reader thread 
	QSemaphore m_semaphoreReaderThreadCompleteOneCycle;

	///@brief  Semaphore for complete writer thread
	QSemaphore m_semaphoreWriterThreadCompleteOneCycle;

};

#endif // RLCONCURRENTPARAMETER_H
