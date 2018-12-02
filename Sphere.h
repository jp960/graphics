#pragma once
#include <iostream>
#include <Eigen/Core>
#include "SceneObject.h"

class Sphere : public SceneObject {
	using SceneObject::intersect;
public:
	Sphere(Eigen::Vector3f centre, int radius, Eigen::Vector3f diffuseColour, Eigen::Vector3f specular);
	~Sphere();
	Eigen::Vector3f centre;
	int radius;
	Intersection intersect(Eigen::Vector3f rayPoint, Eigen::Vector3f rayDirection);
};

