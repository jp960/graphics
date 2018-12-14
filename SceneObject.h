#pragma once
#include <Eigen/Core>
#include "Intersection.h"
#include "Ray.h"
#include "Material.h"
#include "BoundingSphere.h"
#include "Texture.h"

class SceneObject
{
public:
	Material material;
	Texture texture;
	BoundingSphere bs;
	SceneObject();
	~SceneObject();
	virtual Intersection intersect(Ray ray) = 0;
	void setMaterial(Material m);
	void setTexture(Texture t);
};

