#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdlib.h>
#include "object.hpp"

#pragma comment(lib, "OpenGL32")


GLFWwindow* window;
FireBall* f;
float hexDown = 0.6f;
float hexW = 0.5f, hexH = 0.2f;
float tower = 0.2f;
int towerCount = 8;

void Init();
void Update();
void Release();

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void);

float SetRand()
{
    return (float)rand() / RAND_MAX;
}

void SetRandColor(float r, float g, float b, float a)
{
    glColor4f(SetRand() * r, SetRand() * g, SetRand() * b, SetRand() * a);
}

float CarX(float rad)
{
    return glm::sin(glm::radians(rad));
}

float CarY(float rad)
{
    return glm::cos(glm::radians(rad));
}

void DrawHex(float plus, int repeat)
{
    float x, y;
    glBegin(GL_LINE_LOOP);
    for (float i = 0; i < repeat; i++)
    {
        float theta = i * plus;
        x = CarX(theta) * hexW;
        y = CarY(theta) * hexH - hexDown;
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();
}

void DrawPillar(float min, float max)
{
    float x1, x2;
    float y1, y2;
    float h;

    for (float i = 0; i < (int)(max - min); i++)
    {
        float theta = i + min;
        if (theta < 0)
        {
            theta += 360;
        }
        x1 = CarX(theta) * hexW;
        x2 = CarX(theta + 1) * hexW;
        y1 = CarY(theta) * hexH - hexDown;
        y2 = CarY(theta + 1) * hexH - hexDown;
        h = rand() % 8;
        int cons = 0;
        glBegin(GL_TRIANGLE_STRIP);
        while (cons < h)
        {
            SetRandColor(1.0f, 1.0f, 1.0f, 1.0f);
            glVertex3f(x1, y1 + tower * cons, 1.0f);
            SetRandColor(1.0f, 1.0f, 1.0f, 1.0f);
            glVertex3f(x2, y2 + tower * cons, 1.0f);
            cons++;
        }
        glEnd();
    }
}

void Init()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    f = new FireBall();
}

void Release()
{
    delete(f);

    glfwDestroyWindow(window);
    glfwTerminate();
}
void Update()
{
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        ////90도와 같이 각도로 연산하고 싶으면
        ////glm의 삼각함수는 radian 형식으로 입력을 받기 때문에 변환해서 넣어주어야한다.
        //glm::sin(glm::radians(90.0));  

        glClearColor(.0f, 0.0f, 0.0f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        glLineWidth(7.0f);

        DrawHex(1.0f, 360);

        DrawHex(144.0f, 5);

        DrawPillar(-90.0f, 90.0f);

        f->draw();

        DrawPillar(90.0f, 270.0f);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
    Init();
    Update();
    Release();

    exit(EXIT_SUCCESS);
}