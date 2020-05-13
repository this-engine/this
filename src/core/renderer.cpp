// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "renderer.hpp"
#include <stdio.h>
#include <omp.h>
#include <assert.h>

TRenderer::TRenderer(TWindow *window)
{
    assert(window != nullptr);
    RenderThreadIsRunning = false;
    StopRenderThread = false;
}



void TRenderer::renderFrame()
{
}