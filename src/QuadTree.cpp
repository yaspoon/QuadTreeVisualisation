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

#include "QuadTree.h"

QuadTree::QuadTree(int level, SDL_Rect bounds)
{
    this->level = level;
    this->bounds = bounds;
    for(int i = 0; i < 4; i++)
    {
        nodes[i] = NULL;
    }
}

QuadTree::~QuadTree()
{
    for(int i = 0; i < 4; i++)
    {
        delete nodes[i];
    }
}

void QuadTree::clear()
{
    objects.clear();
    if(nodes[0] != NULL)
    {
        for(int i = 0; i < 4; i++)
        {
                nodes[i]->clear();
                delete nodes[i];
                nodes[i] = NULL;
        }
    }
}

void QuadTree::insert(Particle *particle)
{
    if(nodes[0] != NULL)
    {
        int index = getIndex(particle);

        if(index != -1)
        {
            nodes[index]->insert(particle);
            return;
        }
    }

    objects.push_back(particle);

    if(objects.size() > MAX_OBJECTS && level < MAX_LEVELS)
    {
        if(nodes[0] == NULL)
        {
            split();
        }

        int i = 0;
        while(i < objects.size())
        {
            int index = getIndex(objects[i]);
            if(index != -1)
            {
                nodes[index]->insert(objects[i]);
                objects.erase(objects.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }
}

/*
*Retrieve will return a list of particles that occupy the same quadtree
*It doesn't return any of the objects on the way down while traversing the tree
*which is what you would normally want. So removing the else will have the
objects added on the way down
*/
ParticleList QuadTree::retrieve(ParticleList objectList, Particle *particle)
{
    int index = getIndex(particle);
    if(index != -1 && nodes[0] != NULL)
    {
        ParticleList tmp = nodes[index]->retrieve(objectList, particle);
        for(int i = 0; i < tmp.count; i++)
        {
            objectList.particles[objectList.count] = tmp.particles[i];
            objectList.count++;
        }
    }
    else
    {
        for(int i = 0; i < objects.size(); i++)
        {
            objectList.particles[objectList.count] = objects[i];
            objectList.count++;
        }
    }

    return objectList;
}

void QuadTree::draw(SDL_Renderer* renderer)
{
        drawRect(renderer, bounds);
        if(nodes[0] != NULL)
        {
            for(int i = 0; i < 4; i++)
            {
                nodes[i]->draw(renderer);
            }
        }
}

/*
*Subdivides this quadtree into 4 equal sections
*Creating 4 nodes 1 for each section
*/
void QuadTree::split()
{
    int subwidth = (int)(bounds.w / 2);
    int subheight = (int)(bounds.h / 2);
    int x = (int)bounds.x;
    int y = (int)bounds.y;

    SDL_Rect node1Bounds = {x, y, subwidth, subheight};
    nodes[0] = new QuadTree(level + 1, node1Bounds);

    SDL_Rect node2Bounds = {x + subwidth, y, subwidth, subheight};
    nodes[1] = new QuadTree(level + 1, node2Bounds);

    SDL_Rect node3Bounds = {x, y + subheight, subwidth, subheight};
    nodes[2] = new QuadTree(level + 1, node3Bounds);

    SDL_Rect node4Bounds = {x + subwidth, y + subheight, subwidth, subheight};
    nodes[3] = new QuadTree(level + 1, node4Bounds);
}

/*
*getIndex returns which childnode this particle could fit in
*if it can't fit exactly into any of the child nodes it returns -1
*so it should stay in the parent
*/
int QuadTree::getIndex(Particle *particle)
{
    int index = -1;
    Rect posDim = particle->getRect();
    int verticalMidpoint = bounds.x + bounds.w / 2;
    int horizontalMidpoint = bounds.y + bounds.h / 2;

    bool topQuadrant = posDim.y < horizontalMidpoint && posDim.y + posDim.h < horizontalMidpoint;
    bool bottomQuadrant = posDim.y > horizontalMidpoint && posDim.y + posDim.h > horizontalMidpoint;

    if(posDim.x < verticalMidpoint && posDim.x + posDim.w < verticalMidpoint)
    {
        if(topQuadrant)
        {
            index = 0;
        }
        else if(bottomQuadrant)
        {
            index = 2;
        }
    }
    else if(posDim.x > verticalMidpoint && posDim.x + posDim.w > verticalMidpoint)
    {
        if(topQuadrant)
        {
            index = 1;
        }
        else if(bottomQuadrant)
        {
            index = 3;
        }
    }

    return index;
}

void QuadTree::drawRect(SDL_Renderer *renderer, SDL_Rect rect)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    if(SDL_RenderFillRect(renderer, &rect) != 0)
    {
        std::cout << "Failed to draw rect" << std::endl;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    rect.x += 1;
    rect.y += 1;
    rect.w -= 2;
    rect.h -= 2;

    SDL_RenderFillRect(renderer, &rect);
}
