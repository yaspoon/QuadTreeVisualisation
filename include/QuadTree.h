#ifndef QUADTREE_H
#define QUADTREE_H

#include <SDL2/SDL.h>
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
        void insert(Particle *particle);
        ParticleList retrieve(ParticleList objectList, Particle *particle);
        void draw(SDL_Renderer *renderer);

    protected:
    private:
        int level;
        std::vector<Particle*> objects;
        SDL_Rect bounds;
        QuadTree *nodes[4];
        const int MAX_OBJECTS = 2;
        const int MAX_LEVELS = 50;

        void split();
        int getIndex(Particle *particle);

        void drawRect(SDL_Renderer *renderer, SDL_Rect rect);
};
#endif // QUADTREE_H
