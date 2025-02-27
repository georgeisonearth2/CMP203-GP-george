#include "LightingMaterials.h"
#include "Vector3.h"
#include "Constants.h"

void LightingMaterials::render()
{
	// Clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glClearColor(0, 0, 0, 0);
	// Set the light settings
	GLfloat lightIntensity[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lightPosition[] = { 10*sinf(lightAngle), 0.0f, 10*cosf(lightAngle), 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_LIGHT0);
	//set global ambient light
	float globalAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
	// Set the camera
	gluLookAt(0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	drawSphere(Vector3(lightPosition[0], lightPosition[1], lightPosition[2]), 0.1f, Colors::Yellow, Colors::Red, 200);
	drawSphere(Vector3(5.0f, 0.0f, 0.0f), 1.0f, Colors::Red, Colors::Red, 200);
	drawSphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f, Colors::Red, Colors::Red, 100);
	drawSphere(Vector3(-5.0f, 0.0f, 0.0f), 1.0f, Colors::Red, Colors::Red, 0);

	glClear(GL_COLOR_MATERIAL);
	// Render text, should be last object rendered.
	renderTextOutput();
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void LightingMaterials::update(float dt)
{
	//layer1Pos.x += 0.01f * dt * triangleSpeed;
	calculateFPS();

	//move the light around the middle sphere
	lightAngle += 0.01f * dt * rotationSpeed;
	if (lightAngle > 360)
	{
		lightAngle -= 360;
	}
}

//draws a 3d sphere
void LightingMaterials::drawSphere(Vector3 position, float radius, Vector3 color, Vector3 materialColor, float shininess)
{
	//material properties
	float rgba[4] = { materialColor.x, materialColor.y, materialColor.z, 1.0f };
	float specular[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float diffuse[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, rgba);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	//gluQuadricTexture(sphere, GLU_TRUE);
	//sphere
	
	GLUquadricObj* sphere = gluNewQuadric();
	//set position of sphere
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		//set color
		glColor3f(color.x, color.y, color.z);
		gluQuadricDrawStyle(sphere, GLU_FILL);
		gluQuadricNormals(sphere, GLU_SMOOTH);

		
		gluSphere(sphere, radius, 100, 100);
		
		gluDeleteQuadric(sphere);
	glPopMatrix();
	
}