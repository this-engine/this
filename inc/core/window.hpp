// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "core.hpp"

/**
 *  TWindow
 *  @brief      Abstract class to represent a window
 *  @todo       Implements resolution checking
 */
class TWindow
{
protected:

    /** imageWidth @brief WIDTH  */ 
    size_t windowWidth = 640;

    /** imageHeight @brief HEIGHT  */ 
    size_t windowHeight = 480;

    /** Name @brief Name of the window  */ 
    TString windowTitle;


    /** 
     *  initWindow 
     *  @brief do the necessary sdl calls to have a valid window
     */ 
    virtual void initWindow() = 0;


    /** 
     *  loopWindow 
     *  @brief wait for
     */ 
    virtual void loopWindow() = 0;


    /** 
     *  quitWindow 
     *  @brief  react to SDL quit event
     *  @return error code
     */ 
    virtual int quitWindow() = 0;



public:
    /** TSDLWindow @brief constructor with enougth info   */ 
    TWindow(TString name, size_t x, size_t y);

    /** ~TSDLWindow @brief destructor, no need to do anything yet  */ 
    virtual ~TWindow() = default;

    /** 
     *  run() 
     *  @brief  opens a window and keep it open until stated otherwise
     */ 
    void run() 
    {
        initWindow();
        loopWindow();
        quitWindow();
    }

};