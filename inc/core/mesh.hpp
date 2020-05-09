// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_mesh_
#define _this_mesh_

#include <vector>
#include "core.hpp"

/**
 *  TVertex
 *  @brief      3d vertex for meshes
 *  @see        TMesh
 */
class TVertex : public TArchive
{
public:

    TVec3   coord;  /** coord @brief 3D coordinates     */ 
    TColor  color;  /** color @brief linear RGB color   */ 


};


/**
 *  TMesh
 *  @brief      representation of a mesh an function to create a buffer from it
 *  @see        TMesh
 */
class TMesh
{
protected:

    std::vector<TVertex> vertices;


};

#endif //_this_mesh_
