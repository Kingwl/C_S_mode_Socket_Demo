#pragma once
#include "winsock2.h"
#include "initSocket.h"
#include "process.h"
#include "queue"
#pragma comment(lib,"ws2_32.lib")
#include "iostream"
#include "string"
class Client
{
public:
	Client(const char* ip, int port);
	~Client();
	void send(std::string&);
	static void sendMsg(void*);
	static void recvMsg(void*);
	static void recv(void*);
	void addSend(std::string);
	void EnterMainLoop();
	void openThread();
	void init();
private:
	initSocket sockInit;
	sockaddr_in _s_in;
	SOCKET _socket;
	std::queue<std::string> _sendQue;
	std::queue<std::string> _recvQue;

};

