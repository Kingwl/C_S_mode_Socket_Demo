// UDPServer.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "Server.h"
int main(int argc, _TCHAR* argv[])
{
	Server server(4444);
	server.EnterMainLoop();
	return 0;
}

