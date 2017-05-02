#pragma once

#include <iostream>
#include <cmath>

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\\allegro_primitives.h>


#include "animation.h"
#include "Position.h"

//WINDOW INFO
#define SCREEN_W		1200
#define SCREEN_H		700
#define FPS			50.0
#define ANIMATION_SIZE		400

//INFO FOR EXPLOSION2
#define LOAD_TIMER		10
#define LOAD_X1			al_get_display_width(display)/6
#define LOAD_X2			al_get_display_width(display)/1.2
#define LOAD_Y1			al_get_display_height(display)/2.3
#define LOAD_Y2			al_get_display_height(display)/2.1

typedef uint32_t uint;

typedef enum {CAT, EXPLOSION1, EXPLOSION2, HOMERDANCE, SUPERMARIO, SONIC, HEMAN, HULK, PICACHU, MICHAEL, INTRO} animationId;

//PATHS 
#define INTRO_PATH	"resources/Sega/SEGA-F%d.png"
#define A_PATH		"resources/Cat Running/Cat Running-F%d.png"
#define B_PATH		"resources/Explosion 1/Explosion 1-F%d.png"
#define C_PATH		"resources/Explosion 2/Explosion 2-F%d.png"
#define D_PATH		"resources/Homer Dance/homer-F%d.png"
#define E_PATH		"resources/Super Mario/Super Mario Running-F%d.png"
#define F_PATH		"resources/Sonic/Sonic Running-F%d.png"
#define G_PATH		"resources/He-man/heman-F%d.png"
#define H_PATH		"resources/Hulk/hulk-F%d.png"
#define I_PATH		"resources/Picachu/picachu-F%d.png"
#define J_PATH		"resources/Michael/michael_%d.png"

//NUM_FRAMES	(no es el total de frames; sino frames-1, para arrancar con n=0)
#define INTRO_FRAMES	11
#define A_FRAMES	11
#define B_FRAMES	7
#define C_FRAMES	47
#define D_FRAMES	9
#define E_FRAMES	11
#define F_FRAMES	9
#define G_FRAMES	11
#define H_FRAMES	15
#define I_FRAMES	7
#define J_FRAMES	9

//SPEED
#define INTRO_SPEED	0
#define A_SPEED		20
#define B_SPEED		0
#define C_SPEED		0
#define D_SPEED		30
#define E_SPEED		20
#define F_SPEED		30//17.5
#define G_SPEED		30
#define H_SPEED		25
#define I_SPEED		30
#define J_SPEED		20

//PERIODO
#define INTRO_PERIOD	100
#define A_PERIOD	100
#define B_PERIOD	120
#define C_PERIOD	100
#define D_PERIOD	100
#define E_PERIOD	120
#define F_PERIOD	200
#define G_PERIOD	200
#define H_PERIOD	150
#define I_PERIOD	120
#define J_PERIOD	100

typedef struct
{
	float x;
	float y;
} Dimensions;


class walkingAnimation
{
public:
	walkingAnimation();
	//Constructor que recive el id del tipo de animacion (ver animationID)
	walkingAnimation(char _id);
	~walkingAnimation();
	//Comienza la animacion
	void startAnimation();
	
private:

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	Position p;
	Dimensions size;

	animation *character;
	uint id;
	
	uint currentFrame;
	bool explosion, intro;

	//Imprime el frame actual en su corespondiente coordenada
	void printAnimation();
	//Inicializa Allegro, display, event_queue y timer
	int allegro_setup();
	//Un switch-case de los diferentes tipos de animaciones (animationId), que carga los datos particulares de cada animacion
	void dispacherId();
	
};
