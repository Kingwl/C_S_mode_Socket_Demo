#include "stdafx.h"
#include "Server.h"
#include "iostream"
#include "string"
Server::Server(int port)
{
	_Listen = ::socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (_Listen == INVALID_SOCKET)
	{
		exit(0);
	}
	_s_in.sin_family = AF_INET;
	_s_in.sin_port = htons(port);
	_s_in.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(_Listen, (const sockaddr*)&(_s_in), sizeof(_s_in)))
	{
		exit(0);
	}
}
Server::~Server()
{
}
void Server::send(std::string &str)
{
	for (auto &r : _addrs)
	{	
		if (r.first != nullptr && r.second == true)
			::sendto(_Listen, str.c_str(), str.length(), 0, (sockaddr*)r.first, sizeof(*r.first));
	}
}
void Server::recv(void* serv_ptr)
{
	Server* s_ptr = reinterpret_cast<Server*>(serv_ptr);
	sockaddr_in *s_in = new sockaddr_in();
	int nLen(sizeof(*s_in));
	char buff[1024];
	while (true)
	{
		memset(buff, 0, sizeof(buff));
		int nRecv = ::recvfrom(s_ptr->_Listen, buff, 1024, 0, (sockaddr*)s_in, &nLen);
		if (nRecv > 0)
		{
			std::string result(buff);
#ifdef DEBUG
			::sendto(s_ptr->_Listen, "Hello World", 11 , 0, (sockaddr*)s_in, sizeof(*s_in));	
#endif
			s_ptr->_msgQue.push(std::make_pair(s_in, result));
		}
	}
}
void Server::clean()
{
	std::vector<std::vector<std::pair<sockaddr_in*, bool>>::iterator> del;
	auto iter = _addrs.begin();
	for (; iter != _addrs.end(); ++iter)
	{
		if (iter->first == nullptr || iter->second == false)
		{
			del.push_back(iter);
		}
	}
	for (auto &r : del)
	{
		cleanAddr(r);
	}
}
void Server::close()
{
	::closesocket(_Listen);
}
void Server::clear()
{
	cleanAddrs();
	cleanMsgQue();
	
}
void Server::cleanAddr(std::vector<std::pair<sockaddr_in*, bool>>::iterator addr)
{
	delete addr->first;
	addr->first = nullptr;
	addr->second = false;
	_addrs.erase(addr);
}
void Server::cleanAddrs()
{
	auto iter = _addrs.begin();
	for (; iter != _addrs.end(); ++iter)
	{
		cleanAddr(iter);
	}
	_addrs.clear();
}
void Server::cleanMsgQue()
{
	while (_msgQue.empty() == false)
	{
		_msgQue.pop();
	}
}
void Server::MsgLoop(void* serv_ptr)
{
	Server* s_ptr = reinterpret_cast<Server*>(serv_ptr);
	while (true)
	{
		while (s_ptr->_msgQue.empty() == false)
		{
			s_ptr->_addrs.push_back(std::make_pair(s_ptr->_msgQue.front().first, true));
			std::cout << s_ptr->_msgQue.front().second << std::endl;;
			s_ptr->_msgQue.pop();
		}
	}
}
void Server::openThread()
{
	_beginthread(Server::recv, 0, this);
	_beginthread(Server::MsgLoop, 0, this);
	_beginthread(Server::sendMsg, 0, this);

}
void Server::init()
{
	openThread();
}
void Server::addSend(std::string str)
{
	_sendQue.push(str);
}

void Server::sendMsg(void* serv_ptr)
{
	Server* s_ptr = reinterpret_cast<Server*>(serv_ptr);
	while (true)
	{
		while (s_ptr->_sendQue.empty() == false)
		{
			s_ptr->send(s_ptr->_sendQue.front());
			s_ptr->_sendQue.pop();
		}
	}
}
void Server::EnterMainLoop()
{
	init();
	std::string in;
	while (true)
	{
		std::cin >> in;
		addSend(in);
	}
}