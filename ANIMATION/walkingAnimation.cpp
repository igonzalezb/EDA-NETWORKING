#include "walkingAnimation.h"

walkingAnimation::walkingAnimation()
{
}


walkingAnimation::walkingAnimation(char _id)
{
	id = _id - 'a';
	currentFrame = 0;
	explosion = false;
	intro = false;
	
	if(allegro_setup())
		fprintf(stderr, "failed to setup allegro!\n");

	//Seteo coordenadas y tamaño por defecto (dentro del dispacher pueden cambiar en algunos casos)
	p.setX(al_get_display_width(display));
	p.setY(al_get_display_height(display)/4);
	size.x = ANIMATION_SIZE;
	size.y = ANIMATION_SIZE;
	

	dispacherId();

}

void walkingAnimation::startAnimation()
{
	bool do_exit = false, redraw = true;

	al_draw_scaled_bitmap(character.getScenario(), 0.0, 0.0, al_get_bitmap_width(character.getScenario()), al_get_bitmap_height(character.getScenario()), 0.0, 0.0, al_get_display_width(display), al_get_display_height(display), NULL);				//Dibujamos el fondo
	al_flip_display();
	
	al_set_timer_speed(timer, 10.0 / character.getPeriod());	//Cambio el periodo segun el objeto en el que estoy
	al_start_timer(timer);
	
	while (!do_exit)
	{
		ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			p.setX(p.getX() - character.getFrameSpeed());	//Muevo el objeto en el eje x segun su velocidad
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			do_exit = true;

		if (redraw)
		{
			redraw = false;
			al_draw_scaled_bitmap(character.getScenario(), 0.0, 0.0, al_get_bitmap_width(character.getScenario()), al_get_bitmap_height(character.getScenario()), 0.0, 0.0, al_get_display_width(display), al_get_display_height(display), NULL);
			printAnimation();
			al_flip_display();

			if (currentFrame >= character.getCantFrames())
			{
				currentFrame = 0;				//Como ya pasaron todos los frames, vuelvo a comenzar,
				if (explosion || intro)				//a menos que este en la intro o sea una explosion
				{
					do_exit = true;
					al_rest(0.5);				//Esta pausa es para que las explosiones que se corren una vex sola no se corte el audio antes, se podria sacar.
				}
					
			}
			else
				currentFrame++;
		}

		if ((p.getX() < 0.0))
			do_exit = true;		//Si llego al final del display finalizo la animacion

	}

}

int walkingAnimation::allegro_setup()
{
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_image_addon())
	{
		fprintf(stderr, "Unable to start image addon \n");
		al_uninstall_system();
		return -1;
	}

	if (!al_install_audio())
	{
		fprintf(stderr, "Unable to start audio addon \n");
		al_uninstall_system();
		return -1;
	}
	if (!al_init_acodec_addon())
	{
		fprintf(stderr, "Unable to start audio codec addon \n");
		al_uninstall_system();
		return -1;
	}
	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "Unable to start primitives addon \n");
		al_uninstall_system();
		return -1;
	}
	if (!al_reserve_samples(2))
	{
		fprintf(stderr, "Unable to reserve samples \n");
		al_uninstall_system();
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}


	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_set_window_title(display, "TP6 - NETWORKING");

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));


	return 0;

}

void walkingAnimation::printAnimation()
{
	al_draw_scaled_bitmap(character.getAniFrames()[currentFrame], 0.0, 0.0,
		al_get_bitmap_width(character.getAniFrames()[currentFrame]), al_get_bitmap_height(character.getAniFrames()[currentFrame]),
		p.getX(), p.getY(), size.x, size.y, character.isLookingRight());
		
}

void walkingAnimation::dispacherId()
{
	switch (id)
	{
	case CAT:
		character.animationSetup(A_FRAMES, A_SPEED, A_PERIOD, A_PATH, "Cat Running");
		character.lookRight();
		p.setY(al_get_display_height(display) / 2.5);
		break;
	case EXPLOSION1:
		character.animationSetup(B_FRAMES, B_SPEED, B_PERIOD, B_PATH, "Explosion 1");
		p.setX(0.0);
		p.setY(0.0);
		size.x = al_get_display_width(display);
		size.y = al_get_display_height(display);
		explosion = true;
		break;
	case EXPLOSION2:

	//===============================================================================================================================================================
		//Una intro a la explosion -> una imagen de bomba con audio
		ALLEGRO_SAMPLE* sample;
		ALLEGRO_BITMAP* bomb;
		

		sample = al_load_sample("resources/Explosion 2/intro.wav");
		if (!sample)
		{
			fprintf(stderr, "failed to create sample!\n");
		}
		bomb = al_load_bitmap("resources/Explosion 2/bomb.jpg");
		if (!bomb)
		{
			fprintf(stderr, "failed to create bomb!\n");
		}
		
		al_draw_scaled_bitmap(bomb, 0.0, 0.0, al_get_bitmap_width(bomb), al_get_bitmap_height(bomb), 0.0, 0.0, al_get_display_width(display), al_get_display_height(display), NULL);
		al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		
		al_draw_rectangle(LOAD_X1, LOAD_Y1, LOAD_X2, LOAD_Y2,  al_map_rgb(255, 255, 153), 4);
		al_flip_display();
		
		{
			float incrementX = ((LOAD_X2) - (LOAD_X1))/(LOAD_TIMER), increment = LOAD_X1 + incrementX;

			for (uint i = 1; i <= LOAD_TIMER; i++)
			{
				al_draw_filled_rectangle(LOAD_X1, LOAD_Y1, increment, LOAD_Y2, al_map_rgb(255, 255, 153));
				al_flip_display();
				increment = increment + incrementX;
				al_rest(1);
			}
		}
		
		al_stop_samples();
		al_destroy_sample(sample);
	//===============================================================================================================================================================
		character.animationSetup(C_FRAMES, C_SPEED, C_PERIOD, C_PATH, "Explosion 2");
		p.setX(0.0);
		p.setY(0.0);
		size.x = al_get_display_width(display);
		size.y = al_get_display_height(display);
		explosion = true;
		break;
	case HOMERDANCE:
		character.animationSetup(D_FRAMES, D_SPEED, D_PERIOD, D_PATH, "Homer Dance");
		character.lookRight();
		p.setY(al_get_display_height(display) / 2.5);
		break;
	case SUPERMARIO:
		character.animationSetup(E_FRAMES, E_SPEED, E_PERIOD, E_PATH, "Super Mario");
		character.lookRight();
		p.setY(al_get_display_height(display) / 3);
		break;
	case SONIC:
		character.animationSetup(F_FRAMES, F_SPEED, F_PERIOD, F_PATH, "Sonic");
		p.setY(al_get_display_height(display) / 3);
		break;
	case HEMAN:
		character.animationSetup(G_FRAMES, G_SPEED, G_PERIOD, G_PATH, "He-man");
		p.setY(al_get_display_height(display) / 3);
		break;
	case HULK:
		character.animationSetup(H_FRAMES, H_SPEED, H_PERIOD, H_PATH, "Hulk");
		character.lookRight();
		p.setY(al_get_display_height(display) / 3);
		break;
	case PICACHU:
		character.animationSetup(I_FRAMES, I_SPEED, I_PERIOD, I_PATH, "Picachu");
		break;
	case MICHAEL:
		character.animationSetup(J_FRAMES, J_SPEED, J_PERIOD, J_PATH, "Michael");
		break;
	case INTRO:
		character.animationSetup(INTRO_FRAMES, INTRO_SPEED, INTRO_PERIOD, INTRO_PATH, "Sega");
		p.setX(al_get_display_width(display) / 2 - al_get_bitmap_width(character.getAniFrames()[0]) / 2);
		p.setY(al_get_display_height(display) / 2 - al_get_bitmap_height(character.getAniFrames()[0]));
		size.x = al_get_display_width(display) / 2;
		size.y = al_get_display_height(display) / 2;
		intro = true;
		break;
	}
}

walkingAnimation::~walkingAnimation()
{
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	al_uninstall_system();		//No se porque se cuelga el programa
	al_shutdown_image_addon();
	al_uninstall_audio();			//No se porque se cuelga el programa
	al_shutdown_primitives_addon();
		
	
}