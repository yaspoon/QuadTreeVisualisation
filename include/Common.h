/*
Copyright 2014 Brock York twunknown[replace with at]gmail.com

This file is part of QuadTreeTest.

QuadTreeTest is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

QuadTreeTest is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with QuadTreeTest.  If not, see <http://www.gnu.org/licenses/>.
*/

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
