// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.


#include "mesh.hpp"

TMesh::TMesh(std::initializer_list<TVertex> vertices, std::initializer_list<TTriIndices> indices) : Vertices(vertices), Indices(indices)
{
    
}