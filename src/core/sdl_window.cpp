// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include "sdl_window.hpp"


/** 
 *  filterEvents 
 *  @brief  check if an even correspond to quit to clear window
 *  @note   c style function to avoid useless includes in .hpp (function is stat)
 */ 
int filterEvents(void* userdata, SDL_Event* event)
{
    /* This quit event signals the closing of the window */
    if (event->type == SDL_QUIT)  
    {
        return 1;
    }
    return 0;
}

void TSDLWindow::initWindow()
{
    /* Initialize the SDL library (starts the event loop) */
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr,
                "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /* Clean up on exit, exit on window close and interrupt */
    atexit(SDL_Quit);
   
    // this does not work :
    //SDL_SetEventFilter(&filterEvents);

    gameWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    if(!gameWindow) 
    { 
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }


}

void TSDLWindow::loopWindow()
{

    SDL_Event event;

    while ( SDL_WaitEvent(&event) >= 0 ) 
    {
        switch (event.type) 
        { 
            case SDL_QUIT: 
            {
                printf("Quit requested, quitting.\n");
                exit(0);
            }
            break;
            default:
            {
                break;
            }
        }
    }
}



int TSDLWindow::quitWindow()
{
    // nothing to do here
    return 0;
}