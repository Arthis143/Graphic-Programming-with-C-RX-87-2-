
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

BITMAP BMP;							/* Bitmap structure */
HBITMAP hBMP = NULL;				/* Bitmap handle */

float tx = 0.0f, tz = 0.0f, tSpeed = 1.0f;		/* Translate for modelview */
float ptx = 0.0f, pty = 0.0f, ptSpeed = 0.1f;	/* Translate for projection */
float pry = 0.0f, prSpeed = 1.0f;
float pNear = 1.0f, pFar = 10.0f;				/* Perspective near and far */
float x[3];
float p1[3], p2[3], p3[3], p4[3], p5[3], p6[3], p7[3], p8[3];

/* Lighting vars */
bool isLightOn = false;
float tX = -0.8f, tY = 0.8f, tZ = 0.0f;
float lSpeed = 5.0f;

/* Ambient vars */
float amb[] = { 0.0f, 1.0f, 1.0f };			/* Ambient light - White */
float posA[] = { -10.0f, 10.0f, 10.0f };		/* Light position above sphere (Y = 0.8) */
float ambM[] = { 0.0f, 0.0f, 0.0f };		/* Ambient material - Blue */

/* Diffuse vars */
float dif[] = { 0.0f, 1.0f, 1.0f };			/* Diffuse light - White */
float posD[] = { -10.0f, 10.0f, 10.0f };		/* Light position right of sphere (X = 0.8) */
float difM[] = { 0.0f, 0.0f, 0.0f };		/* Diffuse material - Blue */


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

		case 'T':
			pry += prSpeed;
			break;

		case 'R':
			pry -= prSpeed;
			break;

		case VK_SPACE:					/* On or Off light */
			isLightOn = !isLightOn;
			break;

		case 'I':						/* Move light up */
			posA[1] += lSpeed;
			posD[1] += lSpeed;
			tY += lSpeed;
			break;

		case 'K':						/* Move light down */
			posA[1] -= lSpeed;
			posD[1] -= lSpeed;
			tY -= lSpeed;
			break;

		case 'J':						/* Move light left */
			posA[0] -= lSpeed;
			posD[0] -= lSpeed;
			tX -= lSpeed;
			break;

		case 'L':						/* Move light right */
			posA[0] += lSpeed;
			posD[0] += lSpeed;
			tX += lSpeed;
			break;

		case 'U':						/* Move light nearer */
			posA[2] -= lSpeed;
			posD[2] -= lSpeed;
			tZ -= lSpeed;
			break;

		case 'O':						/* Move light further */
			posA[2] += lSpeed;
			posD[2] += lSpeed;
			tZ += lSpeed;
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
GLuint loadTexture(LPCSTR filename)
{
	// Take from step 1
	GLuint texture = 0;					/* Texture name */

	// Step 3: Initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	// Step 4: Assign texture to polygon
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);

	return texture;
}

void drawCubes(float p1[3], float p2[3], float p3[3], float p4[3], float p5[3], float p6[3], float p7[3], float p8[3]) {

	glBegin(GL_QUADS);

	//FRONT-------------------------------------
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(p1[0], p1[1], p1[2]);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(p2[0], p2[1], p2[2]);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(p3[0], p3[1], p3[2]);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(p4[0], p4[1], p4[2]);

	glEnd();

	//BACK--------------------------------------
	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(p5[0], p5[1], p5[2]);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(p6[0], p6[1], p6[2]);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(p7[0], p7[1], p7[2]);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(p8[0], p8[1], p8[2]);

	glEnd();


	//
	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(p3[0], p3[1], p3[2]);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(p4[0], p4[1], p4[2]);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(p8[0], p8[1], p8[2]);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(p7[0], p7[1], p7[2]);

	glEnd();

	//
	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(p3[0], p3[1], p3[2]);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(p2[0], p2[1], p2[2]);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(p6[0], p6[1], p6[2]);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(p7[0], p7[1], p7[2]);

	glEnd();

	//
	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(p2[0], p2[1], p2[2]);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(p1[0], p1[1], p1[2]);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(p5[0], p5[1], p5[2]);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(p6[0], p6[1], p6[2]);

	glEnd();

	//
	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(p4[0], p4[1], p4[2]);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(p1[0], p1[1], p1[2]);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(p5[0], p5[1], p5[2]);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(p8[0], p8[1], p8[2]);

	glEnd();
}

void AssignCoo(float array[3], float x, float y, float z) {
	array[0] = x;
	array[1] = y;
	array[2] = z;
}

void drawCylinder(double br, double tr, double h)
{
	GLUquadricObj* cylinder = NULL;					/* Quadric obj pointer */
	cylinder = gluNewQuadric();						/* Create the quadric obj in the memory */

	//glLineWidth(3.0f);
	gluQuadricDrawStyle(cylinder, GLU_FILL);		/* Draw style - Line */
	gluQuadricTexture(cylinder, true);				/* Enable mapping */
	gluCylinder(cylinder, br, tr, h, 30, 30);		/* Draw sphere */

	gluDeleteQuadric(cylinder);
}

void drawDisk(double ir, double r, int h)
{
	GLUquadricObj* disk = NULL;					/* Quadric obj pointer */
	disk = gluNewQuadric();						/* Create the quadric obj in the memory */

	//glLineWidth(3.0f);
	gluQuadricDrawStyle(disk, GLU_FILL);		/* Draw style - Line */
	gluQuadricTexture(disk, true);				/* Enable mapping */
	gluDisk(disk, ir, r, h, 10);		/* Draw sphere */

	gluDeleteQuadric(disk);
}

void drawSphere(double radius)
{
	GLUquadricObj* sphere = NULL;					/* Quadric obj pointer */
	sphere = gluNewQuadric();						/* Create the quadric obj in the memory */

	glPointSize(3.0);
	//glLineWidth(3.0f);
	gluQuadricDrawStyle(sphere, GLU_FILL);			/* Draw style - Line */
	gluQuadricTexture(sphere, true);				/* Enable mapping */
	gluSphere(sphere, radius, 30, 30);				/* Draw sphere */

	gluDeleteQuadric(sphere);
}

//----------------ARM--------------------------------------------------

void robotShoulder() {

	//GLuint texture[1];

	AssignCoo(p1, 2.8088, 12.8828, 0.985533);
	AssignCoo(p2, 2.81498, 12.8598, -1.75675);
	AssignCoo(p3, 2.89683, 7.52409, -1.7381);
	AssignCoo(p4, 2.91676, 7.59454, 1.02144);
	AssignCoo(p5, 1.77636, 13.4897, 1.26853);
	AssignCoo(p6, 1.72206, 13.4897, -2.05396);
	AssignCoo(p7, 1.82333, 6.93069, -2.05428);
	AssignCoo(p8, 1.87763, 6.93069, 1.2682);

	//texture[0] = loadTexture("MetalBlack.bmp");
	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -1.84968, 13.4606, 1.28002);
	AssignCoo(p2, -1.90398, 13.4606, -2.04246);
	AssignCoo(p3, -1.90398, 6.9006, -2.04246);
	AssignCoo(p4, -1.84968, 6.9006, 1.28002);
	AssignCoo(p5, -2.90686, 12.817, 1.03991);
	AssignCoo(p6, -2.97604, 12.888, -1.71947);
	AssignCoo(p7, -2.97719, 7.55147, -1.73838);
	AssignCoo(p8, -2.88174, 7.52746, 1.00358);

	
	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 1.78392, 13.3975, 1.23897);
	AssignCoo(p2, 1.79624, 12.4975, 1.23893);
	AssignCoo(p3, -1.84343, 12.4975, 1.25047);
	AssignCoo(p4, -1.84343, 13.3975, 1.25047);
	AssignCoo(p5, 1.73058, 13.3975, -2.02446);
	AssignCoo(p6, 1.73058, 12.4975, -2.02446);
	AssignCoo(p7, -1.89677, 12.4975, -2.01295);
	AssignCoo(p8, -1.89677, 13.3975, -2.01295);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 2.46632, 7.51214, 1.06623);
	AssignCoo(p2, 2.46632, 12.9292, 1.23893);
	AssignCoo(p3, 2.42886, 12.9292, -1.22552);
	AssignCoo(p4, 2.42886, 7.51214, -1.22552);
	AssignCoo(p5, -2.24513, 7.51214, 1.08117);
	AssignCoo(p6, -2.24513, 12.9292, 1.08117);
	AssignCoo(p7, -2.28258, 12.9292, -1.21058);
	AssignCoo(p8, -2.28258, 7.51214, -1.21058);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//glDeleteTextures(1, &texture[0]);

	//glDisable(GL_TEXTURE_2D);

}

void robotUpperArm() {

	AssignCoo(p1, 2.12163, 2.59365, -0.839863);
	AssignCoo(p2, 2.12163, 7.29255, -0.839863);
	AssignCoo(p3, -2.11795, 7.29255, -0.826418);
	AssignCoo(p4, -2.11795, 2.59365, -0.826418);
	AssignCoo(p5, 2.14879, 2.59365, 0.821653);
	AssignCoo(p6, 2.14879, 7.29255, 0.821653);
	AssignCoo(p7, -2.09079, 7.29255, 0.835099);
	AssignCoo(p8, -2.09079, 2.59365, 0.835099);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 1.76378, 0.822567, -0.838728);
	AssignCoo(p2, 2.12163, 2.64763, -0.839863);
	AssignCoo(p3, -2.08813, 2.61422, -0.826512);
	AssignCoo(p4, -1.64081, 0.78915, -0.827931);
	AssignCoo(p5, 1.64183, 0.655484, 0.823261);
	AssignCoo(p6, 2.14879, 2.61422, 0.821653);
	AssignCoo(p7, -2.05991, 2.61659, 0.835001);
	AssignCoo(p8, -1.58563, 0.771583, 0.781361);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotBottomArm() {
	AssignCoo(p1, 1.7655, -0.572684, 0.8861);
	AssignCoo(p2, 1.85708, -0.495331, -0.902255);
	AssignCoo(p3, 2.28827, -3.02403, -0.918827);
	AssignCoo(p4, 2.31787, -2.98535, 0.891951);
	AssignCoo(p5, -1.6364, -0.495331, 0.896889);
	AssignCoo(p6, -1.61385, -0.495331, -0.891248);
	AssignCoo(p7, -2.2869, -3.02403, -0.889113);
	AssignCoo(p8, -2.25768, -3.02403, 0.898859);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 2.31774, -3.00746, 0.884349);
	AssignCoo(p2, 2.28852, -3.00746, -0.903623);
	AssignCoo(p3, 2.28852, -11.7438, -0.903623);
	AssignCoo(p4, 2.31774, -11.7438, 0.884349);
	AssignCoo(p5, -2.25768, -3.00746, 0.898859);
	AssignCoo(p6, -2.2869, -3.00746, -0.889113);
	AssignCoo(p7, -2.2869, -11.7438, -0.889113);
	AssignCoo(p8, -2.25768, -11.7438, 0.898859);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotArmJoint() {
	//joint
	AssignCoo(p1, 2.14244, -1.80793, 0.433236);
	AssignCoo(p2, 2.14244, 1.78141, 0.433236);
	AssignCoo(p3, 2.1286, 1.78141, -0.413613);
	AssignCoo(p4, 2.1286, -1.80793, -0.413613);
	AssignCoo(p5, -2.09714, -1.80793, 0.446681);
	AssignCoo(p6, -2.09714, 1.78141, 0.446681);
	AssignCoo(p7, -2.11098, 1.78141, -0.400168);
	AssignCoo(p8, -2.11098, -1.80793, -0.400168);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotInternalFinger() {

	AssignCoo(p1, 1.91196, -13.3001, 0.182404);
	AssignCoo(p2, 1.9066, -13.3001, -0.352363);
	AssignCoo(p3, 2.12669, -14.2899, -0.352791);
	AssignCoo(p4, 2.13204, -14.2899, 0.181977);
	AssignCoo(p5, 1.29414, -13.4726, 0.183604);
	AssignCoo(p6, 1.28878, -13.4726, -0.351163);
	AssignCoo(p7, 1.50886, -14.4624, -0.351591);
	AssignCoo(p8, 1.51422, -14.4624, 0.183177);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 1.38521, -15.7961, -0.305559);
	AssignCoo(p2, 1.38244, -14.776, -0.305554);
	AssignCoo(p3, 0.745734, -14.7782, -0.304318);
	AssignCoo(p4, 0.748509, -15.7982, -0.304322);
	AssignCoo(p5, 1.39057, -15.7961, 0.229209);
	AssignCoo(p6, 1.38779, -14.776, 0.229213);
	AssignCoo(p7, 0.751087, -14.7781, 0.23045);
	AssignCoo(p8, 0.753862, -15.7982, 0.230446);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 0.4104, -15.8634, -0.302357);
	AssignCoo(p2, 0.407625, -14.8434, -0.302353);
	AssignCoo(p3, -0.229079, -14.8455, -0.301116);
	AssignCoo(p4, -0.226305, -15.8656, -0.30112);
	AssignCoo(p5, 0.415753, -15.8634, 0.232411);
	AssignCoo(p6, 0.412978, -14.8434, 0.232415);
	AssignCoo(p7, -0.223726, -14.8455, 0.233652);
	AssignCoo(p8, -0.220952, -15.8656, 0.233647);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -0.567601, -15.7922, -0.303728);
	AssignCoo(p2, -0.570376, -14.7721, -0.303724);
	AssignCoo(p3, -1.20708, -14.7743, -0.302488);
	AssignCoo(p4, -1.20431, -15.7943, -0.302492);
	AssignCoo(p5, -0.562248, -15.7922, 0.231039);
	AssignCoo(p6, -0.565023, -14.7721, 0.231043);
	AssignCoo(p7, -1.20173, -14.7743, 0.23228);
	AssignCoo(p8, -1.19895, -15.7943, 0.232276);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -1.73259, -15.5528, -0.312587);
	AssignCoo(p2, -1.53018, -14.5583, -0.31298);
	AssignCoo(p3, -2.15095, -14.3996, -0.311774);
	AssignCoo(p4, -2.35336, -15.3942, -0.311381);
	AssignCoo(p5, -1.72723, -15.5528, 0.122181);
	AssignCoo(p6, -1.52483, -14.5583, 0.221788);
	AssignCoo(p7, -2.1456, -14.3996, 0.222993);
	AssignCoo(p8, -2.34801, -15.3942, 0.223386);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotOuterFinger() {
	AssignCoo(p1, 2.4322, -15.5781, -0.353384);
	AssignCoo(p2, 2.21212, -14.5883, -0.352957);
	AssignCoo(p3, 1.5943, -14.7608, -0.351757);
	AssignCoo(p4, 1.81438, -15.7506, -0.352184);
	AssignCoo(p5, 2.43756, -15.5781, 0.181384);
	AssignCoo(p6, 2.21748, -14.5883, 0.181811);
	AssignCoo(p7, 1.59966, -14.7608, 0.183011);
	AssignCoo(p8, 1.81974, -15.7506, 0.182584);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 1.43186, -17.0851, -0.305649);
	AssignCoo(p2, 1.42909, -16.0651, -0.305645);
	AssignCoo(p3, 0.792385, -16.0672, -0.304408);
	AssignCoo(p4, 0.795159, -17.0873, -0.304412);
	AssignCoo(p5, 1.43722, -17.0851, 0.229118);
	AssignCoo(p6, 1.43444, -16.065, 0.229123);
	AssignCoo(p7, 0.797738, -16.0672, 0.230359);
	AssignCoo(p8, 0.800512, -17.0873, 0.230355);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 0.428551, -17.2493, -0.302392);
	AssignCoo(p2, 0.425777, -16.2292, -0.302388);
	AssignCoo(p3, -0.210927, -16.2314, -0.301151);
	AssignCoo(p4, -0.208153, -17.2515, -0.301156);
	AssignCoo(p5, 0.433904, -17.2493, 0.232375);
	AssignCoo(p6, 0.43113, -16.2292, 0.23238);
	AssignCoo(p7, -0.205574, -16.2314, 0.233616);
	AssignCoo(p8, -0.2028, -17.2515, 0.233612);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -0.607021, -17.1621, -0.303652);
	AssignCoo(p2, -0.609796, -16.142, -0.303648);
	AssignCoo(p3, -1.2465, -16.1442, -0.302411);
	AssignCoo(p4, -1.24373, -17.1643, -0.302415);
	AssignCoo(p5, -0.601668, -17.1621, 0.231116);
	AssignCoo(p6, -0.604443, -16.142, 0.23112);
	AssignCoo(p7, -1.24115, -16.1442, 0.232357);
	AssignCoo(p8, -1.23837, -17.1643, 0.232353);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -2.01662, -16.8753, -0.312035);
	AssignCoo(p2, -1.81422, -15.8807, -0.312428);
	AssignCoo(p3, -2.43499, -15.7221, -0.311223);
	AssignCoo(p4, -2.63739, -16.7166, -0.31083);
	AssignCoo(p5, -2.01127, -16.8753, 0.222732);
	AssignCoo(p6, -1.80887, -15.8807, 0.222339);
	AssignCoo(p7, -2.42964, -15.7221, 0.223545);
	AssignCoo(p8, -2.63204, -16.7166, 0.223938);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

}

void robotHand() {
	AssignCoo(p1, 1.1334, -11.4834, 0.150552);
	AssignCoo(p2, 1.12804, -11.4834, -0.384215);
	AssignCoo(p3, 1.13586, -14.3592, -0.384227);
	AssignCoo(p4, 1.14122, -14.3592, 0.150541);
	AssignCoo(p5, -1.62891, -11.4929, 0.155918);
	AssignCoo(p6, -1.63426, -11.4929, -0.37885);
	AssignCoo(p7, -1.62644, -14.3686, -0.378862);
	AssignCoo(p8, -1.62109, -14.3686, 0.155906);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	robotInternalFinger();
	robotOuterFinger();
}

void ArmCombine() {

	/*GLuint texture;

	glEnable(GL_TEXTURE_2D);

	texture = loadTexture("SolidBlue.bmp");
	glBindTexture(GL_TEXTURE_2D, texture);*/

	glColor3f(0.5, 0.5, 0.5);
	robotShoulder();
	glColor3f(0.9, 0.9, 0.9);
	robotUpperArm();
	robotBottomArm();
	glColor3f(0.7, 0.7, 0.7);
	robotHand();
	glColor3f(1, 0, 0);
	robotArmJoint();

	/*glDeleteTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);*/

}

void robotDrawLeftArm() {

	glPushMatrix();
	glTranslatef(4.37942, 4.7356, -1.12552);
	glRotatef(3.93835, 0, 0, 1);
	glRotatef(269.588, 0, 1, 0);
	glScalef(0.530227, 0.473188, 1.20369);
	ArmCombine();
	glPopMatrix();

	/*glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(4.64937, -4.59912, -0.990852);
	drawSphere(1);
	glPopMatrix();*/

}

void robotDrawRightArm() {

	glPushMatrix();
	glTranslatef(-5.05678, 4.77922, -1.14512);
	glRotatef(-4.84058, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(0.530227, 0.473188, 1.20369);
	ArmCombine();
	glPopMatrix();

	/*glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(-4.71718, -4.55605, -1.27979);
	drawSphere(1);
	glPopMatrix();*/

}

//-------------BODY-----------------------------------------------------

void robotWaist() {
	AssignCoo(p1, -7.28359, -10.5932, -2.85121);
	AssignCoo(p2, -6.51775, -10.6435, -3.338);
	AssignCoo(p3, -6.51775, -6.43808, -3.35808);
	AssignCoo(p4, -7.28359, -6.38776, -2.87129);
	AssignCoo(p5, 2.00693, -10.5237, -2.17853);
	AssignCoo(p6, 2.77277, -10.574, -2.66532);
	AssignCoo(p7, 2.77277, -6.36855, -2.6854);
	AssignCoo(p8, 2.00693, -6.31823, -2.19861);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -7.29892, -6.76191, -2.85975);
	AssignCoo(p2, -6.53309, -6.81223, -3.34654);
	AssignCoo(p3, -6.53309, -2.60679, -3.36662);
	AssignCoo(p4, -7.29892, -2.55647, -2.87983);
	AssignCoo(p5, 1.99159, -6.69238, -2.18707);
	AssignCoo(p6, 2.75743, -6.7427, -2.67386);
	AssignCoo(p7, 2.75743, -2.53725, -2.69394);
	AssignCoo(p8, 1.99159, -2.48693, -2.20715);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 2.82281, -10.6286, -3.19386);
	AssignCoo(p2, 2.05697, -10.5783, -2.70707);
	AssignCoo(p3, 2.05697, -3.26075, -2.74201);
	AssignCoo(p4, 2.82281, -3.31107, -3.2288);
	AssignCoo(p5, -5.0646, -10.6877, -3.76495);
	AssignCoo(p6, -5.83043, -10.6373, -3.27816);
	AssignCoo(p7, -5.83043, -3.31979, -3.3131);
	AssignCoo(p8, -5.0646, -3.3701, -3.79989);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotChest() {
	AssignCoo(p1, -4.94173, -14.7844, -2.28549);
	AssignCoo(p2, -2.96968, -10.4568, -3.56027);
	AssignCoo(p3, -3.63444, -7.54747, -3.15141);
	AssignCoo(p4, -5.60648, -11.875, -1.87663);
	AssignCoo(p5, -1.48757, -14.7585, -2.03539);
	AssignCoo(p6, 0.484478, -10.431, -3.31017);
	AssignCoo(p7, -0.180274, -7.52162, -2.90132);
	AssignCoo(p8, -2.15232, -11.8491, -1.62653);

	glColor3f(1, 0, 0);
	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -11.2352, -10.3428, -1.26635);
	AssignCoo(p2, -8.68538, -10.6018, -2.93409);
	AssignCoo(p3, -8.68538, -6.39633, -2.95417);
	AssignCoo(p4, -11.3028, -6.22435, -1.29042);
	AssignCoo(p5, 0.581525, -10.2543, -0.410759);
	AssignCoo(p6, 3.26526, -10.5123, -2.06881);
	AssignCoo(p7, 3.26526, -6.30689, -2.08889);
	AssignCoo(p8, 0.647791, -6.13491, -0.425129);

	glColor3f(0.7, 0.7, 0.7);
	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 3.24992, -6.20225, -2.07963);
	AssignCoo(p2, 0.632452, -6.03027, -0.415874);
	AssignCoo(p3, 0.632452, -1.82483, -0.435954);
	AssignCoo(p4, 3.24992, -1.99681, -2.09971);
	AssignCoo(p5, -8.70072, -6.29169, -2.94492);
	AssignCoo(p6, -11.3182, -6.11972, -1.28116);
	AssignCoo(p7, -11.3182, -1.91427, -1.30124);
	AssignCoo(p8, -8.70072, -2.08625, -2.965);

	glColor3f(0.7, 0.7, 0.7);
	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);


	AssignCoo(p1, -9.86176, -12.8142, -2.12797);
	AssignCoo(p2, -8.61918, -10.5154, -2.92917);
	AssignCoo(p3, -9.40966 , -6.44314, -2.44591);
	AssignCoo(p4, -10.6522, -8.74192, -1.64471);
	AssignCoo(p5, 1.95494, -12.7258, -1.27238);
	AssignCoo(p6, 3.19752, -10.427, -2.07358);
	AssignCoo(p7, 2.40704, -6.3547, -1.59032);
	AssignCoo(p8, 1.16446, -8.65348, -0.789122);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -11.2352, -10.3428, -1.26635);
	AssignCoo(p2, -9.91984, -12.7518, -2.09134);
	AssignCoo(p3, -9.20199, -8.838, -2.56654);
	AssignCoo(p4, -10.5173, -6.42897, -1.74155);
	AssignCoo(p5, 0.581525, -10.2543, -0.410759);
	AssignCoo(p6, 1.89686, -12.6633, -1.23575);
	AssignCoo(p7, 2.61471, -8.74956, -1.71095);
	AssignCoo(p8, 1.29938, -6.34053, -0.885964);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotPelvic() {

	AssignCoo(p1, -6.95535, -15.2735, -4.08593);
	AssignCoo(p2, -2.96344, -15.2436, -3.7969);
	AssignCoo(p3, -1.61616, -15.3321, -4.65328);
	AssignCoo(p4, -5.60806, -15.362, -4.94232);
	AssignCoo(p5, -6.917, 0.260726, -4.18449);
	AssignCoo(p6, -2.9251, 0.290603, -3.89546);
	AssignCoo(p7, -1.57781, 0.202081, -4.75184);
	AssignCoo(p8, -5.56971, 0.172205, -5.04087);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 5.47889, 0.313533, -3.28744);
	AssignCoo(p2, 1.48699, 0.283657, -3.57647);
	AssignCoo(p3, 2.83428, 0.195135, -4.43286);
	AssignCoo(p4, 6.82618, 0.225011, -4.14382);
	AssignCoo(p5, 5.46611, -15.1824, -3.20532);
	AssignCoo(p6, 1.47421, -15.2123, -3.49436);
	AssignCoo(p7, 2.82149, -15.3008, -4.35074);
	AssignCoo(p8, 6.8134, -15.271, -4.06171);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//skirt正面
	AssignCoo(p1, -8.76721, -14.3925, -3.9698);
	AssignCoo(p2, -6.5741, -14.5317, -5.31648);
	AssignCoo(p3, -6.5741, -13.287, -5.32242);
	AssignCoo(p4, -8.76721, -13.1478, -3.97574);
	AssignCoo(p5, 6.54667, -14.2794, -2.87496);
	AssignCoo(p6, 8.83521, -14.4179, -4.2148);
	AssignCoo(p7, 8.83521, -13.1731, -4.22075);
	AssignCoo(p8, 6.54667, -13.0346, -2.8809);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -7.15918, -14.3826, -3.87372);
	AssignCoo(p2, -0.230355, -14.3666, -3.71864);
	AssignCoo(p3, 0.457916, -14.5129, -5.13397);
	AssignCoo(p4, -6.47091, -14.5289, -5.28905);
	AssignCoo(p5, -7.15918, -13.1379, -3.87966);
	AssignCoo(p6, -0.230355, -13.1218, -3.72459);
	AssignCoo(p7, 0.457916, -13.2681, -5.13991);
	AssignCoo(p8, -6.47091, -13.2842, -5.29499);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 8.77058, -14.3264, -4.22708);
	AssignCoo(p2, 2.80503, -14.4036, -4.97396);
	AssignCoo(p3, -0.783832, -14.2782, -3.76153);
	AssignCoo(p4, 5.18173, -14.201, -3.01465);
	AssignCoo(p5, 8.77058, -13.0816, -4.23302);
	AssignCoo(p6, 2.80503, -13.1588, -4.9799);
	AssignCoo(p7, -0.783832, -13.0335, -3.76747);
	AssignCoo(p8, 5.18173, -12.9563, -3.02059);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 2.7607, -15.392, -4.58805);
	AssignCoo(p2, -0.607578, -15.4172, -4.83193);
	AssignCoo(p3, 0.541169, -15.2461, -3.17724);
	AssignCoo(p4, -2.82711, -15.2713, -3.42112);
	AssignCoo(p5, 3.01633, 1.17842, -5.03424);
	AssignCoo(p6, 0.195579, 1.11316, -5.24802);
	AssignCoo(p7, 0.189511, 0.595354, -3.23374);
	AssignCoo(p8, -2.645, 0.57414, -3.43897);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//inside skirt
	AssignCoo(p1, -7.31011, -11.3732, -3.90899);
	AssignCoo(p2, -5.0213, -11.5236, -5.36384);
	AssignCoo(p3, -5.0213, -7.31812, -5.38392);
	AssignCoo(p4, -7.31011, -7.16773, -3.92907);
	AssignCoo(p5, 5.02497, -11.2809, -3.01587);
	AssignCoo(p6, 7.31378, -11.4312, -4.47072);
	AssignCoo(p7, 7.31378, -7.2258, -4.4908);
	AssignCoo(p8, 5.02497, -7.07541, -3.03595);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 7.32912, -7.17872, -4.50078);
	AssignCoo(p2, 5.04031 , -7.02833, -3.04593);
	AssignCoo(p3, 5.04031, -1.85, -3.07065);
	AssignCoo(p4, 7.32912, -2.00038, -4.52551);
	AssignCoo(p5, -5.00596, -7.27103, -5.3939);
	AssignCoo(p6, -7.29477, -7.12065, -3.93905);
	AssignCoo(p7, -7.29477, -1.94232, -3.96378);
	AssignCoo(p8, -5.00596, -2.0927, -5.41863);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//left side skirt
	AssignCoo(p1, -6.02264, -11.9098, -3.64055);
	AssignCoo(p2, -4.24058, -12.1036, -5.51492);
	AssignCoo(p3, -6.83873, -12.1153, -5.6286);
	AssignCoo(p4, -8.6208, -11.9216, -3.75424);
	AssignCoo(p5, -6.02264, -2.7535, -3.68427);
	AssignCoo(p6, -4.24058, -2.94725, -5.55864);
	AssignCoo(p7, -6.83873, -2.959, -5.67232);
	AssignCoo(p8, -8.6208, -2.76525, -3.79796);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -7.29082, -10.614, -3.60096);
	AssignCoo(p2, -9.0921, -10.6228, -3.68615);
	AssignCoo(p3, -9.0921, -4.04869, -3.71754);
	AssignCoo(p4, -7.29082, -4.03989, -3.63235);
	AssignCoo(p5, -6.03694, -10.7401, -4.82119);
	AssignCoo(p6, -7.83822, -10.7489, -4.90637);
	AssignCoo(p7, -7.83822, -4.17482, -4.93776);
	AssignCoo(p8, -6.03694, -4.16602, -4.85257);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//right side skirt
	AssignCoo(p1, 6.81072, -12.0184, -4.6911);
	AssignCoo(p2, 9.22798, -11.9943, -4.45727);
	AssignCoo(p3, 9.22798, -2.83792, -4.50099);
	AssignCoo(p4, 6.81072, -2.86209, -4.73482);
	AssignCoo(p5, 3.14531, -11.8382, -2.94724);
	AssignCoo(p6, 5.56258, -11.814, -2.7134);
	AssignCoo(p7, 5.56258, -2.65767, -2.75712);
	AssignCoo(p8, 3.14531, -2.68184, -2.99096);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 5.95299, -10.5084, -2.57949);
	AssignCoo(p2, 4.2715, -10.5252, -2.74215);
	AssignCoo(p3, 4.2715, -3.95111, -2.77354);
	AssignCoo(p4, 5.95299, -3.9343, -2.61088);
	AssignCoo(p5, 8.34719, -10.6262, -3.71857);
	AssignCoo(p6, 6.66571, -10.643, -3.88123);
	AssignCoo(p7, 6.66571, -4.06886, -3.91262);
	AssignCoo(p8, 8.34719, -4.05204, -3.74996);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//skirt behind
	AssignCoo(p1, 6.54667, -0.426612, -2.9411);
	AssignCoo(p2, 8.83521, -0.565107, -4.28094);
	AssignCoo(p3, 8.83521, -1.80983, -4.275);
	AssignCoo(p4, 6.54667, -1.67133, -2.93516);
	AssignCoo(p5, -8.76721, -0.539782, -4.03594);
	AssignCoo(p6, -6.5741, -0.678984, -5.38262);
	AssignCoo(p7, -6.5741, -1.92371, -5.37668);
	AssignCoo(p8, -8.76721, -1.7845, -4.03);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -0.230355, -0.513821, -3.78479);
	AssignCoo(p2, -7.15918, -0.52985, -3.93986);
	AssignCoo(p3, -6.47091, -0.676148, -5.35519);
	AssignCoo(p4, 0.457916, -0.660119, -5.20011);
	AssignCoo(p5, -0.230355, -1.75854, -3.77884);
	AssignCoo(p6, -7.15918, -1.77457, -3.93392);
	AssignCoo(p7, -6.47091, -1.92087, -5.34925);
	AssignCoo(p8, 0.457916, -1.90484, -5.19417);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 5.18173, -0.348297, -3.08079);
	AssignCoo(p2, -0.783832, -0.425499, -3.82767);
	AssignCoo(p3, 2.80503, -0.550824, -5.0401);
	AssignCoo(p4, 8.77058, -0.473622, -4.29322);
	AssignCoo(p5, 5.18173, -1.59302, -3.07485);
	AssignCoo(p6, -0.783832, -1.67022, -3.82173);
	AssignCoo(p7, 2.80503, -1.79555, -5.03416);
	AssignCoo(p8, 8.77058, -1.71834, -4.28728);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//private part
	AssignCoo(p1, -0.575023, -17.6323, -4.84206);
	AssignCoo(p2, 2.79325, -17.6071, -4.59818);
	AssignCoo(p3, 4.27063, -12.5338, -5.56194);
	AssignCoo(p4, 0.902353, -12.5591, -5.80582);
	AssignCoo(p5, -1.58048, -14.767, -4.21632);
	AssignCoo(p6, 1.78779, -14.7418, -3.97243);
	AssignCoo(p7, 3.26517, -9.66854, -4.9362);
	AssignCoo(p8, -0.103108, -9.69374, -5.18008);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 0.551853, -14.1639, -5.57526);
	AssignCoo(p2, 3.92013, -14.1387, -5.33138);
	AssignCoo(p3, 4.56456, -10.4878, -5.75863);
	AssignCoo(p4, 1.19628, -10.5131, -6.00251);
	AssignCoo(p5, -1.39731, -10.722, -4.35212);
	AssignCoo(p6, 1.97096, -10.6968, -4.10824);
	AssignCoo(p7, 2.61539, -7.04598, -4.53549);
	AssignCoo(p8, -0.752888, -7.07119, -4.77937);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 1.42307, -10.4944, -5.97322);
	AssignCoo(p2, 4.25758, -10.4732, -5.76798);
	AssignCoo(p3, 4.20284, -0.887343, -5.77894);
	AssignCoo(p4, 1.36833, -0.908557, -5.98417);
	AssignCoo(p5, 0.075997, -10.4809, -5.11661);
	AssignCoo(p6, 2.91051, -10.4597, -4.91138);
	AssignCoo(p7, 2.85577, -0.873815, -4.92233);
	AssignCoo(p8, 0.021255, -0.89503, -5.12757);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 0.700088, -4.60974, -5.64154);
	AssignCoo(p2, 3.5346, -4.58852, -5.3363);
	AssignCoo(p3, 4.1929, -0.946728, -5.77233);
	AssignCoo(p4, 1.35838, -0.967943, -5.97757);
	AssignCoo(p5, -0.476475, -2.48459, -4.80345);
	AssignCoo(p6, 2.35804, -2.46338, -4.59821);
	AssignCoo(p7, 3.01633, 1.17842, -5.03424);
	AssignCoo(p8, 0.181819, 1.1572, -5.23948);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotJetpack() {
	glColor3f(0.5, 0.5, 0.5);
	////jetpack main cube
	AssignCoo(p1, -1.19667, 1.70808, -0.735941);
	AssignCoo(p2, -9.06383, 1.6492, -1.30556);
	AssignCoo(p3, -6.87774, 1.50557, -2.69513);
	AssignCoo(p4, 0.989431, 1.56445, -2.12551);
	AssignCoo(p5, -1.19667, -2.49736, -0.715861);
	AssignCoo(p6, -9.06383, -2.55624, -1.28548);
	AssignCoo(p7, -6.87774, -2.69987, -2.67505);
	AssignCoo(p8, 0.989431, -2.64099, -2.10543);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//jetpack boost cube left
	AssignCoo(p1, 0.245048, 1.64805, -2.15763);
	AssignCoo(p2, -2.70567, 1.62596, -2.37128);
	AssignCoo(p3, -1.674, -0.813949, -3.01571);
	AssignCoo(p4, 1.27671, -0.791865, -2.80207);
	AssignCoo(p5, -0.554009, -1.68542, -1.63355);
	AssignCoo(p6, -3.50473, -1.70751, -1.8472);
	AssignCoo(p7, -2.47306, -4.14742, -2.49164);
	AssignCoo(p8, 0.477657, -4.12533, -2.27799);
	glColor3f(0.5, 0.5, 0.5);
	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//jetpack boost cube right
	AssignCoo(p1, -3.30023, 1.61856, -2.41795);
	AssignCoo(p2, -6.25094, 1.59648, -2.6316);
	AssignCoo(p3, -5.21928, -0.843433, -3.27604);
	AssignCoo(p4, -2.26856, -0.821349, -3.06239);
	AssignCoo(p5, -4.09928, -1.71491, -1.89388);
	AssignCoo(p6, -7.05, -1.73699, -2.10752);
	AssignCoo(p7, -6.01833, -4.1769, -2.75196);
	AssignCoo(p8, -3.06762, -4.15482, -2.53832);
	glColor3f(0.5, 0.5, 0.5);
	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//jetpack left pipe cube
	AssignCoo(p1, 1.04777, 1.69694, -0.843804);
	AssignCoo(p2, -1.39006, 1.69583, -0.854496);
	AssignCoo(p3, -1.31113, 1.6102, -1.68286);
	AssignCoo(p4, 1.1267, 1.61131, -1.67217);
	AssignCoo(p6, -1.39006, -2.50961, -0.834416);
	AssignCoo(p5, 1.04777, -2.50851, -0.823725);
	AssignCoo(p8, 1.1267, -2.59413, -1.65209);
	AssignCoo(p7, -1.31113, -2.59524, -1.66278);
	glColor3f(0.5, 0.5, 0.5);
	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//jetpack right pipe cube
	AssignCoo(p1, -8.76944, 1.63922, -1.40215);
	AssignCoo(p2, -10.7423, 1.60744, -1.70956);
	AssignCoo(p3, -8.47262, 1.53815, -2.37993);
	AssignCoo(p4, -6.49977, 1.56993, -2.07251);
	AssignCoo(p6, -10.7423, -2.598, -1.68948);
	AssignCoo(p5, -8.76944, -2.56622, -1.38207);
	AssignCoo(p8, -6.49977, -2.63552, -2.05243);
	AssignCoo(p7, -8.47262, -2.66729, -2.35985);
	glColor3f(0.5, 0.5, 0.5);
	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotDrawBody() {

	glPushMatrix();
	glTranslatef(2.71884, 12.3108, -3.89528);
	glRotatef(-18.6498, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.475517, 0.475453, 2.22625);
	robotChest();
	robotWaist();
	robotPelvic();
	glPopMatrix();

}

//----------------HEAD--------------------------------------------------

void robotHead() {

	//left side
	AssignCoo(p1, -1.00772, -1.41663, 1.19483);
	AssignCoo(p2, -1.14578, -1.41663, 1.19483);
	AssignCoo(p3, -1.14578, 0.768572, 1.19483);
	AssignCoo(p4, -1.00772, 0.768572, 1.19483);
	AssignCoo(p5, -1.00772, -1.41663, -1.29079);
	AssignCoo(p6, -1.14578, -1.41663, -1.29079);
	AssignCoo(p7, -1.14578, 0.768572, -1.29079);
	AssignCoo(p8, -1.00772, 0.768572, -1.29079);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -1.01656, -0.031578, 1.19483);
	AssignCoo(p2, -1.17137, -0.031578, 1.19483);
	AssignCoo(p3, -1.67892, 1.11973, 1.19483);
	AssignCoo(p4, -1.01656, 2.15362, 1.19483);
	AssignCoo(p5, -1.01656, -0.031578, -1.29079);
	AssignCoo(p6, -1.17137, -0.031578, -1.29079);
	AssignCoo(p7, -1.67892, 1.11973, -1.29079);
	AssignCoo(p8, -1.01656, 2.15362, -1.29079);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//right side
	AssignCoo(p1, 1.00133, -1.41663, -1.29079);
	AssignCoo(p2, 1.13939, -1.41663, -1.29079);
	AssignCoo(p3, 1.13939, 0.768572, -1.29079);
	AssignCoo(p4, 1.00133, 0.768572, -1.29079);
	AssignCoo(p5, 1.00133, -1.41663, 1.19483);
	AssignCoo(p6, 1.13939, -1.41663, 1.19483);
	AssignCoo(p7, 1.13939, 0.768572, 1.19483);
	AssignCoo(p8, 1.00133, 0.768572, 1.19483);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 0.992959, -0.031578, -1.29079);
	AssignCoo(p2, 1.65532, 1.00232, -1.29079);
	AssignCoo(p3, 1.14776, 2.15362, -1.29079);
	AssignCoo(p4, 0.992959, 2.15362, -1.29079);
	AssignCoo(p5, 0.992959, -0.031578, 1.19483);
	AssignCoo(p6, 1.65532, 1.00232, 1.19483);
	AssignCoo(p7, 1.14776, 2.15362, 1.19483);
	AssignCoo(p8, 0.992959, 2.15362, 1.19483);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//back side
	AssignCoo(p1, 0.412531, 3.01102, -1.23571);
	AssignCoo(p2, 0.165008, 3.16102, -1.23571);
	AssignCoo(p3, 0.165008, 1.16102, -1.23571);
	AssignCoo(p4, 0.412531, 1.01102, -1.23571);
	AssignCoo(p5, 0.412531, 3.01102, 1.19218);
	AssignCoo(p6, 0.165008, 3.16102, 1.19218);
	AssignCoo(p7, 0.165008, 1.16102, 1.19218);
	AssignCoo(p8, 0.412531, 1.01102, 1.19218);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 0.168058, 3.25555, -1.23571);
	AssignCoo(p2, -0.186372, 3.25555, -1.23571);
	AssignCoo(p3, -0.186372, 1.0665, -1.23571);
	AssignCoo(p4, 0.168058, 1.0665, -1.23571);
	AssignCoo(p5, 0.168058, 3.25555, 1.19218);
	AssignCoo(p6, -0.186372, -0.186372, 1.19218);
	AssignCoo(p7, -0.186372, 1.0665, 1.19218);
	AssignCoo(p8, 0.168058, 1.0665, 1.19218);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -0.181195, 3.16102, -1.23571);
	AssignCoo(p2, -0.430295, 3.01102, -1.23571);
	AssignCoo(p3, -0.430295, 1.01102, -1.23571);
	AssignCoo(p4, -0.181195, 1.16102, -1.23571);
	AssignCoo(p5, -0.181195, 3.16102, 1.19218);
	AssignCoo(p6, -0.430295, 3.01102, 1.19218);
	AssignCoo(p7, -0.430295, 1.01102, 1.19218);
	AssignCoo(p8, -0.181195, 1.16102, 1.19218);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 1.00626, 2.13087, -1.28072);
	AssignCoo(p2, 0.407682, 2.96411, -1.23933);
	AssignCoo(p3, 0.407682, 0.964109, -1.23933);
	AssignCoo(p4, 1.00626, 0.964109, -1.26995);
	AssignCoo(p5, 1.00626, 2.14993, 1.18856);
	AssignCoo(p6, 0.407682, 2.96411, 1.18856);
	AssignCoo(p7, 0.407682, 0.964109, 1.18856);
	AssignCoo(p8, 1.00626, 0.964109, 1.18856);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -0.42999, 2.96411, -1.23933);
	AssignCoo(p2, -1.02857, 2.14993, -1.23933);
	AssignCoo(p3, -1.02857, 0.964109, -1.23933);
	AssignCoo(p4, -0.42999, 0.964109, -1.23933);
	AssignCoo(p5, -0.429989, 2.96411, 1.18856);
	AssignCoo(p6, -1.02857, 2.13087, 1.22995);
	AssignCoo(p7, -1.02857, 0.964109, 1.21918);
	AssignCoo(p8, -0.429989, 0.964109, 1.18856);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//top
	AssignCoo(p1, -0.187014, 3.32602, 2.12176);
	AssignCoo(p2, 0.17249, 3.32602, 2.12176);
	AssignCoo(p3, 0.349757, 2.58317, 2.23941);
	AssignCoo(p4, -0.248341, 2.58317, 2.24226);
	AssignCoo(p5, -0.436197, 2.99772, 1.17485);
	AssignCoo(p6, 0.439501, 2.9607, 1.17485);
	AssignCoo(p7, 0.618614, 2.28534, 1.17485);
	AssignCoo(p8, -0.550073, 2.11859, 1.17485);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -0.541136, 2.62005, 2.23325);
	AssignCoo(p2, 0.056962, 2.62005, 2.23325);
	AssignCoo(p3, 0.056962, 0.620046, 2.23325);
	AssignCoo(p4, -0.541136, 0.620046, 2.23325);
	AssignCoo(p5, -1.05204, 2.16598, 1.25492);
	AssignCoo(p6, 0.056962, 2.62005, 0.812891);
	AssignCoo(p7, 0.056962, 0.620046, 0.812891);
	AssignCoo(p8, -1.00818, 0.620046, 1.19005);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, 1.02459, 2.13718, 1.16505);
	AssignCoo(p2, 0.022935, 2.62005, 0.812891);
	AssignCoo(p3, 0.022935, 0.620046, 0.812891);
	AssignCoo(p4, 1.07558, 0.702328, 1.15202);
	AssignCoo(p5, 0.621033, 2.62005, 2.23325);
	AssignCoo(p6, 0.022935, 2.62005, 2.23325);
	AssignCoo(p7, 0.022935, 0.620046, 2.23325);
	AssignCoo(p8, 0.621033, 0.620046, 2.23325);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -1.00744, 0.685923, 1.96742);
	AssignCoo(p2, -0.156964, 0.685923, 2.23325);
	AssignCoo(p3, -0.177763, -1.31408, 2.23325);
	AssignCoo(p4, -1.00744, -1.31408, 1.96742);
	AssignCoo(p5, -1.00772, 0.768572, 1.19483);
	AssignCoo(p6, -0.274357, 0.685923, 0.812891);
	AssignCoo(p7, -0.274357, -1.31408, 0.812891);
	AssignCoo(p8, -1.00744, -1.31408, 0.812891);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -0.384356, 0.572203, 1.64453);
	AssignCoo(p2, 0.416316, 0.572203, 1.64453);
	AssignCoo(p3, 0.416316, -1.4278, 1.64453);
	AssignCoo(p4, -0.384356, -1.4278, 1.64453);
	AssignCoo(p5, -0.384356, 0.572203, 0.22417);
	AssignCoo(p6, 0.416316, 0.572203, 0.22417);
	AssignCoo(p7, 0.156098, -1.4278, 0.22417);
	AssignCoo(p8, -0.052077, -1.4278, 0.22417);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -0.136156, 0.623439, 2.45578);
	AssignCoo(p2, 0.259533, 0.623439, 2.45578);
	AssignCoo(p3, 0.259533, -0.876561, 2.45578);
	AssignCoo(p4, -0.136156, -0.876561, 2.45578);
	AssignCoo(p5, -0.334, 0.623439, 1.03543);
	AssignCoo(p6, 0.457377, 0.623439, 1.03543);
	AssignCoo(p7, 0.457377, -1.37656, 1.03543);
	AssignCoo(p8, -0.334, -1.37656, 1.03543);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//front
	AssignCoo(p1, -1.01314, -1.31983, 1.13516);
	AssignCoo(p2, 0.018888, -1.31983, 1.13516);
	AssignCoo(p3, 0.031333, -1.31996, 0.24023);
	AssignCoo(p4, -1.01314, -1.31983, 0.427183);
	AssignCoo(p5, -1.01314, -0.898156, 1.13516);
	AssignCoo(p6, 0.018888, -0.898156, 1.13516);
	AssignCoo(p7, 0.018888, -0.898156, 0.23033);
	AssignCoo(p8, -1.01314, -0.898156, 0.357417);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -1, -1, 1);
	AssignCoo(p2, 1, -1, 1);
	AssignCoo(p3, 1, -1, -1);
	AssignCoo(p4, -1, -1, -1);
	AssignCoo(p5, -1, 1, 1);
	AssignCoo(p6, 1, 1, 1);
	AssignCoo(p7, 1, 1, -1);
	AssignCoo(p8, -1, 1, -1);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -0.029648, -1.31983, 1.13516);
	AssignCoo(p2, 1.00238, -1.31983, 1.13516);
	AssignCoo(p3, 1.00238, -1.31983, 0.357417);
	AssignCoo(p4, -0.029648, -1.31983, 0.23033);
	AssignCoo(p5, -0.029648, -0.898156, 1.13516);
	AssignCoo(p6, 1.00238, -0.898156, 1.13516);
	AssignCoo(p7, 1.00238, -0.898156, 0.427183);
	AssignCoo(p8, -0.042093, -0.898024, 0.24023);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	AssignCoo(p1, -0.052077, -1.4278, 0.22417);
	AssignCoo(p2, 0.156098, -1.4278, 0.22417);
	AssignCoo(p3, 0.416316, 0.572203, 0.22417);
	AssignCoo(p4, -0.384356, 0.572203, 0.22417);
	AssignCoo(p5, -0.384356, -1.4278, 1.64453);
	AssignCoo(p6, 0.416316, -1.4278, 1.64453);
	AssignCoo(p7, 0.416316, 0.572203, 1.64453);
	AssignCoo(p8, -0.384356, 0.572203, 1.64453);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotHorn() {
	//middle cube
	AssignCoo(p1, -0.181131, -1.9271, 1.99952);
	AssignCoo(p2, 0.292784, -1.9271, 1.99952);
	AssignCoo(p3, 0.352023, -1.9271, 1.16381);
	AssignCoo(p4, -0.241046, -1.92846, 1.1605);
	AssignCoo(p5, -0.181131, -1.37602, 1.99952);
	AssignCoo(p6, 0.292784, -1.37602, 1.99952);
	AssignCoo(p7, 0.351347, -1.37739, 1.01286);
	AssignCoo(p8, -0.241046, -1.37739, 1.02055);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//middle triangle
	AssignCoo(p1, -0.24037, -1.9271, 1.16381);
	AssignCoo(p2, 0.351347, -1.92846, 1.1628);
	AssignCoo(p3, 0.055151, -1.92846, 0.557753);
	AssignCoo(p4, 0.055151, -1.92846, 0.557753);
	AssignCoo(p5, -0.241046, -1.37739, 1.02055);
	AssignCoo(p6, 0.351347, -1.37739, 1.01286);
	AssignCoo(p7, 0.055151, -1.37739, 0.302513);
	AssignCoo(p8, 0.055151, -1.37739, 0.302513);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//left horn
	AssignCoo(p1, -1.97729, -1.80822, 1.82507);
	AssignCoo(p2, -0.21259, -1.80822, 1.48469);
	AssignCoo(p3, -0.21259, -1.80822, 1.48469);
	AssignCoo(p4, -1.97729, -1.80822, 1.82507);
	AssignCoo(p5, -1.96203, -1.51285, 2.04663);
	AssignCoo(p6, -0.182062, -1.51285, 1.92783);
	AssignCoo(p7, -0.243118, -1.51285, 1.04156);
	AssignCoo(p8, -1.99256, -1.51285, 1.6035);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//right horn
	AssignCoo(p1, 0.32375, -1.80822, 1.49237);
	AssignCoo(p2, 2.09141, -1.80822, 1.78667);
	AssignCoo(p3, 2.09141, -1.80822, 1.78667);
	AssignCoo(p4, 0.32375, -1.80822, 1.49237);
	AssignCoo(p5, 0.297355, -1.51285, 1.9362);
	AssignCoo(p6, 2.07821, -1.51285, 2.00861);
	AssignCoo(p7, 2.10461, -1.51285, 1.56473);
	AssignCoo(p8, 0.350146, -1.51285, 1.0485);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotMouth() {
	//face mask main left
	AssignCoo(p1, -0.758519, -1.93898, -0.448233);
	AssignCoo(p2, 0.001934, -2.03898, -0.438109);
	AssignCoo(p3, 0.001934, -2.03898, -1.81301);
	AssignCoo(p4, -0.756103, -1.93898, -1.49756);
	AssignCoo(p5, -0.756103, -1.03898, -0.43811);
	AssignCoo(p6, 0.001934, -1.03898, -0.438109);
	AssignCoo(p7, 0.001934, -1.03898, -1.85847);
	AssignCoo(p8, -0.758519, -0.938978, -1.60977);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//face mask main right
	AssignCoo(p1, 0.001934, -2.03898, -0.438109);
	AssignCoo(p2, 0.762659, -1.93898, -0.448233);
	AssignCoo(p3, 0.762659, -1.93898, -1.49259);
	AssignCoo(p4, 0.001934, -2.03898, -1.81301);
	AssignCoo(p5, 0.001934, -1.03898, -0.438109);
	AssignCoo(p6, 0.760817, -1.03898, -0.438109);
	AssignCoo(p7, 0.762659, -0.938978, -1.61569);
	AssignCoo(p8, 0.001934, -1.03898, -1.85847);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//face mask side left
	AssignCoo(p1, -1.00022, -1.58898, -0.448233);
	AssignCoo(p2, -0.758519, -1.93898, -0.448233);
	AssignCoo(p3, -0.756103, -1.93898, -1.49756);
	AssignCoo(p4, -1.00022, -1.58898, -1.25298);
	AssignCoo(p5, -1.00022, -0.588978, -0.448233);
	AssignCoo(p6, -0.756103, -1.03898, -0.43811);
	AssignCoo(p7, -0.758519, -0.938978, -1.60977);
	AssignCoo(p8, -1.00022, -0.588978, -1.25298);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);

	//face mask side right
	AssignCoo(p1, 0.762659, -1.93898, -0.448233);
	AssignCoo(p2, 1.00436, -1.58898, -0.448233);
	AssignCoo(p3, 1.00436, -1.58898, -1.25298);
	AssignCoo(p4, 0.762659, -1.93898, -1.49259);
	AssignCoo(p5, 0.760817, -1.03898, -0.438109);
	AssignCoo(p6, 1.00436, -0.588978, -0.448233);
	AssignCoo(p7, 1.00436, -0.588978, -1.34311);
	AssignCoo(p8, 0.762659, -0.938978, -1.61569);

	drawCubes(p1, p2, p3, p4, p5, p6, p7, p8);
}

void robotDrawHead() {

	glPushMatrix();
	glTranslatef(-0.279077, 12.7944, -0.573511);
	glRotatef(-90, 1, 0, 0);
	glScalef(1.01638, 0.577244, 0.775103);
	robotHorn();
	robotMouth();
	robotHead();
	glPopMatrix();

}

//--------------------SWORD---------------------------------------------

void robotSwordhandle() {
	glColor3f(0.5, 0.5, 0.5);
	//sword handle
	AssignCoo(p1, 4.1366, -1.49571, -1);
	AssignCoo(p2, -1.41167, -1.49571, -1);
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

void robotDrawSword() {

	glPushMatrix();
	glTranslatef(-11.8814, 5.5975, -1.67188);
	glRotatef(180, 0, 1, 0);
	glScalef(0.336975, 8.25759, 0.382484);
	robotSwordhandle();
	robotSwordBlade();
	glPopMatrix();

}

//---------------------------SHEILD---------------------------------------

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

void robotDrawShield() {

	glPushMatrix();
	glTranslatef(11.9145, 3.50987, 1.45277);
	glScalef(0.377375, 0.760072, 1.0);
	robotSheildStar();
	robotSheildInner();
	robotSheildOutter();
	glPopMatrix();

}

//-----------------------------LEG----------------------------------------
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

void robotLeftLegJoint() {

	//knee
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glTranslatef(1.85719, -4.19922, -0.6079);
	drawSphere(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(0.672724, -4.37042, -0.616218);
	glRotatef(90, 0, 1, 0);
	drawCylinder(0.852952, 0.852952, 2.419492);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(0.672724, -4.37042, -0.616218);
	glRotatef(90, 0, 1, 0);
	drawDisk(0, 0.852952, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(3.09346, -4.37042, -0.616218);
	glRotatef(90, 0, 1, 0);
	drawDisk(0, 0.852952, 10);
	glPopMatrix();

	//foot
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(0.034762, -13.1984, -1.209808);
	glRotatef(90, 0, 1, 0);
	drawCylinder(0.852952, 0.852952, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(0.034762, -13.1984, -1.209808);
	glRotatef(90, 0, 1, 0);
	drawDisk(0, 0.852952, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(4, -13.1984, -1.209808);
	glRotatef(90, 0, 1, 0);
	drawDisk(0, 0.852952, 10);
	glPopMatrix();
}

void robotDrawLeftLeg() {

	glPushMatrix();
	glTranslatef(1.88998, -4.36152, -0.626873);
	glRotatef(-90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glScalef(0.768733, 0.852985, 1.20982);
	robotThigh();
	robotCalf();
	robotKnee();
	robotLeg();
	glPopMatrix();

	robotLeftLegJoint();
}

void robotRightLegJoint() {

	//knee
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glTranslatef(-2.31506, -4.07892, -0.6079);
	drawSphere(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(-1.06502, -4.25015, -0.637532);
	glRotatef(-90, 0, 1, 0);
	drawCylinder(0.852952, 0.852952, 2.419492);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(-1.08004, -4.25015, -0.637532);
	glRotatef(90, 0, 1, 0);
	drawDisk(0, 0.852952, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(-3.49952, -4.25015, -0.637532);
	glRotatef(90, 0, 1, 0);
	drawDisk(0, 0.852952, 10);
	glPopMatrix();

	//foot
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(-0.437932, -13.051, -1.242388);
	glRotatef(-90, 0, 1, 0);
	drawCylinder(0.852952, 0.852952, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(-0.437932, -13.051, -1.242388);
	glRotatef(-90, 0, 1, 0);
	drawDisk(0, 0.852952, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(-4.43749, -13.051, -1.242388);
	glRotatef(-90, 0, 1, 0);
	drawDisk(0, 0.852952, 10);
	glPopMatrix();

}

void robotDrawRightLeg() {

	glPushMatrix();
	glTranslatef(-2.28227, -4.24122, -0.626873);
	glRotatef(-90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glScalef(0.768733, 0.852985, 1.20982);
	robotThigh();
	robotCalf();
	robotKnee();
	robotLeg();
	glPopMatrix();

	robotRightLegJoint();

}

//-----------------------------------------------------------------------

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

void lighting()
{
	if (isLightOn) {
		glEnable(GL_LIGHTING);		/* Enable light */
	}
	else {
		glDisable(GL_LIGHTING);		/* Disable light */
	}

	/* Light 0: Red ambient light, pos(0.0, 0.8, 0.0) above sphere */
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_POSITION, posA);
	//glEnable(GL_LIGHT0);

	/* Light 1: Green diffuse light, pos(0.0, 0.8, 0.0) right of sphere */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT1, GL_POSITION, posD);
	glEnable(GL_LIGHT1);
}

//-----------------------------------------------------------------------

void display()
{
	clearColor();
	glClearColor(1, 1, 1, 1);

	projection();

	lighting();

	glMatrixMode(GL_MODELVIEW);						/* Refer to modelview matrix */
	glLoadIdentity();

	glTranslatef(tx, 0.0f, tz);						/* Translate for modelview */

	GLuint texture[1];
	texture[0] = loadTexture("testPaper.bmp");

	//Arm
	robotDrawRightArm();
	robotDrawLeftArm();

	//Body
	robotDrawBody();

	//Head
	robotDrawHead();

	//Leg
	robotDrawLeftLeg();
	robotDrawRightLeg();

	//Sword
	robotDrawSword();

	//Shield
	robotDrawShield();

	glDeleteTextures(1, &texture[0]);
	glDisable(GL_TEXTURE_2D);

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