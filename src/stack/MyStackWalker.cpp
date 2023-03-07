#include "stack/MyStackWalker.hpp"

#include <string>
#include <log4cplus/loggingmacros.h>
#include <logger/LoggerAppenders.hpp>

#pragma comment(lib,"Dbghelp.lib")



void MyStackWalker::OnOutput(LPCSTR szText)
{
	std::string text(szText);
	text.erase(std::remove(text.begin(), text.end(), '\n'), text.end());

	//std::cout<<"Call Stack : "" << text << std::endl;  
	LOG4CPLUS_WARN(log4cplus::Logger::getInstance(DEVELOPER_APPENDER_ID), "[Call Stack] " << text.c_str());
	StackWalker::OnOutput(szText);
}
