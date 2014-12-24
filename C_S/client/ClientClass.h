#pragma once
#include "winsock2.h"
#include "InitSock.h"
class ClientClass
{
public:
	ClientClass(const char* ip, int port);
	~ClientClass();
	bool recvSocket();
	void closeSocket();
private:
	InitSock _initSock;

	SOCKET _socket;
	sockaddr_in _sin;
	bool _has_connect;
	
};

