#pragma once
/*

Created by Pedro Dans 27/Mar/2017
Reviewed by Agustin Perez Moreno 11/04/2017

*/


#include <iostream>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "Connection.h"

#define HELLO_PORT_STR "12345"
#define SERVER_IP "25.65.241.42"

class client {
public:
	client();
	void startConnection(const char* host);
	void receiveMessage();
	void sendMessage();
	void writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes);

private:
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* socket_forClient;
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
};