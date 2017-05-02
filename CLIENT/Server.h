#pragma once


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
	void receiveMessage();
	void writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes);

	void setServerAcceptor(boost::asio::ip::tcp::acceptor*);
	boost::asio::io_service *getIO_handler();
	char youGo[257];

private:
	boost::asio::io_service *IO_handler;
	boost::asio::ip::tcp::socket *socket_forServer;
	boost::asio::ip::tcp::acceptor *server_acceptor;
};

