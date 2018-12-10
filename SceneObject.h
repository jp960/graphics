#pragma once
#include <Eigen/Core>
#include "Intersection.h"
#include "Ray.h"
#include "Material.h"

class SceneObject
{
public:
	Material material;
	SceneObject(Material m);
	~SceneObject();
	virtual Intersection intersect(Ray ray) = 0;
};

