/*
 * TiApplication.cpp
 *
 *  Created on: 2012-03-16
 *      Author: dcampbell
 */

#include "TiApplication.h"
#include "CsApplication.h"
#include <stdio.h>
#include <string.h>

TiApplication::TiApplication()
{
	m_javaScript=NULL;
}

TiApplication::TiApplication(const char* javaScript)
{
	m_javaScript=new char[strlen(javaScript?m_javaScript:"")+1];
	if(javaScript)
	{
		strcpy(m_javaScript,javaScript);
	}
}

TiApplication::~TiApplication()
{
	if(m_javaScript)
	{
		delete[] m_javaScript;
		m_javaScript=NULL;
	}
}

int TiApplication::Run(const char* javaScript,int argc,char **argv)
{
	TiApplication app(javaScript);
	return app.InternalRun(argc,argv);
}

int TiApplication::InternalRun(int argc,char **argv)
{
	Application app(argc,argv);
	return 0;
}
