#pragma once

//#include "Client.h"
//#include "Server.h"

typedef char byte_t;

enum youGoElements {ANIMATION, COUNT};

bool callback(char argc, char**argv);

void TCPserver();
void asioTcpClient(const char* host);

//byte_t* userYouGo(void);
