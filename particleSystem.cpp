#include "particleSystem.h"
#include "Particle.h"
#include "mathLib3D.h"
#include <math.h>
#include <stdlib.h>
#include <time.h> 
#include <list>

using namespace std;

float gravity = 9.8f;
bool onQuad = true;

particleSystem::particleSystem()
{
    list<Particle> s;
    this->particles = s;
    this->origin = Point3D(0.0,1.0,0.0);
}

//implements particle explosion
void particleSystem::explode(Point3D eOrigin, int eMat)
{
    for (int i=0; i<40; i++) {
        Particle p;
        p.position = eOrigin; //explosion site
        p.direction.dx = ((float(rand())/float(RAND_MAX))*2.0f) - 1.0f;
        p.direction.dy = ((float(rand())/float(RAND_MAX))+0.3f);
        p.direction.dz = ((float(rand())/float(RAND_MAX))*2.0f) - 1.0f;
        p.speed = 2.0f;
        p.size = 0.8f;
        p.material = eMat;
        p.colour[0] = 0.7;
        p.colour[1] = 0.1;
        p.colour[2] = 0.1;
        particles.push_back(p);
    }
}

//updates each particle
void particleSystem::update(bool friction)
{
    //computes new position of each particle
    list<Particle>::iterator it;
    for (it = particles.begin(); it != particles.end(); it++){

        //update position
        it->position.px = it->position.px + (it->direction.dx * it->speed);
        it->position.py = it->position.py + (it->direction.dy * it->speed);
        it->position.pz = it->position.pz + (it->direction.dz * it->speed);

        //checks if particle is on floor
        if ((it->position.px <= 100.0) && (it->position.px >= -100.0) && (it->position.pz <= 100.0) && (it->position.pz >= -100.0))
            onQuad = true;
        else
            onQuad = false;

        //particle bounces if it collides with floor
        if (it->position.py < 1.0f && onQuad) {
            it->direction.dy = (-1.0f)*it->direction.dy;
            it->position.py = it->position.py + (it->direction.dy * it->speed);
            if (it->size == 5.0f) {
                it->age = 500; //particles exlplodes and dies
                explode(it->position, it->material);
            }
            else if (it->speed > 0.0f && friction == true) {
                it->speed -= 0.2f;
            }
            else if (it->speed <= 0.0f && friction == true)
                it->speed = 0.0f;
            
        }

        //implements gravity
        it->direction.dy = it->direction.dy - gravity/200.0f;
        
        //increases age of particle, if too old they die
        //particles get erased if they fall a certain distance off the floor
        it->age += 1;
        if (it->age >= 500 || it->position.py < -100) {
            it = particles.erase(it);
            --it;
        }
    }
}

//adds new particle to system
void particleSystem::add()
{
    Particle p;
    p.position = origin; //initial position is in the centre of floor
    p.direction.dx = ((float(rand())/float(RAND_MAX))*0.5f) - 0.25f;
    p.direction.dy = ((float(rand())/float(RAND_MAX))*1.5f) + 0.8f;
    p.direction.dz = ((float(rand())/float(RAND_MAX))*0.5f) - 0.25f;
    p.speed = 1.5f;
    particles.push_back(p);
}

//adds explosive particle to system
void particleSystem::addExplosive()
{
    Particle e;
    e.position = origin;
    e.direction.dx = ((float(rand())/float(RAND_MAX))*0.5f) - 0.25f;
    e.direction.dy = ((float(rand())/float(RAND_MAX))*1.5f) + 0.8f;
    e.direction.dz = ((float(rand())/float(RAND_MAX))*0.5f) - 0.25f;
    e.speed = 1.5f;
    e.colour[0] = 0.7;
    e.colour[1] = 0.1;
    e.colour[2] = 0.1;
    e.size = 5.0f;
    particles.push_back(e);
}