#include "lab_m1/Tema2/Tema2.h"
#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


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
    camera->Set(glm::vec3(0, 1.1, 3.5f), glm::vec3(0, -0.7, 0), glm::vec3(0, 1, 0));

    camera2 = new implemented::Camera();
    camera2->Set(glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0));

    left = -3;
    right = 3;
    bottom = -2.5;
    top = 2.5;
    zNear = 0.01f;
    zFar = 40;
    fov = 50;
    persp = true;
    minFOV = 0.1f;
    maxFOV = 179.9f;

    carX = 0;
    carZ = 0;
    carAngle = 0;


    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // TODO(student): After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters


    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);



}

void Tema2::CreateTree(float x, float z) {
    vector<VertexFormat> verticesTrunk
    {
        VertexFormat(glm::vec3(x-0.025, 1,  z-0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x-0.025, 1,  z+0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x+0.025, 1,  z-0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x+0.025, 1,  z+0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x-0.025, 1.075,  z-0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x-0.025, 1.075,  z+0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x+0.025, 1.075,  z-0.025), glm::vec3(0.36, 0.25, 0.109)),
        VertexFormat(glm::vec3(x+0.025, 1.075,  z+0.025), glm::vec3(0.36, 0.25, 0.109)),
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

    vector<unsigned int> indices=
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



    Mesh* trunk = new Mesh("trunk");
    trunk->InitFromData(verticesTrunk, indices);
    RenderMesh(trunk, shaders["VertexColor"], glm::mat4(1));
    Mesh* leaves = new Mesh("leaves");
    leaves->InitFromData(verticesLeaves, indices);
    RenderMesh(leaves, shaders["VertexColor"], glm::mat4(1));
}

void Tema2::CreateTrees() {
    CreateTree(0, 0);
    CreateTree(-2.06, 0.67);
    CreateTree(-2.79, 0.84);
    CreateTree(-1.64, 1);
    CreateTree(-2.1, 1.6);
    //A
    CreateTree(-1.03, 1.83);
    CreateTree(-1.22, 1.12);
    CreateTree(-0.31, 1.81);
    CreateTree(-0.65, 1.23);
    CreateTree(-0.06, 1.14);
    CreateTree(0.91, 1.26);
    CreateTree(1.32, 0.89);
    CreateTree(0.97, 0.2);
    CreateTree(2.03, 0.37);
    CreateTree(2.87, 0.02);
    CreateTree(3.69, 0.89);
    CreateTree(4.8, 0.11);
    CreateTree(4, -0.29);

    CreateTree(4.83, -0.96);
    CreateTree(4.39, -1.61);
    CreateTree(3.55, -1.13);
    CreateTree(2.88, -1.27);
    CreateTree(3.6, -1.9);
    CreateTree(2.68, -2.04);
    CreateTree(2.02, -1.34);
    CreateTree(1.57, -2.15);
    CreateTree(0.51, -2.14);
    CreateTree(-0.03, -1.33);
    CreateTree(-0.91, -1.63);
    CreateTree(-0.36, -0.77);
    CreateTree(-1.04, -0.46);
    CreateTree(-2.16, -0.89);
    CreateTree(-2.73, -0.46);
    CreateTree(-2.12, 0.13);
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

    Mesh* grass = new Mesh("grass");
    grass->InitFromData(verticesGrass, indicesGrass);
    RenderMesh(grass, shaders["VertexColor"], glm::mat4(1));
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

    Mesh* sky = new Mesh("sky");
    sky->InitFromData(verticesSky, indicesSky);
    RenderMesh(sky, shaders["VertexColor"], glm::mat4(1));
}

void Tema2::CreateCar(glm::mat4 & modelMatrix)
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



    Mesh* car = new Mesh("car");
    car->InitFromData(verticesCar, indicesCar);
    RenderMesh(car, shaders["VertexColor"], modelMatrix);
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
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
        0, 1, 42, //a b s1
        1, 43, 42, //b t1 s1
        1, 2, 43, //b, c, t1
        2, 22, 43, //
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


        //15, 16, 62
    };


    Mesh* track = new Mesh("track");
    track->InitFromData(vertices, indices);
    RenderMesh(track, shaders["VertexColor"], glm::mat4(1));
}

void Tema2::RenderScene() {
    DrawTrack();
    CreateGrass();
    CreateSky();
    glm::mat4 modelMatrix = glm::mat4(1);
    //modelMatrix = glm::translate(modelMatrix, glm::vec3(0.7, 0, 1));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition().x, camera->GetTargetPosition().y - 0.872, camera->GetTargetPosition().z));
    modelMatrix = glm::rotate(modelMatrix, carAngle, glm::vec3(0, 1, 0));
    CreateCar(modelMatrix);
    CreateTrees();
}


void Tema2::Update(float deltaTimeSeconds)
{
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    glLineWidth(3);
    glPointSize(5);

    RenderScene();
    projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // TODO(student): render the scene again, in the new viewport
    RenderScene();
}


void Tema2::FrameEnd()
{
}


void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    float cameraSpeed = 1.0f;

    if (window->KeyHold(GLFW_KEY_W)) {
        // TODO(student): Translate the camera forward
        camera->MoveForward(cameraSpeed * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        // TODO(student): Translate the camera to the left
        camera->RotateThirdPerson_OY(cameraSpeed * deltaTime);
        carAngle += deltaTime * cameraSpeed;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        // TODO(student): Translate the camera backward
        camera->MoveForward(-cameraSpeed/2 * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        // TODO(student): Translate the camera to the right
        camera->RotateThirdPerson_OY(-cameraSpeed * deltaTime);
        carAngle -= deltaTime * cameraSpeed;
    }

    // TODO(student): Change projection parameters. Declare any extra
    // variables you might need in the class header. Inspect this file
    // for any hardcoded projection arguments (can you find any?) and
    // replace them with those extra variables.

    if (window->KeyHold(GLFW_KEY_R) && persp && fov > minFOV) {
        fov -= deltaTime * 10;
        projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, zNear, zFar);
    }

    // X to increase FOV (works only on perspective view)
    if (window->KeyHold(GLFW_KEY_T) && persp && fov < maxFOV) {
        fov += deltaTime * 10;
        projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, zNear, zFar);
    }

    // I to decrease width in orthographic view
    if (window->KeyHold(GLFW_KEY_I) && !persp) {
        right -= 5 * deltaTime;
        left += 5 * deltaTime;
        projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
    }

    // O to increase width in orthographic view
    if (window->KeyHold(GLFW_KEY_J) && !persp) {
        right += 5 * deltaTime;
        left -= 5 * deltaTime;
        projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
    }

    // J to decrease height in orthographic view
    if (window->KeyHold(GLFW_KEY_K) && !persp) {
        top -= 5 * deltaTime;
        bottom += 5 * deltaTime;
        projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
    }

    // K to decrease height in orthographic view
    if (window->KeyHold(GLFW_KEY_L) && !persp) {
        top += 5 * deltaTime;
        bottom -= 5 * deltaTime;
        projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
    }
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections
    if (key == GLFW_KEY_O)
    {
        persp = false;
        projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
    }
    if (key == GLFW_KEY_P) {
        persp = true;
        projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, zNear, zFar);
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateFirstPerson_OX(-deltaY * sensivityOX);
            camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OX(-deltaY * sensivityOX);
            camera->RotateThirdPerson_OY(-deltaX * sensivityOY);

        }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}