

#include "Connection.h"
#include "Client.h"
#include "Server.h"

//#include <Windows.h>

using namespace std;

enum mode { CLIENT, SERVER };

int main(int argc, char* argv[])
{
	//bool mode = CLIENT; //BORRAR ESTA LINEA Y PONER LA DE ABAJO

	bool mode = callback(argc, argv);

	switch (mode)
	{
	case SERVER:
		TCPserver(); //(userYouGo());
		break;
	case CLIENT:
		asioTcpClient(SERVER_IP);		//SERVER_IP es el que despues se llama host
		Sleep(10000);
		getchar();
		break;
	}
	return 0;
}


void TCPserver()
{
	server conquering;
	std::cout << std::endl << "Start Listening on port " << HELLO_PORT << std::endl;
	conquering.startConnection();
	std::cout << "Somebody connected to port " << HELLO_PORT << std::endl;
	//conquering.sendMessage();
	//conquering.receiveMessage();
}

void asioTcpClient(const char* host)
{
	client conquering;
	conquering.startConnection(host);
	conquering.receiveMessage();
	conquering.sendMessage();
}



///////////////////////////////////// callback ///////////////////////////////////////

bool callback(char argc, char**argv)
{
	for (int i = 1; i != argc; i++) {
		if (!strcmp(argv[i], "iniciar"))
			return SERVER;
	}
	return CLIENT;
}

/////////////////


