// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ClientClass.h"

int _tmain(int argc, _TCHAR* argv[])
{
	ClientClass client("127.0.0.1", 4444);
	client.sendSocket("hello?");
	while (true)
	{
		client.recvSocket();
	}
	system("pause");
	return 0;
}

