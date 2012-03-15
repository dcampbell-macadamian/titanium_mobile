/*
 * TintApp.cpp
 *
 *  Created on: 2012-03-09
 *      Author: dcampbell
 */

#include "TintApp.h"
#include <math.h>
#include <stdarg.h>

TintApp::TintApp()
{
	m_egl_disp=EGL_NO_DISPLAY;
	m_egl_surf=EGL_NO_SURFACE;
	m_egl_ctx=EGL_NO_CONTEXT;
	m_screen_win=NULL;
}

TintApp::~TintApp()
{
	if(m_egl_disp!=EGL_NO_DISPLAY)
	{
		eglMakeCurrent(m_egl_disp,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
		if(m_egl_surf!=EGL_NO_SURFACE)
		{
			eglDestroySurface(m_egl_disp,m_egl_surf);
			m_egl_surf=EGL_NO_SURFACE;
		}
		if(m_egl_ctx!=EGL_NO_CONTEXT)
		{
			eglDestroyContext(m_egl_disp,m_egl_ctx);
			m_egl_ctx=EGL_NO_CONTEXT;
		}
		if(m_screen_win!=NULL)
		{
			screen_destroy_window(m_screen_win);
			m_screen_win=NULL;
		}
		eglTerminate(m_egl_disp);
		m_egl_disp=EGL_NO_DISPLAY;
	}
	eglReleaseThread();
}

int TintApp::InitializeApp()
{
	LogError("InitializeApp");
	screen_create_context(&m_screen_ctx,0);
	bps_initialize();
	if(EXIT_SUCCESS!=InitEGL())
	{
		LogError("InitEGL failed");
		return -1;
	}
	LogError("EGL initialized");
	//int dpi=CalculateDPI();
	m_surface_width=0;
	m_surface_height=0;
	eglQuerySurface(m_egl_disp,m_egl_surf,EGL_WIDTH,&m_surface_width);
	eglQuerySurface(m_egl_disp,m_egl_surf,EGL_HEIGHT,&m_surface_height);
	EGLint err=eglGetError();
    if(err!=0x3000)
    {
    	LogError("eglQuerySurface failed");
        return EXIT_FAILURE;
    }
    LogError("eglQuerySurface");
    m_width=(float)m_surface_width;
    m_height=(float)m_surface_height;
    LogErrorFormat("Setting view port (%f,%f)",m_width,m_height);
    glViewport(0,0,m_surface_width,m_surface_height);
    LogError("glViewport");
    glMatrixMode(GL_PROJECTION);
    LogError("glMatrixMode");
    glLoadIdentity();
    LogError("glLoadIdentity");
    LogErrorFormat("Width/Height=%f/%f",m_width,m_height);
    glOrthof(0.0f,m_width/m_height,0.0f,1.0f,-1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(1.0f/m_height,1.0f/m_height,1.0f);
    LogError("glLoadIdentity");
    if(BPS_SUCCESS!=screen_request_events(m_screen_ctx))
    {
    	LogError("screen_request_events failed");
    	return -1;
    }
    LogError("screen_request_events");
    if(BPS_SUCCESS!=navigator_request_events(0))
    {
    	LogError("navigator_request_events failed");
    	return -1;
    }
    LogError("navigator_request_events");
	return 0;
}

int TintApp::Run()
{
	bps_event_t* event;
	int rc;
	for(;;)
	{
		event=NULL;
		rc=bps_get_event(&event,0);
		if((event)&&(bps_event_get_domain(event)==navigator_get_domain())&&
				(NAVIGATOR_EXIT==bps_event_get_code(event)))
		{
			break;
		}
		Render();
	}
	LogError("Loop complete");
	screen_stop_events(m_screen_ctx);
	return 0;
}

int TintApp::InitEGL()
{
	int usage;
	int format=SCREEN_FORMAT_RGBX8888;
	int rc;
    EGLint attrib_list[]=
    {
    		EGL_RED_SIZE,8,
    		EGL_GREEN_SIZE,8,
    		EGL_BLUE_SIZE,8,
    		EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
    		EGL_RENDERABLE_TYPE,0,
    		EGL_NONE
    };

#ifdef USING_GL11
    usage=SCREEN_USAGE_OPENGL_ES1|SCREEN_USAGE_ROTATION;
    attrib_list[9]=EGL_OPENGL_ES_BIT;
#elif defined(USING_GL20)
    usage=SCREEN_USAGE_OPENGL_ES2|SCREEN_USAGE_ROTATION;
    attrib_list[9]=EGL_OPENGL_ES2_BIT;
    EGLint attributes[]={EGL_CONTEXT_CLIENT_VERSION,2,EGL_NONE};
#else
    LogError("TintApp::InitEGL should be compiled with either USING_GL11 or USING_GL20 -D flags");
    return EXIT_FAILURE;
#endif
    m_egl_disp=eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(m_egl_disp==EGL_NO_DISPLAY)
    {
    	LogError("TintApp::InitEGL eglGetDisplay failed");
    	return EXIT_FAILURE;
    }
    rc=eglInitialize(m_egl_disp,NULL,NULL);
    if(rc!=EGL_TRUE)
    {
    	LogError("TintApp::InitEGL eglInitialize failed");
    	return EXIT_FAILURE;
    }
    rc=eglBindAPI(EGL_OPENGL_ES_API);
    if(rc!=EGL_TRUE)
    {
    	LogError("TintApp::InitEGL eglBindAPI failed");
        return EXIT_FAILURE;
    }
    int num_configs;
    if(!eglChooseConfig(m_egl_disp,attrib_list,&m_egl_conf,1,&num_configs))
    {
    	LogError("TintApp::InitEGL eglChooseConfig failed");
    	return EXIT_FAILURE;
    }
#ifdef USING_GL20
    m_egl_ctx=eglCreateContext(m_egl_disp,m_egl_conf,EGL_NO_CONTEXT,attributes);
#elif defined(USING_GL11)
    m_egl_ctx=eglCreateContext(m_egl_disp,m_egl_conf,EGL_NO_CONTEXT,NULL);
#endif
    if(m_egl_ctx==EGL_NO_CONTEXT)
    {
    	LogError("TintApp::InitEGL eglCreateContext failed");
        return EXIT_FAILURE;
    }
    rc=screen_create_window(&m_screen_win,m_screen_ctx);
    if(rc)
    {
    	LogError("TintApp::InitEGL screen_create_window failed");
        return EXIT_FAILURE;
    }
    rc=screen_set_window_property_iv(m_screen_win,SCREEN_PROPERTY_FORMAT,&format);
    if(rc)
    {
    	LogError("TintApp::InitEGL screen_set_window_property_iv(...SCREEN_PROPERTY_FORMAT...) failed");
        return EXIT_FAILURE;
    }
    rc=screen_set_window_property_iv(m_screen_win,SCREEN_PROPERTY_USAGE,&usage);
    if(rc)
    {
    	LogError("TintApp::InitEGL screen_set_window_property_iv(...SCREEN_PROPERTY_USAGE...) failed");
        return EXIT_FAILURE;
    }
    rc=screen_get_window_property_pv(m_screen_win,SCREEN_PROPERTY_DISPLAY,(void**)&m_screen_disp);
    if(rc)
    {
    	LogError("TintApp::InitEGL screen_get_window_property_iv(...SCREEN_PROPERTY_DISPLAY...) failed");
        return EXIT_FAILURE;
    }
    int screen_resolution[2];
    rc=screen_get_display_property_iv(m_screen_disp,SCREEN_PROPERTY_SIZE,screen_resolution);
    if(rc)
    {
    	LogError("TintApp::InitEGL screen_get_window_property_iv(...SCREEN_PROPERTY_SIZE...) failed");
        return EXIT_FAILURE;
    }
    int angle=atoi(getenv("ORIENTATION"));
    screen_display_mode_t screen_mode;
    rc=screen_get_display_property_pv(m_screen_disp,SCREEN_PROPERTY_MODE,(void**)&screen_mode);
    if(rc)
    {
    	LogError("TintApp::InitEGL screen_get_display_property_pv(...SCREEN_PROPERTY_MODE...) failed");
        return EXIT_FAILURE;
    }
    int size[2];
    rc=screen_get_window_property_iv(m_screen_win,SCREEN_PROPERTY_BUFFER_SIZE,size);
    if(rc)
    {
    	LogError("TintApp::InitEGL screen_get_window_property_iv(...SCREEN_PROPERTY_BUFFER_SIZE...) failed");
        return EXIT_FAILURE;
    }
    int buffer_size[2]={size[0],size[1]};
    if((angle==0)||(angle==180))
    {
        if(((screen_mode.width>screen_mode.height)&&(size[0]<size[1]))||
        		((screen_mode.width<screen_mode.height)&&(size[0]>size[1])))
        {
        	buffer_size[1]=size[0];
        	buffer_size[0]=size[1];
        }
    }
    else if((angle==90)||(angle==270))
    {
        if(((screen_mode.width>screen_mode.height)&&(size[0]>size[1]))||
        		(((screen_mode.width<screen_mode.height)&&(size[0]<size[1]))))
        {
        	buffer_size[1]=size[0];
        	buffer_size[0]=size[1];
        }
    }
    else
    {
    	LogError("TintApp::InitEGL unexpected angle");
    	return EXIT_FAILURE;
    }
    rc=screen_set_window_property_iv(m_screen_win,SCREEN_PROPERTY_BUFFER_SIZE,buffer_size);
    if(rc)
    {
    	LogError("TintApp::InitEGL screen_set_window_property_iv(...SCREEN_PROPERTY_BUFFER_SIZE...) failed");
        return EXIT_FAILURE;
    }
    rc=screen_set_window_property_iv(m_screen_win,SCREEN_PROPERTY_ROTATION,&angle);
    if(rc)
    {
    	LogError("TintApp::InitEGL screen_set_window_property_iv(...SCREEN_PROPERTY_ROTATION...) failed");
        return EXIT_FAILURE;
    }
    rc=screen_create_window_buffers(m_screen_win,2);
    if(rc)
    {
    	LogError("TintApp::InitEGL screen_create_window_buffers failed");
        return EXIT_FAILURE;
    }
    m_egl_surf=eglCreateWindowSurface(m_egl_disp,m_egl_conf,m_screen_win,NULL);
    if(m_egl_surf==EGL_NO_SURFACE)
    {
    	LogError("TintApp::InitEGL eglCreateWindowSurface failed");
        return EXIT_FAILURE;
    }
    rc=eglMakeCurrent(m_egl_disp,m_egl_surf,m_egl_surf,m_egl_ctx);
    if(rc!=EGL_TRUE)
    {
    	LogError("TintApp::InitEGL eglMakeCurrent failed");
        return EXIT_FAILURE;
    }
    EGLint interval=1;
    rc=eglSwapInterval(m_egl_disp,interval);
    if(rc!=EGL_TRUE)
    {
    	LogError("TintApp::InitEGL eglSwapInterval failed");
        return EXIT_FAILURE;
    }
	return 0;
}

int TintApp::CalculateDPI()
{
	int rc;
	int screen_phys_size[2];
	rc=screen_get_display_property_iv(m_screen_disp,
			SCREEN_PROPERTY_PHYSICAL_SIZE,screen_phys_size);
	if(rc)
	{
		return EXIT_FAILURE;
	}
	if((screen_phys_size[0]==0)&&(screen_phys_size[1]==0))
	{
		return 170;
	}
	int screen_resolution[2];
	double diagonal_pixels=
			sqrt(screen_resolution[0]*screen_resolution[0]+screen_resolution[1]*screen_resolution[1]);
	double diagonal_inches=0.0393700787*
			sqrt(screen_phys_size[0]*screen_phys_size[0]+screen_phys_size[1]*screen_phys_size[1]);
	return (int)(diagonal_pixels/diagonal_inches+0.5);
}

void TintApp::Render()
{
	eglSwapBuffers(m_egl_disp,m_egl_surf);
}

void TintApp::LogError(const char* msg)
{
	fprintf(stderr,"%s\n",msg);
}

void TintApp::LogErrorFormat(const char* format,...)
{
	char s[128];
	va_list arg;
	va_start(arg,format);
	vsprintf(s,format,arg);
	va_end(arg);
	LogError(s);
}
