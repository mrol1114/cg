#pragma once

#include <cstdlib>
#include <GLFW/glfw3.h>
#include <array>
#include <cmath>

struct Vertex
{
    float x;
    float y;
};

class BezierCurve
{
public:
    void Draw()
    {
        DrawBezierCurve();
        DrawControlPoints();
        DrawBezierLines();
    }

private:
    void DrawBezierCurve()
    {
        glLineWidth(2.0f);
        glColor3f(0, 0, 1);

        glBegin(GL_LINE_STRIP);
        for (float i = 0; i <= 100; i += 0.1)
        {
            float t = i / 100.0f;
            Vertex p = CalculateBezierVertexPosition(t);
            glVertex2f(p.x, p.y);
        }
        glEnd();
    }

    Vertex CalculateBezierVertexPosition(float t)
    {
        Vertex vertex;

        vertex.x = std::powf(1.0 - t, 3) * m_anchorVertecies[0].x 
            + 3 * std::powf(1.0 - t, 2) * t * m_anchorVertecies[1].x
            + 3 * (1.0 - t) * t * t * m_anchorVertecies[2].x
            + t * t * t * m_anchorVertecies[3].x;

        vertex.y = std::powf(1.0 - t, 3) * m_anchorVertecies[0].y
            + 3 * std::powf(1.0 - t, 2) * t * m_anchorVertecies[1].y
            + 3 * (1.0 - t) * t * t * m_anchorVertecies[2].y
            + t * t * t * m_anchorVertecies[3].y;

        return vertex;
    }

    void DrawControlPoints()
    {
        glPointSize(10);
        glColor3f(1, 0, 0);

        glBegin(GL_POINTS);
        for (const auto& point : m_anchorVertecies)
        {
            glVertex2f(point.x, point.y);
        }
        glEnd();
    }

    void DrawBezierLines()
    {
        glPointSize(10);
        glColor3f(1, 0, 0);

        glBegin(GL_LINES);
        for (size_t i = 0; i < m_anchorVertecies.size() - 1; i++)
        {
            glVertex2f(m_anchorVertecies[i].x, m_anchorVertecies[i].y);
            glVertex2f(m_anchorVertecies[i + 1].x, m_anchorVertecies[i + 1].y);
        }
        glEnd();
    }

    std::array<Vertex, 4> m_anchorVertecies = { Vertex{-0.5, - 0.5}, Vertex{-0.5, 0.5}, Vertex{0.5, 0.5}, Vertex{0.5, -0.5} };
};