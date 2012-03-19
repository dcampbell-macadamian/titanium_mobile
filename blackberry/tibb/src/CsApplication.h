/*
 * CsApplication.h
 *
 *  Created on: 2012-03-16
 *      Author: dcampbell
 */

#ifndef CSAPPLICATION_H_
#define CSAPPLICATION_H_

#include <bb/cascades/Application>

using namespace bb::cascades;

namespace bb
{
    namespace cascades
    {
        class Container;
    }
}

class CsApplication :
	public QObject
{
public:
	CsApplication();
	virtual ~CsApplication();
};

#endif /* CSAPPLICATION_H_ */
