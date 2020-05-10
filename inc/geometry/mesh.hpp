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
struct TVertex : public TArchive
{
    TVec3   coord;  /** coord @brief 3D coordinates     */ 
    TVec3   norml;  /** norml @brief vertex's normal    */
    TVec2   uvcrd;  /** uvcrd @brief vertex's uv coord  */  
    TColor  color;  /** color @brief linear RGB color   */
};

/**
 *  TTriIndices
 *  @brief      indices for making a 
 *  @see        TMesh
 */
struct TTriIndices : public TArchive
{
    size_t indices[3];
};


/**
 *  TMesh
 *  @brief      representation of a mesh an function to create a buffer from it
 *  @see        TMesh
 */
struct TMesh
{

    /**
     *  Vertices
     *  @brief     all the vertices from that mesh and their relevant info
     */
    TMesh(std::initializer_list<TVertex> vertices, std::initializer_list<TTriIndices> indices);


    /**
     *  Vertices
     *  @brief     all the vertices from that mesh and their relevant info
     */
    std::vector<TVertex> Vertices;


    /**
     *  Indices
     *  @brief     indices to make triangular faces out of Vertices
     */
    std::vector<TTriIndices> Indices;



};

#endif //_this_mesh_
