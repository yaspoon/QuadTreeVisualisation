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

#ifndef PARTICLE_H
#define PARTICLE_H

#include "Common.h"
#include <SDL2/SDL.h>
#if defined _WIN32 || defined __CYGWIN__
    #undef main
#endif
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
    std::pair<float, float> **particles;
    Uint32 count;
    Uint32 size;
};

#endif // PARTICLE_H
