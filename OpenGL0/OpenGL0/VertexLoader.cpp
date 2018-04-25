#include "model.h"

/* TODO
 * Add functionality for o line
 *  - usemtl
 *  - mtlib
 *  - polylines
*/

/*int main()
{
	vector<OBJ> models = loadOBJ("simpleCube.obj", 0.5);
	//printOBJ(models);
	float *arr = verticesToFloat(models[0]);
	free(arr);
	return 0;
}*/

// Returns size of the array allocated in triangles
vector<OBJ> loadOBJ(string path, float scale)
{
	// Open filestream
	string line;
	ifstream model(path);

	// variables
	OBJ objModel;
	objModel.texturesIncludeW = false;
	objModel.verticesIncludeW = false;
	int i;

	// Check if file was successfully opened
	if (!model.is_open()) {
		cout << "Cannot open file";
		exit(-1);
	}

	// Set up vector
	vector<OBJ> objects;
	bool firstObject = true;

	// Iterate line by line
	while (getline(model, line)) {
		// Get information for line header
		string header = line.substr(0, 2);

		// Break by spaces
		istringstream iss(line);
		vector<string> results((istream_iterator<string>(iss)), istream_iterator<string>());

		// Found vertex
		if (header == "v ") {
			i = 0;
			for (string s : results) {
				if (s == "v") continue;
				objModel.vertices.push_back(stof(s));
				if (i == 3) {
					objModel.verticesIncludeW = true;
				}
				i++;
			}
		}
		// Found texture coordinate
		else if (header == "vt") {
			i = 0;
			for (string s : results) {
				if (s == "vt") continue;
				objModel.textures.push_back(stof(s));
				if (i == 2) {
					objModel.texturesIncludeW = true;
				}
				i++;
			}
		}
		// Found vertex normal
		else if (header == "vn") {
			for (string s : results) {
				if (s == "vn") continue;
				objModel.normals.push_back(stof(s));
			}
		}
		/* Found face */
		else if (header == "f ") {
			i = 0;
			for (string s : results) {
				char *cstr = new char[s.length() + 1];
				strcpy(cstr, s.c_str());
				if (s == "f") continue;

				// No texture vertices
				if (s.find("//") != string::npos) {
					objModel.faceMode = 3;

					// Get vertex
					char *tok = strtok(cstr, "//");
					objModel.faces.push_back(strtol(tok, NULL, 10));
					
					// Get normal
					tok = strtok(NULL, "//");
					objModel.facesNormal.push_back(strtol(tok, NULL, 10));
				}
				// Normal progression
				else if (s.find("/") != string::npos) {
					if (count(s.begin(), s.end(), '/') > 1)
						objModel.faceMode = 2;
					else
						objModel.faceMode = 1;

					// Get vertex
					char *tok = strtok(cstr, "/");
					objModel.faces.push_back(strtol(tok, NULL, 10));

					// Get texture
					tok = strtok(NULL, "/");
					objModel.facesTexture.push_back(strtol(tok, NULL, 10));

					// Get normal (if exists)
					tok = strtok(NULL, "/");
					if (tok != NULL) {
						objModel.facesNormal.push_back(strtol(tok, NULL, 10));
					}
				}
				// Just vertices
				else {
					objModel.faceMode = 0;
					objModel.faces.push_back(stoi(s));
				}
				i++;
			}
			objModel.facesSize = i;
		}
		else if (header == "o ") {

			// Push previous object on stack if not first time
			if (!firstObject) {
				objects.push_back(objModel);
				OBJ newobj;
				objModel = newobj;
			}

			// Get name of new object
			for (string s : results) {
				if (s == "o") continue;
				objModel.name = s;
			}
			firstObject = false;
		}
	}
	// Push last object
	objects.push_back(objModel);
	model.close();
	return objects;
}

void printOBJ(vector<OBJ> objects) {
	
	for (OBJ obj : objects) {
		int i;

		// Print name
		cout << "###########\n" << obj.name << "\n######################\n\n";
		// Print header info
		obj.verticesIncludeW ? (cout << "Vertices include W\n") : (cout << "Vertices do not include W\n");
		obj.texturesIncludeW ? (cout << "Textures include W\n") : (cout << "Textures do not include W\n");
		cout << "Facemode: " << obj.faceMode << "\n";
		cout << "facesSize: " << obj.facesSize << "\n";

		// Set up increments correctly based on whether W is included in textures and vertices
		int vincr = obj.verticesIncludeW ? 4 : 3;
		int tincr = obj.texturesIncludeW ? 3 : 2;

		// Print vertices
		cout << "\nVertices:";
		i = 0;
		for (float f : obj.vertices) {
			if ((i % vincr) == 0) cout << "\nv" << (i / vincr) + 1 << ": ";
			cout << f << " ";
			i++;
		}

		// Print textures
		cout << "\n\nTextures:";
		i = 0;
		for (float f : obj.textures) {
			if ((i % tincr) == 0) cout << "\nvt" << (i / tincr) + 1 << ": ";
			cout << f << " ";
			i++;
		}

		// Print normals
		cout << "\n\nNormals:";
		i = 0;
		for (float f : obj.normals) {
			if ((i % 3) == 0) cout << "\nvn" << (i / 3) + 1 << ": ";
			cout << f << " ";
			i++;
		}

		// Print material information

		// Print faces
		cout << "\n\nFaces:";
		i = 0;
		for (int j : obj.faces) {
			if ((i % obj.facesSize) == 0) cout << "\nf" << (i / obj.facesSize) + 1 << ": ";
			cout << j << " ";
			i++;
		}

		// Print face textures
		cout << "\n\nFace textures:";
		i = 0;
		for (int j : obj.facesTexture) {
			if ((i % obj.facesSize) == 0) cout << "\nft" << (i / obj.facesSize) + 1 << ": ";
			cout << j << " ";
			i++;
		}

		// Print face normals
		cout << "\n\nFace normals:";
		i = 0;
		for (int j : obj.facesNormal) {
			if ((i % obj.facesSize) == 0) cout << "\nfn" << (i / obj.facesSize) + 1 << ": ";
			cout << j << " ";
			i++;
		}
	}
}

float *verticesToFloat(OBJ obj) {
	// Calculate size
	int arrSize = obj.vertices.size() * 3;
	float *vertices = new float[arrSize];
	int i = 0;
	int j = 0;

	int vincr = obj.verticesIncludeW ? 4 : 3;

	// Populate vertices
	for (int f : obj.faces) {
		for (j = 0; j < vincr; j++) {
			vertices[i+j] = obj.vertices[((f - 1) * vincr) + j];
			//cout << " " << vertices[i+j];
		}
		/*if (((i % (vincr * obj.facesSize)) == ((vincr * obj.facesSize) - vincr)))
			cout << "\n";
		else
			cout << ", ";
		*/

		i += vincr;
	}

	return vertices;
}
