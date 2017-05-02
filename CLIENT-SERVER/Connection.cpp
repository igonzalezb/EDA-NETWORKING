
#include "Connection.h"
#include <conio.h>
#include <stdio.h>



using namespace std;
//void userYouGo(char*);

enum mode { CLIENT, SERVER };

int main(int argc, char* argv[])
{
	walkingAnimation *intro = new walkingAnimation('k');
	intro->startAnimation();
	delete intro;

	bool mode = callback(argc, argv);

	switch (mode)
	{
	case SERVER:
		TCPserver();
		break;
	case CLIENT:
		asioTcpClient();
		break;
	}
	return 0;
}


void TCPserver()
{
	server conquering;
	std::cout << std::endl << "Start Listening on port " << HELLO_PORT << std::endl;
	conquering.setServerAcceptor(new boost::asio::ip::tcp::acceptor(*conquering.getIO_handler(),
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT)));
	conquering.startConnection();
	std::cout << "Somebody connected to port " << HELLO_PORT << std::endl;
	conquering.receiveMessage(); //RECIBE EL youGo 
	conquering.sendMessage(); //DEVUELVE el youGo con el contador incrementado, o un nuevo youGo si se termino la secuencia
}

void asioTcpClient()
{
	client conquering;

	char ip[255][20];

	for (int k = 0; k != 255; k++)
	{
		tomo_ips(ip[k], k);
		if (ip[k + 1][0] == '\n')
			break;
	}
	
	char youGo[257]; //HACERLE DEFINE
	for (unsigned int i = 0; i < 257; i++)//HACERLE DEFINE al 257
	{
		youGo[i] = '\n';
	}
	
	userYouGo(youGo);


	unsigned int countMax = setCountMax(youGo); 

	for (unsigned int i = 0; youGo[i] != '\n'; i++)
	{
		conquering.youGo[i] = youGo[i];
	}


	for (unsigned int i = SECUENCIA; i < SECUENCIA + (countMax-1); i++)
	{
		unsigned int computerNumber = conquering.youGo[i];
		printf("computer number: %d\n", computerNumber);

		if (computerNumber == 0x0)
		{
			walkingAnimation *character = new walkingAnimation(youGo[0]);
			character->startAnimation();
			delete character;

			if (i == (SECUENCIA + (countMax - 2)))
			{
				userYouGo(youGo);
			}

		}
		
		conquering.startConnection(&ip[computerNumber][0]); //ver si se pone host. Hay que pasarle el IP. ver si pasar como puntero o que
		conquering.sendMessage(); //MANDA el youGo con la info
		conquering.receiveMessage(); //RECIBE el nuevo youGo

		if (i == SECUENCIA + (countMax - 2))
		{
			countMax = setCountMax(youGo);
			i = SECUENCIA;
		}
	}
}



///////////////////////////////////// callback ///////////////////////////////////////
// si la persona pone "iniciar" en linea de comandos, es el CLIENTE, EL QUE DIRIGE TODO!!

bool callback(char argc, char**argv)
{
	for (int i = 1; i != argc; i++)
	{
		if (!strcmp(argv[i], "iniciar"))
			return CLIENT;
	}
	return SERVER;
}

/////////////////





////////////////////// arreglo ips     //si no encuentra el archivo, que hace?

void tomo_ips(char*ip, int x) {


	char ip_provisoria[20];
	ifstream direcciones_ip("Direcciones.txt");

	if (!(direcciones_ip.is_open()))
		exit(1);
	int i = 0;
	while (!direcciones_ip.eof()) {

		for (int w = 0; w <= x; w++)
			direcciones_ip.getline(ip_provisoria, 20, '\n');
		for (int j = 0; j != 19; j++, i++) {
			if (ip_provisoria[j]<'0' && ip_provisoria[j]>'9' && ip_provisoria[j] != '.') {
				ip[i] = '\0';			//CAMBIA EL \0 SI QUERES PARA PONER OTRO TERMINADOR
				break;
			}
			else {
				ip[i] = ip_provisoria[j];
			}

		}

	}
}


///////////////////////////////////// cuantas_pc_tengo //////////////////////////////////////	

int cuantas_pc_tengo(void)
{
	char nada[20];
	ifstream direcciones_ip("Direcciones.txt");
	int j = 0;
	if (!(direcciones_ip.is_open()))
		exit(1);
	int i = 0;
	while (!direcciones_ip.eof())
	{
		direcciones_ip.getline(nada, 20, '\n');
		j++;
	}
	return j - 1; //-1 para sacarle el EOF
}


///////////////////////////////////// userYouGo //////////////////////////////////////	
//
// Función que espera a que el usuario haya ingresado:
//			-Animación deseada (De la A a la F)
//			-La secuencia de máquinas en las que se mostrará dicha animación.
//			 (1,2, ... , 255 en el orden en el que se deseen, las máquinas que se
//			 conecten)
//
//////////////////////////////////////////////////////////////////////////////////////

void userYouGo(char *animacion_y_orden_de_maquina)
{
	char mis_animaciones[10] = { 'a','b','c','d','e','f','g','h','i','j'};		//SON LAS ANIMACIONES ORDENADAS QUE HACEN REFERENCIA A LO QUE VAN A MOSTRAR
	
	printf("Pulse las letras de la A a la J en el orden que quiere las animaciones\n");
	bool do_exit = false;
	char letter;

	while (!do_exit)
	{
		letter = getchar();
		if (((letter >= 'a') && (letter <= 'j')) || ((letter >= 'A') && (letter <= 'J'))) 
		{
			animacion_y_orden_de_maquina[ANIMATION] = letter;
			do_exit = true;
		}
		else
			printf("Caracter invalido\n Try Again\n");
			
	}

	animacion_y_orden_de_maquina[COUNT] = 0X0;	//Lo voy a tomar como contador 

	bool seleccion_de_maquinas_incompleta = true;
	char quit;
	while (seleccion_de_maquinas_incompleta)
	{
		printf("Seleccione el orden que desea que las maquinas se conecten\n");
		
		for (unsigned int i = SECUENCIA, caracter_a_numero = 0; i < 257 && seleccion_de_maquinas_incompleta; i++)
		{
			animacion_y_orden_de_maquina[COUNT] = 0X1;

			cin >> caracter_a_numero;
			cout << "Nro de maquina: " << caracter_a_numero << endl;
			letter = (unsigned char)caracter_a_numero;			//Casteo el numero para ponerlo en binario
			animacion_y_orden_de_maquina[i] = letter;
			if (caracter_a_numero > 255)
			{
				printf("Caracter No valido, vuele a ingresar el numero\n");
				i--;
				continue;
			}
			printf("Desea salir? presione s\n");
			cin >> quit;
			if (quit == 's')
				break;
		}

		seleccion_de_maquinas_incompleta = false;
	}
}



/////////////////////////////////// setCountMax //////////////////////////////////////

unsigned int setCountMax(char*youGo) 
{
	unsigned int countMax = 0;
	for (int contador = SECUENCIA; contador < 255; contador++) {
		if (*(youGo + contador) != EOF && *(youGo + contador) != '\n')
			countMax++;
		else
		{
			break;
			//return -1;		//-1 es el error no le pongo define para que no salte error
		}
	}
	return countMax;
}
