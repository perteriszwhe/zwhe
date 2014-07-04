#ifndef __STRINGUTILS_H__
#define __STRINGUTILS_H__

#include "cocos2d.h"
#include <string>
using namespace cocos2d;

class StringUtils: public CCObject
{
public:
	static std::string replaceAll(std::string str,std::string src,std::string dst);

	static bool isEmpty(std::string &str);

	static bool isEmpty(const char *str);

	static std::string removeNull(const char *str);

	static std::string formatTime(int time);

};

#endif


