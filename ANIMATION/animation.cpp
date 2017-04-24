#include "animation.h"


animation::animation()
{}

void animation::animationSetup(unsigned int _cantFrames, float _frameSpeed, float _period, char path[], char id[])
{
	unsigned int j = 0;
	char aPath[100];		//Arreglo auxiliar para strings de paths ya completos
	cantFrames = _cantFrames;	//seteo las variables de la clase en el valor del objeto actual
	frameSpeed = _frameSpeed;
	period = _period;

	aniFrames = new ALLEGRO_BITMAP*[cantFrames];		//Arreglo dinamico de bitmaps, para los frames
	
								
	//Cargo el fondo segun el objeto en que estoy
	sprintf(aPath, "resources/%s/Scenario.png", id);	//todos las animaciones deben tener un scenario.png con ese formato y en ese path
	Scenario = al_load_bitmap(aPath);
	if (!Scenario) {
		fprintf(stderr, "failed to create Scenario bitmap!\n");
	}

	//Cargo la musica segun el objeto en el que estoy
	sprintf(aPath, "resources/%s/sample.wav", id);		//todos las animaciones deben tener un sample.wav con ese formato y en ese path
	sample = al_load_sample(aPath);
	if (!sample)
	{
		fprintf(stderr, "failed to create sample!\n");
	}

	
	for (unsigned int i = 0; i <= cantFrames; i++)
	{

		sprintf(aPath, path, i);		//voy cambiando de frame (i), copiando el string con el valor de frame en que estoy en aPath

		aniFrames[i] = al_load_bitmap(aPath);	//Voy cargando los bitmaps al arreglo variable
		if (!aniFrames[i])
		{
			fprintf(stderr, "failed to create ::'%s':: frame: %d\n", path, i);
		}
	}

	al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);		//comienzo a reproducir la musica

}


unsigned int animation::getCantFrames()
{
	return cantFrames;
}
float animation::getFrameSpeed()
{
	return frameSpeed;
}

ALLEGRO_BITMAP * animation::getScenario()
{
	return Scenario;
}

ALLEGRO_BITMAP** animation::getAniFrames()
{
	return aniFrames;
}

bool animation::isLookingRight()
{
	return lookingRight;
}

void animation::lookRight()
{
	lookingRight = true;
}

double animation::getPeriod()
{
	return period;
}


animation::~animation()
{
	al_destroy_bitmap(Scenario);

	for (unsigned int i = 0; i < cantFrames; i++)	//Destruyo todos los frames
	{
		al_destroy_bitmap(aniFrames[i]);
	}
	al_stop_samples();
	al_destroy_sample(sample);

	delete aniFrames[];		//Elimino el arreglo dinamico de bitmaps
}
