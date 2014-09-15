#pragma once

#include <iostream>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

#define MAX_BUFFER_LENGTH 512
#define PORT 8888
#define SERVER "192.168.0.175"

class Client
{
public:
	Client();
	~Client();

	bool CreateSocket();
	void Connect();
	void Disconnect();

	void SendString(const char* message);
	void GetString();

	void Stop(){ IsConnected = false; }

	bool IsClientConnected(){ return IsConnected; }

private:
	bool IsConnected;

	WSADATA wsaData;

	sockaddr_in si_other;

	int sock;
	int slen = sizeof(si_other);

	char buf[MAX_BUFFER_LENGTH];
	char mssg[MAX_BUFFER_LENGTH];
};

