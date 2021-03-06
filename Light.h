#pragma once
#include <Eigen/Core>

class Light
{
public:
	Light(Eigen::Vector3f direction, float _localIntensity, Eigen::Vector3f _localColour);
	Light();
	~Light();
	Eigen::Vector3f direction;
	Eigen::Vector3f local;
};

