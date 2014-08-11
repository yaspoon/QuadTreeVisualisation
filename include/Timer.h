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

#ifndef TIMER_H
#define TIMER_H

#include "SDL2/SDL.h"
#if defined _WIN32 || defined __CYGWIN__
    #undef main
#endif


class Timer
{

    private:

        //if the timer has started
        bool started;

        //if the timer is paused
        bool paused;

        //Ticks when the timer began
        int startTicks;

        //Ticks when the timer was paused
        int pausedTicks;


    public:

        Timer( void );

        virtual ~Timer( void );

        //Start the timer
        void start( void );

        //Stop the timer
        void stop( void );

        //Pause the timer
        void pause( void );

        //Unpause the timer
        void unpause( void );

        //get the current ticks
        Uint32 getTicks( void );

        //Check if the timer is paused
        bool isPaused( void );

        //Check if the timer has started
        bool isStarted( void );
};

#endif // TIMER_H
