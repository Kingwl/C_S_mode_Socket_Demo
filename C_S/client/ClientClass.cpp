#include "stdafx.h"
#include "ClientClass.h"
#include "iostream"

ClientClass::ClientClass(const char* ip, int port)
:_has_connect(false)
{
	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
	{
		std::cout << "socket create failed" << std::endl;
		exit(0);
	}
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
	_sin.sin_addr.S_un.S_addr = inet_addr(ip);
	if (::connect(_socket, (const sockaddr*)&_sin, sizeof(_sin)) == -1)
	{
		std::cout << "connect failed" << std::endl;
		exit(0);

	}
	_has_connect = true;
	

}


ClientClass::~ClientClass()
{
	closeSocket();
}
bool ClientClass::recvSocket()
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	if (_has_connect)
	{
		int r = ::recv(_socket, buff, 1024, 0);
		if (r > 0)
		{
			std::cout << buff << std::endl;
			return true;
		}
		return false;
	}
	return false;
	
}

void ClientClass::closeSocket()
{
	::closesocket(_socket);
	_has_connect = false;
}