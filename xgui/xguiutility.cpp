#include "xguiutility.h"
#include <QFileDialog>
#include <QMessageBox>

bool NXGUIUtility::IsDirCanWritable(const QString & strTitle, const QString& strDirectory)
{
	QFile tempFile(strDirectory + QDir::separator() + "ttttmp");
	if (!tempFile.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(NULL, strTitle, "Can not write in this directory!");
		return false;
	}

	tempFile.close();
	QFile::remove(strDirectory + QDir::separator() + "ttttmp");
	return true;
}

bool NXGUIUtility::IsFileCanWritable(const QString & strTitle, const QString & strFile)
{
	QFile file(strFile);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(nullptr, strTitle, "Can not open the file to write!");
		return false;
	}
	return true;
}
