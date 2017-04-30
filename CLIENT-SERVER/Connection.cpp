
#include "Connection.h"


using namespace std;

enum mode { CLIENT, SERVER };

int main(int argc, char* argv[])
{
	bool mode = callback(argc, argv);

	int cuantas_pc = cuantas_pc_tengo();
	
	
	
	switch (mode)
	{
	case SERVER:
		TCPserver();
		break;
	case CLIENT:
		asioTcpClient(); 
		Sleep(10000);
		getchar();
		break;
	}
	return 0;
}


void TCPserver()
{
	server conquering;
	std::cout << std::endl << "Start Listening on port " << HELLO_PORT << std::endl;
	conquering.startConnection();
	std::cout << "Somebody connected to port " << HELLO_PORT << std::endl;
	conquering.receiveMessage(); //RECIBE EL youGo 
	conquering.sendMessage(); //DEVUELVE el youGo con el contador incrementado, o un nuevo youGo si se termino la secuencia
}

void asioTcpClient()
{
	client conquering;

	char ip[255][20];

	for (int k = 0; k != 255; k++) {
		tomo_ips(ip[k], k);
		if (ip[k + 1][0] == '\n')
			break;
	}

	//funcion userYouGo. Que agarre el valor nuevo de youGo que ponga el usuario. 

	char *animacion_y_orden_de_maquina;
	animacion_y_orden_de_maquina = (char*)new char[256];

	conquering.userYouGo(animacion_y_orden_de_maquina);


	//Averiguar countMax (por ahora tener count en cero)
	unsigned int countMax = 10; //ver

	//le va mandando el youGo a los servidores segun el orden de la secuencia
	for (unsigned int i = SECUENCIA; i < SECUENCIA+countMax; i++)
	{
		unsigned int computerNumber = (unsigned int)conquering.youGo[i]; //ver este casteo y declarar youGo.
		conquering.startConnection(ip[computerNumber][0]); //ver si se pone host. Hay que pasarle el IP. ver si pasar como puntero o que
		conquering.sendMessage(); //MANDA el youGo con la info
		conquering.receiveMessage(); //RECIBE el nuevo youGo
	}
}



///////////////////////////////////// callback ///////////////////////////////////////
// si la persona pone "iniciar" en linea de comandos, es el CLIENTE, EL QUE DIRIGE TODO!!

bool callback(char argc, char**argv)
{
	for (int i = 1; i != argc; i++) {
		if (!strcmp(argv[i], "iniciar"))
			return CLIENT;
	}
	return SERVER;
}

/////////////////





////////////////////// arreglo ips  
void tomo_ips(char*ip, int x) {


	char ip_provisoria[20];
	ifstream direcciones_ip("Direcciones.txt");

	if (!(direcciones_ip.is_open()))
		exit(1);
	int i = 0;
	while (!direcciones_ip.eof()) {

		for (int w = 0; w <= x; w++)
			direcciones_ip.getline(ip_provisoria, 20, '\n');
		for (int j = 0; j != 19; j++) {
			ip[i] = ip_provisoria[j];
			i++;
		}

	}
}

int cuantas_pc_tengo(void) {
	char nada[20];
	ifstream direcciones_ip("Direcciones.txt");
	int j = 0;
	if (!(direcciones_ip.is_open()))
		exit(1);
	int i = 0;
	while (!direcciones_ip.eof()) {
		direcciones_ip.getline(nada, 20, '\n');
		j++;
	}
	
	return j - 1; //-1 para sacarle el EOF
}
