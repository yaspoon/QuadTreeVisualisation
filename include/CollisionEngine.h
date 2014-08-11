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

#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H

#include "Common.h"
#include "Particle.h"
#include <utility>
#include <cmath>

class CollisionEngine
{
    public:
        CollisionEngine();
        virtual ~CollisionEngine();
        void performCollisionDetection(Particle *particle, ParticleList colliders);
    protected:
    private:
        CollisionResult testForCollision(Particle collider1, Particle collider2);
        CollisionResult checkForOverlap(std::pair<float,float> collider1Points, std::pair<float,float> collider2Points);
        bool isInside(float point, std::pair<float,float> points);
        bool isContained(std::pair<float,float> collider1Points, std::pair<float,float> collider2Points);
        float distanceBetween(float firstPoint, float secondPoint);
        float calculatePushOut(std::pair<float,float> contained, std::pair<float,float> container);
};

#endif // COLLISIONENGINE_H
