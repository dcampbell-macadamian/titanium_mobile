/*
 * runtime.cpp
 *
 *  Created on: 2012-03-16
 *      Author: dcampbell
 */

#include "TiApplication.h"

extern "C"
{
	int ti_run(const char* javaScript,int argc,char **argv)
	{
		return TiApplication::Run(javaScript,argc,argv);
	}
}
