#include "stdafx.h"
#include "initSocket.h"


initSocket::initSocket()
{
	WSADATA wsaData;
	WORD socketVersion = MAKEWORD(2, 2);
	if (::WSAStartup(socketVersion, &wsaData))
	{
		exit(0);
	}
}


initSocket::~initSocket()
{
	::WSACleanup();
}
