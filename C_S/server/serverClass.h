#pragma once
#include "winsock2.h"
#include "InitSock.h"
#pragma comment(lib,"WS2_32")
class serverClass
{
public:
	serverClass(int port) ;
	~serverClass();
	bool acceptClient();
	bool sSend(const char* str);
	bool sRecv();
	void closeSocket();
private:
	InitSock _initSock;
	SOCKET _sListen;
	SOCKET _sClient;
	sockaddr_in _r_sin;
	sockaddr_in _sin;
	bool _has_connect;
};

