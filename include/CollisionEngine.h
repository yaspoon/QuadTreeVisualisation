#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H

#include "Common.h"
#include "Particle.h"
#include <utility>

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
