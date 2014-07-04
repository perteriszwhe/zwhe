#include "StringUtils.h"

std::string StringUtils::replaceAll( std::string str,std::string src,std::string dst )
{
	int npos = str.find(src);
	while( npos != std::string::npos)
	{
		str.replace(npos,src.length(),dst);
		npos = str.find(src,npos);
	}
	return str;
}

bool StringUtils::isEmpty( std::string &str )
{
	if( str.length() == 0)
		return true;
	return false;
}

bool StringUtils::isEmpty( const char *str )
{
	if( str == NULL || strlen(str) == 0)
		return true;
	return false;
}

std::string StringUtils::removeNull( const char *str )
{
	if( str == NULL || strlen(str) == 0)
		return "";
	return str;
}

std::string StringUtils::formatTime( int time )
{
	int minute = time / 3600;
	int second = (time % 3600) / 60;
	int microseconds = (time % 3600) % 60;
	char buffer[9];
	sprintf(buffer,"%02d:%02d:%02d",minute,second,microseconds);
	return buffer;
}

