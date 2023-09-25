
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float tx = 0.0f, tz = 0.0f, tSpeed = 1.0f;		/* Translate for modelview */
float ptx = 0.0f, pty = 0.0f, ptSpeed = 0.1f;	/* Translate for projection */
float pry = 0.0f, prSpeed = 1.0f;
float pNear = -20.0f, pFar = 20.0f;				/* Perspective near and far */

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		case VK_UP:
			if (tz > pNear)
				tz -= tSpeed;
			break;

		case VK_DOWN:
			if (tz < pFar)
				tz += tSpeed;
			break;

		case VK_LEFT:
			tx -= tSpeed;
			break;

		case VK_RIGHT:
			tx += tSpeed;
			break;

		case 'A':
			ptx -= ptSpeed;
			break;

		case 'D':
			ptx += ptSpeed;
			break;

		case 'L':
			pry += prSpeed;
			break;

		case 'R':
			pry -= prSpeed;
			break;
		}
		break;
		

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void robotShoulderTrape() {
	glBegin(GL_QUADS);

	//外侧正面
	glVertex3f(2.91676, 7.59454, 1.02144);
	glVertex3f(2.8088, 12.8828, 0.985533);
	glVertex3f(2.81498, 12.8598, -1.75675);
	glVertex3f(2.89683, 7.52409, -1.7381);

	//正面右侧斜面
	glVertex3f(2.89683, 7.52409, -1.7381);
	glVertex3f(2.81498, 12.8598, -1.75675);
	glVertex3f(1.72206, 13.4897, -2.05396);
	glVertex3f(1.82333, 6.93069, -2.05428);

	//正面上侧斜面
	glVertex3f(2.81498, 12.8598, -1.75675);
	glVertex3f(1.72206, 13.4897, -2.05396);
	glVertex3f(1.77636, 13.4897, 1.26853);
	glVertex3f(2.8088, 12.8828, 0.985533);

	//正面左侧斜面
	glVertex3f(2.8088, 12.8828, 0.985533);
	glVertex3f(1.77636, 13.4897, 1.26853);
	glVertex3f(1.87763, 6.93069, 1.2682);
	glVertex3f(2.91676, 7.59454, 1.02144);

	//正面下侧斜面
	glVertex3f(1.87763, 6.93069, 1.2682);
	glVertex3f(2.91676, 7.59454, 1.02144);
	glVertex3f(2.89683, 7.52409, -1.7381);
	glVertex3f(1.82333, 6.93069, -2.05428);

	glEnd;
}

void drawCube(float len, float h, float d)
{
	/* Face 1: Bottom */
	glBegin(GL_LINE_LOOP);

	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(0.0f, 0.0f, d);			/* Point 1: Top left */
	glVertex3f(len, 0.0f, d);			/* Point 2: Top right */
	glVertex3f(len, 0.0f, 0.0f);			/* Point 3: Bottom right */
	glVertex3f(0.0f, 0.0f, 0.0f);			/* Point 4: Bottom left */

	glEnd();

	/* Face 2: Left */
	glBegin(GL_LINE_LOOP);

	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(0.0f, 0.0f, 0.0f);			/* Point 1: Bottom right */
	glVertex3f(0.0f, h, 0.0f);			/* Point 2: Bottom left */
	glVertex3f(0.0f, h, d);			/* Point 3: Top left */
	glVertex3f(0.0f, 0.0f, d);			/* Point 4: Top right */

	glEnd();

	/* Face 3: Front */
	glBegin(GL_LINE_LOOP);

	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(0.0f, 0.0f, d);			/* Point 1: Bottom left */
	glVertex3f(0.0f, h, d);			/* Point 2: Top left */
	glVertex3f(len, h, d);			/* Point 3: Top right */
	glVertex3f(len, 0.0f, d);			/* Point 4: Bottom right */

	glEnd();

	/* Face 4: Right */
	glBegin(GL_LINE_LOOP);

	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(len, 0.0f, d);			/* Point 1: Top left */
	glVertex3f(len, h, d);			/* Point 2: Top right */
	glVertex3f(len, h, 0.0f);			/* Point 3: Bottom right */
	glVertex3f(len, 0.0f, 0.0f);			/* Point 4: Bottom left */

	glEnd();

	/* Face 5: Back */
	glBegin(GL_LINE_LOOP);

	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(len, 0.0f, 0.0f);			/* Point 1: Top right */
	glVertex3f(0.0f, 0.0f, 0.0f);			/* Point 2: Top left */
	glVertex3f(0.0f, h, 0.0f);			/* Point 3: Bottom left */
	glVertex3f(len, h, 0.0f);			/* Point 3: Bottom right */

	glEnd();

	/* Face 6: Top */
	glBegin(GL_LINE_LOOP);

	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(len, h, 0.0f);			/* Point 1: Bottom left */
	glVertex3f(0.0f, h, 0.0f);			/* Point 2: Bottom right */
	glVertex3f(0.0f, h, d);			/* Point 3: Top right */
	glVertex3f(len, h, d);			/* Point 4: Top left */

	glEnd();
}

void robotShoulder() {

	robotShoulderTrape();

	glLoadIdentity();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(3.7273,0,0);
	glPopMatrix();


}

void clearColor()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void projection()
{
	/* Projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();						/* Reset the projection matrix */
	glTranslatef(ptx, pty, 0.0f);			/* Translation along X and Y axist*/
	glRotatef(pry, 0.0f, 1.0f, 0.0f);

	//glFrustum(-20.0, 20.0, -20.0, 20.0, pNear, pFar);
	glOrtho(-30.0, 30.0, -30.0, 30.0, pNear, pFar);
}

void display()
{
	clearColor();

	projection();

	glMatrixMode(GL_MODELVIEW);						/* Refer to modelview matrix */
	glLoadIdentity();
	glTranslatef(tx, 0.0f, tz);						/* Translate for modelview */
	glColor3f(1,1,1);

	drawCube(1, 1, 1);
	robotShoulderTrape();

	glFlush();
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------