#pragma once
#include <Eigen/Core>
#include "Intersection.h"

class SceneObject
{
public:
	Eigen::Vector3f diffuse;
	Eigen::Vector3f specular;
	float reflectivity;
	float transparency;
	float refractiveIndex;
	SceneObject(Eigen::Vector3f diffuse, Eigen::Vector3f specular, float reflectivity, float transparency, float refractiveIndex);
	~SceneObject();
	virtual Intersection intersect(Eigen::Vector3f rayPoint, Eigen::Vector3f rayDirection) = 0;
};

