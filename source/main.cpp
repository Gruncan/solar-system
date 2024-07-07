#include "GLFW/glfw3.h"
#include <string>

#include "core/util/console_handler.h"


int main(int argc, char* argv[])
{
    bool startConsole = false;
    if (argc == 2)
        if(strcmp(argv[1], "debug") == 0)
            startConsole = true;


    // Initialize the library
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }


    // Make the window's context current
    glfwMakeContextCurrent(window);

    using namespace SolarSystem::Core;
    CConsoleHandler* consoleHandler = CConsoleHandler::get_instance();

    // TODO move this into start somewhere..
    std::thread t1([&] {consoleHandler->start(startConsole);});

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        consoleHandler->log("Test");

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    t1.join();
    consoleHandler->stop();
    return 0;
}

