#include "xarchive.h"

CXArchive::CXArchive(QByteArray* pByteArray, QIODevice::OpenMode eFlag, bool bSave)
	:QDataStream(pByteArray,eFlag)
{
	m_bSave = bSave;
}