#pragma once
#include<Windows.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>



using namespace std;

GLint TextureFromFile(const char *path, string directory);
