#pragma once
#include "Telo.h"
#include "SvaTela.h"
#include <math.h>

class Lopta : public Telo
{
private:
	float R;
public:
	Lopta(Boja b, float x, float y, float z, float R) : Telo(b, x, y, z, R)
	{
		this->R = R;
	}

	void ctraj()
	{
		int p = SvaTela::getPrec();
		int n = SvaTela::getVerticalPrec();
		glPushMatrix();
		{
			glTranslatef(x, y, z);
			glScalef(R, R, R);
			glRotatef(45, 1, 0, 0);
			glRotatef(Rx, 1, 0, 0);
			glRotatef(Ry, 0, 1, 0);
			glRotatef(Rz, 0, 0, 1);
			double color_r1 = colors3fv[b][3][0];
			double color_r2 = colors3fv[b][2][0];
			double color_g1 = colors3fv[b][3][1];
			double color_g2 = colors3fv[b][2][1];
			double color_b1 = colors3fv[b][3][2];
			double color_b2 = colors3fv[b][2][2];

			// Up
			glColor3f(color_r1, color_g1, color_b1);
			glBegin(GL_TRIANGLE_FAN);
			{
				glVertex3f(0, 0.5, 0);
				double rUp = cos(DEG_TO_RAD(90 - 180 / n)) / 2;
				double hUp = sin(DEG_TO_RAD(90 - 180 / n)) / 2;
				int theta;
				for(theta = 0; theta <= 360; theta += 360 / p)
				{
					glVertex3f(rUp*cos(DEG_TO_RAD(theta)), hUp, rUp*sin(DEG_TO_RAD(theta)));
				}
				if(theta != 360) glVertex3f(rUp*cos(DEG_TO_RAD(360)), hUp, rUp*sin(DEG_TO_RAD(360)));
			}glEnd();

			// Middle
			double d_color_r = (color_r2 - color_r1) / (n - 1);
			double d_color_g = (color_g2 - color_g1) / (n - 1);
			double d_color_b = (color_b2 - color_b1) / (n - 1);
			for(int i = 0; i < n - 2; i++)
			{
				double rUp = cos(DEG_TO_RAD(90 - (i + 1) * 180 / n)) / 2;
				double rDown = cos(DEG_TO_RAD(90 - (i + 2) * 180 / n)) / 2;
				double hUp = sin(DEG_TO_RAD(90 - (i + 1) * 180 / n)) / 2;
				double hDown = sin(DEG_TO_RAD(90 - (i + 2) * 180 / n)) / 2;

				double curr_r = color_r1 + d_color_r*(i + 1);
				double curr_g = color_g1 + d_color_g*(i + 1);
				double curr_b = color_b1 + d_color_b*(i + 1);
				glColor3f(curr_r, curr_g, curr_b);
				glBegin(GL_QUAD_STRIP);
				{
					int theta;
					for(theta = 0; theta <= 360; theta += 360 / p)
					{
						glVertex3f(rUp*cos(DEG_TO_RAD(theta)), hUp, rUp*sin(DEG_TO_RAD(theta)));
						glVertex3f(rDown*cos(DEG_TO_RAD(theta)), hDown, rDown*sin(DEG_TO_RAD(theta)));
					}
					if(theta != 360)
					{
						glVertex3f(rUp*cos(DEG_TO_RAD(360)), hUp, rUp*sin(DEG_TO_RAD(360)));
						glVertex3f(rDown*cos(DEG_TO_RAD(360)), hDown, rDown*sin(DEG_TO_RAD(360)));
					}
				}glEnd();
			}

			// Down
			glColor3f(color_r2, color_g2, color_b2);
			glBegin(GL_TRIANGLE_FAN);
			{
				glVertex3f(0, -0.5, 0);
				double rDown = cos(DEG_TO_RAD(90 - (n - 1) * 180 / n)) / 2;
				double hDown = sin(DEG_TO_RAD(90 - (n - 1) * 180 / n)) / 2;
				int theta;
				for(theta = 0; theta <= 360; theta += 360 / p)
				{
					glVertex3f(rDown*cos(DEG_TO_RAD(theta)), hDown, rDown*sin(DEG_TO_RAD(theta)));
				}
				if(theta != 360) glVertex3f(rDown*cos(DEG_TO_RAD(360)), hDown, rDown*sin(DEG_TO_RAD(360)));
			}glEnd();
		}glPopMatrix();
	}
};