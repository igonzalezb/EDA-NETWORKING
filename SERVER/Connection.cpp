
#include "Connection.h"
#include <conio.h>
#include <stdio.h>



using namespace std;
//void userYouGo(char*);

enum mode { CLIENT, SERVER };

int main(int argc, char* argv[])
{
	bool mode = callback(argc, argv);

	//int cuantas_pc = cuantas_pc_tengo();


	switch (mode)
	{
	case SERVER:
		TCPserver();
		break;
	case CLIENT:
		asioTcpClient();
		Sleep(10000);
		printf("saliooooo\n");
		getchar();
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

	/*
	for (int k = 0; k != 255; k++)
	{
		tomo_ips(ip[k], k);
		if (ip[k + 1][0] == '\n')
			break;
	}
	*/

	//funcion userYouGo. Que agarre el valor nuevo de youGo que ponga el usuario. 

	char youGo[257]; //HACERLE DEFINE
	for (unsigned int i = 0; i < 257; i++)//HACERLE DEFINE al 257
	{
		youGo[i] = '\n';
	}

	//youGo = (char*)new char[cuantas_pc_tengo+2];  //Ver esto

	//userYouGo(&youGo[0]);

	userYouGo(youGo);

	printf("%c %c %c %c %c %c %c %c \n", youGo[0], youGo[1], youGo[2], youGo[3], youGo[4], youGo[5], youGo[6], youGo[7]); //prueba


	//Averiguar countMax (por ahora tener count en cero)
	unsigned int countMax = setCountMax(youGo); //ver


								//le va mandando el youGo a los servidores segun el orden de la secuencia
	printf("%u\n", countMax);

	for (unsigned int i = 0; youGo[i] != '\n'; i++)
	{
		conquering.youGo[i] = youGo[i];
		printf("paso por aca %d\n",i); //prueba
	}

	
	for (unsigned int i = SECUENCIA; i < SECUENCIA + countMax; i++)
	{
		//unsigned int computerNumber = conquering.youGo[i]-'0'; //ver este casteo y declarar youGo.
		
		//ip[computerNumber][20];
		//conquering.startConnection("localhost");
		//conquering.startConnection(&ip[computerNumber][0]); //ver si se pone host. Hay que pasarle el IP. ver si pasar como puntero o que
		
		printf("paso por aca !!!!!!!\n"); //prueba
		conquering.startConnection("localhost"); //DESPUES PONER LA LINEA DE ARRIBA. ESTA ES DE PRUEBA
		conquering.sendMessage(); //MANDA el youGo con la info
		conquering.receiveMessage(); //RECIBE el nuevo youGo
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

void userYouGo(char *animacion_y_orden_de_maquina) //de prueba "k03412"
{
	animacion_y_orden_de_maquina[0] = 'i';
	animacion_y_orden_de_maquina[1] = 0x0;
	animacion_y_orden_de_maquina[2] = '1';
		animacion_y_orden_de_maquina[3] = '4';
		animacion_y_orden_de_maquina[4] = '3';
		animacion_y_orden_de_maquina[5] = '2';

		printf("paso por aca\n"); //prueba
}

//
//void userYouGo(char *animacion_y_orden_de_maquina)
//{
//	//WINDOW * winTest = NULL;     //Puntero en dónde se guarda la terminal (Window) en donde voy a trabajar.
//	//winTest = initscr();
//	//immedok(winTest, TRUE);
//	//noecho();
//	//start_color();
//	//init_pair(2, COLOR_BLACK, COLOR_YELLOW);
//	//color_set(2, NULL);
//
//
//	char mis_animaciones[10] = { 'a','b','c','d','e','f','g','h','i','j'};//SON LAS ANIMACIONES ORDENADAS QUE HACEN REFERENCIA A LO QUE VAN A MOSTRAR
//	unsigned char character = 0;
//
//
//	printf("Pulse las letras de la A a la J en el orden que quiere las animaciones\n");
//
//	//while (character == 0) {
//	unsigned int i=0; //prueba
//	while (i<1){ //prueba
//
//		character = getch();			//toma la letra del teclado para asignarla
//		if (((character < 'a') && (character > 'j')) || ((character < 'A') && (character > 'J'))) { //esto no esta ANDANDO!!!!!!!
//			printf("Caracter invalido\n Try Again\n");
//			continue;
//		}
//
//		for (int w = 0; w != 10; w++) { //hacer un define del 10
//			if (character == mis_animaciones[w]) {
//				animacion_y_orden_de_maquina[0] = character; 
//				printf("Animacion %c seleccionada\n", mis_animaciones[w]);
//				character = 0;//ES TURBIOOOOOOOOO
//				break;
//			}
//		}
//		if (character != 0) {
//			printf("Error animacion no existente\n");
//			character = 0; //ES TURBIOOOOOOOOO
//			continue;
//		}
//		else
//			break;
//
//		i++; //prueba
//	}
//
//	animacion_y_orden_de_maquina[1] = 0X0;	//Lo voy a tomar como contador 
//
//
//	character = 0;		//Reutilizo mi character para castear el numero a binario y ponerlo en el string
//	bool seleccion_de_maquinas_incompleta = true;
//
//	//while (seleccion_de_maquinas_incompleta) {  //meter comparacion con cantidad
//	//unsigned int i=0;//DESPUES BORRAR
//	while (i < 6){ //DESPUES BORRAR
//		int caracter_a_numero = 0;
//		printf("Seleccione el orden que desea que las maquinas se conecten separados por un espacio\n");
//		int j = 2;
//		//
//		//EL 7 ES UN NUMERO ARBITRARIO QUE YO FIJE COMO MAXIMO DE PC -> TIENE QUE IR EL DE CUANTAS PC TENGO
//		//
//		unsigned int countMax = setCountMax(animacion_y_orden_de_maquina);
//
//		for (; character == 0 && j != (countMax+2); j++) {			//El maximo de j lo define la cantidad de maquinas que hay +2
//
//			cin >> caracter_a_numero;
//
//			cout << "Nro de maquina: " << caracter_a_numero << endl;
//			character = (unsigned char)caracter_a_numero;			//Casteo el numero para ponerlo en binario
//
//			animacion_y_orden_de_maquina[j] = character;
//			character = 0;
//		}
//		//clear();
//		printf("El orden seleccionado es el siguiente:\n");
//		for (unsigned int c = 0; c != j-2; c++) {
//			printf("%d\n", (unsigned char)animacion_y_orden_de_maquina[c + 2]);
//		}
//
//		printf("Confirmar? <S> Sino presione otra tecla para volver a iniciar la secuencia\n\n");
//		if (char c = getch() == 's')
//			seleccion_de_maquinas_incompleta = false;
//		i++; //DESPUES BORRAR
//	}
//	//clear();
//}



/////////////////////////////////// setCountMax //////////////////////////////////////

unsigned int setCountMax(char*youGo) 
{
	unsigned int countMax = 0;
	printf("hola\n");

	for (int contador = 2; contador < 255; contador++) {
		printf("holaaaa\n");
		if (*(youGo + contador) != EOF && *(youGo + contador) != '\0' && *(youGo + contador) != '\n')
			countMax++;
		else
		{
			break;
			//return -1;		//-1 es el error no le pongo define para que no salte error
		}
	}
	printf("chau\n");
	return countMax;
}
