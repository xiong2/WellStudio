#ifndef XGUIUTILITY_H
#define XGUIUTILITY_H

/*!
 *	@class	NXGUIUtility in file "keguiutility.h"
 *	@brief	common functions for GUI
 *	@author	pezy
 *	@date	2017-04-27
 */

#include "xgui_global.h"
#include <QString>

namespace NXGUIUtility
{
	bool XGUI_EXPORT IsDirCanWritable(const QString& strTitle, const QString& strDirectory);
	bool XGUI_EXPORT IsFileCanWritable(const QString& strTitle, const QString& strFile);
};

#endif // KEGUIUTILITY_H
