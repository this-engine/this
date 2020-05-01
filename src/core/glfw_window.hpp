// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "window.hpp"

/**
 *  TSDLWindow
 *  @brief      Simple wrapper around sdl
 *  @todo       Implements resolution checking
 */
class TGLFWWindow  : public TWindow
{
public:
    
    TGLFWWindow(TString name, size_t x, size_t y) : TWindow(name, x,y){}
};
