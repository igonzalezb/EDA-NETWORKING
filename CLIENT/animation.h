#pragma once

#include <iostream>

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

class animation
{
public:
	animation();
	//Setea y crea a la animacion
	//Recibe la cantidad de frames, la velocidad de la caminata, el perdiodo de los frames,
	//un string de la direccion de los bitmaps(con %d en el numero de frame), y un string con el nombre de la carpeta que contiene el background y musica
	animation(unsigned int _cantFrames, float _frameSpeed, float _period, char path[], char id[]);
	~animation();
	//Devuelve true si esta mirando a la derecha
	bool isLookingRight();
	//Setea el objeto para que vea a la derecha(para los casos en que la imagen ve a la izquierda; un flip)
	void lookRight();
	//Diferentes getters para los datos miembros privados
	unsigned int getCantFrames();
	float getFrameSpeed();
	ALLEGRO_BITMAP * getScenario();
	ALLEGRO_BITMAP** getAniFrames();
	double getPeriod();

private:
	ALLEGRO_BITMAP *Scenario = NULL;
	ALLEGRO_BITMAP **aniFrames = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	
	float frameSpeed;
	double period;
	unsigned int cantFrames;
	bool lookingRight;
};

