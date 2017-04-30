#include "Server.h"



void server::writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes) {
	std::cout << std::endl << "Write Callback called" << std::endl;
}

void server::startConnection(unsigned int i) 
{
	server_acceptor[i]->accept(*socket_forServer[i]);
}

void server::sendMessage(unsigned int i) 
{
	char message[] = "Hello from server.";
	std::cout << "Sending" << std::endl; //para debug
	boost::function<void(const boost::system::error_code&, std::size_t)> handler(
		boost::bind(&server::writeCompletitionCallback, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	//std::cout << "sending1" << std::endl; //para debug
	boost::asio::async_write(*socket_forServer[i], boost::asio::buffer(message), handler);
	//std::cout << "sending2" << std::endl; //para debug
}

server::server() 
{
	
	for (unsigned int j = 0; j < 255; j++)
	{
		IO_handler[j] = new boost::asio::io_service();
		socket_forServer[j] = new boost::asio::ip::tcp::socket(*IO_handler[j]);
	}
	
	//server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
	//	boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT));
	std::cout << std::endl << "Ready. Port " << HELLO_PORT << " created" << std::endl;
}

void server::receiveMessage(unsigned int i) 
{
	boost::system::error_code error;
	char buf[512];
	size_t len = 0;
	std::cout << "Receiving Message" << std::endl;
	do
	{
		len = socket_forServer[i]->read_some(boost::asio::buffer(buf), error);

		if (!error)
		{
			std::cout << '|';
			buf[len] = '\0';
		}

	} while (error); //CAMBIE !ERROR POR ERROR

	if (error != boost::asio::error::eof)
		std::cout << std::endl << "Client says: " << buf << std::endl;
	else
		std::cout << "Error while trying to connect to server %d" << error.message() << std::endl;
}


/////////////// setter de server_acceptor
void server::setServerAcceptor(boost::asio::ip::tcp::acceptor* newAcceptor, unsigned int i)
{
	server_acceptor[i] = newAcceptor;
}

boost::asio::ip::tcp::acceptor* server::getServerAcceptor(unsigned int i)
{
	return server_acceptor[i];
}

/////////////// getter de IO_handler
boost::asio::io_service* server::getIO_handler(unsigned int i)
{
	return IO_handler[i];
}