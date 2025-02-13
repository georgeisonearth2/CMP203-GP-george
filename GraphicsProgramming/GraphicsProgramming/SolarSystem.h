#ifndef _SolarSystem_H
#define _SolarSystem_H

#include "Scene.h"
#include "Vector3.h"
class SolarSystem :
	public Scene
{
public:
	using Scene::Scene;
	void render() override;
	void update(float dt) override;
private:
	Vector3 layer1Pos;
	float triangleSpeed = 10;
	void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides);
};
#endif
