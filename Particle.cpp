#include <math.h>
#include <time.h> 
#include "mathLib3D.h"
#include "Particle.h"
#include <stdlib.h>

//defines a particle object
Particle::Particle()
{
	this->position = Point3D();
	this->direction = Vec3D();
	this->speed = 0.0;
	this->angle = Vec3D(float(rand())/float(RAND_MAX), float(rand())/float(RAND_MAX), float(rand())/float(RAND_MAX));
	this->size = ((rand() % 5) + 3)/5.0;
	this->colour[0] = (float(rand())/float(RAND_MAX)*0.4)+0.4;
    this->colour[1] = (float(rand())/float(RAND_MAX))+0.4;
    this->colour[2] = (float(rand())/float(RAND_MAX))+0.6;
	this->material = (rand() % 3);
    this->age = (rand() % 100) + 1;
}
