#include "Server.h"


Server::Server()
{
	slen = sizeof(si_other);

	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		std::cout << "Error starting winsock.\n";
		exit(1);
	}
	std::cout << "Winsock started.\n";
}


Server::~Server()
{
}

bool Server::CreateSocket()
{
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		std::cout << "Error opening socket.\n";
		exit(2);
	}
	std::cout << "Socket created.\n";
	return true;
}

void Server::Bind()
{
	server.sin_family		= AF_INET;
	server.sin_addr.s_addr	= INADDR_ANY;
	server.sin_port			= htons(PORT);

	if (bind(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR){
		std::cout << "Error binding server.\n";
		exit(3);
	}
	std::cout << "Server bound.\n";
}

void Server::GetData()
{
	fflush(stdout);

	memset(buf, '\0', MAX_BUFFER_LENGTH);

	if ((recv_len = recvfrom(sock, buf, MAX_BUFFER_LENGTH, 0, (sockaddr*)&si_other, &slen)) == SOCKET_ERROR)
	{
		std::cout << "Error recieving data";
		exit(4);
	}

	std::cout << "Recieved packet from: " << inet_ntoa(si_other.sin_addr) << ":" << ntohs(si_other.sin_port) << std::endl
		<<"Data: "<<buf<<std::endl;	

	if (sendto(sock, buf, recv_len, 0, (sockaddr*)&si_other, slen) == SOCKET_ERROR)
	{
		std::cout << "Error replying to the data.\n";
		exit(5);
	}
}

void Server::Reply()
{

}

void Server::Disconnect()
{
	closesocket(sock);
	WSACleanup();
}