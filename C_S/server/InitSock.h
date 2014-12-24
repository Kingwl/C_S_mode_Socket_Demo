#pragma once
#include "winsock2.h"
#pragma comment(lib,"WS2_32")
class InitSock
{
public:
	InitSock(BYTE minorVer = 2, BYTE majorVer = 2);
	~InitSock();
};

