#pragma once
#include <Eigen/Core>
#include "Intersection.h"

class SceneObject
{
public:
	Eigen::Vector3f diffuseColour;
	Eigen::Vector3f specular;
	SceneObject(Eigen::Vector3f diffuseColour, Eigen::Vector3f specular);
	~SceneObject();
	virtual Intersection intersect(Eigen::Vector3f rayPoint, Eigen::Vector3f rayDirection) = 0;
};

