#include "Server.h"
#include <conio.h>


void server::writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes) {
	std::cout << std::endl << "Write Callback called" << std::endl;
}

void server::startConnection()
{
	server_acceptor->accept(*socket_forServer);
}

void server::sendMessage()
{
	char message[] = "Hello from server.";
	std::cout << "Sending" << std::endl; //para debug
	boost::function<void(const boost::system::error_code&, std::size_t)> handler(
		boost::bind(&server::writeCompletitionCallback, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	//std::cout << "sending1" << std::endl; //para debug
	boost::asio::async_write(*socket_forServer, boost::asio::buffer(message), handler);
	//std::cout << "sending2" << std::endl; //para debug
}

server::server()
{
	IO_handler = new boost::asio::io_service();
	socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
	//server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
	//	boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT));
	std::cout << std::endl << "Ready. Port " << HELLO_PORT << " created" << std::endl;
}

void server::receiveMessage()
{
	boost::system::error_code error;
	char buf[512];
	for (unsigned int i = 0; i < 512; i++)
	{
		buf[i] = '\n';
	}
	size_t len = 0;
	std::cout << "Receiving Message" << std::endl;
	do
	{
		len = socket_forServer->read_some(boost::asio::buffer(buf), error);

		if (!error)
		{
			std::cout << '|';
			buf[len] = '\0';
		}

	} while (error); //CAMBIE !ERROR POR ERROR

	if (error != boost::asio::error::eof)
	{
		walkingAnimation *character = new walkingAnimation(buf[0]); //MANDARLE EL ELEMENTO 0 DE buf. buf ACA ES LO MISMO QUE youGo. tiene la letra de la animacion
		character->startAnimation();
		delete character;

		buf[COUNT]++; // incremento contador. 

					  //////ACA AVERIGUAR EL VALOR DE countMax)  VER COMO HACERLO
		
		unsigned int countMax = setCountMax(buf);
		////////////

		if (buf[COUNT] >= countMax)
		{
			userYouGo(buf); // va a esperar a que  se ingrese todo por teclado. Ya hace como un setter, tiene acceso a youGo.
							//GUARDAR BUF EN youGo
		}

	}
	else
		std::cout << "Error while trying to connect to server %d" << error.message() << std::endl;
}


/////////////// setter de server_acceptor
void server::setServerAcceptor(boost::asio::ip::tcp::acceptor* newAcceptor)
{
	server_acceptor = newAcceptor;
}

/////////////// getter de IO_handler
boost::asio::io_service* server::getIO_handler()
{
	return IO_handler;
}