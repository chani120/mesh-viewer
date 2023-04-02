# mesh-viewer

Implements a simple PLY viewer

<img width="180" alt="Screenshot 2023-04-02 180201" src="https://user-images.githubusercontent.com/44120884/229381394-9e8734bb-e51a-4906-bd3c-cd437334a570.png">


## How to build

*Windows*

Open git bash to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ start mesh-viewer.sln
```

Your solution file should contain two projects: `mesh-viewer` and `test-ply-mesh`.
To run from the git bash command shell, 

```
mesh-viewer/build $ ../bin/Debug/test-ply-mesh.exe
mesh-viewer/build $ ../bin/Debug/mesh-viewer.exe
```

*macOS*

Open terminal to the directory containing this repository.

```
mesh-viewer $ mkdir build
mesh-viewer $ cd build
mesh-viewer/build $ cmake ..
mesh-viewer/build $ make
```

To run each program from build, you would type

```
mesh-viewer/build $ ../bin/mesh-viewer
```

## Demo of basic features

[screen-capture (1).webm](https://user-images.githubusercontent.com/44120884/229380854-4f9a3d37-0f73-4920-a55e-7717aa2f6aae.webm)

[screen-capture (2).webm](https://user-images.githubusercontent.com/44120884/229380874-addd3e57-ff31-4929-bbed-8bcb50b24f5e.webm)

[screen-capture (3).webm](https://user-images.githubusercontent.com/44120884/229380883-2d8d5d23-53f7-4deb-ab03-a9c78f89f5ba.webm)


## Unique features 

[screen-capture (4).webm](https://user-images.githubusercontent.com/44120884/229380900-be02e3ea-8538-4f5e-bee0-7f0ee9e0dd61.webm)

https://user-images.githubusercontent.com/44120884/229381041-66bfcec3-5fbc-49fe-8257-e5a3e8596bae.mp4

[screen-capture (7).webm](https://user-images.githubusercontent.com/44120884/229381089-e3df8415-0e5f-48fe-8c1b-27308d7dda46.webm)



