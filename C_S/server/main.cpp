// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "serverClass.h"
#include "iostream"
int main(int argc, char* argv[])
{
	serverClass server(4444);
	while (true)
	{
		bool flag = server.acceptClient();
		if (flag)
		{
			std::cout << "connected!" << std::endl;
			server.sSend("hello client");
			server.closeSocket();
		}
	}
	return 0;
}

