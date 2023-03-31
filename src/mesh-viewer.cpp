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
        renderer.loadShader("normals", "../shaders/normals.vs", "../shaders/normals.fs");
        renderer.loadShader("phong-pixel", "../shaders/phong-pixel.vs", "../shaders/phong-pixel.fs");
        renderer.loadShader("phong-vertex", "../shaders/phong-vertex.vs", "../shaders/phong-vertex.fs");
        renderer.loadShader("toon", "../shaders/toon.vs", "../shaders/toon.fs");
        renderer.loadShader("spotlight", "../shaders/spotlight.vs", "../shaders/spotlight.fs");
        renderer.loadShader("texture", "../shaders/texture.vs", "../shaders/texture.fs");
        renderer.loadTexture("stars", "../textures/stars.jpeg", 0);

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
            azimuth_var = azimuth_var - dx * 0.02;
            elevation_var = elevation_var + dy * 0.02;



           
            float x = rad * sin(azimuth_var) * cos(elevation_var);
            float y = rad * sin(elevation_var);
            float z = rad * cos(azimuth_var) * cos(elevation_var);
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
        rad = rad + dy * 0.5;
        float x = (rad * sin(azimuth_var) * cos(elevation_var));
        float y = (rad * sin(elevation_var));
        float z = (rad * cos(azimuth_var) * cos(elevation_var));
        eyePos = vec3(x, y, z);
    }

    void keyUp(int key, int mods) {
        if (key == GLFW_KEY_N) {
            model_var = (model_var + 1) % mesh_var.size();
           }
        if (key == GLFW_KEY_P) {
            if (model_var != 0) {
                model_var = model_var - 1;
            }
            else {
                model_var = mesh_var.size() - 1;
            }
        }
        if (key == GLFW_KEY_S) {
            shader_var = (shader_var + 1) % shaders.size();          
        }
    }

    void draw() {
        renderer.beginShader(shaders[shader_var]);
        renderer.texture("diffuseTexture", "stars");
        renderer.setUniform("light_var.pos", eyePos);
        renderer.setUniform("light_var1.pos", vec4(30.0,20.0,-20.0,1.0));
        renderer.setUniform("light_var1.la", vec3(1.0f));
        renderer.setUniform("light_var1.ld", vec3(1.0f));
        renderer.setUniform("light_var1.ls", vec3(1.0f));
        renderer.setUniform("light_var.la", vec3(0.25, 0.3, 0.6));
        renderer.setUniform("light_var.ld", vec3(0.2, 0.2, 0.1));
        renderer.setUniform("light_var.ls", vec3(0.4, 0.8, 0.9));
        renderer.setUniform("mat_var.ka", vec3(0.1f));
        renderer.setUniform("mat_var.kd", vec3(1.0f));
        renderer.setUniform("mat_var.ks", vec3(0.6f));
        renderer.setUniform("mat_var.shine", 44.4f);  
        renderer.setUniform("light_var1.exponent", 15.0f);
        renderer.setUniform("light_var1.cutoff", 30.0f);

        mesh = mesh_var[model_var];
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
        renderer.endShader();
       
    }

protected:
    std::vector<string> files_vec = GetFilenamesInDir("../models", "ply");
    PLYMesh mesh;
    std::vector<PLYMesh> mesh_var;
    std::vector<string> shaders = { "normals", "phong-pixel","phong-vertex","toon", "spotlight", "texture"};
    vec3 eyePos = vec3(10, 0, 0);
    vec3 lookPos = vec3(0, 0, 0);
    vec3 up = vec3(0, 1, 0);
    float elevation_var = 0;
    float azimuth_var = 0;
    float rad = 10;
    int model_var = 0;
    int shader_var = 0;
    bool selected = false;
};

int main(int argc, char** argv)
{
    MeshViewer viewer;
    viewer.run();
    return 0;
}