#include "lab_m1/Tema2/Tema2.h"

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
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    left = 0;
    right = 7;
    bottom = 0;
    top = 5;
    zNear = 0.01f;
    zFar = 100;
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


void Tema2::Update(float deltaTimeSeconds)
{
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(carZ, 0, carX));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(carAngle), glm::vec3(0, 1, 0));

        RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
    }

    
    

    // TODO(student): Draw more objects with different model matrices.
    // Attention! The `RenderMesh()` function overrides the usual
    // `RenderMesh()` that we've been using up until now. This new
    // function uses the view matrix from the camera that you just
    // implemented, and the local projection matrix.

    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    if (renderCameraTarget)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
    }
}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
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
    float cameraSpeed = 2.0f;

    if (window->KeyHold(GLFW_KEY_W)) {
        // TODO(student): Translate the camera forward
        camera->MoveForward(cameraSpeed * deltaTime);
        carX -= cameraSpeed * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        // TODO(student): Translate the camera to the left
        camera->RotateThirdPerson_OY(cameraSpeed * deltaTime);
        carAngle += cameraSpeed * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        // TODO(student): Translate the camera backward
        camera->MoveForward(-cameraSpeed * deltaTime);
        carX += cameraSpeed * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        // TODO(student): Translate the camera to the right
        camera->RotateThirdPerson_OY(-cameraSpeed * deltaTime);
        carAngle -= cameraSpeed * deltaTime;
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
