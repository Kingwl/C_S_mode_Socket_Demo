// ConsoleApplication2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ClientClass.h"

int _tmain(int argc, _TCHAR* argv[])
{
	ClientClass client("127.0.0.1", 4444);
	
	while (client.recvSocket())
	{

	}
	system("pause");
	return 0;
}

