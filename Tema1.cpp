#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

    glBindVertexArray(0);

    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}

void Tema1::Init()
{
    lives = 3;
    bullets = 3;
    duckx = 400;
    ducky = 300;
    score = 0;
    alive = 1;
    escaped = 0;
    timeAlive = 0;
    newDuck = 0;
    speed = 5;
    duckAngle = AI_MATH_PI / 4;
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(-500, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    angularStep = 0;

    vector<VertexFormat> vertices_beak
    {
        VertexFormat(glm::vec3(100, -8.75,  0), glm::vec3(1, 1, 0)),
        VertexFormat(glm::vec3(100, 8.75,  0), glm::vec3(1, 1, 0)),
        VertexFormat(glm::vec3(143.75, 0,  0), glm::vec3(1, 1, 0))      
    };

    vector<VertexFormat> vertices_body
    {
        VertexFormat(glm::vec3(-88, -35,  0), glm::vec3(0.258, 0.16, 0.117)),
        VertexFormat(glm::vec3(-88, 35,  0), glm::vec3(0.258, 0.16, 0.117)),
        VertexFormat(glm::vec3(88, 0,  0), glm::vec3(0.258, 0.16, 0.117))
    };

    vector<VertexFormat> vertices_left
    {
        VertexFormat(glm::vec3(-26.25, 0,  1), glm::vec3(0.258, 0.16, 0.117)),
        VertexFormat(glm::vec3(-5, 87.5,  1), glm::vec3(0.258, 0.16, 0.117)),
        VertexFormat(glm::vec3(26.25, 0,  1), glm::vec3(0.258, 0.16, 0.117))
    };

    vector<VertexFormat> vertices_right
    {
        VertexFormat(glm::vec3(-26.25, 0,  1), glm::vec3(0.258, 0.16, 0.117)),
        VertexFormat(glm::vec3(-5, -87.5,  1), glm::vec3(0.258, 0.16, 0.117)),
        VertexFormat(glm::vec3(26.25, 0,  1), glm::vec3(0.258, 0.16, 0.117))
    };

    vector<unsigned int> indices =
    {
        0, 1, 2 
        
    };

    CreateMesh("beak", vertices_beak, indices);
    CreateMesh("body", vertices_body, indices);
    CreateMesh("left", vertices_left, indices);
    CreateMesh("right", vertices_right, indices);

    Mesh* head = object2D::CreateCircle("head", glm::vec3(90, 0, 1), 30, glm::vec3(0.062, 0.29, 0.125));
    AddMeshToList(head);

    //LIVES
    if (lives >= 1) {
        Mesh* life1 = object2D::CreateCircle("life1", glm::vec3(0, 0, 2), 12.5, glm::vec3(1, 0, 0));
        AddMeshToList(life1);
    }
    if (lives >= 2) {
        Mesh* life2 = object2D::CreateCircle("life2", glm::vec3(0, 0, 2), 12.5, glm::vec3(1, 0, 0));
        AddMeshToList(life2);
    }
    if (lives == 3) {
        Mesh* life3 = object2D::CreateCircle("life3", glm::vec3(0, 0, 2), 12.5, glm::vec3(1, 0, 0));
        AddMeshToList(life3);
    }
    
    //BULLETS
    if (bullets >= 1) {
        Mesh* bullet1 = object2D::CreateRect("bullet1", glm::vec3(-112, 125, 2), 35, 10, glm::vec3(0, 1, 0), false);
        AddMeshToList(bullet1);
    }
    if (bullets >= 2) {
        Mesh* bullet2 = object2D::CreateRect("bullet2", glm::vec3(-112, 125, 2), 35, 10, glm::vec3(0, 1, 0), false);
        AddMeshToList(bullet2);
    }
    if (bullets == 3) {
        Mesh* bullet3 = object2D::CreateRect("bullet3", glm::vec3(-112, 125, 2), 35, 10, glm::vec3(0, 1, 0), false);
        AddMeshToList(bullet3);
    }

    //GRASS
    Mesh* grass = object2D::CreateRect("grass", glm::vec3(100, 100, 2), 150, 1280, glm::vec3(0.062, 0.5, 0.125));
    AddMeshToList(grass);

    //SCORE
    Mesh* wireframe = object2D::CreateRect("wireframe", glm::vec3(0, 0, 2), 50, 200, glm::vec3(1, 1, 1), false);
    AddMeshToList(wireframe);
    Mesh* scorebar = object2D::CreateRect("scorebar", glm::vec3(0, 0, 2), 49, 198, glm::vec3(0, 0, 1));
    AddMeshToList(scorebar);

    //HITBOX
    Mesh* hitbox = object2D::CreateRect("hitbox", glm::vec3(-150, -90, 1), 180, 300, glm::vec3(1, 1, 1), false);
    AddMeshToList(hitbox);
}


void Tema1::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();

    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{

    glClearColor(0.2, 0, 0.4, 1);

    if (ducky <= 0 && alive==0) {
        newDuck = 1;
        alive = 1;
        score++;
        bullets = 3;
        timeAlive = 0;
        speed += 1;
    }

    if (ducky >= 710 && escaped == 1) {
        newDuck = 1;
        lives--;
        escaped = 0;
        timeAlive = 0;
        bullets = 3;
    }

    if (alive == 1 && escaped == 0) {
        duckx += cos(duckAngle) * speed;
        ducky += sin(duckAngle) * speed;

        timeAlive += deltaTimeSeconds;
        if (timeAlive >= 5) {
            escaped = 1;
        }
    }


    if (alive == 0) ducky -= 8;
    if (escaped == 1 && alive==1) ducky += 5;

    if (duckx < -500 || duckx > 775) duckAngle = AI_MATH_PI - duckAngle;
    if (duckx < -500) {
        duckx = -500;
    }
    if (duckx > 775) {
        duckx = 775;
    }
    
    if (ducky < 0 || ducky > 715) duckAngle = -duckAngle;
    if (ducky < 0) {
        ducky = 0;
    }
    if (ducky > 715) {
        ducky = 715;
    }

    if (newDuck == 1) {
        newDuck = 0;
        duckx = rand()%800-300;
        ducky = 176;
        duckAngle = (rand() % 52) + 52;
        duckAngle /= 100;
        dir = rand() % 2;
        if (dir == 0) duckAngle += AI_MATH_PI/2;
    }

    if (score == 20) {
        exit(0);
    }

    glm::ivec2 resolution = window->GetResolution();
    
    rot += deltaTimeSeconds;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duckx, ducky);
    modelMatrix *= transform2D::Rotate(duckAngle);

    if (alive == 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(duckx, ducky);
        modelMatrix *= transform2D::Rotate(3 * AI_MATH_PI / 2);
        
    }
    
    if (escaped == 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(duckx, ducky);
        modelMatrix *= transform2D::Rotate(AI_MATH_PI / 2);

    }  

    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["hitbox"], shaders["VertexColor"], modelMatrix);

    if (escaped == 0 && alive == 1) {
        if (angularStep >= AI_MATH_PI / 6) h = -1;
        else if (angularStep <= 0) h = 1;
        if (deltaTimeSeconds < 0.25) angularStep += h * deltaTimeSeconds * AI_MATH_PI;
    }
    

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duckx, ducky);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Rotate(duckAngle);

    if (alive == 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(duckx, ducky);
        modelMatrix *= transform2D::Rotate(3 * AI_MATH_PI / 2);

        
    }
    
    if (escaped == 1) {
        modelMatrix = glm::mat3(1);
        if (angularStep >= AI_MATH_PI / 6) h = -1;
        else if (angularStep <= 0) h = 1;
        if (deltaTimeSeconds < 0.25) angularStep += h * deltaTimeSeconds * AI_MATH_PI;

        modelMatrix *= transform2D::Translate(duckx, ducky);
        modelMatrix *= transform2D::Rotate(AI_MATH_PI / 2);
        modelMatrix *= transform2D::Rotate(angularStep);

    
    }
    
    RenderMesh2D(meshes["right"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(duckx, ducky);
    modelMatrix *= transform2D::Rotate(-angularStep);
    modelMatrix *= transform2D::Rotate(duckAngle);
    if (alive == 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(duckx, ducky);
        modelMatrix *= transform2D::Rotate(3 * AI_MATH_PI / 2);

    }
    
    if (escaped == 1) {
        modelMatrix = glm::mat3(1);
        if (angularStep >= AI_MATH_PI / 6) h = -1;
        else if (angularStep <= 0) h = 1;
        if (deltaTimeSeconds < 0.25) angularStep += h * deltaTimeSeconds * AI_MATH_PI;

        modelMatrix *= transform2D::Translate(duckx, ducky);
        modelMatrix *= transform2D::Rotate(AI_MATH_PI / 2);
        modelMatrix *= transform2D::Rotate(-angularStep);

    }
    

    RenderMesh2D(meshes["left"], shaders["VertexColor"], modelMatrix);
    
    if (lives >= 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(550, 685);

        RenderMesh2D(meshes["life1"], shaders["VertexColor"], modelMatrix);
    }

    if (lives >= 2) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(590, 685);
        RenderMesh2D(meshes["life2"], shaders["VertexColor"], modelMatrix);
    }
    
    if (lives == 3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(630, 685);
        RenderMesh2D(meshes["life3"], shaders["VertexColor"], modelMatrix);
    }

    if (bullets >= 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(775, 545);
        RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], modelMatrix);
    }

    if (bullets >= 2) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(810, 545);
        RenderMesh2D(meshes["bullet2"], shaders["VertexColor"], modelMatrix);
    }

    if (bullets == 3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(845, 545);
        RenderMesh2D(meshes["bullet3"], shaders["VertexColor"], modelMatrix);
    }


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(540, 600);
    RenderMesh2D(meshes["wireframe"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(541, 601) * transform2D::Scale(0.05 * score, 1);
    RenderMesh2D(meshes["scorebar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(-600, -100);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);
    if (lives == 0) exit(0);
}


void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
}


void Tema1::OnKeyRelease(int key, int mods)
{
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    
    if (escaped == 0) {
        alive = 0;
    }
    bullets--;
    if (mouseX > duckx-150 && mouseX < duckx+150 && mouseY<720 - ducky - 90 && mouseY>720 - ducky - 90) {
        printf("%d, %d\n", mouseX, mouseY);
        
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

