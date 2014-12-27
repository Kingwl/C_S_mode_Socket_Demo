#pragma once
#include "initSocket.h"
#include "vector"
#include "process.h"
#include "queue"
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")

class Server
{
public:
	Server(int port);
	~Server();
	static void sendMsg(void*);
	static void recv(void*);
	static void MsgLoop(void*);

	void send(std::string&);
	void addSend(std::string str);

	void openThread();
	void EnterMainLoop();

	void clear();
	void clean();
	void close();

protected:
	void cleanAddr(std::vector<std::pair<sockaddr_in*, bool>>::iterator addr);
	void cleanAddrs();
	void cleanMsgQue();

	void init();

private:
	initSocket sockInit;
	SOCKET _Listen;
	sockaddr_in _s_in;
	std::vector<std::pair<sockaddr_in*,bool>> _addrs;
	std::queue<std::pair<sockaddr_in*, std::string>> _msgQue;
	std::queue<std::string> _sendQue;
};

