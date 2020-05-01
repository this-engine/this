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

public:
    /** TSDLWindow @brief constructor with enougth info   */ 
    TWindow(TString name, size_t x, size_t y);

    /** 
     *  run() 
     *  @brief   start the window 
     *  @note    pure virtual method to force subclasses implements it
     *  @todo    make compatible with threading
     */ 
    virtual void run() =0;

};