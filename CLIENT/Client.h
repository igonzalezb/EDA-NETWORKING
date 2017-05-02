#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "Connection.h"



#define HELLO_PORT_STR "12345"
#define SERVER_IP "localhost"

class client {
public:
	client();
	void startConnection(const char* host);
	void receiveMessage();
	void sendMessage();
	void writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes);
	char youGo[257];
	//void userYouGo(char *animacion_y_orden_de_maquina);

private:
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* socket_forClient;
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
};
