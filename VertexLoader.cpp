#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string.h>

using namespace std;
/*bool loadOBJ(string path, float *triangles, float scale);

int main()
{
	float *triangles = NULL;
	loadOBJ("simpleCube.obj", triangles, 0.5);
	free(triangles);
	return 0;
}*/

bool loadOBJ(string path, float *triangles, float scale)
{
	// Open filestream
	string line;
	ifstream model(path);
	vector<float> vertices;
	vector<int> faces;

	// Check if file was successfully opened
	if (!model.is_open()) {
		cout << "Cannot open file";
		return false;
	}

	// Check if file is open
	while (getline(model, line)) {
		string header = line.substr(0, 2);
		// Found vertex
		if (header == "v ") {
			istringstream iss(line);
			vector<string> results((istream_iterator<string>(iss)), istream_iterator<string>());
			for (string s : results) {
				if (s == "v") continue;
				vertices.push_back(stof(s));
			}
		}
		// Found texture coordinate
		else if (header == "vt") {
		}
		// Found vertex normal
		else if (header == "vn") {
		}
		// Found face
		else if (header == "f ") {
			cout << "Found a face!\n";
			istringstream iss(line);
			vector<string> results((istream_iterator<string>(iss)), istream_iterator<string>());
			for (string s : results) {
				if (s == "f") continue;
				faces.push_back(stoi(s));
			}
		}
	}

	// Calculate the number of floats needed for vector array
	int size = faces.size() * 3;
	triangles = (float *) malloc(sizeof(float) * size);

	// Fill triangle array
	int index;
	int i = 0;
	for (int v : faces) {
		index = (v - 1) * 3;
		triangles[i] = vertices[index] * scale;
		triangles[i+1] = vertices[index+1] * scale;
		triangles[i+2] = vertices[index+2] * scale;
		i += 3;
	}

	/* Print triangles
	int tri;
	for (i = 0; i < size; i+= 3) {
		tri = (i / 3) + 1;
		cout << "Triangle " << tri << ": <" << triangles[i] << "," << triangles[i + 1] << "," << triangles[i + 2] << ">\n";
	} */

	model.close();
	return true;
}