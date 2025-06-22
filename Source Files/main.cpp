// main.cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "App.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1400, 800, "Traffic Simulation", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        if (app) app->camera.processMouse((float)xpos, (float)ypos);
        });


    App app;
	glfwSetWindowUserPointer(window, &app); 

    app.init();
    glewInit();

    float lastTime = (float)glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        float now = (float)glfwGetTime();
        float deltaTime = now - lastTime;
        lastTime = now;

        app.update(deltaTime);
        app.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
