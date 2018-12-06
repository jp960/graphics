#pragma once
#include <iostream>
#include <Eigen/Core>
#include "SceneObject.h"

class Sphere : public SceneObject {
	using SceneObject::intersect;
public:
	Sphere(Eigen::Vector3f centre, int radius, Eigen::Vector3f diffuse, Eigen::Vector3f specular, float reflectivity, float transparency, float refractiveIndex);
	~Sphere();
	Eigen::Vector3f centre;
	int radius;
	Intersection intersect(Eigen::Vector3f rayPoint, Eigen::Vector3f rayDirection);
};

