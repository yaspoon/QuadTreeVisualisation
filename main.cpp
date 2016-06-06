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

#include <SDL2/SDL.h>

#if defined _WIN32 || defined __CYGWIN__
    #undef main
#endif

#include <iostream>
#include "QuadTree.h"
#include <stdlib.h>
#include <time.h>
#include "Common.h"
#include "Particle.h"
#include "Timer.h"
#include <sstream>
#include "CollisionEngine.h"
#include <cmath>

void checkbounds(Particle *particle);
std::vector<Particle*> initialiseParticles();
//void InitialiseParticleArrays(vec2 *pos, vec2 *dirs, float *speed);
void InitialiseParticleArrays(float *pos, float *dirs);
void checkboundsArray(float *positions, float *directions, const int MAX_PARTICLES, const int screen_width, const int screen_height);
vec2 generateDirection();
void cleanupObjects(std::vector<Particle*> objects);
void drawRectangles(float *positions, SDL_Renderer *renderer);

const bool drawFrame = false;

int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) //Initialise SDL and check it worked
    {
        SDL_Window *mainWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(mainWindow != NULL)
        {
            SDL_Renderer *renderer;
            renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
            if( renderer != NULL)
            {
                SDL_Event event;
                bool quit = false;
                SDL_Rect bounds = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
                QuadTree quadTree(0, bounds);

                //std::vector<Particle*> objects;

                srand(time(NULL));
                float positions[MAX_PARTICLES * 2];
                float directions[MAX_PARTICLES * 2];
                //objects = initialiseParticles();
                InitialiseParticleArrays(positions, directions);

                Timer gameTimer;
                Timer frameTimer;
                gameTimer.start();
                frameTimer.start();
                Uint32 lastFrame = gameTimer.getTicks();
                Uint32 currentFrame = lastFrame;
                Uint32 frames = 0;

                CollisionEngine collisionEngine;
                //Main loop
                //while(!quit)
                for(int i = 0; i < MAX_FRAMES && !quit; i++)
                {
                    //Get frame times
                    lastFrame = currentFrame;
                    currentFrame = gameTimer.getTicks();

                    //EventLoop to handle input to quit------------------------------------------------------------
                    while(SDL_PollEvent(&event))
                    {
                        if(event.type == SDL_QUIT)
                        {
                            quit = true;
                        }
                        else if(event.key.keysym.scancode == SDL_SCANCODE_Q)
                        {
                            quit = true;
                        }
                    }
                    //End EventLoop---------------------------------------------------------------------------------

                    //update each object---------------------------------------------------------------------------
                    float frameTime = (currentFrame - lastFrame) / 1000.0f;
                    /*for(std::vector<Particle*>::iterator it = objects.begin(); it != objects.end(); ++it)
                    {
                        (*it)->update(frameTime);
                    }*/
                    for(int i = 0; i < MAX_PARTICLES; i+=2)
                    {
                        positions[i] += directions[i] * frameTime;
                        positions[i+1] += directions[i+1] * frameTime;
                    }
                    //End update-----------------------------------------------------------------------------------

                    //bounds checking------------------------------------------------------------------------------
                    /*for(std::vector<Particle*>::iterator it = objects.begin(); it != objects.end(); ++it)
                    {
                        checkbounds((*it));
                    }*/
                    checkboundsArray(positions, directions, MAX_PARTICLES, SCREEN_WIDTH, SCREEN_HEIGHT);
                    //End bounds checking--------------------------------------------------------------------------

                    //Generate quadtree-----------------------------------------------------------------------------
                    quadTree.clear(); //Clear old quadtree partitioning
                    /*for(std::vector<Particle*>::iterator it = objects.begin(); it != objects.end(); ++it) //For each particle add it to the quadtree
                    {
                        quadTree.insert(*it);
                    }*/
                    for(int i = 0; i < MAX_PARTICLES; i+=2)
                    {
                        quadTree.insert(&(positions[i]), i / 2); //We want the index to be the particle number
                    }
                    //End generate quadtree------------------------------------------------------------------------

                    //Collision handling-----------------------------------------------------------------------------
                    /*ParticleList colliderList;
                    colliderList.particles = new Particle*[MAX_PARTICLES];
                    colliderList.count = 0;
                    colliderList.size = MAX_PARTICLES;
                    for(std::vector<Particle*>::iterator it = objects.begin(); it != objects.end(); ++it)
                    {
                        colliderList = quadTree.retrieve(colliderList, *it);
                        collisionEngine.performCollisionDetection(*it, colliderList);
                        colliderList.count = 0;
                    }
                    delete[] colliderList.particles;
                    */
                    for(int i = 0; i < MAX_PARTICLES; i+=2)
                    {

                    }
                    //End Collision handling------------------------------------------------------------------------

                    //Draw frame------------------------------------------------------------------------------------
                    if(drawFrame)
                    {
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); //Reset drawing color to clear screen
                            SDL_RenderClear(renderer); //Clear screen of last frame
                            quadTree.draw(renderer); //Draw the quadtrees regions to the screen
                            /*for(std::vector<Particle*>::iterator it = objects.begin(); it != objects.end(); ++it) //Draw each particle to the screen
                            {
                                (*it)->draw(renderer);
                            }*/
                            drawRectangles(positions, renderer);
                            SDL_RenderPresent(renderer); //Copy the frame into gfx memory
                    }
                    //End Draw frame--------------------------------------------------------------------------------

                    //Frames per second calculation code----------------------------------------------------------
                    /*Uint32 currentFrameTime = frameTimer.getTicks();
                    if(currentFrameTime > 1000) //1 second has past
                    {
                        std::ostringstream convert;
                        convert << frames;
                        std::string newWindowTitle = WINDOW_TITLE;
                        newWindowTitle +=  " FPS:" + convert.str();
                        SDL_SetWindowTitle(mainWindow, newWindowTitle.c_str());

                        std::cout << "FPS:" << frames << std::endl;
                        frames = 0;
                        frameTimer.start();
                    }*/
                    frames++; //Increment frame counter so we can figure out the FPS
                    //End frames per second-------------------------------------------------------------------------
                }
                float currentFrameTime = frameTimer.getTicks() / 1000.0f;
                std::cout << "50000 frames in " << currentFrameTime << " seconds " << (float)frames / currentFrameTime << "FPS";

                //cleanupObjects(objects);
                SDL_DestroyRenderer(renderer);
            }
            else
            {
                std::cout << "ERROR: Failed to create renderer SDL_Error:" << SDL_GetError() << std::endl;
            }
            SDL_DestroyWindow(mainWindow); //Cleanup mainwindow before exiting
            SDL_Quit();
        }
        else
        {
            std::cout << "ERROR: Failed to create main window SDL_Error:" << SDL_GetError() << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR:Failed to initialise sdl SDL_Error:" << SDL_GetError() << std::endl;
    }
    return 0;
}

void drawRectangles(float *positions, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);

    for(int i = 0; i < MAX_PARTICLES; i+=2)
    {
        SDL_Rect tmp = {(int)positions[i], (int)positions[i+1], PARTICLE_WIDTH, PARTICLE_HEIGHT};

        if(SDL_RenderFillRect(renderer, &tmp) != 0)
        {
            std::cout << "Failed to draw rect" << std::endl;
        }
    }
}

/*
*CheckBounds. simple function to make sure the
*particles stay in the drawing area
*If the particle goes out the drawing area
*it's direction is reversed and it's placed at the edge
*it left from
*/
void checkbounds(Particle *particle)
{
    Rect rect = particle->getRect();
    vec2 dir = particle->getDir();

    if(rect.x < 0) //If the particle went out the left side
    {
        rect.x = 0;
        dir.x = -dir.x; //Send it in the opposite direction
    }
    else if(rect.x + rect.w > SCREEN_WIDTH) //If the particle went out the right side
    {
        rect.x = SCREEN_WIDTH - rect.w;
        dir.x = -dir.x;
    }
    else if(rect.y < 0) //If the particle went out the top
    {
        rect.y = 0;
        dir.y = -dir.y;
    }
    else if(rect.y +  rect.h > SCREEN_HEIGHT) //If the particle went out the bottom
    {
        rect.y = SCREEN_HEIGHT - rect.h;
        dir.y = -dir.y;
    }

    particle->setRect(rect);
    particle->setDir(dir);
}

/*
*InitialiseParticles returns a list of
*randomly generated particles for
*the system to use
*/
std::vector<Particle*> initialiseParticles()
{
    std::vector<Particle*> particles;

    for(int i = 0; i < MAX_PARTICLES; i++)
    {
        //Randomly generate the start point of the particle
        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;
        Rect rect = {x, y, PARTICLE_WIDTH, PARTICLE_HEIGHT}; //Create particle dimensions

        vec2 dir = generateDirection(); //Generate the direction it's traveling in initialy

        Particle *p = new Particle(rect, dir, PARTICLE_SPEED); //Create a new particle with the given dimensions, direction and speed

        particles.push_back(p);
    }

    return particles;
}

/*
*Randomly generates a direction vector
*so the each particle will move in a psuedo
*random direction
*/
vec2 generateDirection()
{
    vec2 dir;

    if((rand() % 100) < 50) //50% chance that the direction will be negative
    {
       if((rand() % 100) < 50) //50% chance both directions are negative
       {
            dir.x = (float)(-(rand() % 100) + 1);
            dir.y = (float)(-(rand() % 100) + 1);
       }
       else //Nope only one of the directions will be negative
       {
           if((rand() % 100) < 50) //50% chance the x direction is negative
           {
                dir.x = (float)(-(rand() % 100) + 1);
                dir.y = (float)((rand() % 100) + 1);
           }
           else //Y direction becomes negative
           {
                dir.x = (float)((rand() % 100) + 1);
                dir.y = (float)(-(rand() % 100) + 1);
           }
       }
    }
    else //Direction is positive
    {
        dir.x = (float)((rand() % 100) + 1);
        dir.y = (float)((rand() % 100) + 1);
    }

    float length = sqrt((dir.x * dir.x) + (dir.y * dir.y)); //Calculate the length of the direction vector so it can be normalised

    //Normalise the vector
    dir.x = dir.x / length;
    dir.y = dir.y / length;

    return dir;
}

void cleanupObjects(std::vector<Particle*> objects)
{
    for(std::vector<Particle*>::iterator it = objects.begin(); it != objects.end(); ++it)
    {
        delete *it;
    }
}

//void InitialiseParticleArrays(vec2 *pos, vec2 *dirs, float *speed)
void InitialiseParticleArrays(float *pos, float *dirs)
{
    for(int i = 0; i < MAX_PARTICLES; i+=2)
    {
        //Randomly generate the start point of the particle
        pos[i] = rand() % SCREEN_WIDTH; //x
        pos[i+1] = rand() % SCREEN_HEIGHT; //y

        vec2 dir = generateDirection(); //Generate the direction it's traveling in initialy

        dirs[i] = dir.x * PARTICLE_SPEED;
        dirs[i+1] = dir.y * PARTICLE_SPEED;

    }
}

void checkboundsArray(float *positions, float *directions, const int num_particles, const int screen_width, const int screen_height)
{
    for(int i = 0; i < num_particles; i+=2)
    {
        Rect rect;
        vec2 dir;

        rect.x = positions[i];
        rect.y = positions[i+1];
        rect.w = PARTICLE_WIDTH;
        rect.h = PARTICLE_HEIGHT;

        dir.x = directions[i];
        dir.y = directions[i+1];

        if(rect.x < 0) //If the particle went out the left side
        {
            rect.x = 0;
            dir.x = -dir.x; //Send it in the opposite direction
        }
        else if(rect.x + rect.w > SCREEN_WIDTH) //If the particle went out the right side
        {
            rect.x = SCREEN_WIDTH - rect.w;
            dir.x = -dir.x;
        }
        else if(rect.y < 0) //If the particle went out the top
        {
            rect.y = 0;
            dir.y = -dir.y;
        }
        else if(rect.y +  rect.h > SCREEN_HEIGHT) //If the particle went out the bottom
        {
            rect.y = SCREEN_HEIGHT - rect.h;
            dir.y = -dir.y;
        }

        positions[i] = rect.x;
        positions[i+1] = rect.y;

        directions[i] = dir.x;
        directions[i+1] = dir.y;

    }
}
