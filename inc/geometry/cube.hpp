// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_cube_
#define _this_cube_

#include "mesh.hpp"

/**
 *  TCube
 *  @brief      a simple mesh of a cube
 *  @see        TMesh
 */
class TCube : public TMesh
{
    TCube(float width = 1.0f, float height = 1.0f, float depth = 1.0f, TColor color = TColor::SlateBlue);

};


#endif //_this_cube_
