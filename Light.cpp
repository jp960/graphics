#include "Light.h"


Light::Light(Eigen::Vector3f _direction, float _localIntensity, Eigen::Vector3f _localColour) {
	direction = _direction;
	local = { _localIntensity, _localIntensity, _localIntensity };
}

Light::Light()
{
}

Light::~Light()
{
}
