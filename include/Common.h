#ifndef COMMON_H
#define COMMON_H

struct vec2
{
    float x;
    float y;
};

struct Rect
{
    float x;
    float y;
    int w;
    int h;
};

struct CollisionResult
{
    bool isColliding;
    vec2 minAxis;
    float minDistance;
};

struct Axes
{
    vec2 axis[2];
};

struct Vertices
{
    vec2 vertex[4];
};

struct Projections
{
    float projection[4];
};

#endif // COMMON_H
