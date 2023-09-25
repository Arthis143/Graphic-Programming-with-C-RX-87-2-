
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

	glVertex3f(1.82333, 6.93069, -2.05428);
	glVertex3f(1.72206, 13.4897, -2.05396);
	glVertex3f(1.77636, 13.4897, 1.26853);
	glVertex3f(1.87763, 6.93069, -1.2682);

	glEnd();
}

void robotShoulderTop() {

	//Top of the shoulder
	glBegin(GL_QUADS);

	glVertex3f(1.78392, 13.3975, 1.23897);
	glVertex3f(1.78392, 12.4975, 1.23897);
	glVertex3f(-1.84343, 12.4975, 1.25047);
	glVertex3f(-1.84343, 13.3975, 1.25047);

	glVertex3f(-1.84343, 12.4975, 1.25047);
	glVertex3f(-1.84343, 13.3975, 1.25047);
	glVertex3f(-1.89677, 13.3975, -2.01295);
	glVertex3f(1.73058, 13.3975, -2.02446);

	glVertex3f(-1.89677, 13.3975, -2.01295);
	glVertex3f(1.73058, 13.3975, -2.02446);
	glVertex3f(1.73058, 12.4975, -2.02446);
	glVertex3f(-1.89677, 12.4975, -2.01295);

	glVertex3f(1.73058, 12.4975, -2.02446);
	glVertex3f(-1.89677, 12.4975, -2.01295);
	glVertex3f(1.78392, 12.4975, 1.23897);
	glVertex3f(-1.84343, 12.4975, 1.25047);

	glEnd();
	
	//middle content of shoulder
	glBegin(GL_QUADS);
	glVertex3f(2.46632, 12.9292, 1.06623);
	glVertex3f(2.46632, 7.51214, 1.06623);
	glVertex3f(-2.24513, 7.51214, 1.08117);
	glVertex3f(-2.24513, 12.9292, 1.08117);

	glVertex3f(2.46632, 7.51214, 1.06623);
	glVertex3f(2.42886, 7.51214, -1.22552);
	glVertex3f(-2.28258, 7.51214, -1.21058);
	glVertex3f(-2.24513, 7.51214, 1.08117);

	glVertex3f(2.42886, 7.51214, -1.22552);
	glVertex3f(2.42886, 12.9292, -1.22552);
	glVertex3f(-2.28258, 12.9292, -1.21058);
	glVertex3f(-2.28258, 12.9292, -1.21058);
	glEnd();
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

void drawCubes(float p1[3], float p2[3], float p3[3], float p4[3], float p5[3], float p6[3], float p7[3], float p8[3]) {

	glBegin(GL_QUADS);

	glVertex3f(p1[0], p1[1], p1[2]);
	glVertex3f(p2[0], p2[1], p2[2]);
	glVertex3f(p3[0], p3[1], p3[2]);
	glVertex3f(p4[0], p4[1], p4[2]);

	glVertex3f(p1[0], p1[1], p1[2]);
	glVertex3f(p3[0], p3[1], p3[2]);
	glVertex3f(p8[0], p8[1], p8[2]);
	glVertex3f(p7[0], p7[1], p7[2]);

	glVertex3f(p5[0], p5[1], p5[2]);
	glVertex3f(p6[0], p6[1], p6[2]);
	glVertex3f(p7[0], p7[1], p7[2]);
	glVertex3f(p8[0], p8[1], p8[2]);

	glVertex3f(p1[0], p1[1], p1[2]);
	glVertex3f(p2[0], p2[1], p2[2]);
	glVertex3f(p6[0], p6[1], p6[2]);
	glVertex3f(p7[0], p7[1], p7[2]);

	glVertex3f(p2[0], p2[1], p2[2]);
	glVertex3f(p4[0], p4[1], p4[2]);
	glVertex3f(p5[0], p5[1], p5[2]);
	glVertex3f(p6[0], p6[1], p6[2]);

	glVertex3f(p3[0], p3[1], p3[2]);
	glVertex3f(p4[0], p4[1], p4[2]);
	glVertex3f(p5[0], p5[1], p5[2]);
	glVertex3f(p8[0], p8[1], p8[2]);

	glEnd();
}

void robotShoulder() {

	robotShoulderTrape();

	robotShoulderTop();

	glLoadIdentity();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(3.7273,0,0);
	robotShoulderTrape();
	glPopMatrix();
}

void robotArm() {

	glBegin(GL_QUADS);

	glVertex3f(2.14879, 7.29255, 0.821653); //左上
	glVertex3f(2.12163, 7.29255, -0.839863);//右上
	glVertex3f(2.14879, 2.61422, 0.821653);
	glVertex3f(2.12163, 2.64763, -0.839863);

	glVertex3f(-2.11795, 7.29255, -0.826418);//右下
	glVertex3f(-2.09079, 7.29255, 0.835099);//左下
	glVertex3f(-2.11795, 2.59365, -0.826418);
	glVertex3f(-2.09079, 2.59365, 0.835099);

	glVertex3f(2.14879, 7.29255, 0.821653); //左上
	glVertex3f(-2.09079, 7.29255, 0.835099);//左下
	glVertex3f(-2.09079, 2.59365, 0.835099);
	glVertex3f(2.14879, 2.61422, 0.821653);

	glVertex3f(2.12163, 7.29255, -0.839863);//右上
	glVertex3f(-2.11795, 7.29255, -0.826418);//右下
	glVertex3f(2.12163, 2.64763, -0.839863);
	glVertex3f(-2.11795, 2.59365, -0.826418);

	glEnd();

	float p1[] = {2.14879, 2.61422, 0.821653};
	float p2[] = { 2.12163, 2.64763, -0.839863 };
	float p3[] = { 1.64183, 0.655484, 0.823261 };
	float p4[] = { 2.1286, -1.80793, -0.413613 };
	float p5[] = { -1.64081, 0.78915, -0.827931 };
	float p6[] = { -2.08813, 2.61422, -0.826512 };
	float p7[] = { -2.05991, 2.61659, 0.835001 };
	float p8[] = { -1.58563, 0.771583, 0.781361 };

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	float p1[] = { 2.14244, 1.78141, 0.433236 };
	float p2[] = { 2.1286, 1.78141, -0.413613 };
	float p3[] = { 2.14244, -1.80793, 0.433236 };
	float p4[] = { 1.76378, 0.822567, -0.838728 };
	float p5[] = { -2.11098, -1.80793, -0.400168 };
	float p6[] = { -2.11098, 1.78141, -0.400168 };
	float p7[] = { -2.09714, 1.78141, 0.446681 };
	float p8[] = { -2.09714, -1.80793, 0.446681 };

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	float p1[] = { 1.7655, -0.572684, 0.8861 };
	float p2[] = { 2.1286, 1.78141, -0.413613 };
	float p3[] = { 2.14244, -1.80793, 0.433236 };
	float p4[] = { 1.76378, 0.822567, -0.838728 };
	float p5[] = { -2.11098, -1.80793, -0.400168 };
	float p6[] = { -2.11098, 1.78141, -0.400168 };
	float p7[] = { -2.09714, 1.78141, 0.446681 };
	float p8[] = { -2.09714, -1.80793, 0.446681 };

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);


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

	//gluPerspective(20.0, 1.0, -1.0, 4.0);
	//glFrustum(-20.0, 20.0, -20.0, 20.0, pNear, pFar);
	glOrtho(-20.0, 20.0, -20.0, 20.0, pNear, pFar);
}

void display()
{
	clearColor();

	projection();

	glMatrixMode(GL_MODELVIEW);						/* Refer to modelview matrix */
	glLoadIdentity();
	glTranslatef(tx, 0.0f, tz);						/* Translate for modelview */
	glColor3f(1,1,1);

	//drawCube(1, 1, 1);
	robotArm();

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