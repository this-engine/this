// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "logo.hpp"

TLogo::TLogo()
{
    float width  = 1.f;
    float height = 1.f;
    float depth  = 1.f;
    const QVector<GLfloat> A = {-width, -height, -depth, -1.f,-1.f,-1.f}; // 0
    const QVector<GLfloat> B = {-width, -height,  depth, -1.f,-1.f, 1.f}; // 1
    const QVector<GLfloat> C = { width, -height,  depth,  1.f,-1.f, 1.f}; // 2
    const QVector<GLfloat> D = { width, -height, -depth,  1.f,-1.f,-1.f}; // 3

    const QVector<GLfloat> E = {-width,  height, -depth, -1.f, 1.f,-1.f}; // 4
    const QVector<GLfloat> F = {-width,  height,  depth, -1.f, 1.f, 1.f}; // 5 
    const QVector<GLfloat> G = { width,  height,  depth,  1.f, 1.f, 1.f}; // 6
    const QVector<GLfloat> H = { width,  height, -depth,  1.f, 1.f,-1.f}; // 7

    Data << A << B << C << D << E << F << G<< H ;
    /*
    Indices = {
                {0,1,2},{2,3,0}, //ABC, CDA
                {1,0,4},{4,5,1}, //BAE, EFB
                {2,1,5},{5,6,2}, //CBF, FGC
                {3,2,6},{6,7,3}, //DCG, GHD
                {0,3,7},{7,4,0}, //ADH, HEA
                {4,7,6},{6,5,4}  //EHG, GFE
            };
    */

}