// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_vector_
#define _this_vector_

typedef float real;
typedef union { struct { real x, y, z; }; struct { real r, g, b; }; real row[3];        } vec3;
typedef union { struct { real x, y, z, w; }; struct { real r, g, b, a; }; real row[4];  } vec4;
typedef union { vec4 column[4]; real data[16]; real matrix[4][4];                       } mat4;
typedef union { struct { float x, y; }; struct { float u, v; }; float row[2];           } vec2;

#endif//_this_vector_

