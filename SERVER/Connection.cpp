


#include "Connection.h"
#include "Client.h"
#include "Server.h"

//#include <Windows.h>

using namespace std;

enum mode { CLIENT, SERVER };

int main(int argc, char* argv[])
{
	//bool mode = SERVER; //BORRAR ESTA LINEA Y PONER LA DE ABAJO

	bool mode = callback(argc, argv);

	switch (mode)
	{
	case SERVER:
		TCPserver(); //(userYouGo());
		Sleep(10000);
		getchar();
		break;
	case CLIENT:
		asioTcpClient(SERVER_IP);		//SERVER_IP es el que despues se llama host
		Sleep(10000);
		getchar();
		break;
	}
	return 0;
}

//server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
//	boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT));

void TCPserver()
{
	server conquering;

	conquering.setServerAcceptor(new boost::asio::ip::tcp::acceptor(*conquering.getIO_handler(),
				boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT))); // cambio tcp::v4() por address::from_string("127.0.0.1")
	

	std::cout << std::endl << "Start Listening on port " << HELLO_PORT << std::endl;
	conquering.startConnection();
	std::cout << "Somebody connected to port " << HELLO_PORT << std::endl;
	conquering.sendMessage();
	conquering.receiveMessage();
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