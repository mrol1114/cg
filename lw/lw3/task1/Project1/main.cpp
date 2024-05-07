#include <math.h>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Parabolla", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1, 1, 1);

        glPushMatrix();
        glBegin(GL_LINE_STRIP);
        for (float x = -2; x < 3; x += 0.1) {
            float y = x*x - 3*x - 8;
            glVertex2f(x / 20, y / 20);
        }
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glBegin(GL_LINE_STRIP);

        glEnd();
        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}