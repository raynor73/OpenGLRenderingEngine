// OpenGLRenderingEngine.cpp : Defines the entry point for the application.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "framework.h"
#include "main.h"
#include <PlatformDependent/Windows/Utils.h>
#include "Resource.h"
#include <RenderingEngine/OpenGLRenderingEngine.h>
#include <PlatformDependent/Windows/WindowsLogger.h>
#include <Research/Mesh.h>
#include <Research/Transformation.h>
#include <Research/Material.h>
#include <Research/PerspectiveCamera.h>
#include <filesystem>
#include <PlatformDependent/Windows/WindowsReadOnlyFs.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "Research/BaseLight.h"
#include "Research/DirectionalLight.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

#define CONSOLE_BUFFER_SIZE 1024
#define INITIAL_WINDOW_WIDTH 1440
#define INITIAL_WINDOW_HEIGHT 900

using namespace PlatformDependent::Windows;
using namespace PlatformDependent::Windows::Utils;
using namespace RenderingEngine;
using namespace std;

static bool setupConsolse(HINSTANCE hInstance) {
    if (!createNewConsole(CONSOLE_BUFFER_SIZE)) {
        showDialog(
            getString(hInstance, IDS_GENERIC_ERROR_TITLE).get(),
            getString(hInstance, IDS_ERROR_OPENING_CONSOLE).get()
        );
        return false;
    }

    return true;
}

static void glfwError(int id, const char *description)
{
    std::cout << description << std::endl;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    if (!setupConsolse(hInstance)) {
        return EXIT_FAILURE;
    }

    L::setLogger(make_shared<WindowsLogger>());

    GLFWwindow* window;

    glfwSetErrorCallback(&glfwError);
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "OpenGL Rendering Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        showDialog(
            getString(hInstance, IDS_GENERIC_ERROR_TITLE).get(),
            getString(hInstance, IDS_ERROR_INITIALIZING_GLEW).get()
        );
        return -1;
    }

    auto openGLErrorDetector = make_shared<OpenGLErrorDetector>();
    auto readOnlyFs = make_shared<WindowsReadOnlyFs>();
    auto shaderSourceLoader = make_shared<OpenGLShaderSourceLoader>(readOnlyFs);
    auto shaderSourcePreprocessor = make_shared<OpenGLShaderSourcePreprocessor>(shaderSourceLoader);
    auto shaderRepository = make_shared<OpenGLShadersRepository>(openGLErrorDetector);

    OpenGLRenderingEngine openGLRenderingEngine(
        openGLErrorDetector,
        shaderRepository,
        shaderSourcePreprocessor
    );
    Research::Mesh mesh {
        {
            Research::Vertex { { 0, 0.5, 0 }, { 0, 0, 1 }, { 0, 0 } },
            Research::Vertex { { 0.5, -0.5, 0 }, { 0, 0, 1 }, { 0, 0 } },
            Research::Vertex { { -0.5, -0.5, 0 }, { 0, 0, 1 }, { 0, 0 } }
        },
        { 2, 1, 0 }
    };
    auto transformation = make_shared<Research::Transformation>();
    transformation->setPosition(glm::vec3(0, 0, -1));
    auto material = make_shared<Research::Material>(glm::vec4(1));
    openGLRenderingEngine.createRenderableMesh(mesh, transformation, material);
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    Research::PerspectiveCamera camera { 
        0.1f,
        1000,
        90,
        uint32_t(windowWidth), 
        uint32_t(windowHeight)
    };
    Light ambient = make_shared<Research::BaseLight>(glm::vec3(1), 0.1);
    auto lights = vector<Light>();
    auto directionalLight = make_shared<Research::DirectionalLight>(glm::vec3(0, 1, 0), 1, glm::vec3(-1, 0, 0));
    lights.push_back(directionalLight);

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    float yAngle = 0.0f;
    float xAngle = 0.0f;
    float zAngle = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //ImGui::ShowDemoWindow();
        ImGui::Begin("Hello, world!");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::SliderAngle("Y angle", &yAngle);
        ImGui::SliderAngle("X angle", &xAngle);
        ImGui::SliderAngle("Z angle", &zAngle);
        ImGui::End();

        /* Render here */
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        camera.setViewportSize(windowWidth, windowHeight);
        transformation->setRotation(glm::quat(glm::vec3(xAngle, yAngle, zAngle)));
        openGLRenderingEngine.render(
            camera,
            ambient,
            lights
        );

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
       
    
    return 0;
}
