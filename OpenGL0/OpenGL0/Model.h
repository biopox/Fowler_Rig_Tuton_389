#pragma once
#include<Windows.h>

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
int loadOBJ(string path, float *triangles, float scale);
GLint TextureFromFile(const char *path, string directory);
