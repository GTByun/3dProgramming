#pragma once

class FireBall
{
public:
    FireBall()
    {
        r1 = 0.05f;
        r2 = 0.08f;
        r3 = 0.11f;
        r4 = 0.14f;
        rot = 0;
    }
    ~FireBall() {}

    float r1;
    float r2;
    float r3;
    float r4;
    float rot;

    void draw()
    {
        glLineWidth(7.0f);

        DrawCircleNew(0.25f, 0.0f, 1.0f, 0.5f, r4, r3);

        DrawCircleNew(0.75f, 0.25f, 1.0f, 0.75f, r3, r2);

        DrawCircleNew(1.0f, 0.75f, 1.0f, 0.9f, r2, r1);

        rot++;
    }
private:
    float CarX(float rad)
    {
        return glm::sin(glm::radians(rad));
    }

    float CarY(float rad)
    {
        return glm::cos(glm::radians(rad));
    }

    float SetRand()
    {
        return (float)rand() / RAND_MAX;
    }

    void BasePos(float min, float max, float theta, float* x, float* y)
    {
        float r = SetRand() * (max - min) + min;
        *x = CarX(theta) * r;
        *y = CarY(theta) * r;
    }

    void Rot(float x, float y, float* rx, float* ry)
    {
        *rx = x * glm::cos(rot) - y * glm::sin(rot);
        *ry = x * glm::sin(rot) + y * glm::cos(rot);
    }

    void DrawCircle(float max, float min)
    {
        float x, y;
        float rx, ry;
        for (float theta = 0; theta < 361; theta++)
        {
            BasePos(min, max, theta, &x, &y);

            Rot(x, y, &rx, &ry);
            glVertex3f(rx, ry, 0.0f);
        }
    }

    void DrawCircleNew(float gMax, float gMin, float aMax, float aMin, float max, float min)
    {
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(SetRand() * 0.25f + 0.75f, SetRand() * (gMax - gMin) + gMin, SetRand() * 0.25f, SetRand() * (aMax - aMin) + aMin);
        glVertex3f(0.0f, 0.0f, 0.0f);
        DrawCircle(max, min);
        glEnd();
    }
};