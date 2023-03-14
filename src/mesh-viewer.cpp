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
      file_var = GetFilenamesInDir("../models", "ply");
        for (string var : file_var) {
            PLYMesh eachFile;
            eachFile.load("../models/" + var);
            mesh_vec.push_back(eachFile);
        }
        mesh = mesh_vec[0];
   }

   void mouseMotion(int x, int y, int dx, int dy) {
      if (selected) {
         float x; 
         float y;
         float z;
         elevation = elevation + dy * 0.1;
         azimuth = azimuth - dx * 0.1;
         x = rad * sin(azimuth) * cos(elevation);
         y = rad * sin(elevation);
         z = rad * cos(azimuth) * cos(elevation);
         eyePos = vec3(x, y, z);
        }
    }
   }

   void mouseDown(int button, int mods) {
   }

   void mouseUp(int button, int mods) {
   }

   void scroll(float dx, float dy) {
      float x = (rad + dy)* sin(azimuth) * cos(elevation);
      float y = (rad + dy)*sin(elevation);
      float z = (rad + dy)* cos(azimuth) * cos(elevation);
      eyePos = vec3(x, y, z);
   }

   void keyUp(int key, int mods) {
      if (key == GLFW_KEY_N) {
            models = (models + 1) % mesh_vec.size();
        }
        else if(key == GLFW_KEY_M){
            if (models != 0) {
                models = models - 1;
            }
            else {
                models = mesh_vec.size() - 1;
            }
        }
   }

   void draw() {
      std::cout << file_var[models] << std::endl;
      mesh = mesh_vec[models];
      float aspect = ((float)width()) / height();
      renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
      renderer.lookAt(eyePos, lookPos, up);
      float x_var;
      float y_var;
      float z_var; 
      GLfloat x_bounds = mesh.maxBounds().x - mesh.minBounds().x;
      GLfloat y_bounds = mesh.maxBounds().y - mesh.minBounds().y;
      GLfloat z_bounds = mesh.maxBounds().z - mesh.minBounds().z;
      if ((x_bounds > z_bounds) || (x_bounds > y_bounds)) {
         x_var = 5.0f / x_bounds;
         y_var = 5.0f / x_bounds;
         z_var = 5.0f / x_bounds;
      }
      else if (z_bounds > y_bounds) {
         x_var = 5.0f / z_bounds;
         y_var = 5.0f / z_bounds;
         z_var = 5.0f / z_bounds;
      }
      else if (y_bounds > z_bounds) {
         x_var = 5.0f / y_bounds;
         y_var = 5.0f / y_bounds;
         z_var = 5.0f / y_bounds;

      }
      renderer.scale(vec3(x_var, y_var, z_var));
      renderer.translate(vec3(0, 0, 0));
      renderer.lookAt(eyePos,lookPos, up);
      renderer.mesh(mesh);
      
   }

protected:
   std::vector<string> file_var = GetFilenamesInDir("../models", "ply");
    PLYMesh mesh;
    std::vector<PLYMesh> mesh_vec;
    vec3 eyePos = vec3(10, 0, 0);
    vec3 lookPos = vec3(0, 0, 0);
    vec3 up = vec3(0, 1, 0);
    bool selected = false;
    float elevation = 0;
    float azimuth = 0;
    float rad = 10;
    int models = 0;
};

int main(int argc, char** argv)
{
   MeshViewer viewer;
   viewer.run();
   return 0;
}

