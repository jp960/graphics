/***************************************************************************
 * This is the parent class for all objects in the scene. It holds the
 * Material, Texture and Bounding Sphere of that object. It has methods to
 * set the Material and the Texture and a abstract intersect method to be
 * implemented by the children scene objects like Mesh or Sphere.
 */
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

