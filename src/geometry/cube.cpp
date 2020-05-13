// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.


#include "cube.hpp"

TCube::TCube(float width, float height, float depth, TColor color)
{
    
    const TVertex A = TVertex({-width, -height, -depth},{-1.f,-1.f,-1.f},{0.f,0.f},{color.r(), color.g(), color.b()}); // 0
    const TVertex B = TVertex({-width, -height,  depth},{-1.f,-1.f, 1.f},{0.f,1.f},{color.r(), color.g(), color.b()}); // 1
    const TVertex C = TVertex({ width, -height,  depth},{ 1.f,-1.f, 1.f},{1.f,1.f},{color.r(), color.g(), color.b()}); // 2
    const TVertex D = TVertex({ width, -height, -depth},{ 1.f,-1.f,-1.f},{1.f,0.f},{color.r(), color.g(), color.b()}); // 3

    const TVertex E = TVertex({-width,  height, -depth},{-1.f, 1.f,-1.f},{0.f,0.f},{color.r(), color.g(), color.b()}); // 4
    const TVertex F = TVertex({-width,  height,  depth},{-1.f, 1.f, 1.f},{0.f,1.f},{color.r(), color.g(), color.b()}); // 5 
    const TVertex G = TVertex({ width,  height,  depth},{ 1.f, 1.f, 1.f},{1.f,1.f},{color.r(), color.g(), color.b()}); // 6
    const TVertex H = TVertex({ width,  height, -depth},{ 1.f, 1.f,-1.f},{1.f,0.f},{color.r(), color.g(), color.b()}); // 7

    Vertices = {A, B, C, D, E, F, G, H };
    Indices = {
                {0,1,2},{2,3,0}, //ABC, CDA
                {1,0,4},{4,5,1}, //BAE, EFB
                {2,1,5},{5,6,2}, //CBF, FGC
                {3,2,6},{6,7,3}, //DCG, GHD
                {0,3,7},{7,4,0}, //ADH, HEA
                {4,7,6},{6,5,4}  //EHG, GFE
            };
}