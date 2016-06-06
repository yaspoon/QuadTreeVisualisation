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

#ifndef QUADTREE_H
#define QUADTREE_H

#include <SDL2/SDL.h>
#if defined _WIN32 || defined __CYGWIN__
    #undef main
#endif
#include <vector>
#include <memory>
#include <iostream>
#include "Particle.h"

class QuadTree
{
    public:
        QuadTree(int level, SDL_Rect bounds);
        virtual ~QuadTree();
        void clear();
        void insert(float *position, int index);
        //ParticleList retrieve(ParticleList objectList, Particle *particle);
        void draw(SDL_Renderer *renderer);

    protected:
    private:
        int level;
        std::vector<std::pair<int, std::pair<float, float> > > objects;
        SDL_Rect bounds;
        QuadTree *nodes[4];
        const int MAX_OBJECTS = 2;
        const int MAX_LEVELS = 500;

        void split();
        int getIndex(float *position);

        void drawRect(SDL_Renderer *renderer, SDL_Rect rect);
};
#endif // QUADTREE_H
