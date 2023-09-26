
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float tx = 0.0f, tz = 0.0f, tSpeed = 1.0f;		/* Translate for modelview */
float ptx = 0.0f, pty = 0.0f, ptSpeed = 0.1f;	/* Translate for projection */
float pry = 0.0f, prSpeed = 1.0f;
float pNear = 1.0f, pFar = 10.0f;				/* Perspective near and far */
float x[3];
float p1[3], p2[3], p3[3], p4[3], p5[3], p6[3], p7[3], p8[3];

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
void drawCubes(float p1[3], float p2[3], float p3[3], float p4[3], float p5[3], float p6[3], float p7[3], float p8[3]) {

	glBegin(GL_QUADS);

	glVertex3f(p1[0], p1[1], p1[2]);
	glVertex3f(p2[0], p2[1], p2[2]);
	glVertex3f(p3[0], p3[1], p3[2]);
	glVertex3f(p4[0], p4[1], p4[2]);

	glVertex3f(p5[0], p5[1], p5[2]);
	glVertex3f(p6[0], p6[1], p6[2]);
	glVertex3f(p7[0], p7[1], p7[2]);
	glVertex3f(p8[0], p8[1], p8[2]);

	glVertex3f(p3[0], p3[1], p3[2]);
	glVertex3f(p4[0], p4[1], p4[2]);
	glVertex3f(p8[0], p8[1], p8[2]);
	glVertex3f(p7[0], p7[1], p7[2]);

	glVertex3f(p3[0], p3[1], p3[2]);
	glVertex3f(p2[0], p2[1], p2[2]);
	glVertex3f(p6[0], p6[1], p6[2]);
	glVertex3f(p7[0], p7[1], p7[2]);

	glVertex3f(p2[0], p2[1], p2[2]);
	glVertex3f(p1[0], p1[1], p1[2]);
	glVertex3f(p5[0], p5[1], p5[2]);
	glVertex3f(p6[0], p6[1], p6[2]);

	glVertex3f(p4[0], p4[1], p4[2]);
	glVertex3f(p1[0], p1[1], p1[2]);
	glVertex3f(p5[0], p5[1], p5[2]);
	glVertex3f(p8[0], p8[1], p8[2]);

	glEnd();
}

void AssignCoo(float array[3], float x, float y, float z) {
	array[0] = x;
	array[1] = y;
	array[2] = z;
}

void robotSwordhandle() {
	glColor3f(0.5, 0.5, 0.5);
	//sword handle
	AssignCoo(p1, 4.1366, -1.49571, -1);
	AssignCoo(p2, -1.41167, -1.49571,-1);
	AssignCoo(p3, -1.41167, -1.56273, -1);
	AssignCoo(p4, 4.1366, -1.56273, -1);
	AssignCoo(p5, 4.1366, -1.49571, 1);
	AssignCoo(p6, -1.41167, -1.49571, 1);
	AssignCoo(p7, -1.41167, -1.56273, 1);
	AssignCoo(p8, 4.1366, -1.56273, 1);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 4.03623, -1.0726, -0.563555);
	AssignCoo(p2, 2.93743, -1.07289, -0.563555);
	AssignCoo(p3, 3.00574, -1.50329, -0.563555);
	AssignCoo(p4, 4.10455, -1.503, -0.563555);
	AssignCoo(p5, 4.03623, -1.0726, 0.563556);
	AssignCoo(p6, 2.93743, -1.07289, 0.563556);
	AssignCoo(p7, 3.00574, -1.50329, 0.563556);
	AssignCoo(p8, 4.10455, -1.503, 0.563556);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 4.1366, -1.00933, -1);
	AssignCoo(p2, -1.41167, -1.00933, -1);
	AssignCoo(p3, -1.41167, -1.07635, -1);
	AssignCoo(p4, 4.1366, -1.07635, -1);
	AssignCoo(p5, 4.1366, -1.00933, 1);
	AssignCoo(p6, -1.41167, -1.00933, 1);
	AssignCoo(p7, -1.41167, -1.07635, 1);
	AssignCoo(p8, 4.1366, -1.07635, 1);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 3.14271, -0.946185, -1);
	AssignCoo(p2, -0.352612, -0.946185, -1);
	AssignCoo(p3, -0.346618, -1.0598, -1);
	AssignCoo(p4, 3.14271, -1.05971, -1);
	AssignCoo(p5, 3.14271, -0.946185, 1);
	AssignCoo(p6, -0.352613, -0.946185, 1);
	AssignCoo(p7, -0.356403, -1.05846, 1);
	AssignCoo(p8, 3.14271, -1.05971, 1);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 5.0679, -0.961365, -0.521471);
	AssignCoo(p2, 3.14271, -0.946185, -1);
	AssignCoo(p3, 3.14271, -1.05971, -1);
	AssignCoo(p4, 5.0679, -1.0593, -1.0022);
	AssignCoo(p5, 5.0679, -0.960029, 0.565138);
	AssignCoo(p6, 3.14271, -0.946185, 1);
	AssignCoo(p7, 3.14271, -1.05971, 1);
	AssignCoo(p8, 5.0679, -1.0593, 0.997797);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -0.352612, -0.946185, -1);
	AssignCoo(p2, -2.24262, -0.959106, -0.567342);
	AssignCoo(p3, -2.24262, -1.05838, -1);
	AssignCoo(p4, -0.346618, -1.0598, -1);
	AssignCoo(p5, -0.352613, -0.946185, 1);
	AssignCoo(p6, -2.24262, -0.960442, 0.519268);
	AssignCoo(p7, -2.24262, -1.05838, 1);
	AssignCoo(p8, -0.356403, -1.05846, 1);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//sword handle extend
	AssignCoo(p1, 1.75502, -0.316029, -1);
	AssignCoo(p2, -0.927876, -0.231378, -1);
	AssignCoo(p3, -0.927876, -0.979766, -1);
	AssignCoo(p4, 1.76714, -0.979766, -1);
	AssignCoo(p5, 1.73079, -0.318594, 1);
	AssignCoo(p6, -0.927876, -0.231378, 1);
	AssignCoo(p7, -0.927876, -0.979766, 1);
	AssignCoo(p8, 1.76714, -0.979766, 1);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotSwordBlade() {
	glColor3f(0, 1, 1);
	//sword blade left
	AssignCoo(p1, 2.92367, 0.999431, -0.015655);
	AssignCoo(p2, 1, 1, -1);
	AssignCoo(p3, 1, -1, -1);
	AssignCoo(p4, 2.91532, -1, -0.01524);
	AssignCoo(p5, 2.92367, 0.999431, -0.015655);
	AssignCoo(p6, 1, 1, 1);
	AssignCoo(p7, 1, -1, 1);
	AssignCoo(p8, 2.91532, -1, -0.01524);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//sword blade right
	AssignCoo(p1, 1, 1, -1);
	AssignCoo(p2, -1.03566, 0.999983, -0.024917);
	AssignCoo(p3, -0.96648, -1, -0.004507);
	AssignCoo(p4, 1, -1, -1);
	AssignCoo(p5, 1, 1, 1);
	AssignCoo(p6, -1.03566, 0.999983, -0.024917);
	AssignCoo(p7, -0.96648, -1, -0.004507);
	AssignCoo(p8, 1, -1, 1);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//sword sharp point left
	AssignCoo(p1, 0.942348, 1.1135, 0.00179);
	AssignCoo(p2, 0.942348, 1.1135, 0.00179);
	AssignCoo(p3, 0.9318, 0.999983, -1.01309);
	AssignCoo(p4, 2.92367, 0.999431, -0.015655);
	AssignCoo(p5, 0.942348, 1.1135, 0.00179);
	AssignCoo(p6, 0.942348, 1.1135, 0.00179);
	AssignCoo(p7, 1, 1, 1);
	AssignCoo(p8, 2.92367, 0.999431, -0.015655);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//sword sharp point left
	AssignCoo(p1, 0.942348, 1.1135, 0.00179);
	AssignCoo(p2, 0.942348, 1.1135, 0.00179);
	AssignCoo(p3, -1.03566, 0.999983, -0.024917);
	AssignCoo(p4, 0.9318, 0.999983, -1.01309);
	AssignCoo(p5, 0.942348, 1.1135, 0.00179);
	AssignCoo(p6, 0.942348, 1.1135, 0.00179);
	AssignCoo(p7, -1.03566, 0.999983, -0.024917);
	AssignCoo(p8, 1, 1, 1);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotSheildStar() {
	glColor3f(1, 1, 0);
	//star top
	AssignCoo(p1, 5.21452, -3.93078, 0.379473);
	AssignCoo(p2, 5.21452, -3.93078, 0.379473);
	AssignCoo(p3, 5.19338, -8.39247, 0.90944);
	AssignCoo(p4, 5.19338, -8.39247, 0.90944);
	AssignCoo(p5, 5.21452, -3.93078, 0.379473);
	AssignCoo(p6, 5.21452, -3.93078, 0.379473);
	AssignCoo(p7, 6.41944, -8.34672, 0.379473);
	AssignCoo(p8, 3.946, -8.34672, 0.379473);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//star bottom
	AssignCoo(p1, 5.19338, -8.39247, 0.90944);
	AssignCoo(p2, 5.19338, -8.39247, 0.90944);
	AssignCoo(p3, 5.42321, -14.3822, 0.351127);
	AssignCoo(p4, 5.42321, -14.3822, 0.351127);
	AssignCoo(p5, 3.64639, -8.52911, 0.351127);
	AssignCoo(p6, 6.77338, -8.50378, 0.351127);
	AssignCoo(p7, 5.42321, -14.3822, 0.351127);
	AssignCoo(p8, 5.42321, -14.3822, 0.351127);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//star left
	AssignCoo(p1, -2.25114, -8.60466, 0.36994);
	AssignCoo(p2, 5.19338, -8.39247, 0.90944);
	AssignCoo(p3, 5.19338, -8.39247, 0.90944);
	AssignCoo(p4, -2.25114, -8.60466, 0.36994);
	AssignCoo(p5, -2.25114, -8.60466, 0.36994);
	AssignCoo(p6, 5.47357, -7.93352, 0.36994);
	AssignCoo(p7, 5.52314, -9.00392, 0.36994);
	AssignCoo(p8, -2.25114, -8.60466, 0.36994);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//star right
	AssignCoo(p1, 5.19338, -8.39247, 0.90944);
	AssignCoo(p2, 12.7446, -8.36711, 0.364191);
	AssignCoo(p3, 12.7446, -8.36711, 0.364191);
	AssignCoo(p4, 5.19338, -8.39247, 0.90944);
	AssignCoo(p5, 5.0765, -7.91642, 0.36994);
	AssignCoo(p6, 12.7446, -8.36711, 0.364191);
	AssignCoo(p7, 12.7446, -8.36711, 0.364191);
	AssignCoo(p8, 5.14118, -8.98667, 0.36994);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotSheildInner() {
	//inner sheild top part
	glColor3f(1, 0, 0);
	AssignCoo(p1, -1.32236, 9.84181, 0.409807);
	AssignCoo(p2, 11.8563, 9.86458, 0.409807);
	AssignCoo(p3, 14.0655, 0.051611, 0.409807);
	AssignCoo(p4, -3.74197, 0.074381, 0.409807);
	AssignCoo(p5, -4.16278, 9.81904, -1.59019);
	AssignCoo(p6, 14.4337, 9.84181, -1.59019);
	AssignCoo(p7, 16.3799, 0.051611, -1.59019);
	AssignCoo(p8, -7.11602, 0.082658, -1.83611);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//inner sheild bottom part
	AssignCoo(p1, -3.74197, 0.074381, 0.409807);
	AssignCoo(p2, 14.0655, 0.051611, 0.409807);
	AssignCoo(p3, 10.6023, -15.5141, 0.410095);
	AssignCoo(p4, 0.081041, -15.4813, 0.410095);
	AssignCoo(p5, -7.11602, 0.082658, -1.83611);
	AssignCoo(p6, 16.3799, 0.051611, -1.59019);
	AssignCoo(p7, 12.5717, -15.4813, -1.5899);
	AssignCoo(p8, -2.34278, -15.4813, -1.5899);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotSheildOutter() {
	glColor3f(0.4, 0.4, 0.4);
	//outter sheild top part
	AssignCoo(p1, -1.92759, 10.8513, 0.163893);
	AssignCoo(p2, 12.3574, 10.8764, 0.163893);
	AssignCoo(p3, 14.752, 0.082658, 0.163893);
	AssignCoo(p4, -4.87705, 0.033821, 0.136858);
	AssignCoo(p5, -5.00644, 10.8263, -1.83611);
	AssignCoo(p6, 15.1511, 10.8513, -1.83611);
	AssignCoo(p7, 17.2607, 0.082658, -1.83611);
	AssignCoo(p8, -7.20403, 0.033821, -1.86314);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//outter sheild bottom part
	AssignCoo(p1, -4.87705, 0.033821, 0.136858);
	AssignCoo(p2, 14.752, 0.082658, 0.163893);
	AssignCoo(p3, 10.9387, -16.228, 0.136858);
	AssignCoo(p4, -0.469466, -16.1937, 0.136858);
	AssignCoo(p5, -7.20403, 0.033821, -1.86314);
	AssignCoo(p6, 17.2607, 0.082658, -1.83611);
	AssignCoo(p7, 13.074, -16.1937, -1.86314);
	AssignCoo(p8, -3.09759, -16.1937, -1.86314);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotShoulderTrape() {

	float p1[] = { 2.8088, 12.8828, 0.985533 };
	float p2[] = { 2.81498, 12.8598, -1.75675 };
	float p3[] = { 2.89683, 7.52409, -1.7381 };
	float p4[] = { 2.91676, 7.59454, 1.02144 };
	float p5[] = { 1.77636, 13.4897, 1.26853 };
	float p6[] = { 1.72206, 13.4897, -2.05396 };
	float p7[] = { 1.82333, 6.93069, -2.05428 };
	float p8[] = { 1.87763, 6.93069, 1.2682 };

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

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

void robotThigh() {
	glColor3f(0.6, 0.6, 0.6);
	//top part
	AssignCoo(p1, -7.98572, 1.56141, 0.981337);
	AssignCoo(p2, -7.96253, 1.58652, -1.02846);
	AssignCoo(p3, -2.00744, 1.58617, -1.00072);
	AssignCoo(p4, -2.05546, 1.56114, 1.00319);
	AssignCoo(p5, -7.98572, -1.44363, 0.962677);
	AssignCoo(p6, -7.96253, -1.41852, -1.04712);
	AssignCoo(p7, -2.00744, -1.41887, -1.01938);
	AssignCoo(p8, -2.07273, -1.44403, 0.995344);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
	glColor3f(1, 1, 1);
	//bottom connect with knee
	AssignCoo(p1, -2.05546, 1.56114, 1.00319);
	AssignCoo(p2, -2.00744, 1.58617, -1.00072);
	AssignCoo(p3, -0.598124, 1.58455, -0.870883);
	AssignCoo(p4, -0.588871, 1.56284, 0.867124);
	AssignCoo(p5, -2.07273, -1.44403, 0.995344);
	AssignCoo(p6, -2.00744, -1.41887, -1.01938);
	AssignCoo(p7, -0.551954, -1.42157, -0.803264);
	AssignCoo(p8, -0.559141, -0.559141, 0.851124);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotCalf() {
	glColor3f(0.6, 0.6, 0.6);
	//top calf connect with knee
	AssignCoo(p1, 0.669485, 1.56378, 0.791335);
	AssignCoo(p2, 0.670384, 1.58331, -0.772017);
	AssignCoo(p3, 2.43441, 1.58619, -1.00261);
	AssignCoo(p4, 2.41121, 1.56109, 1.00719);
	AssignCoo(p5, 0.618189, -1.44111, 0.761545);
	AssignCoo(p6, 0.670133, -1.422, -0.768895);
	AssignCoo(p7, 2.50539, -1.41897, -1.01085);
	AssignCoo(p8, 2.44816, -1.44381, 0.977009);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//bottom calf
	glColor3f(0.8, 0.8, 0.8);
	AssignCoo(p1, 2.41121, 1.56109, 1.00719);
	AssignCoo(p2, 2.43441, 1.58619, -1.00261);
	AssignCoo(p3, 11.0545, 1.58569, -0.962452);
	AssignCoo(p4, 11.0313, 1.56059, 1.04735);
	AssignCoo(p5, 2.44816, -1.44381, 0.977009);
	AssignCoo(p6, 2.50539, -1.41897, -1.01085);
	AssignCoo(p7, 11.0545, -1.41935, -0.981111);
	AssignCoo(p8, 11.0313, -1.44445, 1.02869);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotKnee() {

	//inner knee
	glColor3f(0.3, 0.3, 0.3);
	AssignCoo(p1, -2.64185, 1.67429, 0.619857);
	AssignCoo(p2, -2.62696, 1.6904, -0.670088);
	AssignCoo(p3, 3.32813, 1.69005, -0.642344);
	AssignCoo(p4, 3.31324, 1.67394, 0.647601);
	AssignCoo(p5, -2.64185, 0.005882, 0.609497);
	AssignCoo(p6, -2.62696, 0.021996, -0.680448);
	AssignCoo(p7, 3.32813, 0.021649, -0.652704);
	AssignCoo(p8, 3.31324, 0.005536, 0.637241);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
	glColor3f(1, 0, 0);
	//outter knee
	AssignCoo(p1, -2.142, 2.54471, 0.387958);
	AssignCoo(p2, -2.15029, 2.55429, -0.379301);
	AssignCoo(p3, 2.98104, 2.27485, -0.26999);
	AssignCoo(p4, 2.97445, 2.28316, 0.301249);
	AssignCoo(p5, -2.64185, 1.67429, 0.619857);
	AssignCoo(p6, -2.62696, 1.6904, -0.670088);
	AssignCoo(p7, 3.49727, 1.56154, -0.446292);
	AssignCoo(p8, 3.52145, 1.55059, 0.429957);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotLeg() {
	//heel 
	glColor3f(1, 0, 0);
	AssignCoo(p1, 9.25282, 2.56476, 1.31175);
	AssignCoo(p2, 9.2826, 2.59699, -1.26852);
	AssignCoo(p3, 10.5477, 3.02497, -1.25997);
	AssignCoo(p4, 10.518, 2.99274, 1.3203);
	AssignCoo(p5, 10.8366, -1.23713, 1.29552);
	AssignCoo(p6, 10.8663, -1.2049, -1.28475);
	AssignCoo(p7, 12.1315, -0.776927, -1.2762);
	AssignCoo(p8, 12.1017, -0.809158, 1.30407);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//shoe top front
	glColor3f(1, 1, 1);
	AssignCoo(p1, 12.4659, 4.80661, 0.566337);
	AssignCoo(p2, 12.4782, 4.80505, -0.501516);
	AssignCoo(p3, 12.4782, 4.80505, -0.501516);
	AssignCoo(p4, 12.4659, 4.80661, 0.566337);
	AssignCoo(p5, 10.3105, 0.516495, 1.47986);
	AssignCoo(p6, 10.3443, 0.553061, -1.44734);
	AssignCoo(p7, 12.4983, 0.552935, -1.4373);
	AssignCoo(p8, 12.4548, 0.72872, 1.49699);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//shoe bottom front
	glColor3f(1, 0, 0);
	AssignCoo(p1, 12.4659, 4.80661, 0.566337);
	AssignCoo(p2, 12.4782, 4.80505, -0.501516);
	AssignCoo(p3, 13.7276, 5.26961, -0.713431);
	AssignCoo(p4, 13.7106, 5.24377, 0.758701);
	AssignCoo(p5, 12.4548, 0.72872, 1.49699);
	AssignCoo(p6, 12.4983, 0.552935, -1.4373);
	AssignCoo(p7, 13.7352, 0.764948, -1.40323);
	AssignCoo(p8, 13.7017, 0.728647, 1.5028);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//shoe bottom back
	glColor3f(0, 1, 1);
	AssignCoo(p1, 12.4548, 0.72872, 1.49699);
	AssignCoo(p2, 12.4983, 0.552935, -1.4373);
	AssignCoo(p3, 13.7352, 0.764948, -1.40323);
	AssignCoo(p4, 13.7017, 0.728647, 1.5028);
	AssignCoo(p5, 12.4568, -2.40453, 1.30553);
	AssignCoo(p6, 12.4864, -2.37253, -1.25652);
	AssignCoo(p7, 13.7332, -2.3726, -1.25071);
	AssignCoo(p8, 13.7037, -2.40461, 1.31134);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//shoe top back
	glColor3f(1, 1, 0);
	AssignCoo(p1, 11.6576, 2.12367, 1.10147);
	AssignCoo(p2, 11.673, 2.139, -1.06889);
	AssignCoo(p3, 13.827, 2.13888, -1.05885);
	AssignCoo(p4, 13.8059, 2.11051, 1.21146);
	AssignCoo(p5, 11.6458, -2.09687, 1.25803);
	AssignCoo(p6, 11.673, -2.06748, -1.09501);
	AssignCoo(p7, 13.827, -2.06761, -1.08497);
	AssignCoo(p8, 13.7999, -2.097, 1.26806);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
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

	robotShoulderTop();

	glLoadIdentity();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(3.7273,0,0);
	robotShoulderTrape();
	glPopMatrix();
}

void robotArm() {

	//robotShoulderTrape();
	//robotShoulderTop();

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

	AssignCoo(p1, 2.14244, 1.78141, 0.433236);
	AssignCoo(p2, 2.1286, 1.78141, -0.413613);
	AssignCoo(p3, 2.14244, -1.80793, 0.433236);
	AssignCoo(p4, 1.76378, 0.822567, -0.838728);
	AssignCoo(p5, -2.11098, -1.80793, -0.400168);
	AssignCoo(p6, - 2.11098, 1.78141, -0.400168);
	AssignCoo(p7, - 2.09714, 1.78141, 0.446681);
	AssignCoo(p8, - 2.09714, -1.80793, 0.446681);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 1.7655, -0.572684, 0.8861 );
	AssignCoo(p2, 1.85708, -0.495331, -0.902255 );
	AssignCoo(p3, 2.31787, -2.98535, 0.891951 );
	AssignCoo(p4, 2.28827, -3.02403, -0.918827 );
	AssignCoo(p5, -2.2869, -3.02403, -0.889113 );
	AssignCoo(p6, -1.61385, -0.495331, -0.891248 );
	AssignCoo(p7, -1.6364, -0.495331, 0.896889 );
	AssignCoo(p8, -2.25768, -3.02403, 0.898859 );

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 2.31774, -3.00746, 0.884349 );
	AssignCoo(p2, 2.28852, -3.00746, -0.903623 );
	AssignCoo(p3, 2.31774, -11.7438, 0.884349 );
	AssignCoo(p4, 2.28852, -11.7438, -0.903623 );
	AssignCoo(p5, -2.2869, -11.7438, -0.889113 );
	AssignCoo(p6, -2.2869, -3.00746, -0.889113 );
	AssignCoo(p7, -2.25768, -3.00746, 0.898859 );
	AssignCoo(p8, -2.25768, -11.7438, 0.898859 );

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

	//gluPerspective(45.0f, 1.0f, -1.0, 4.0);
	//glFrustum(-30.0, 30.0, -30.0, 30.0, pNear, pFar);
	glOrtho(-20.0, 20.0, -20.0, 20.0, -20, 20);
}

void display()
{
	clearColor();

	projection();

	glMatrixMode(GL_MODELVIEW);						/* Refer to modelview matrix */
	glLoadIdentity();

	glTranslatef(tx, 0.0f, tz);						/* Translate for modelview */
	//glRotatef(pry, 0, 1, 0);
	
	glColor3f(1,1,1);

	/*drawCube(1, 1, 1);
	glPushMatrix();
	glRotatef(269.59, 0, 1, 0);
	glScalef(0.530, 0.473, 1.204);
	glColor3f(1, 1, 1);
	robotShoulder();
	glColor3f(1, 1, 0);
	robotArm();
	glPopMatrix();*/

	//glPushMatrix();
	//glScalef(0.377375, 0.760072, 1.0);
	//robotSheildStar();
	//robotSheildInner();
	//robotSheildOutter();
	//glPopMatrix();

	//glPushMatrix();
	//glRotatef(180, 0, 1, 0);
	//glScalef(0.336975, 8.25759, 0.382484);
	//robotSwordhandle();
	//robotSwordBlade();
	//glPopMatrix();

	//glPushMatrix();
	//glRotatef(-89.5799, 0, 0, 1);
	//glRotatef(89.4954, 1, 0, 0);
	//glScalef(0.768733, 0.852985, 1.20982);
	//robotThigh();
	//robotCalf();
	//robotKnee();
	//robotLeg();
	//glPopMatrix();

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