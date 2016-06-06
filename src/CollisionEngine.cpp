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

#include "CollisionEngine.h"
#include <vector>

CollisionEngine::CollisionEngine()
{
    //ctor
}

CollisionEngine::~CollisionEngine()
{
    //dtor
}

/*void CollisionEngine::performCollisionDetection(Particle *particle, ParticleList colliders)
{
    for(int i = 0; i < colliders.count; i++)
    {
        Particle *particle2 = colliders.particles[i];
        if(particle != particle2)
        {
            CollisionResult result = testForCollision(*particle, *particle2);
            if(result.isColliding == true)
            {
                Rect tmp = particle->getRect();
                Rect tmp2 = particle2->getRect();

                vec2 p1direction = particle->getDir();
                vec2 p2direction = particle2->getDir();

                float xdistance = result.minAxis.x * (result.minDistance / 2);
                xdistance = (xdistance < 1.0f) ? 1.0f : xdistance;
                float ydistance = result.minAxis.y * (result.minDistance / 2);
                ydistance = (ydistance < 1.0f) ? 1.0f : ydistance;

                if(result.minAxis.x != 0)
                {
                    tmp.x -= xdistance;
                    tmp2.x += xdistance;

                    if(tmp.x < tmp2.x)
                    {
                        if(p1direction.x > 0 && p2direction.x < 0)
                        {
                            p1direction.x = -p1direction.x;
                            p2direction.x = -p2direction.x;
                        }
                    }
                    else
                    {
                        if(p1direction.x < 0 && p2direction.x > 0)
                        {
                            p1direction.x = -p1direction.x;
                            p2direction.x = -p2direction.x;
                        }
                    }
                }
                else if(result.minAxis.y != 0)
                {
                    tmp.y -= ydistance;
                    tmp2.y += ydistance;

                    if(tmp.y < tmp2.y)
                    {
                        if(p1direction.y > 0 && p2direction.y < 0)
                        {
                            p1direction.y = -p1direction.y;
                            p2direction.y = -p2direction.y;
                        }
                    }
                    else
                    {
                        if(p1direction.y < 0 && p2direction.y > 0)
                        {
                            p1direction.y = -p1direction.y;
                            p2direction.y = -p2direction.y;
                        }
                    }
                }
                particle->setRect(tmp);
                particle2->setRect(tmp2);
                particle->setDir(p1direction);
                particle2->setDir(p2direction);
            }
        }
    }
}*/

void CollisionEngine::performCollisionDetection(float *positions, std::vector<int> indexs)
{

}

CollisionResult CollisionEngine::testForCollision(Particle collider1, Particle collider2)
{
    CollisionResult retval = {true, {0, 0}, 0};
    retval.minDistance = 1000.0f;

    Axes collider1Axes = collider1.getNormedAxes();
    int i = 0;
    while(retval.isColliding && i < 2)
    {
        /*Project each vertex of the two colliders onto the axis and then
         *check them for overlap*/
        std::pair<float,float> collider1Points = collider1.minMaxProjectOnto(collider1Axes.axis[i]);
        std::pair<float,float> collider2Points = collider2.minMaxProjectOnto(collider1Axes.axis[i]);
        CollisionResult overlaping = checkForOverlap(collider1Points, collider2Points);
        if(!overlaping.isColliding) //If there is no overlap then stop
        {
            retval.isColliding = false;
        }
        else //Yes they're overlaping on this axis
        {
            //Check if this is the smallest distance we have found so far
            if(fabs(overlaping.minDistance) < fabs(retval.minDistance))
            {
                retval.minDistance = overlaping.minDistance;
                retval.minAxis = collider1Axes.axis[i];
            }
        }

        i++;;
    }

    //If they weren't overlaping on the first set of axes then no point testing this axes
    if(retval.isColliding)
    {
        Axes collider2Axes = collider2.getNormedAxes();
        i = 0;
        while(retval.isColliding && i < 2)
        {
            /*Project each of the colliders vertices onto the axes
             *of collider2*/
             std::pair<float,float> collider1Points = collider1.minMaxProjectOnto(collider2Axes.axis[i]);
             std::pair<float,float> collider2Points = collider2.minMaxProjectOnto(collider2Axes.axis[i]);
            CollisionResult overlaping = checkForOverlap(collider1Points, collider2Points);
            if(!overlaping.isColliding) //if not overlaping then stop
            {
                retval.isColliding = false;
            }
            else //There is overlap
            {
                //Check if this is the smallest distance so far
                if(fabs(overlaping.minDistance) < fabs(retval.minDistance))
                {
                    retval.minDistance = overlaping.minDistance;
                    retval.minAxis = collider2Axes.axis[i];
                }
            }
            i++;
        }
    }

    return retval;
}

CollisionResult CollisionEngine::checkForOverlap(std::pair<float,float> collider1Points, std::pair<float,float> collider2Points)
{
    CollisionResult retval = {false, {0,0}, 0};

    if(isContained(collider1Points, collider2Points)) //Collider1 is completely contained by collider2
    {
        retval.minDistance = calculatePushOut(collider1Points, collider2Points);
        retval.isColliding = true;
    }
    else if(isContained(collider2Points, collider1Points)) //Collider2 is completely contained by collider1
    {
        retval.minDistance = calculatePushOut(collider2Points, collider1Points);
        retval.isColliding = true;
    }
    else if(isInside(collider1Points.first, collider2Points)) //Collider1s min point is inside collider2 so it's on the right
    {

        retval.minDistance = collider2Points.second - collider1Points.first;
        retval.isColliding = true;
    }
    else if(isInside(collider1Points.second, collider2Points)) //Collider1s max point is inside collider2 so it's on the left
    {
        retval.minDistance = collider2Points.first - collider1Points.second;
        retval.isColliding = true;
    }
    /*else they are not overlaping at all*/

    return retval;
}

/*
 *Tests if point is between (inside) the other two points
 */
bool CollisionEngine::isInside(float point, std::pair<float,float> points)
{
    bool retval = false;

    if(points.first < point && point < points.second)
    {
        retval = true;
    }
    else if(points.second < point && point < points.first) //Incase they're all negative
    {
        retval = true;
    }

    return retval;
}

bool CollisionEngine::isContained(std::pair<float,float> collider1Points, std::pair<float,float> collider2Points)
{
    bool retval = false;

    if((isInside(collider1Points.first, collider2Points) || collider1Points.first == collider2Points.first) && (isInside(collider1Points.second, collider2Points) || collider1Points.second == collider2Points.second))
    {
        retval = true;
    }

    return retval;
}

float CollisionEngine::distanceBetween(float firstPoint, float secondPoint)
{
    float retval = 0.0f;

    if(firstPoint < secondPoint)
    {
        retval = secondPoint - firstPoint;
    }
    else
    {
        retval = firstPoint - secondPoint;
    }

    return retval;
}

/*When one object is contained within the other, this calculates how far they must move to push out*/
float CollisionEngine::calculatePushOut(std::pair<float,float> contained, std::pair<float,float> container)
{
    float retval = 0.0f;
    if(distanceBetween(contained.first, container.first) < distanceBetween(contained.second, container.second))
    {
        retval = (container.first - contained.first) - (contained.second - contained.first);
    }
    else
    {
        retval = (container.second - contained.second) + (contained.second - contained.first);
    }

    return retval;
}
