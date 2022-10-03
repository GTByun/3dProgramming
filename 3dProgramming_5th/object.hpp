#pragma once

class FireBall
{
public:
    FireBall() {}
    ~FireBall() {}

    void draw()
    {
        glLineWidth(7.0f);
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        float x, y;
        for (float theta = 0; theta < 361; theta++)
        {
            x = glm::sin(glm::radians(theta)) * 0.5;
            y = glm::cos(glm::radians(theta)) * 0.5;

            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            glVertex3f(x, y, 0.0f);

        }
        glEnd();
    }
};