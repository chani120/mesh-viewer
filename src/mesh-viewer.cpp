//--------------------------------------------------
// Author:Chani
// Date:
// Description: Loads PLY file_var in ASCII format
//--------------------------------------------------


#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"
#include "plymesh.h"
#include "osutils.h"

using namespace std;
using namespace glm;
using namespace agl;

class MeshViewer : public Window {
public:
    MeshViewer() : Window() {
    }

    void setup() {
        files_vec = GetFilenamesInDir("../models", "ply");
        for (string var : files_vec) {
            PLYMesh file_var;
            file_var.load("../models/" + var);
            mesh_var.push_back(file_var);
        }
        mesh = mesh_var[0];
    }

    void mouseMotion(int x, int y, int dx, int dy) {
        if (selected) {       
            float x = rad * sin(azimuth_var - dx * 0.1) * cos(element_var + dy * 0.1);
            float y = rad * sin(element_var + dy * 0.1);
            float z = rad * cos(azimuth_var - dx * 0.1) * cos(element_var + dy * 0.1);
            eyePos = vec3(x, y, z);
        }
    }

    void mouseDown(int button, int mods) {
        selected = true;
    }

    void mouseUp(int button, int mods) {
        selected = false;
    }

    void scroll(float dx, float dy) {
        float x = (rad + dy) * sin(azimuth_var) * cos(element_var);
        float y = (rad + dy) * sin(element_var);
        float z = (rad + dy) * cos(azimuth_var) * cos(element_var);
        eyePos = vec3(x, y, z);
    }

    void keyUp(int key, int mods) {
        if (key == GLFW_KEY_P) {
            models = (models + 1) % mesh_var.size();
        }
        else if (key == GLFW_KEY_P) {
            if (models != 0) {
                models = models - 1;
            }
            else {
                models = mesh_var.size() - 1;
            }
        }
    }

    void draw() {
        std::cout << files_vec[models] << std::endl;
        mesh = mesh_var[models];
        float aspect = ((float)width()) / height();
        renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
        renderer.lookAt(eyePos, lookPos, up);

        float a = 1;
        float b = 1;
        float c = 1;  
        GLfloat x_bounds = mesh.maxBounds().x - mesh.minBounds().x;
        GLfloat y_bounds = mesh.maxBounds().y - mesh.minBounds().y;
        GLfloat z_bounds = mesh.maxBounds().z - mesh.minBounds().z;
        if ((x_bounds > z_bounds) || (x_bounds > y_bounds)) {
            a = 5.0f / x_bounds;
            b = 5.0f / x_bounds;
            c = 5.0f / x_bounds;
        }
        else if (y_bounds > z_bounds) {
            a = 5.0f / y_bounds;
            b = 5.0f / y_bounds;
            c = 5.0f / y_bounds;
        }
        else if (z_bounds > y_bounds) {
            a = 5.0f / z_bounds;
            b = 5.0f / z_bounds;
            c = 5.0f / z_bounds;
        }
        renderer.scale(vec3(a, b, c));
        renderer.translate(vec3(0, 0, 0));
        renderer.lookAt(eyePos, lookPos, up);
        renderer.mesh(mesh);
       
    }

protected:
    std::vector<string> files_vec = GetFilenamesInDir("../models", "ply");
    PLYMesh mesh;
    std::vector<PLYMesh> mesh_var;
    vec3 eyePos = vec3(10, 0, 0);
    vec3 lookPos = vec3(0, 0, 0);
    vec3 up = vec3(0, 1, 0);
    float element_var = 0;
    float azimuth_var = 0;
    float rad = 10;
    int models = 0;
    bool selected = false;
};

int main(int argc, char** argv)
{
    MeshViewer viewer;
    viewer.run();
    return 0;
}