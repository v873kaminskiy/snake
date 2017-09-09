#include <time.h>
#include <GLUT/glut.h>
#include <cstdlib>

int N = 30, M = 20, Scale = 25, dir, num = 4;

int w = Scale * N;
int h = Scale * M;

struct
{
	int x;
	int y;
} s[100];

class Fructs
{
	public:
		int x, y;

	void New()
	{
		x = rand() % N;
		y = rand() % M;
	}

	void DrawApple()
	{
		glColor3f(0.0, 1.0, 0.0);
		glRectf(x * Scale, y * Scale, (x + 1) * Scale, (y + 1) * Scale);
	}
} m[10];

void Tick()
{
	for (int i = num; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}
	if (dir == 0) s[0].y += 1;
	if (dir == 1) s[0].x -= 1;
	if (dir == 2) s[0].x += 1;
	if (dir == 3) s[0].y -= 1;

	for (int i = 0; i < 10; i++)
		if ((s[0].x == m[i].x) && (s[0].y == m[i].y))
		{
			num++;
			m[i].New();
		}

	if (s[0].x > N)
		dir = 1;
	if (s[0].x < 0)
		dir = 2;
	if (s[0].y > M)
		dir = 3;
	if (s[0].y < 0)
		dir = 0;
	
	for (int i = 1; i < num; i++)
		if (s[0].x == s[i].x && s[0].y == s[i].y)
			num = i;

}

void DrawSnake()
{
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < num; i++)
		glRectf(s[i].x * Scale, s[i].y * Scale, (s[i].x + 1) * Scale, (s[i].y + 1) * Scale);
}
void DrawField()
{
	glColor3f(0.0, 0.1, 0.0);
	glRectf(0,0,w,h);
	glColor3f(0.0, 0.8, 0.0);
	glBegin(GL_LINES);

	for (int i = 0; i <= w; i += Scale)
	{
		glVertex2f(i, 0); 
		glVertex2f(i,h);
	}
	for (int j = 0; j <= h; j += Scale)
	{
		glVertex2f(0, j); 
		glVertex2f(w,j);
	}
	glEnd();
}

void MyKeyboard(int key, int a, int b)
{
	switch(key)
	{
		case 101: if (dir != 3) dir = 0; break;
		case 102: if (dir != 1) dir = 2; break;
		case 100: if (dir != 2) dir = 1; break;
		case 103: if (dir != 0) dir = 3; break;
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawField();
	for (int i = 0; i < 10; i++)
		m[i].DrawApple();
	DrawSnake();
	glFlush();
}

void timer (int = 0)
{
	display();
	Tick();
	glutTimerFunc(50, timer, 0);
}

int main(int argc, char **argv)
{
	s[0].x = 10;
	s[0].y = 10;

	for (int i = 0; i < 10; i++)
		m[i].New();

	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (w, h);
	glutCreateWindow ("Test");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w+2, 0, h+2);
	glutDisplayFunc (display);
	glutTimerFunc(50, timer, 0);
	glutSpecialFunc(MyKeyboard);

	glutMainLoop();
}