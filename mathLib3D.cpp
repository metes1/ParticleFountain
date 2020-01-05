#include <math.h>
#include "mathLib3D.h"

// if point isn't given coordinates, the default is (0,0,0)
Point3D::Point3D()
{
    this->px = 0.0;
    this->py = 0.0;
    this->pz = 0.0;
}

Point3D::Point3D(float inx, float iny, float inz)
{
    this->px = inx;
    this->py = iny;
    this->pz = inz;
}

float Point3D::distanceTo(Point3D other)
{
    return sqrt (pow (other.px-this->px, 2) + pow (other.py-this->py, 2) + pow (other.pz-this->pz, 2));
}

// if vector isn't given coordinates, the default is (0,0,0)
Vec3D::Vec3D()
{
    this->dx = 0.0;
    this->dy = 0.0;
    this->dz = 0.0;
}

Vec3D::Vec3D(float inx, float iny, float inz)
{
    this->dx = inx;
    this->dy = iny;
    this->dz = inz;
}

float Vec3D::length()
{
    return sqrt (pow (this->dx, 2) + pow (this->dy, 2) + pow (this->dz, 2));
}

Vec3D Vec3D::normalize()
{   
    float nx = this->dx/length();
    float ny = this->dy/length();
    float nz = this->dz/length();
    Vec3D vecN(nx, ny, nz);
    return vecN;
}
    
Vec3D Vec3D::multiply(float scalar)
{
    Vec3D vecM(this->dx*scalar, this->dy*scalar, this->dz*scalar);
    return vecM;
}

Point3D Vec3D::movePoint(Point3D source)
{
    Point3D pNew(source.px + this->dx, source.py + this->dy, source.pz + this->dz);
    return pNew;
}

Vec3D Vec3D::createVector(Point3D p1, Point3D p2)
{
    Vec3D vecNew(p2.px-p1.px, p2.py-p1.py, p2.pz-p1.pz);
    return vecNew;
}
