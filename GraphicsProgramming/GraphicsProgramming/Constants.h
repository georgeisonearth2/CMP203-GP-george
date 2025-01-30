#include "Vector3.h"

class Colors
{
public:
	static const Vector3 Cyan;
	static const Vector3 Red;
	static const Vector3 Green;
	static const Vector3 Blue;
};
const Vector3 Colors::Cyan = Vector3(0.0f, 1.0f, 1.0f);
const Vector3 Colors::Red = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Colors::Green = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Colors::Blue = Vector3(0.0f, 0.0f, 1.0f);