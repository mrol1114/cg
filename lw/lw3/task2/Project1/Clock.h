#pragma once

#include <math.h>
#include <string>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>

class Clock
{
public:
	void Draw()
	{
        SYSTEMTIME st;
        GetLocalTime(&st);

        DrawClockMarks();
        // вынести в перемнные
        DrawTimeHand(-st.wSecond * SECOND_HAND_MARKER_ANGLE, SECOND_HAND_HEIGHT, SECOND_HAND_WIDTH);
        DrawTimeHand(-st.wMinute * MINUTE_HAND_MARKER_ANGLE, MINUTE_HAND_HEIGHT, MINUTE_HAND_WIDTH);
        DrawTimeHand(CalculateHourHandAngle(st), HOUR_HAND_HEIGHT, HOUR_HAND_WIDTH);
	}

private:
    void DrawClockMarks()
    {
        for (int i = 0; i <= 12; i++)
        {
            glPushMatrix();
            glTranslated(0, 0, 0);
            glRotated(i * HOUR_HAND_MARKER_ANGLE, 0, 0, 1);

            glLineWidth(CLOCK_MARK_WIDTH);

            glBegin(GL_LINES);
            glVertex2d(0, 0.8);
            glVertex2d(0, 1);
            glEnd();

            glPopMatrix();
        }
    }

    void DrawTimeHand(double angle, double height, float width)
    {
        glPushMatrix();
        glTranslated(0, 0, 0);
        glRotated(angle, 0, 0, 1);

        glLineWidth(width);

        glBegin(GL_LINES);
        glVertex2d(0, 0);
        glVertex2d(0, height);
        glEnd();
        glPopMatrix();
    }

    float CalculateHourHandAngle(const SYSTEMTIME& st)
    {
        return - HOUR_HAND_MARKER_ANGLE * st.wHour - st.wMinute * 0.5;
    }

    inline static float SECOND_HAND_HEIGHT = 0.7;
    inline static float MINUTE_HAND_HEIGHT = 0.6;
    inline static float HOUR_HAND_HEIGHT = 0.5;

    inline static float SECOND_HAND_WIDTH = 3;
    inline static float MINUTE_HAND_WIDTH = 4;
    inline static float HOUR_HAND_WIDTH = 6;
    inline static float CLOCK_MARK_WIDTH = 4;

    inline static float SECOND_HAND_MARKER_ANGLE = 6;
    inline static float MINUTE_HAND_MARKER_ANGLE = 6;
    inline static float HOUR_HAND_MARKER_ANGLE = 30;
};