#include "Scene.h"
#include "Vector3.h"
#include "Constants.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input* in)
{

	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.

	// Initialise scene variables

}
//empty page
void Scene::Number1()
{
	//empty <3
}
//white triangle
void Scene::Number2()
{
	drawTriangle(Vertex(Vector3(0, 0, 0), Colors::White), Vertex(Vector3(2, 0, 0), Colors::White), Vertex(Vector3(1, 2, 0), Colors::White));
}
//green triangle
void Scene::Number3()
{
	drawTriangle(Vertex(Vector3(0, 0, 0), Colors::Green), Vertex(Vector3(2, 0, 0), Colors::Green), Vertex(Vector3(1, 2, 0), Colors::Green));
}
// rgb triangle
void Scene::Number4()
{
	drawTriangle(Vertex(Vector3(0, 0, 0), Colors::Red), Vertex(Vector3(2, 0, 0), Colors::Green), Vertex(Vector3(1, 2, 0), Colors::Blue));
}
//render a quad made of 2 triangles
void Scene::Number5()
{
	drawTriangle(Vertex(Vector3(0, 0, 0), Colors::Red), Vertex(Vector3(1, 0, 0), Colors::Green), Vertex(Vector3(1, -1, 0), Colors::Blue));
	drawTriangle(Vertex(Vector3(0, 0, 0), Colors::Red), Vertex(Vector3(1, -1, 0), Colors::Blue), Vertex(Vector3(0, -1, 0), Colors::Red));
}
//render a triangle strip + triangle fan + quad strip + polygon + wireframe on r pressed
void Scene::Number6()
{
	Vertex
		v1(Vector3(0, 0, 0), Colors::Red),
		v2(Vector3(1, 0, 0), Colors::Green),
		v3(Vector3(1, -1, 0), Colors::Blue),
		v4(Vector3(2, 0, 0), Colors::Cyan),
		v5(Vector3(2, -1, 0), Colors::Red),
		v6(Vector3(3, 0, 0), Colors::Green),
		v7(Vector3(3, -1, 0), Colors::Blue),
		v8(Vector3(4, 0, 0), Colors::Cyan);
	drawStrip(new Vertex[8]{ v1, v2, v3, v4, v5, v6, v7, v8 }, 8);

	if (isWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Scene::Number7()
{

}

void Scene::handleInput(float dt)
{
	if (input->isKeyDown('r'))
	{
		isWireframe = !isWireframe;
		Sleep(100);
	}
	// Handle user input
	if (input->isKeyDown('1'))
		currentNumber = 1;
	else if (input->isKeyDown('2'))
		currentNumber = 2;
	else if (input->isKeyDown('3'))
		currentNumber = 3;
	else if (input->isKeyDown('4'))
		currentNumber = 4;
	else if (input->isKeyDown('5'))
		currentNumber = 5;
	else if (input->isKeyDown('6'))
		currentNumber = 6;
	else if (input->isKeyDown('7'))
		currentNumber = 7;
}

void Scene::update(float dt)
{
	// update scene related variables.

	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//triangle vertices
	/*drawTriangle(v1, v2, v3);
	drawTriangle(v2, v3, v4);*/
	//Vertex
	//	v1(Vector3(0, 0, 0), Colors::Red),
	//	v2(Vector3(1, 0, 0), Colors::Green),
	//	v3(Vector3(1, -1, 0), Colors::Blue),
	//	v4(Vector3(2, 0, 0), Colors::Cyan),
	//	v5(Vector3(2, -1, 0), Colors::Red),
	//	v6(Vector3(3, 0, 0), Colors::Green),
	//	v7(Vector3(3, -1, 0), Colors::Blue),
	//	v8(Vector3(4, 0, 0), Colors::Cyan);
	//drawStrip(new Vertex[8]{ v1, v2, v3, v4, v5, v6, v7, v8 }, 8);
	////quad vertices
	//Vertex v1(Vector3(0, 0, 0), Colors::Blue), v2(Vector3(1, 0, 0), Colors::Red), v3(Vector3(1, -1, 0), Colors::Red), v4(Vector3(0, -1, 0), Colors::Blue);
	//drawQuad(v1, v2, v3, v4);

	switch (currentNumber)
	{
	case 1:
		Number1();
		break;
	case 2:
		Number2();
		break;
	case 3:
		Number3();
		break;
	case 4:
		Number4();
		break;
	case 5:
		Number5();
		break;
	case 6:
		Number6();
		break;

	case 7:
		Number7();
		break;
	}

	// Render text, should be last object rendered.
	renderTextOutput();

	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blending function
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h)
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void Scene::drawTriangle(Vertex v1, Vertex v2, Vertex v3)
{
	glBegin(GL_TRIANGLES);

	//vertex 1
	glColor3f(v1.color.x, v1.color.y, v1.color.z);
	glVertex3f(v1.position.x, v1.position.y, v1.position.z);

	//vertex 2
	glColor3f(v2.color.x, v2.color.y, v2.color.z);
	glVertex3f(v2.position.x, v2.position.y, v2.position.z);

	//vertex 3
	glColor3f(v3.color.x, v3.color.y, v3.color.z);
	glVertex3f(v3.position.x, v3.position.y, v3.position.z);

	glEnd();
}

void Scene::drawQuad(Vertex v1, Vertex v2, Vertex v3, Vertex v4)
{
	glBegin(GL_QUADS);

	//vertex 1
	glColor3f(v1.color.x, v1.color.y, v1.color.z);
	glVertex3f(v1.position.x, v1.position.y, v1.position.z);

	//vertex 2
	glColor3f(v2.color.x, v2.color.y, v2.color.z);
	glVertex3f(v2.position.x, v2.position.y, v2.position.z);

	//vertex 3
	glColor3f(v3.color.x, v3.color.y, v3.color.z);
	glVertex3f(v3.position.x, v3.position.y, v3.position.z);

	//vertex 4
	glColor3f(v4.color.x, v4.color.y, v4.color.z);
	glVertex3f(v4.position.x, v4.position.y, v4.position.z);

	glEnd();
}

void Scene::drawStrip(Vertex vArray[], int size)
{
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < size; i++)
	{
		glColor3f(vArray[i].color.x, vArray[i].color.y, vArray[i].color.z);
		glVertex3f(vArray[i].position.x, vArray[i].position.y, vArray[i].position.z);
	}
	glEnd();
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width / (float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
