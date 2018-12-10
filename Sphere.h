#pragma once
#include <iostream>
#include <Eigen/Core>
#include "SceneObject.h"

class Sphere : public SceneObject {
	using SceneObject::intersect;
public:
	Sphere(Eigen::Vector3f centre, int radius, Material m);
	~Sphere();
	Eigen::Vector3f centre;
	int radius;
	Intersection intersect(Ray ray);
};

