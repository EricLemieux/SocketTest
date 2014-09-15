#include "Client.h"


Client::Client()
{
	IsConnected = false;

	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
		std::cout << "Error Starting winsock";
		//Controlled Crash
		exit(1);
	}

	std::cout << "Winsock started\n";
}


Client::~Client()
{
}

bool Client::CreateSocket()
{
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		std::cout << "Error creating socket\n";
		exit(2);
	}
	std::cout << "Socket Created.\n";
	return true;
}


void Client::Connect()
{
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	IsConnected = true;

	std::cout << "Connected to server.\n";
}

void Client::Disconnect()
{
	closesocket(sock);
	WSACleanup();
}

void Client::SendString(const char* message)
{
	std::cout << "starting to send mesage.\n";
	if (sendto(sock, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR){
		std::cout << "Error sending string.\n";
		exit(10);
	}
	std::cout << "sent " << message << "to server.\n";
}

void Client::GetString()
{
	memset(buf, '\0', MAX_BUFFER_LENGTH);

	if (recvfrom(sock, buf, MAX_BUFFER_LENGTH, 0,(sockaddr*)&si_other, &slen) == SOCKET_ERROR)
	{
		std::cout << "Error recieving data from server.\n";
		exit(11);
	}
	else
	{
		std::cout << buf << std::endl;
	}
}