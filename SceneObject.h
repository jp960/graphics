#pragma once
#include <Eigen/Core>
#include "Intersection.h"
#include "Ray.h"
#include "Material.h"
#include "BoundingSphere.h"

class SceneObject
{
public:
	Material material;
	BoundingSphere bs;
	SceneObject();
	~SceneObject();
	virtual Intersection intersect(Ray ray) = 0;
	void setMaterial(Material m);
};

