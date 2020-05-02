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

    // TWindow Overrides 
    virtual void initWindow() override final;
    virtual void loopWindow() override final;
    virtual int  quitWindow() override final;

public:

    /** simple constructor basedon parent */
    TSDLWindow(TString name, size_t x, size_t y) : TWindow(name, x, y){}

};