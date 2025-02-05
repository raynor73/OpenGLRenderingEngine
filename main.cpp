// OpenGLRenderingEngine.cpp : Defines the entry point for the application.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "framework.h"
#include "main.h"
#include <PlatformDependent/Windows/Utils.h>
#include "Resource.h"
#include <PlatformDependent/Windows/WindowsLogger.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "Research/Demo1.h"

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

    Research::Demo1 demo1{ window };

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    int windowWidth, windowHeight;

    while (!glfwWindowShouldClose(window)) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /* Render here */
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        demo1.update();

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
