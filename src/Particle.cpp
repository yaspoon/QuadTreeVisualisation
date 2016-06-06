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

#include "Particle.h"
#include <iostream>

Particle::Particle(Rect rect, vec2 dir, float speed)
{
        this->rect = rect;
        this->dir = dir;
        this->speed = speed;
}

Particle::~Particle()
{
        //dtor
}

Rect Particle::getRect()
{
        return rect;
}

vec2 Particle::getDir()
{
        return dir;
}

float Particle::getSpeed()
{
        return speed;
}

void Particle::setRect(Rect newRect)
{
        rect = newRect;
}

void Particle::setDir(vec2 newDir)
{
        dir = newDir;
}

void Particle::setSpeed(float newSpeed)
{
        speed = newSpeed;
}

void Particle::update(float dt)
{
        rect.x += (dir.x * speed) * dt;
        rect.y += (dir.y * speed) * dt;
}

/*void Particle::draw(SDL_Renderer *renderer)
{
     SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);

     SDL_Rect tmp = {(int)rect.x, (int)rect.y, rect.w, rect.h};

    if(SDL_RenderFillRect(renderer, &tmp) != 0)
    {
        std::cout << "Failed to draw rect" << std::endl;
    }
}*/

/*
Creates the vertices of the box in the order
top left
topright
bottom right
bottom left

since in sdl (0,0) is the top left of the window
so why not start in the top left then
*/
Vertices Particle::getVertices()
{
    Vertices vertices;

    vec2 topleft = {rect.x, rect.y};
    vertices.vertex[0] = topleft;

    vec2 topRight = {rect.x + rect.w, rect.y};
    vertices.vertex[1] = topRight;

    vec2 bottomRight = {rect.x + rect.w, rect.y + rect.h};
    vertices.vertex[2] = bottomRight;

    vec2 bottomLeft = {rect.x, rect.y + rect.h};
    vertices.vertex[3] = bottomLeft;

    return vertices;
}

/*std::vector<vec2> Particle::getAxes()
{
    std::vector<vec2> vertices = getVertices();
    std::vector<vec2> axes;

    for(std::vector<vec2>::iterator it = vertices.begin(); it != vertices.end(); ++it)
    {
        vec2 first = *it;
        vec2 second;

        std::vector<vec2>::iterator itDup = it;

        if(++itDup == vertices.end())
        {
            second = *(vertices.begin());
        }
        else
        {
            second = *itDup;
        }

        vec2 axis;
        axis.x = second.x - first.x;
        axis.y = second.y - first.y;

        axes.push_back(axis);

    }

    return axes;
}

std::vector<vec2> Particle::getPerpAxes()
{
    std::vector<vec2> axes = getAxes();

    for(std::vector<vec2>::iterator it = axes.begin(); it != axes.end(); ++it)
    {
        vec2 axis = *it;

        float tmp = axis.x;
        axis.x = -(axis.y);
        axis.y = tmp;

        *it = axis;
    }

    return axes;
}*/

Axes Particle::getNormedAxes()
{
    /*std::vector<vec2> axes = getPerpAxes();

    for(std::vector<vec2>::iterator it = axes.begin(); it != axes.end(); ++it)
    {
        vec2 axis = *it;

        float length = sqrt((axis.x * axis.x) + (axis.y * axis.y));

        axis.x = axis.x / length;
        axis.y = axis.y / length;

        *it = axis;
    }*/

    Axes axes;
    axes.axis[0] = {1, 0};
    axes.axis[1] = {0, 1};

    return axes;
}

Projections Particle::projectOnto( vec2 axis )
{
    Projections projections;
    Vertices vertices = getVertices();

    for(int i = 0; i < 4; i++) //project each vertex onto the given axis
    {
        vec2 vertex = vertices.vertex[i];
        float dp = dotProduct(vertex, axis);//vertex.x * axis.x) + (vertex.y * axis.y); //Calc dot product of vertex and axis to project it onto the axis
        projections.projection[i] = dp;
    }

    return projections;
}

std::pair<float,float> Particle::minMaxProjectOnto(vec2 axis)
{
    Projections projectedPoints = projectOnto(axis);
    float min = projectedPoints.projection[0];
    float max = projectedPoints.projection[0];
    for(int i = 0; i < 4; i++)
    {
        if(projectedPoints.projection[i] < min)
        {
            min = projectedPoints.projection[i];
        }
        if(projectedPoints.projection[i] > max)
        {
            max = projectedPoints.projection[i];
        }
    }
    std::pair<float,float> retval;
    retval.first = min;
    retval.second = max;
    return retval;
}

float Particle::dotProduct( vec2 one, vec2 two )
{
    return (one.x * two.x) + (one.y * two.y );
}

bool Particle::operator!=(Particle &other)
{
    bool retval = true;

    bool samerect = other.rect.x == rect.x && other.rect.y == rect.y && other.rect.w == rect.w && other.rect.h == rect.h;
    bool samedir = other.dir.x == dir.x && other.dir.y == dir.y;

    if(samerect && other.speed == speed && samedir)
    {
        retval = false;
    }
    return retval;
}
