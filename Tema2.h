#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/Tema2_camera.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:

        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Tema2();
        ~Tema2();

        void Init() override;

    private:

        void FrameStart() override;
        void DrawTrack();
        void CreateCars();
        void CreateTree(float x, float z, int i);
        void CreateTrees();
        void CreateGrass();
        void CreateSky();
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void RenderScene();
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
        float area(glm::vec2 a, glm::vec2 b, glm::vec2 c);
        int isOnTrack(float x, float z);
        int isCollision(glm::vec3 car, glm::vec3 obstacle);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        implemented::Camera* camera;
        implemented::Camera* camera2;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        // TODO(student): If you need any other class variables, define them here.
        float left, right, bottom, top, zNear, zFar;
        float carAngle;
        ViewportArea miniViewportArea;
        Mesh* trunks[50];
        Mesh* leaves[50];
        Mesh* track;
        Mesh* car;
        Mesh* sky;
        Mesh* grass;
        Mesh* obstacle[3];
        glm::vec3 traseu[3][22];
        float m[3];
        glm::vec3 v[3];
        glm::vec3 H[3];
        int contor[3];
        float obsAngle[3];
        int shouldIstop1;
        int shouldIstop2;
        int shouldIstop3;
        int shouldIstop;
        float timer;
        int start[3];
    };
}   // namespace m1