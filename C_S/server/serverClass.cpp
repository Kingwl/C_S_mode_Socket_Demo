#include "stdafx.h"
#include "serverClass.h"
#include "iostream"

serverClass::serverClass(int port)
:_has_connect(false)
{
	_sListen = ::socket(AF_INET, SOCK_STREAM, 0);
	if (_sListen == INVALID_SOCKET)
	{
		std::cout << "socket create failed" << std::endl;
	}
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(_sListen, (const sockaddr*)&_sin, sizeof(_sin)) == SOCKET_ERROR)
	{
		std::cout << "bind failed" << std::endl;
	}
	if (::listen(_sListen, 5) == SOCKET_ERROR)
	{
		std::cout << "listen failed" << std::endl;
	}
}


serverClass::~serverClass()
{
	closeSocket();
	::closesocket(_sListen);
}
bool serverClass::acceptClient()
{
	int nAddrLen = sizeof(_r_sin);
	_sClient = ::accept(_sListen, (SOCKADDR*)&_r_sin, &nAddrLen);
	if (_sClient == INVALID_SOCKET)
	{
		return false;
	}
	_has_connect = true;
	return true;
}
bool serverClass::sSend(const char* str)
{
	if (_has_connect)
	{
		::send(_sClient, str, strlen(str), 0);
	}
	return false;

}
void serverClass::closeSocket()
{
	::closesocket(_sClient);
	_has_connect = false;
}
bool serverClass::sRecv()
{
	char buff[1024];
	if (_has_connect)
	{
		memset(buff, 0, sizeof(buff));
		int s = ::recv(_sListen, buff, 1024, 0);
		if (s > 0)
		{
			std::cout << buff;
			return true;
		}
		return false;
	}
	return false;
}