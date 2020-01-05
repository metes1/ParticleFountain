#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Particle.h"
#include "mathLib3D.h"
#include <list>

class particleSystem
{
	public:
	std::list<Particle> particles;
    Point3D origin;
    particleSystem();
	void add();
	void update(bool friction);
	void addExplosive();
	void explode(Point3D eOrigin, int eMat);
};

#endif