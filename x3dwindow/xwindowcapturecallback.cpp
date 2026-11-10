#include "xwindowcapturecallback.h"

#include <osg/Image>
#include <osg/RenderInfo>
#include <osgDB/WriteFile>

CXWindowCaptureCallback::CXWindowCaptureCallback(GLenum readBuffer, const std::string& name)
	: m_readBuffer(readBuffer), m_fileName(name)
{
	m_image = new osg::Image;
}

CXWindowCaptureCallback::~CXWindowCaptureCallback()
{

}

void CXWindowCaptureCallback::operator()(osg::RenderInfo& renderInfo) const
{
#if !defined(OSG_GLES1_AVAILABLE) && !defined(OSG_GLES2_AVAILABLE)
	glReadBuffer(m_readBuffer);
#else
	osg::notify(osg::NOTICE) << "Error: GLES unable to do glReadBuffer" << std::endl;
#endif

	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_mutex);
	osg::GraphicsContext* gc = renderInfo.getState()->getGraphicsContext();

	if (gc->getTraits())
	{
		GLenum pixelFormat;

		if (gc->getTraits()->alpha)
			pixelFormat = GL_RGBA;
		else
			pixelFormat = GL_RGB;

#if defined(OSG_GLES1_AVAILABLE) || defined(OSG_GLES2_AVAILABLE)
		if (pixelFormat == GL_RGB)
		{
			GLint value = 0;
#ifndef GL_IMPLEMENTATION_COLOR_READ_FORMAT
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#endif
			glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, &value);
			if (value != GL_RGB ||
				value != GL_UNSIGNED_BYTE)
			{
				pixelFormat = GL_RGBA;//always supported
			}
		}
#endif
		int width = gc->getTraits()->width;
		int height = gc->getTraits()->height;

		m_image->readPixels(0, 0, width, height, pixelFormat, GL_UNSIGNED_BYTE);

		if (!m_fileName.empty())
		{
			osgDB::writeImageFile(*m_image, m_fileName);
		}
	}
}