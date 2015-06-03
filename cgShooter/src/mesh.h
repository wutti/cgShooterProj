#pragma once

#include "cgmath.h"
#include "GL/glew.h"

struct Material
{
	vec4	ambient;
	vec4	diffuse;
	vec4	specular;
	float	shininess;
};

// vertex/index/mesh definitions
struct vertex { vec3 pos; vec3 norm; vec2 tex; };
struct Mesh
{
	GLuint				vertexBuffer;
	GLuint				indexBuffer;
	std::vector<vertex>	vertexList;
	std::vector<uint>	indexList;
};

Mesh* loadMesh(char* );
Mesh* loadBox();