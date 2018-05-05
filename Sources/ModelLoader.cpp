#include <iostream>
#include <vector>
#include <glm/glm.hpp>
bool loadOBJ(std::string path, std::vector<glm::vec3> out_vertices, std::vector<glm::vec2> out_uvs, std::vector<glm::vec3> out_normals) {
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen(path.c_str, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec3 uv = temp_vertices[uvIndex - 1];
		out_uvs.push_back(vertex);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_vertices[normalIndex - 1];
		out_normals.push_back(vertex);
	}
}

/*#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main()
{
loadModel("cube.obj");
return 0;
}

/** Parses .obj file, adding vectors to the relevant vecs when found
* @param fileName	name of the .obj file
* @return			true if parsed correctly, false if there was an error
**
bool loadModel(std::string fileName) {
// Open filestream
std::string line;
std::ifstream model(fileName);

// Parse filestream
if (model.is_open()) {
while (getline(model, line)) {
std::string header = line.substr(0, 1);
// Found vertex
if (header == "v ") {
std::istringstream iss(line)
}
// Found texture coordinate
else if (header == "vt") {
}
// Found vertex normal
else if (header == "vn") {
}
// Found face
else if (header == "f") {
}
}
// Return false if not open
} else {
std::cout << "Cannot open file";
return false;
}
model.close();
return true;
}

glm::vec3 getVertices(std::string line, bool vertex)
{
std::istringstream iss(line);
std::string tok;
std::getline(iss, tok, ' ');	// Gets rid of 'v_' or 'f'
if (vertex) {
glm::vec3 vertex;
std::getline(iss, tok, ' ')
vertex.x = stof(tok, nullptr);
}

}
}*/