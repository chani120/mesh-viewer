//--------------------------------------------------
// Author:
// Date:
// Description: Loads PLY files in ASCII format
//--------------------------------------------------

#include "plymesh.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
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
        initBuffers(&_faces, &_positions, &_normals);
    }

    PLYMesh::~PLYMesh() {
    }

   bool PLYMesh::load(const std::string& filename) {
      if ( _positions.size() != 0 ) {
         std::cout << "WARNING: Cannot load different files with the same PLY mesh\n";
         return false;
      }
      
         ifstream file_var;
         file_var.open(filename);
         if (!file_var.is_open()) {
            return false;
        }
        string data_var;
        file_var >> data_var;
        if (data_var.compare("ply") != 0) {
            return false;
        }
        while (data_var.compare("vertex") != 0) {
            file_var >> data_var;
        }
        file_var >> data_var;
        int numVertex = stoi(data_var);
        while (data_var.compare("face") != 0) {
            file_var >> data_var;
        }
        file_var >> data_var;
         int numFace = stoi(data_var);
        printf("numface: %d\n", numFace);
        while (data_var.compare("end_header") != 0) {
            file_var >> data_var;
        }

        for (int i = 0; i < numVertex; i++) {
            GLfloat var1, var2, var3, var4, var5, var6;
            file_var >> var1 >> var2 >> var3 >> var4 >> var5 >> var6;
            vec3 vec_var = vec3{ var1, var2, var3 };
            _positions.push_back(var1);
            _positions.push_back(var2);
            _positions.push_back(var3);
            _normals.push_back(var4);
            _normals.push_back(var5);
            _normals.push_back(var6);
            file_var >> data_var;
            file_var >> data_var;
        }
        for (int i = 0; i < numFace; i++) {
            file_var >> data_var;
            GLuint f1, f2, f3;
            file_var >> f1 >> f2>> f3;
            _faces.push_back(f1);
            _faces.push_back(f2);
            _faces.push_back(f3);
        }  
        return true;
   }
   glm::vec3 PLYMesh::minBounds() const {
   glm::vec3 minBound(_positions[0], _positions[1], _positions[2]);
     
     for (int i = 3; i < _positions.size(); i += 3) {
         glm::vec3 vertex(_positions[i], _positions[i+1], _positions[i+2]);
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

      for (int i = 3; i < _positions.size(); i += 3) {
         glm::vec3 vertex(_positions[i], _positions[i+1], _positions[i+2]);
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
        return _positions.size()/3;
    }

    void PLYMesh::clear() {
        _positions.clear();
        _faces.clear();
        _normals.clear();
        maxB = vec3( - 100000, -100000, -100000);
        minB = vec3(100000, 100000, 100000);
    }

    int PLYMesh::numTriangles() const {
        return _faces.size()/3;
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
}