#ifndef MATHLIB_3D_H
#define MATHLIB_3D_H

class Point3D {
public:
    Point3D();
    Point3D(float inx, float iny, float inz);
    float px;
    float py;
    float pz;

    float distanceTo(Point3D other);
};

class Vec3D {
public:
    Vec3D();
    Vec3D(float inx, float iny, float inz);
    float dx;
    float dy;
    float dz;

    float length();
    Vec3D normalize();
    Vec3D multiply(float scalar);
    Point3D movePoint(Point3D source);

    static Vec3D createVector(Point3D p1, Point3D p2);
};

#endif
