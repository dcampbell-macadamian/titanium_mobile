/*
 * TiApplication.h
 *
 *  Created on: 2012-03-16
 *      Author: dcampbell
 */

#ifndef TIAPPLICATION_H_
#define TIAPPLICATION_H_

class TiApplication
{
public:
	static int Run(const char* javaScript,int argc,char **argv);
private:
	TiApplication();
	TiApplication(const char* javaScript);
	virtual ~TiApplication();

	int InternalRun(int argc,char **argv);

	char* m_javaScript;
};

#endif /* TIAPPLICATION_H_ */
