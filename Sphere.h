#pragma once
#include <iostream>
#include <Eigen/Core>
#include "SceneObject.h"

class Sphere : public SceneObject {
public:
	using SceneObject::intersect;
	using SceneObject::setMaterial;
	Sphere(Eigen::Vector3f centre, int radius);
	~Sphere();
	Eigen::Vector3f centre;
	int radius;
	Intersection intersect(Ray ray);
};

