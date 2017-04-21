#include "Client.h"

client::client() {
	IO_handler = new boost::asio::io_service();
	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
}

void client::startConnection(const char* host) {
	
	bool exit;

	endpoint = client_resolver->resolve(boost::asio::ip::tcp::resolver::query(host, HELLO_PORT_STR));
	
	do {
		exit = true;
		try {
			boost::asio::connect(*socket_forClient, endpoint);
		}
		catch (const std::exception& e)
		{
			std::cout << "Waiting for server" << std::endl;
			exit = false;
		}
	} while (!exit);

}

void client::receiveMessage() {
	boost::system::error_code error;
	char buf[512];
	size_t len = 0;
	std::cout << "Receiving Message" << std::endl;
	do
	{
		len = socket_forClient->read_some(boost::asio::buffer(buf), error);

		if (!error)
		{
			std::cout << '|';
			buf[len] = '\0';
			std::cout << "Receiving" << std::endl; //para debug
			//break;
		}
		//if (buf[len] == '\0')
			//break;

	} while (error); // cambie !error por error. 

	//std::cout << "Receiving" << std::endl;

	if (error != boost::asio::error::eof)
		std::cout << std::endl << "Server says: " << buf << std::endl;
	else
		std::cout << "Error while trying to connect to server %d" << error.message() << std::endl;
}

void client::writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes) {
	std::cout << std::endl << "Write Callback called" << std::endl;
}

void client::sendMessage()
{
	std::cout << std::endl << "Sending " << std::endl; //Para debug
	char message[] = "Hello from client.";

	boost::function<void(const boost::system::error_code&, std::size_t)> handler(
		boost::bind(&client::writeCompletitionCallback, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	boost::asio::async_write(*socket_forClient, boost::asio::buffer(message), handler);
}

