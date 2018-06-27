#ifndef _GEOMETRY_F_H_
#define _GEOMETRY_F_H_

const GLfloat cube3fv[8][3] = {
								{ -0.5f, -0.5f,  0.5f },
								{  0.5f, -0.5f,  0.5f },
								{  0.5f,  0.5f,  0.5f },
								{ -0.5f,  0.5f,  0.5f },
								{  0.5f, -0.5f, -0.5f },
								{ -0.5f, -0.5f, -0.5f },
								{ -0.5f,  0.5f, -0.5f },
								{  0.5f,  0.5f, -0.5f }
							};

void crtajKocku(float x, float y, float z, float a);

#endif