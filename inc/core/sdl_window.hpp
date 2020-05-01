// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "window.hpp"

// forward declaration
class SDL_Window;

/**
 *  TSDLWindow
 *  @brief      Simple wrapper around sdl
 */
class TSDLWindow : public TWindow
{
private:

    /** gameWindow @brief Main Game Window, will be initialized by this class    */ 
    SDL_Window* gameWindow = nullptr;

protected:

    /** 
     *  initWindow 
     *  @brief do the necessary sdl calls to have a valid window
     */ 
    virtual void initWindow();


    /** 
     *  loopWindow 
     *  @brief wait for
     */ 
    virtual void loopWindow();


    /** 
     *  quitWindow 
     *  @brief  react to SDL quit event
     *  @return error code
     */ 
    virtual int quitWindow();

public:

    /** simple constructor basedon parent */
    TSDLWindow(TString name, size_t x, size_t y) : TWindow(name, x, y){}

    /** window class override */
    virtual void run() override final
    {
        initWindow();
        loopWindow();
        quitWindow();
    }

};