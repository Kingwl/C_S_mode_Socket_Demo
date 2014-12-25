#pragma once
#include "winsock2.h"
#include "InitSock.h"
#include "map"
#include "vector"
#include "process.h"
#pragma comment(lib,"WS2_32")
class serverClass
{
public:
	serverClass(int port) ;
	~serverClass();
	bool sSend(const char* str);
	bool sRecv();
	void closeSocket();
	int size();
private:
	InitSock _initSock;
	SOCKET _sListen;
	std::vector<sockaddr_in*> _addrs;
	sockaddr_in _sin;
};

