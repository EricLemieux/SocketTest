#include "Server.h"

void CheckForErrors()
{
	std::cout << WSAGetLastError() << std::endl;
}

int main()
{
	Server* server = new Server;
	CheckForErrors();

	server->CreateSocket();
	CheckForErrors();

	server->Bind();
	CheckForErrors();

	while (true)
	{
		std::cout << "Waiting for data.\n";

		server->GetData();
		CheckForErrors();

		//server->Reply();
	}

	server->Disconnect();
	CheckForErrors();

	delete server;

	return 0;
}