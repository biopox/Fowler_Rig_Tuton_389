#pragma once
#include<Windows.h>

#include<stdlib.h>
#include<stdio.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string.h>
#include <map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

using namespace std;

class OBJ {
public:
	vector<float> vertices;
	vector<float> textures;
	vector<float> normals;
	vector<int> faces;			// vertices of each face
	vector<int> facesNormal;	// normals of each face
	vector<int> facesTexture;	// texture coordinates of each face
	bool verticesIncludeW;		// If .obj has v x y z [w]
	bool texturesIncludeW;		// If .obj has vt u v [w]
	int facesSize;				// Size of face e.g. triangles are 3
	int faceMode;				// v:		0
								// v, t:	1
								// v, t, n: 2
								// v, n:	3
	string name;				// Name of object
};

vector<OBJ> loadOBJ(string path, float scale);
void printOBJ(vector<OBJ> objects);

GLint TextureFromFile(const char *path, string directory);
