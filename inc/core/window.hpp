// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_window_
#define _this_window_

#include "core.hpp"


// forward declaration
class TRenderer;


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
     *  renderer 
     *  @brief  the class that takes care of producing pixels inside your window
     */ 
    TRenderer* renderer;

public:
    /** TSDLWindow @brief constructor with enougth info   */ 
    TWindow(TString name, size_t x, size_t y);

    /** ~TSDLWindow @brief destructor, no need to do anything yet  */ 
    virtual ~TWindow() = default;

    /** 
     *  shouldClose 
     *  @brief      should return true if you want that window to close
     *  @returns    true if should close, false otherwise 
     */ 
    virtual bool shouldClose() = 0;

    /** 
     *  refreshEvent 
     *  @brief      implement here any function that needs to be called
     *              from main thread.
     *  @note       this will be run from main thread
     */ 
    virtual void refreshEvent() {}
  


};

#endif // _this_window_