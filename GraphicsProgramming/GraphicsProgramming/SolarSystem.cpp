#include "SolarSystem.h"
#include "Vector3.h"
#include "Constants.h"
void SolarSystem::render()
{
	// Clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(layer1Pos.x, layer1Pos.y, layer1Pos.z);
	Vertex
		v1(Vector3(0, 0, 0), Colors::Red),
		v2(Vector3(1, 0, 0), Colors::Green),
		v3(Vector3(1, -1, 0), Colors::Blue);
	drawTriangle(v1, v2, v3);
	drawCircle(0, 0, 0, 1, 100);
	// Render text, should be last object rendered.
	renderTextOutput();
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void SolarSystem::update(float dt)
{
	layer1Pos.x += 0.01f * dt * triangleSpeed;
	calculateFPS();
}

void SolarSystem::drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides)
{
    int numberOfVertices = numberOfSides + 2;

    GLfloat twicePi = 2.0f * 3.14159256f;

    GLfloat* circleVerticesX = new GLfloat[numberOfVertices];
    GLfloat* circleVerticesY = new GLfloat[numberOfVertices];
    GLfloat* circleVerticesZ = new GLfloat[numberOfVertices];

    circleVerticesX[0] = x;
    circleVerticesY[0] = y;
    circleVerticesZ[0] = z;

    for (int i = 1; i < numberOfVertices; i++)
    {
        circleVerticesX[i] = x + (radius * cos(i * twicePi / numberOfSides));
        circleVerticesY[i] = y + (radius * sin(i * twicePi / numberOfSides));
        circleVerticesZ[i] = z;
    }

    GLfloat* allCircleVertices = new GLfloat[(numberOfVertices) * 3];

    for (int i = 0; i < numberOfVertices; i++)
    {
        allCircleVertices[i * 3] = circleVerticesX[i];
        allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
        allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
    glDisableClientState(GL_VERTEX_ARRAY);
}