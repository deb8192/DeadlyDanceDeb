#include "pruebaOpengl.hpp"

pruebaOpengl::pruebaOpengl()
{

}

void pruebaOpengl::crearVentana()
{
    GLFWwindow* window;
    
    
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "no se puede inicializar glfw" << std::endl;
    }   

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Prueba", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}