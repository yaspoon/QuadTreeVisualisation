#ifndef PARTICLE_H
#define PARTICLE_H

#include "Common.h"
#include <SDL2/SDL.h>
#include <vector>


class Particle
{
        public:
                Particle(Rect rect, vec2 dir, float speed);
                virtual ~Particle();

                Rect getRect();
                vec2 getDir();
                float getSpeed();

                void setRect(Rect newRect);
                void setDir(vec2 newDir);
                void setSpeed(float newSpeed);

                void update(float dt);
                void draw(SDL_Renderer *renderer);

                float dotProduct( vec2 one, vec2 two );
                Projections projectOnto( vec2 axis );
                std::pair<float,float> minMaxProjectOnto(vec2 axis);
                Vertices getVertices();
                //std::vector<vec2> getAxes();
                //std::vector<vec2> getPerpAxes();
                Axes getNormedAxes();

                bool operator!=(Particle &other);
        protected:
        private:
                Rect rect;
                vec2 dir;
                float speed;

};

struct ParticleList
{
    Particle **particles;
    Uint32 count;
    Uint32 size;
};

#endif // PARTICLE_H
