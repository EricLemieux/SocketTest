//Simple test Client
//Eric Lemieux 2014

#include <iostream>

#include "Client.h"

void CheckForErrors()
{
	std::cout << WSAGetLastError() << std::endl;
}

int main(){
	auto* client = new Client();
	CheckForErrors();

	client->CreateSocket();
	CheckForErrors();

	client->Connect();
	CheckForErrors();

	while(client->IsClientConnected())
	{
		
		char* c = "Hello world";
		//std::cin >> c;

		std::cout <<"Sending String: "<< c << std::endl;
		client->SendString(c);
		CheckForErrors();

		std::cout << "Waiting for reply from server.\n";
		client->GetString();
		CheckForErrors();

		client->Stop();
	}

	client->Disconnect();
	CheckForErrors();

	delete client;

	return 0;
}