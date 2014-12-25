#include "stdafx.h"
#include "ClientClass.h"
#include "iostream"

ClientClass::ClientClass(const char* ip, int port)
{
	_socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (_socket == INVALID_SOCKET)
	{
		std::cout << "socket create failed" << std::endl;
		exit(0);
	}
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
	_sin.sin_addr.S_un.S_addr = inet_addr(ip);
}


ClientClass::~ClientClass()
{
	closeSocket();
}
bool ClientClass::recvSocket()
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	sockaddr_in *s_in = new sockaddr_in;
	int *nLen = new int(sizeof(*s_in));
	int nRecv = ::recvfrom(_socket, buff, 1024, 0, (sockaddr*)s_in, nLen);
	if (nRecv > 0)
	{
		std::cout << buff << std::endl;
		return true;
	}
	return false;
	
}

void ClientClass::closeSocket()
{
	::closesocket(_socket);
}

void ClientClass::sendSocket(const char *str)
{
	::sendto(_socket, str, strlen(str), 0, (const sockaddr*)&_sin, sizeof(_sin));
}