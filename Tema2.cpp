#include "lab_m1/Tema2/Tema2.h"
#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;

Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    renderCameraTarget = false;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(1.5, 1.1, -1.7), glm::vec3(5, 0.1, -1.7), glm::vec3(0, 1, 0));

    left = -2;
    right = 2;
    bottom = -1.125;
    top = 1.125;
    zNear = 0.01f;
    zFar = 50;

    carAngle = 0;

    shouldIstop = 0;
    shouldIstop1 = 0;
    shouldIstop2 = 0;
    shouldIstop3 = 0;
    timer = 0;

    CreateTrees();
    DrawTrack();
    CreateCars();
    CreateGrass();
    CreateSky();

    traseu[0][0] = glm::vec3(-2.52, 0, 0.61); 
    traseu[0][1] = glm::vec3(-1.73, 0, 1.41); 
    traseu[0][2] = glm::vec3(-0.62, 0, 1.55);
    traseu[0][3] = glm::vec3(0.22, 0, 1.37); 
    traseu[0][4] = glm::vec3(0.8, 0, 1);
    traseu[0][5] = glm::vec3(1.2, 0, 0.6);
    traseu[0][6] = glm::vec3(1.73, 0, 0.13);
    traseu[0][7] = glm::vec3(2.38, 0, 0.13);
    traseu[0][8] = glm::vec3(2.89, 0, 0.38);
    traseu[0][9] = glm::vec3(3.54, 0, 0.52);
    traseu[0][10] = glm::vec3(4.38, 0, -0.03);
    traseu[0][11] = glm::vec3(4.36, 0, -0.99);
    traseu[0][12] = glm::vec3(3.91, 0, -1.42);
    traseu[0][13] = glm::vec3(3.31, 0, -1.57);
    traseu[0][14] = glm::vec3(2.34, 0, -1.67);
    traseu[0][15] = glm::vec3(1.47, 0, -1.81);
    traseu[0][16] = glm::vec3(0.52, 0, -1.81);
    traseu[0][17] = glm::vec3(-0.35, 0, -1.63);
    traseu[0][18] = glm::vec3(-0.67, 0, -1.04);
    traseu[0][19] = glm::vec3(-1.3, 0, -0.8);
    traseu[0][20] = glm::vec3(-2.05, 0, -0.52);
    traseu[0][21] = glm::vec3(-2.5, 0, -0.03);

    traseu[1][0] = glm::vec3(1.12, 0, 0.51); 
    traseu[1][1] = glm::vec3(1.73, 0, 0.05);
    traseu[1][2] = glm::vec3(2.37, 0, 0.05);
    traseu[1][3] = glm::vec3(2.91, 0, 0.27);
    traseu[1][4] = glm::vec3(3.53, 0, 0.44);
    traseu[1][5] = glm::vec3(4.2, 0, -0.13);
    traseu[1][6] = glm::vec3(4.22, 0, -0.95);
    traseu[1][7] = glm::vec3(3.82, 0, -1.32);
    traseu[1][8] = glm::vec3(3.23, 0, -1.46);
    traseu[1][9] = glm::vec3(2.31, 0, -1.57);
    traseu[1][10] = glm::vec3(1.44, 0, -1.7);
    traseu[1][11] = glm::vec3(0.52, 0, -1.75);
    traseu[1][12] = glm::vec3(-0.32, 0, -1.55);
    traseu[1][13] = glm::vec3(-0.62, 0, -0.95);
    traseu[1][14] = glm::vec3(-1.24, 0, -0.7);
    traseu[1][15] = glm::vec3(-1.94, 0, -0.44);
    traseu[1][16] = glm::vec3(-2.4, 0, 0);
    traseu[1][17] = glm::vec3(-2.35, 0, 0.61);
    traseu[1][18] = glm::vec3(-1.67, 0, 1.28);
    traseu[1][19] = glm::vec3(-0.63, 0, 1.46);
    traseu[1][20] = glm::vec3(0.21, 0, 1.27);
    traseu[1][21] = glm::vec3(0.77, 0, 0.91);


    traseu[2][0] = glm::vec3(2.36, 0, -1.79);
    traseu[2][1] = glm::vec3(1.49, 0, -1.9);
    traseu[2][2] = glm::vec3(0.51, 0, -1.9);
    traseu[2][3] = glm::vec3(-0.41, 0, -1.72);
    traseu[2][4] = glm::vec3(-0.8, 0, -1.13);
    traseu[2][5] = glm::vec3(-1.4, 0, -0.9);
    traseu[2][6] = glm::vec3(-2.13, 0, -0.59);
    traseu[2][7] = glm::vec3(-2.62, 0, -0.07);
    traseu[2][8] = glm::vec3(-2.69, 0, 0.63);
    traseu[2][9] = glm::vec3(-1.74, 0, 1.54);
    traseu[2][10] = glm::vec3(-0.61, 0, 1.63);
    traseu[2][11] = glm::vec3(0.24, 0, 1.44);
    traseu[2][12] = glm::vec3(0.84, 0, 1.03);
    traseu[2][13] = glm::vec3(1.23, 0, 0.63);
    traseu[2][14] = glm::vec3(1.75, 0, 0.2);
    traseu[2][15] = glm::vec3(2.37, 0, 0.21);
    traseu[2][16] = glm::vec3(2.89, 0, 0.46);
    traseu[2][17] = glm::vec3(3.55, 0, 0.61);
    traseu[2][18] = glm::vec3(4.45, 0, 0.06);
    traseu[2][19] = glm::vec3(4.5, 0, -1);
    traseu[2][20] = glm::vec3(4, 0, -1.5);
    traseu[2][21] = glm::vec3(3.34, 0, -1.72);

    for (int i = 0; i < 3; i++) {
        H[i] = traseu[i][0];
        m[i] = (traseu[i][1].z - traseu[i][0].z) / (traseu[i][1].x - traseu[i][0].x);
        obsAngle[i] = atan(m[i]);
        v[i] = traseu[i][1] - traseu[i][0];
        contor[i] = 0;
        start[i] = 0;
    }
    
}

void Tema2::CreateTree(float x, float z, int i) {
    vector<VertexFormat> verticesTrunk
    {
        VertexFormat(glm::vec3(x - 0.025, 1,  z - 0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x - 0.025, 1,  z + 0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x + 0.025, 1,  z - 0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x + 0.025, 1,  z + 0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x - 0.025, 1.075,  z - 0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x - 0.025, 1.075,  z + 0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x + 0.025, 1.075,  z - 0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x + 0.025, 1.075,  z + 0.025), glm::vec3(0.36, 0.25, 0.109)),
    };

    vector<VertexFormat> verticesLeaves
    {
        VertexFormat(glm::vec3(x - 0.075, 1.0751,  z - 0.075), glm::vec3(0.145, 0.368, 0.164)),
        VertexFormat(glm::vec3(x - 0.075, 1.0751,  z + 0.075), glm::vec3(0.145, 0.368, 0.164)),
        VertexFormat(glm::vec3(x + 0.075, 1.0751,  z - 0.075), glm::vec3(0.145, 0.368, 0.164)),
        VertexFormat(glm::vec3(x + 0.075, 1.0751,  z + 0.075), glm::vec3(0.145, 0.368, 0.164)),
        VertexFormat(glm::vec3(x - 0.075, 1.2,  z - 0.075), glm::vec3(0.145, 0.368, 0.164)),
        VertexFormat(glm::vec3(x - 0.075, 1.2,  z + 0.075), glm::vec3(0.145, 0.368, 0.164)),
        VertexFormat(glm::vec3(x + 0.075, 1.2,  z - 0.075), glm::vec3(0.145, 0.368, 0.164)),
        VertexFormat(glm::vec3(x + 0.075, 1.2,  z + 0.075), glm::vec3(0.145, 0.368, 0.164)),
    };

    vector<unsigned int> indices =
    {

        0, 1, 5,
        0, 5, 4,
        1, 3, 7,
        1, 7, 5,
        3, 2, 6,
        3, 6, 7,
        2, 0, 4,
        2, 4, 6,
        4, 5, 7,
        4, 7, 6,
        0, 1, 3,
        0, 3, 2
    };

    trunks[i] = new Mesh("trunk");
    trunks[i]->InitFromData(verticesTrunk, indices);
    leaves[i] = new Mesh("leaves");
    leaves[i]->InitFromData(verticesLeaves, indices);
    
}

void Tema2::CreateTrees() {
    CreateTree(0, 0, 1);
    CreateTree(-2.06, 0.67, 2);
    CreateTree(-2.79, 0.84, 3);
    CreateTree(-1.64, 1, 4);
    CreateTree(-2.1, 1.6, 5);
    CreateTree(-1.03, 1.83, 6);
    CreateTree(-1.22, 1.12, 7);
    CreateTree(-0.31, 1.81, 8);
    CreateTree(-0.65, 1.23, 9);
    CreateTree(-0.06, 1.14, 10);
    CreateTree(0.91, 1.26, 11);
    CreateTree(1.32, 0.89, 12);
    CreateTree(0.97, 0.2, 13);
    CreateTree(2.03, 0.37, 14);
    CreateTree(2.87, 0.02, 15);
    CreateTree(3.69, 0.89, 16);
    CreateTree(4.8, 0.11, 17);
    CreateTree(4, -0.29, 18);

    CreateTree(4.83, -0.96, 19);
    CreateTree(4.39, -1.61, 20);
    CreateTree(3.55, -1.13, 21);
    CreateTree(2.88, -1.27, 22);
    CreateTree(3.6, -1.9, 23);
    CreateTree(2.68, -2.04, 24);
    CreateTree(2.02, -1.34, 25);
    CreateTree(1.57, -2.15, 26);
    CreateTree(0.51, -2.14, 27);
    CreateTree(-0.03, -1.33, 28);
    CreateTree(-0.91, -1.63, 29);
    CreateTree(-0.36, -0.77, 30);
    CreateTree(-1.04, -0.46, 31);
    CreateTree(-2.16, -0.89, 32);
    CreateTree(-2.73, -0.46, 33);
    CreateTree(-2.12, 0.13, 34);
}

void Tema2::CreateGrass() {
    vector<VertexFormat> verticesGrass
    {
        VertexFormat(glm::vec3(-100, 0.8,  -100), glm::vec3(0.486, 0.85, 0.458)),
        VertexFormat(glm::vec3(-100, 0.8,  100), glm::vec3(0.486, 0.85, 0.458)),
        VertexFormat(glm::vec3(100, 0.8,  -100), glm::vec3(0.486, 0.85, 0.458)),
        VertexFormat(glm::vec3(100, 0.8,  100), glm::vec3(0.486, 0.85, 0.458)),
    };



    vector<unsigned int> indicesGrass =
    {
        0, 1, 2,
        1, 2, 3

    };

    grass = new Mesh("grass");grass->InitFromData(verticesGrass, indicesGrass);
}

void Tema2::CreateSky() {
    vector<VertexFormat> verticesSky
    {
        VertexFormat(glm::vec3(-100, 0.1,  -100), glm::vec3(0.431, 0.647, 1)),
        VertexFormat(glm::vec3(-100, 0.1,  100), glm::vec3(0.431, 0.647, 1)),
        VertexFormat(glm::vec3(100, 0.1,  -100), glm::vec3(0.431, 0.647, 1)),
        VertexFormat(glm::vec3(100, 0.1,  100), glm::vec3(0.431, 0.647, 1)),
        VertexFormat(glm::vec3(-100, 100,  -100), glm::vec3(0.431, 0.647, 1)),
        VertexFormat(glm::vec3(-100, 100,  100), glm::vec3(0.431, 0.647, 1)),
        VertexFormat(glm::vec3(100, 100,  -100), glm::vec3(0.431, 0.647, 1)),
        VertexFormat(glm::vec3(100, 100,  100), glm::vec3(0.431, 0.647, 1)),
    };



    vector<unsigned int> indicesSky =
    {
        0, 1, 5,
        0, 5, 4,
        1, 3, 7,
        1, 7, 5,
        3, 2, 6,
        3, 6, 7,
        2, 0, 4,
        2, 4, 6

    };

    sky = new Mesh("sky");
    sky->InitFromData(verticesSky, indicesSky);
}

void Tema2::CreateCars()
{
    vector<VertexFormat> verticesCar
    {
        VertexFormat(glm::vec3(-0.025, 1,  -0.05), glm::vec3(0.011, 0.925, 0.988)),
        VertexFormat(glm::vec3(-0.025, 1,  0.05), glm::vec3(0.011, 0.925, 0.988)),
        VertexFormat(glm::vec3(0.025, 1,  -0.05), glm::vec3(0.011, 0.925, 0.988)),
        VertexFormat(glm::vec3(0.025, 1,  0.05), glm::vec3(0.011, 0.925, 0.988)),
        VertexFormat(glm::vec3(-0.025, 1.05,  -0.05), glm::vec3(0.011, 0.925, 0.988)),
        VertexFormat(glm::vec3(-0.025, 1.05,  0.05), glm::vec3(0.011, 0.925, 0.988)),
        VertexFormat(glm::vec3(0.025, 1.05,  -0.05), glm::vec3(0.011, 0.925, 0.988)),
        VertexFormat(glm::vec3(0.025, 1.05,  0.05), glm::vec3(0.011, 0.925, 0.988)),
    };

    vector<VertexFormat> verticesObstacle1
    {
        VertexFormat(glm::vec3(-0.025, 1,  -0.05), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-0.025, 1,  0.05), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(0.025, 1,  -0.05), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(0.025, 1,  0.05), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-0.025, 1.05,  -0.05), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-0.025, 1.05,  0.05), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(0.025, 1.05,  -0.05), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(0.025, 1.05,  0.05), glm::vec3(1, 0, 0)),
    };

    vector<VertexFormat> verticesObstacle2
    {
        VertexFormat(glm::vec3(-0.025, 1,  -0.05), glm::vec3(0, 1, 0)),
        VertexFormat(glm::vec3(-0.025, 1,  0.05), glm::vec3(0, 1, 0)),
        VertexFormat(glm::vec3(0.025, 1,  -0.05), glm::vec3(0, 1, 0)),
        VertexFormat(glm::vec3(0.025, 1,  0.05), glm::vec3(0, 1, 0)),
        VertexFormat(glm::vec3(-0.025, 1.05,  -0.05), glm::vec3(0, 1, 0)),
        VertexFormat(glm::vec3(-0.025, 1.05,  0.05), glm::vec3(0, 1, 0)),
        VertexFormat(glm::vec3(0.025, 1.05,  -0.05), glm::vec3(0, 1, 0)),
        VertexFormat(glm::vec3(0.025, 1.05,  0.05), glm::vec3(0, 1, 0)),
    };

    vector<VertexFormat> verticesObstacle3
    {
        VertexFormat(glm::vec3(-0.025, 1,  -0.05), glm::vec3(0, 0, 1)),
        VertexFormat(glm::vec3(-0.025, 1,  0.05), glm::vec3(0, 0, 1)),
        VertexFormat(glm::vec3(0.025, 1,  -0.05), glm::vec3(0, 0, 1)),
        VertexFormat(glm::vec3(0.025, 1,  0.05), glm::vec3(0, 0, 1)),
        VertexFormat(glm::vec3(-0.025, 1.05,  -0.05), glm::vec3(0, 0, 1)),
        VertexFormat(glm::vec3(-0.025, 1.05,  0.05), glm::vec3(0, 0, 1)),
        VertexFormat(glm::vec3(0.025, 1.05,  -0.05), glm::vec3(0, 0, 1)),
        VertexFormat(glm::vec3(0.025, 1.05,  0.05), glm::vec3(0, 0, 1)),
    };



    vector<unsigned int> indicesCar =
    {

        0, 1, 5,
        0, 5, 4,
        1, 3, 7,
        1, 7, 5,
        3, 2, 6,
        3, 6, 7,
        2, 0, 4,
        2, 4, 6,
        4, 5, 7,
        4, 7, 6

        /*
        0, 1, 2,
        3, 4, 5,
        0, 6, 7
        */
    };

    car = new Mesh("car");
    car->InitFromData(verticesCar, indicesCar);

    obstacle[0] = new Mesh("obstacle1");
    obstacle[0]->InitFromData(verticesObstacle1, indicesCar);

    obstacle[1] = new Mesh("obstacle2");
    obstacle[1]->InitFromData(verticesObstacle2, indicesCar);

    obstacle[2] = new Mesh("obstacle3");
    obstacle[2]->InitFromData(verticesObstacle3, indicesCar);


}


void Tema2::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::DrawTrack()
{
    vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-2.22, 1,  0.61), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-1.6, 1,  1.15), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-0.65, 1,  1.36), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(0.16, 1,  1.17), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(0.7, 1,  0.83), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(1.06, 1,  0.43), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(1.72, 1,  -0.07), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(2.37, 1,  -0.08), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(2.92, 1,  0.17), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(3.51, 1,  0.3), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(4.12, 1,  -0.18), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(4.1, 1,  -0.91), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(3.72, 1,  -1.21), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(3.2, 1,  -1.32), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(2.3, 1,  -1.42), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(1.44, 1,  -1.59), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(0.54, 1,  -1.63), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-0.26, 1,  -1.46), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-0.53, 1, -0.84), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-1.18, 1,  -0.6), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-1.86, 1,  -0.36), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-2.3, 1,  0.06), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-0.58, 1,  1.76), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(0.28, 1,  1.59), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(0.9, 1,  1.14), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(1.3, 1,  0.75), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(1.76, 1,  0.31), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(2.38, 1,  0.31), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(2.87, 1,  0.58), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(3.56, 1,  0.74), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(4.55, 1,  0.12), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(4.59, 1,  -1.02), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(4.1, 1,  -1.62), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(3.38, 1,  -1.84), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(2.37, 1,  -1.89), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(1.5, 1,  -2), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(0.5, 1,  -2), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-0.49, 1,  -1.8), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-0.89, 1,  -1.22), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-1.5, 1,  -1), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-2.24, 1,  -0.68), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-2.75, 1,  -0.12), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-2.83, 1,  0.64), glm::vec3(0.258, 0.258, 0.258)),
        VertexFormat(glm::vec3(-1.82, 1,  1.67), glm::vec3(0.258, 0.258, 0.258))

    };



    vector<unsigned int> indices =
    {
        0, 1, 42,
        1, 43, 42,
        1, 2, 43,
        2, 22, 43,
        2, 3, 22,
        3, 23, 22,
        3, 4, 23,
        4, 24, 23,
        4, 5, 24,
        5, 25, 24,
        5, 6, 25,
        6, 26, 25,
        6, 7, 26,
        7, 27, 26,
        7, 8, 27,
        8, 28, 27,
        8, 9, 28,
        9, 29, 28,
        9, 10, 29,
        10, 30, 29,
        10, 11, 30,
        11, 31, 30,
        11, 12, 31,
        12, 32, 31,
        12, 13, 32,
        13, 33, 32,
        13, 14, 33,
        14, 34, 33,
        14, 15, 34,
        15, 35, 34,
        15, 16, 35,
        16, 36, 35,
        16, 17, 36,
        17, 37, 36,
        17, 18, 37,
        18, 38, 37,
        18, 19, 38,
        19, 39, 38,
        19, 20, 39,
        20, 40, 39,
        20, 21, 40,
        21, 41, 40,
        21, 0, 41,
        0, 42, 41

    };

    track = new Mesh("track");
    track->InitFromData(vertices, indices);
}

int Tema2::isCollision(glm::vec3 car, glm::vec3 obstacle) {
    int ret = 0;
    if (sqrt((car.x - obstacle.x) * (car.x - obstacle.x) + (car.z - obstacle.z) * (car.z - obstacle.z)) <= 0.051) {
        ret = 1;
    }
    return ret;
}

void Tema2::RenderScene() {
    
    RenderMesh(track, shaders["VertexColor"], glm::mat4(1));
    RenderMesh(grass, shaders["VertexColor"], glm::mat4(1));
    RenderMesh(sky, shaders["VertexColor"], glm::mat4(1));
    
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition().x, camera->GetTargetPosition().y-0.9625, camera->GetTargetPosition().z));
    modelMatrix = glm::rotate(modelMatrix, carAngle, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
    RenderMesh(car, shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < 3; i++) {
        modelMatrix = glm::mat4(1);

        H[i] = H[i] + v[i] * 0.003f;

        modelMatrix = glm::translate(modelMatrix, H[i]);
        modelMatrix = glm::rotate(modelMatrix, -obsAngle[i], glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));

        RenderMesh(obstacle[i], shaders["VertexColor"], modelMatrix);

        if ((contor[i] < 20 && length(glm::vec2((H[i] - traseu[i][contor[i] + 1]).x, (H[i] - traseu[i][contor[i] + 1]).z)) <= 0.005)) {

            if (contor[i] == 20 && i == 0) {
                printf("SIU");
            }

            contor[i] = contor[i] + 1;
            m[i] = (traseu[i][contor[i] + 1].z - traseu[i][contor[i]].z) / (traseu[i][contor[i] + 1].x - traseu[i][contor[i]].x);
            H[i] = traseu[i][contor[i]];
            obsAngle[i] = atan(m[i]);
            start[i] = 1;

        }
        else if ((contor[i] == 20 && length(glm::vec2((H[i] - traseu[i][21]).x, (H[i] - traseu[i][21]).z)) <= 0.005)) {
            contor[i] = 21;
            m[i] = (traseu[i][0].z - traseu[i][21].z) / (traseu[i][0].x - traseu[i][21].x);
            H[i] = traseu[i][21];
            obsAngle[i] = atan(m[i]);

        }
        else if((contor[i] == 21 && length(glm::vec2((H[i] - traseu[i][0]).x, (H[i] - traseu[i][0]).z)) <= 0.005)){
            contor[i] = 0;
            m[i] = (traseu[i][1].z - traseu[i][0].z) / (traseu[i][1].x - traseu[i][0].x);
            H[i] = traseu[i][0];
            obsAngle[i] = atan(m[i]);
        }

        if (contor[i] == 21) {
            v[i] = traseu[i][0] - traseu[i][21];
            
        }
        else {
            v[i] = traseu[i][contor[i] + 1] - traseu[i][contor[i]];

        }
        
    }

    for (int i = 1; i < 35; i++) {
        RenderMesh(trunks[i], shaders["VertexColor"], glm::mat4(1));
        RenderMesh(leaves[i], shaders["VertexColor"], glm::mat4(1));
    }
    
}


void Tema2::Update(float deltaTimeSeconds)
{
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    glLineWidth(3);
    glPointSize(5);

    RenderScene();

    camera2 = camera;
    camera = new implemented::Camera();
    camera->Set(glm::vec3(camera2->GetTargetPosition().x, 1.5, camera2->GetTargetPosition().z), glm::vec3(camera2->GetTargetPosition().x, camera2->GetTargetPosition().y, camera2->GetTargetPosition().z), glm::vec3(1, 0, 0));

    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(0, 0, resolution.x / 5.f, resolution.y / 5.f);

    projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    RenderScene();
    camera = camera2;
}


void Tema2::FrameEnd()
{

}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

float Tema2::area(glm::vec2 a, glm::vec2 b, glm::vec2 c) {
    float p = (length(b - c) + length(a - c) + length(a - b))*0.5;
    float areaa = sqrt(p * (p - length(b - c)) * (p - length(a - c)) * (p - length(a - b)));
    return areaa;
}

int Tema2::isOnTrack(float x, float z) {
    int ret = 0;
    glm::vec2 point1 , point2, point3;
    glm::vec2 carPosition = glm::vec2(x, z);
    for (int i = 0; i < 44*3; i+=3) {
        point1 = glm::vec2(track->vertices[track->indices[i]].position.x, track->vertices[track->indices[i]].position.z);
        point2 = glm::vec2(track->vertices[track->indices[i+1]].position.x, track->vertices[track->indices[i+1]].position.z);
        point3 = glm::vec2(track->vertices[track->indices[i+2]].position.x, track->vertices[track->indices[i+2]].position.z);

        if (area(point1, point2, carPosition) + area(point2, point3, carPosition) + area(point1, point3, carPosition) - area(point1, point2, point3) <= 0.005) {
            ret = 1;
        }
    }
    return ret;
}


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float cameraSpeed = 1.0f;

    if (isCollision(camera->GetTargetPosition(), H[0])) {
        shouldIstop1 = 1;
    }

    if (isCollision(camera->GetTargetPosition(), H[1])) {
        shouldIstop2 = 1;
    }

    if (isCollision(camera->GetTargetPosition(), H[2])) {
        shouldIstop3 = 1;
    }

    if (shouldIstop1 || shouldIstop2 || shouldIstop3) {
        shouldIstop = 1;
        shouldIstop1 = 0;
        shouldIstop2 = 0;
        shouldIstop3 = 0;
    }
    if (shouldIstop) {
        timer += deltaTime;
    }
    if (timer > 0.6) {
        timer = 0;
        shouldIstop = 0;
    }


    if (window->KeyHold(GLFW_KEY_W) && timer == 0) {
        camera->MoveForward(cameraSpeed * deltaTime);
        if (isOnTrack(camera->GetTargetPosition().x, camera->GetTargetPosition().z) == 0) {
            
            camera->MoveForward(-cameraSpeed * deltaTime);
        }
        
    }

    else if (window->KeyHold(GLFW_KEY_S) && timer == 0) {
        camera->MoveForward(-cameraSpeed / 2 * deltaTime);
        if (isOnTrack(camera->GetTargetPosition().x, camera->GetTargetPosition().z) == 0) {
            camera->MoveForward(cameraSpeed / 2 * deltaTime);

        }
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        camera->RotateThirdPerson_OY(cameraSpeed * deltaTime);
        carAngle += deltaTime * cameraSpeed;
    }

    

    if (window->KeyHold(GLFW_KEY_D)) {
        camera->RotateThirdPerson_OY(-cameraSpeed * deltaTime);
        carAngle -= deltaTime * cameraSpeed;
    }

}


void Tema2::OnKeyPress(int key, int mods)
{
    
}


void Tema2::OnKeyRelease(int key, int mods)
{

}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{

}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}