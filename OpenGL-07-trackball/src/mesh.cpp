#include "mesh.h"
#include "objloader.h"

Mesh* loadMesh(char* object )
{
	Mesh* pNewMesh = new Mesh();
	sp::ObjLoader loader = sp::ObjLoader();
	
	loader.load(object);
	size_t vertexBufferSize = loader.getVertCount();
	pNewMesh->vertexList.resize(vertexBufferSize*sizeof(vertex));
	const float* pos = loader.getPositions();
	const float* norm = loader.getNormals();
	const float* tex = loader.getTexCoords(1);
	int counterTex=0;
	int counterNorm=0;
	int counterPos=0;
	
	for (unsigned int i = 0; i < vertexBufferSize; i++){
		pNewMesh->vertexList[i].pos = vec3(pos[counterPos], pos[counterPos + 1], pos[counterPos + 2]);
		pNewMesh->vertexList[i].norm = vec3(norm[counterNorm], norm[counterNorm + 1], norm[counterNorm + 2]);
		pNewMesh->vertexList[i].tex = vec2(tex[counterTex], tex[counterTex + 1]);
		counterTex += 2;
		counterPos += 3;
		counterNorm += 3;
	}
	/*size_t indexBufferSize = loader.getIndexCount();
	pNewMesh->indexList.resize(indexBufferSize*sizeof(uint));
	for (int i = 0; i < indexBufferSize; i++){
		loader.get
	}*/


	return pNewMesh;
}

Mesh* loadBox(){
	float d = 0.5f;
	Mesh* pNewMesh = new Mesh();
	sp::ObjLoader loader = sp::ObjLoader();
	size_t vertexBufferSize = 6 * 6;
	pNewMesh->vertexList.resize(vertexBufferSize*sizeof(vertex));
	//front
	pNewMesh->vertexList[0].pos = vec3(d,d,d);
	pNewMesh->vertexList[1].pos = vec3(-d, d, d);
	pNewMesh->vertexList[2].pos = vec3(d, -d, d);

	pNewMesh->vertexList[3].pos = vec3(d, -d, d);
	pNewMesh->vertexList[4].pos = vec3(-d, d, d);
	pNewMesh->vertexList[5].pos = vec3(-d, -d, d);
	//back
	pNewMesh->vertexList[6].pos = vec3(d, d, -d);
	pNewMesh->vertexList[7].pos = vec3(-d, d, -d);
	pNewMesh->vertexList[8].pos = vec3(d, -d, -d);

	pNewMesh->vertexList[9].pos = vec3(d, -d, -d);
	pNewMesh->vertexList[10].pos = vec3(-d, d, -d);
	pNewMesh->vertexList[11].pos = vec3(-d, -d, -d);
	//top
	pNewMesh->vertexList[12].pos = vec3(d, d, d);
	pNewMesh->vertexList[13].pos = vec3(d, d, -d);
	pNewMesh->vertexList[14].pos = vec3(-d, d, -d);

	pNewMesh->vertexList[15].pos = vec3(d, d, d);
	pNewMesh->vertexList[16].pos = vec3(-d, d, -d);
	pNewMesh->vertexList[17].pos = vec3(-d, d, d);
	//bottom
	pNewMesh->vertexList[12].pos = vec3(d, -d, d);
	pNewMesh->vertexList[13].pos = vec3(d, -d, -d);
	pNewMesh->vertexList[14].pos = vec3(-d, -d, -d);

	pNewMesh->vertexList[15].pos = vec3(d, -d, d);
	pNewMesh->vertexList[16].pos = vec3(-d, -d, -d);
	pNewMesh->vertexList[17].pos = vec3(-d, -d, d);
	//left
	pNewMesh->vertexList[12].pos = vec3(-d, d, d);
	pNewMesh->vertexList[13].pos = vec3(-d, d, -d);
	pNewMesh->vertexList[14].pos = vec3(-d, -d, d);

	pNewMesh->vertexList[15].pos = vec3(-d, -d, d);
	pNewMesh->vertexList[16].pos = vec3(-d, d, -d);
	pNewMesh->vertexList[17].pos = vec3(-d, -d, -d);
	//right
	pNewMesh->vertexList[12].pos = vec3(d, d, d);
	pNewMesh->vertexList[13].pos = vec3(d, d, -d);
	pNewMesh->vertexList[14].pos = vec3(d, -d, d);

	pNewMesh->vertexList[15].pos = vec3(d, -d, d);
	pNewMesh->vertexList[16].pos = vec3(d, d, -d);
	pNewMesh->vertexList[17].pos = vec3(d, -d, -d);

	return pNewMesh;
}