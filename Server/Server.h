#pragma once

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

#define MAX_BUFFER_LENGTH 512
#define PORT 8888

class Server
{
public:
	Server();
	~Server();

	bool CreateSocket();

	void Bind();

	void GetData();
	void Reply();

	void Disconnect();

private:
	SOCKET sock;
	sockaddr_in server, si_other;
	int slen, recv_len;
	char buf[MAX_BUFFER_LENGTH];
	WSADATA wsaData;
};

