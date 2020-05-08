// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "window.hpp" 
#include "renderer.hpp" 
 
TWindow::TWindow(TString name, size_t x, size_t y)  :   windowWidth(x), windowHeight(y), windowTitle(name) ,Renderer(nullptr)
{

}

TWindow::~TWindow()
{
    if(Renderer)
        Renderer.reset(nullptr);
}

void TWindow::init()
{
    if(Renderer)
    {
        Renderer->init();
    }
}


void TWindow::deleteWindow()
{
    Renderer.reset(nullptr);
}