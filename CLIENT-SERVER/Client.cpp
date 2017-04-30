#include "Client.h"

client::client() {
	IO_handler = new boost::asio::io_service();
	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
}

void client::startConnection(const char* host) {
	endpoint = client_resolver->resolve(
		boost::asio::ip::tcp::resolver::query(host, HELLO_PORT_STR));
	boost::asio::connect(*socket_forClient, endpoint);
}

void client::receiveMessage() {
	boost::system::error_code error;
	char buf[512];
	size_t len = 0;
	std::cout << "Receiving Message" << std::endl;
	do
	{
		len = socket_forClient->read_some(boost::asio::buffer(buf), error);

		if (!error)
		{
			std::cout << '|';
			buf[len] = '\0';
			std::cout << "Receiving" << std::endl; //para debug
												   //break;
		}
		//if (buf[len] == '\0')
		//break;

	} while (error); // cambie !error por error. 

					 //std::cout << "Receiving" << std::endl;
	if (error != boost::asio::error::eof)
	{
		animation character(*buf); //MANDARLE EL ELEMENTO 0 DE buf. buf ACA ES LO MISMO QUE youGo. tiene la letra de la animacion
		character.startAnimation();

		buf[COUNT]++; // incremento contador. 

		//////ACA AVERIGUAR EL VALOR DE countMax)  VER COMO HACERLO
		std::string str(buf); //bien?
		unsigned int countMax = str.length() - 2;
		////////////

		if (buf[COUNT] >= countMax)
		{
			buf = userYouGo(); // va a esperar a que  se ingrese todo por teclado. Ya hace como un setter, tiene acceso a youGo.
			//GUARDAR BUF EN youGo
		}
	}
	else
		std::cout << "Error while trying to connect to server %d" << error.message() << std::endl;
}

void client::writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes) {
	std::cout << std::endl << "Write Callback called" << std::endl;
}

void client::sendMessage()
{
	std::cout << std::endl << "Sending " << std::endl; //Para debug

	boost::function<void(const boost::system::error_code&, std::size_t)> handler(
		boost::bind(&client::writeCompletitionCallback, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

	boost::asio::async_write(*socket_forClient, boost::asio::buffer(youGo), handler); //revisar como le paso youGo
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

void client::userYouGo(char *animacion_y_orden_de_maquina)
{
	WINDOW * winTest = NULL;                     //Variable en dónde se guarda la terminal (Window) en donde voy a trabajar.
	char mis_animaciones[11] = { 'a','b','c','d','e','f','g','h','i','j','k' };//SON LAS ANIMACIONES ORDENADAS QUE HACEN REFERENCIA A LO QUE VAN A MOSTRAR
	unsigned char c = 0;

	winTest = initscr();
	immedok(winTest, TRUE);
	printw("Pulse las letras de la A a la Z en el orden que quiere las animaciones\n");

	noecho();

	while (c == 0) {

		c = getch();			//While con for re turbio para chequear las le
		if (c < 'a' || c > 'z')
			break;
		for (int w = 0; w != 8; w++) {
			if (c == mis_animaciones[w]) {
				animacion_y_orden_de_maquina[0] = c;
				printw("Animacion %c seleccionada\n", mis_animaciones[w]);
				c = 0;
				break;
			}
		}
		if (c != 0) {
			printw("Error animacion no existente\n");
			c = 0;
			continue;
		}
		else
			break;
	}
	*(animacion_y_orden_de_maquina + 1) = 0X1;	//Lo voy a tomar como contador 

	start_color();
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	color_set(2, NULL);
	c = 0;
	while (1) {
		int j = 2;
		int caracter_a_numero = 0;
		printw("Seleccione el orden que desea que las maquinas se conecten separados por un espacio\n");
		//No se por que no funciona con enters pero si con espacios
		while (c == 0 && j != 7) {			//El maximo de j lo define la cantidad de maquinas que hay +2

			std::cin >> caracter_a_numero;					//While con for re turbio para chequear las le
			std::cout << "Nro de maquina: " << caracter_a_numero << std::endl;
			c = (unsigned char)caracter_a_numero;

			animacion_y_orden_de_maquina[j] = c;
			c = 0;
			j++;
		}
		clear();
		printw("El orden seleccionado es el siguiente:\n");
		for (int c = 0; c != j - 2; c++) {
			printw("%d\n", (unsigned char)animacion_y_orden_de_maquina[c + 2]);
		}

		printw("Confirmar? <S> Sino presione otra tecla para volver a iniciar la secuencia\n\n");
		if (char c = getch() == 's')
			break;

		else {
			clear();
			c = 0;
			continue;
		}
	}
	clear();
}