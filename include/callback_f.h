#ifndef _CALLBACK_F_H_
#define _CALLBACK_F_H_

void draw(void);
void reshape(int width, int height);
void key_down(unsigned char key, int x, int y);
void special_key_down(int key, int x, int y);
void mouse_action(int button, int state, int x, int y);
void mouse_motion(int x, int y);

#endif