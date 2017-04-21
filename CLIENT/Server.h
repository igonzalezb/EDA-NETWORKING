#pragma once

/*

Created by Pedro Dans 27/Mar/2017
Reviewed by Agustin Perez Moreno 11/04/2017

*/


#include <iostream>
#include <exception>
#include <array>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "Connection.h"

//#include <Windows.h>

#define HELLO_PORT 12345

class server {
public:
	server();
	void startConnection();
	void sendMessage();
	void writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes);

private:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forServer;
	boost::asio::ip::tcp::acceptor* server_acceptor;
};

