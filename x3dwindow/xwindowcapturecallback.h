#ifndef XWINDOWCAPTURECALLBACK_H
#define XWINDOWCAPTURECALLBACK_H

/*!
*	@brief	save the screenshot of 3D window.
*	@author	pezy
*	@date	2016-05-12
*/

#include "x3dwindow_global.h"
#include <osg/Camera>
#include <OpenThreads/Mutex>
namespace osg { class Image; class RenderInfo; };

class X3DWINDOW_EXPORT CXWindowCaptureCallback : public osg::Camera::DrawCallback
{
public:
	CXWindowCaptureCallback(GLenum readBuffer, const std::string& name);
	~CXWindowCaptureCallback();

	virtual void operator ()(osg::RenderInfo& renderInfo) const;

private:
	GLenum m_readBuffer;
	std::string m_fileName;
	osg::ref_ptr<osg::Image> m_image;
	mutable OpenThreads::Mutex  m_mutex;
};

#endif // KEWINDOWCAPTURECALLBACK_H
