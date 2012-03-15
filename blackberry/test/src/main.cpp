/*
 * main.cpp
 *
 *  Created on: 2012-03-09
 *      Author: dcampbell
 */

#include "TintApp.h"
#include "JavascriptEngine.h"

int main(int argc,char* argv[])
{
	TintApp app;
	JavascriptEngine eng;
	int ret;

	eng.InitializeScriptEngine();
	eng.ExecuteScript("var Ti=Titanium; Ti.version");
	ret=app.InitializeApp();
	if(ret)
	{
		app.LogError("Failed to initialize application");
		return ret;
	}
	app.LogError("Application initialized");
	ret=app.Run();
	return ret;
}
