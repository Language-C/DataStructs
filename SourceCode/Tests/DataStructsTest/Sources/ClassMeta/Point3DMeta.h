#pragma once
#include <stdlib.h>

extern "C"
{
#include <ClassOriented/ClassOriented.h>
#include <ClassMeta.h>
}

struct Point3D
{
    Point3D(int xyz = 0) : X(xyz), Y(xyz), Z(xyz) { }
    Point3D(int x, int yz) : X(x), Y(yz), Z(yz) { }
    Point3D(int x, int y, int z) : X(x), Y(y), Z(z) { }
    int X, Y, Z;
};

struct Point3DParams {
    int x, y, z;
};

static CopyConstructor(Point3D, dst, src)
{
    if (src) {
        *((Point3D*)(dst)) = *((Point3D*)(src));
    }
}

static Constructor(Point3D, self)
{
    ((Point3D*)self)->X = 0;
    ((Point3D*)self)->Y = 0;
    ((Point3D*)self)->Z = 0;
}

static ParamConstructor(Point3D, self, params)
{
    ((Point3D*)self)->X = ((Point3DParams*)params)->x;
    ((Point3D*)self)->Y = ((Point3DParams*)params)->y;
    ((Point3D*)self)->Z = ((Point3DParams*)params)->z;
}

static Destructor(Point3D, self)
{
    ((Point3D*)self)->X = 0;
    ((Point3D*)self)->Y = 0;
    ((Point3D*)self)->Z = 0;
}

static ClassMeta* Point3DConfig()
{
    static ClassMeta Ponit3DMeta = MakeClassMeta(Point3D);
    return &Ponit3DMeta;
}
