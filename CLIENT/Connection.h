
#pragma once

#include <iostream>
#include <string>

#include <fstream>

#include "Client.h"
#include "Server.h"

//typedef char byte_t;

enum youGoElements { ANIMATION, COUNT, SECUENCIA };

bool callback(char argc, char**argv);

void TCPserver();
void asioTcpClient();//(const char* host);


int cuantas_pc_tengo(void);
void tomo_ips(char*ip, int x);


void userYouGo(char*);
unsigned int setCountMax(char*youGo);

