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
		bool flag = server.sRecv();
		if (flag)
		{
			char c[100];
			sprintf_s(c, "hello size: %d", server.size());
			server.sSend(c);
		}
	}
	return 0;
}

