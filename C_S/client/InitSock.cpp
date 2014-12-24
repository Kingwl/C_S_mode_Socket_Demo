#include "stdafx.h"
#include "InitSock.h"


InitSock::InitSock(BYTE minorVer /*  = 2  */, BYTE majorVer/*  = 2  */)
{
	WSADATA wsaData;
	WORD sockerVersion = MAKEWORD(minorVer, majorVer);
	if (::WSAStartup(sockerVersion, &wsaData))
	{
		exit(0);
	}
}


InitSock::~InitSock()
{
	::WSACleanup();

}
