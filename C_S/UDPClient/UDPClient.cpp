// UDPClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Client.h"

int main(int argc, _TCHAR* argv[])
{
	Client client("127.0.0.1",4444);
	client.EnterMainLoop();
	return 0;
}

