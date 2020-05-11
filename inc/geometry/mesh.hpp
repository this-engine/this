// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_mesh_
#define _this_mesh_

#include <vector>
#include "core.hpp"
#include "color.hpp"
/**
 *  TVertex
 *  @brief      3d vertex for meshes
 *  @see        TMesh
 */
struct TVertex : public TArchive
{
    TVec3   Coord;  /** coord @brief 3D coordinates     */ 
    TVec3   Norml;  /** norml @brief vertex's normal    */
    TVec2   UVcrd;  /** uvcrd @brief vertex's uv coord  */  
    TColor  Color;  /** color @brief linear RGB color   */

    TVertex(TVec3 coord, TVec3   norml, TVec2   uvcrd, TColor  color)
    : Coord(coord), Norml(norml), UVcrd(uvcrd), Color(color){}
};

/**
 *  TTriIndices
 *  @brief      indices for making a 
 *  @see        TMesh
 */
typedef struct TTriIndices { size_t idx[3]; } TTriIndices;

/**
 *  TMesh
 *  @brief      representation of a mesh an function to create a buffer from it
 *  @see        TMesh
 */
struct TMesh
{
    /**
     *  TMesh()
     *  @brief     Empty constructor, leaves everything empty
     */
    TMesh() {}

    /**
     *  TMesh()
     *  @brief     construct from vertices and indices 
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
