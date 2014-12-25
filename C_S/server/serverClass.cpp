#include "stdafx.h"
#include "serverClass.h"
#include "iostream"

serverClass::serverClass(int port)
{
	_sListen = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (_sListen == INVALID_SOCKET)
	{
		std::cout << "socket create failed" << std::endl;
	}
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;

	if (::bind(_sListen, (const sockaddr*)&_sin, sizeof(_sin)) == SOCKET_ERROR)
	{
		std::cout << "bind failed" << std::endl;
	}
}


serverClass::~serverClass()
{
	closeSocket();
}
bool serverClass::sSend(const char* str)
{
	for (auto &p : _addrs)
	{
		::sendto(_sListen, str, strlen(str), 0, (sockaddr*)p, sizeof(*p));
	}
	return true;
}
int serverClass::size()
{
	return _addrs.size();
}
void serverClass::closeSocket()
{
	::closesocket(_sListen);
}
bool serverClass::sRecv()
{
	sockaddr_in *s_in = new sockaddr_in;
	int *nLen = new int(sizeof(*s_in));
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	int nRecv = ::recvfrom(_sListen, buff, 1024, 0, (sockaddr*)s_in, nLen);
	if (nRecv > 0)
	{
		_addrs.push_back(s_in);
		std::cout << buff<< " size: "<<size() << std::endl;
		return true;
	}
	return false;

}
