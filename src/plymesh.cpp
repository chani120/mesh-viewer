#include "plymesh.h"
#include "fstream"
#include <sstream>

using namespace std;
using namespace glm;

namespace agl {

    PLYMesh::PLYMesh(const std::string& filename) {
        load(filename);
    }

    PLYMesh::PLYMesh() {
    }

    void PLYMesh::init() {
        assert(_positions.size() != 0);
        initBuffers(&_faces, &_positions, &_normals, &_uvCoords);
    }

    PLYMesh::~PLYMesh() {
    }

    bool PLYMesh::load(const std::string& filename) {

        if (_positions.size() != 0) {
            std::cout << "WARNING: Cannot load different files with the same PLY mesh\n";
            return false;
        }

        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        std::string line;
        if (!std::getline(file, line) || line != "ply") {
            return false;
        }

        int numVertices = 0;
        int faces_var = 0; 
        while (std::getline(file, line) && line != "end_header") {
            std::istringstream iss(line);
            std::string keyword;
            iss >> keyword;

            if (keyword == "element") {
                std::string elementType;
                int count;
                iss >> elementType >> count;

                if (elementType == "vertex") {
                    numVertices = count;
                }
                else if (elementType == "face") {
                    faces_var = count;
                }
            }
        }

        for (int i = 0; i < numVertices; i++) {
            std::getline(file, line);
            std::istringstream iss(line);
            float x_var, y_var, z_var, x_normal, y_normal, z_normal;
            iss >> x_var >> y_var >> z_var >> x_normal >> y_normal >> z_normal;
            _positions.push_back(x_var);
            _positions.push_back(y_var);
            _positions.push_back(z_var);
            _normals.push_back(x_normal);
            _normals.push_back(y_normal);
            _normals.push_back(z_normal);
            float uCoords, vCoords;
            iss >> uCoords >> vCoords;
            _uvCoords.push_back(uCoords);
            _uvCoords.push_back(vCoords);
        }

        for (int i = 0; i < faces_var; i++) {
            int count, v1, v2, v3;
            file >> count >> v1 >> v2 >> v3;
            _faces.push_back(v1);
            _faces.push_back(v2);
            _faces.push_back(v3);
            for (int j = 0; j < count - 3; j++) {
                int vi;
                file >> vi;
                _faces.push_back(v1 - 1);   
                _faces.push_back(vi - 1);
                _faces.push_back(vi - 1);
            }
        }

        if (numVertices == 0 || faces_var == 0) {
            return false;
        }

        return true;
    }

    glm::vec3 PLYMesh::minBounds() const {
        glm::vec3 minBound(_positions[0], _positions[1], _positions[2]);

        for (int i = 0; i < _positions.size(); i += 3) {
            glm::vec3 vertex(_positions[i], _positions[i + 1], _positions[i + 2]);
            if (vertex.x < minBound.x) {
                minBound.x = vertex.x;
            }
            if (vertex.y < minBound.y) {
                minBound.y = vertex.y;
            }
            if (vertex.z < minBound.z) {
                minBound.z = vertex.z;
            }
        }

        return minBound;
    }

    glm::vec3 PLYMesh::maxBounds() const {

        glm::vec3 maxBound(_positions[0], _positions[1], _positions[2]);

        for (int i = 0; i < _positions.size(); i += 3) {
            glm::vec3 vertex(_positions[i], _positions[i + 1], _positions[i + 2]);
            if (vertex.x > maxBound.x) {
                maxBound.x = vertex.x;
            }
            if (vertex.y > maxBound.y) {
                maxBound.y = vertex.y;
            }
            if (vertex.z > maxBound.z) {
                maxBound.z = vertex.z;
            }
        }

        return maxBound;
    }

    int PLYMesh::numVertices() const {
        return _positions.size() / 3;
    }

    int PLYMesh::numTriangles() const {
        return _faces.size() / 3;
    }

    const std::vector<GLfloat>& PLYMesh::positions() const {
        return _positions;
    }

    const std::vector<GLfloat>& PLYMesh::normals() const {
        return _normals;
    }

    const std::vector<GLuint>& PLYMesh::indices() const {
        return _faces;
    }

    void PLYMesh::clear() {
        _positions.clear();
        _normals.clear();
        _faces.clear();
    }
}

