#include "stdafx.h"
#include "Client.h"


Client::Client(const char *ip, int port)
{
	_socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (_socket == INVALID_SOCKET)
	{
		exit(0);
	}
	_s_in.sin_family = AF_INET;
	_s_in.sin_port = htons(port);
	_s_in.sin_addr.S_un.S_addr = inet_addr(ip);
	send(std::string("connect"));
}


Client::~Client()
{
}
void Client::send(std::string &str)
{
	::sendto(_socket, str.c_str(), str.length(), 0,(const sockaddr*)&_s_in,sizeof(_s_in));
}
void Client::sendMsg(void* client_ptr)
{
	Client* c_ptr = reinterpret_cast<Client*>(client_ptr);
	while (true)
	{
		while (c_ptr->_sendQue.empty() == false)
		{
			c_ptr->send(c_ptr->_sendQue.front());
			c_ptr->_sendQue.pop();
		}
	}
}
void Client::recvMsg(void *client_ptr)
{
	Client* c_ptr = reinterpret_cast<Client*>(client_ptr);
	sockaddr_in s_in;
	int nLen(sizeof(s_in));
	char buff[1024];
	while (true)
	{
		memset(buff, 0, sizeof(buff));
		int nRecv = ::recvfrom(c_ptr->_socket, buff, 1024, 0, (sockaddr*)&s_in, &nLen);
		if (nRecv > 0)
		{
			std::string result(buff);
			c_ptr->_recvQue.push(result);
		}
	}
}
void Client::recv(void *client_ptr)
{
	Client* c_ptr = reinterpret_cast<Client*>(client_ptr);
	while (true)
	{
		while (c_ptr->_recvQue.empty() == false)
		{
			std::string recvStr = c_ptr->_recvQue.front();
			std::cout << recvStr << std::endl;
			c_ptr->_recvQue.pop();
		}
	}
}
void Client::addSend(std::string str)
{
	_sendQue.push(str);
}
void Client::EnterMainLoop()
{
	init();
	std::string in;
	while (true)
	{
		std::getline(std::cin, in);
		addSend(in);
	}
}
void Client::openThread()
{
	_beginthread(Client::sendMsg, 0, this);
	_beginthread(Client::recvMsg, 0, this);
	_beginthread(Client::recv, 0, this);
}
void Client::init()
{
	openThread();
}