#ifndef LightingMaterials_H
#define LightingMaterials_H
#include "Scene.h"
#include "Vector3.h"
#include "Constants.h"
class LightingMaterials : public Scene
{
private:
	float rotationSpeed = 100;
	float lightAngle = 0.0f;
public:
	using Scene::Scene;
	void render() override;
	void update(float dt) override;
	void drawSphere(Vector3 position, float size, Vector3 color, Vector3 materialColor, float shininess);
};
#endif

