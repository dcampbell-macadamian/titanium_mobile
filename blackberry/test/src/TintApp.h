/*
 * TintApp.h
 *
 *  Created on: 2012-03-09
 *      Author: dcampbell
 */

#ifndef TINTAPP_H_
#define TINTAPP_H_

#include <stdio.h>
#include <stdlib.h>
#include <GLES/gl.h>
#ifdef USING_GL11
#include <GLES/glext.h>
#elif defined(USING_GL20)
#include <GLES2/gl2.h>
#else
#error tint must be compiled with either USING_GL11 or USING_GL20 flags
#endif
#include <sys/platform.h>
#include "bps/event.h"
#include <screen/screen.h>
#include <EGL/egl.h>
#include <bps/navigator.h>
#include <bps/screen.h>
#include <bps/bps.h>
#include <bps/event.h>
#include <bps/orientation.h>
#include <ft2build.h>

class TintApp
{
public:
	TintApp();
	virtual ~TintApp();
	int InitializeApp();
	int Run();
	void LogError(const char* msg);
	void LogErrorFormat(const char* format,...);
private:
	int InitEGL();
	int CalculateDPI();
	void Render();
	screen_context_t m_screen_ctx;
	screen_display_t m_screen_disp;
	screen_window_t m_screen_win;
	EGLDisplay m_egl_disp;
	EGLSurface m_egl_surf;
	EGLConfig m_egl_conf;
	EGLContext m_egl_ctx;
	EGLint m_surface_width;
	EGLint m_surface_height;
	float m_width;
	float m_height;
};

#endif /* TINTAPP_H_ */
