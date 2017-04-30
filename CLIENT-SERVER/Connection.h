#pragma once

#include <iostream>
#include <string>
#include <curses.h>
#include <fstream>

#include "Client.h"
#include "Server.h"

typedef char byte_t;

enum youGoElements { ANIMATION, COUNT,SECUENCIA };

bool callback(char argc, char**argv);

void TCPserver();
void asioTcpClient(const char* host);


int cuantas_pc_tengo(void);
void tomo_ips(char*ip, int x);


//byte_t* userYouGo(void);
