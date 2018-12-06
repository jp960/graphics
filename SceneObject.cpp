#include "SceneObject.h"
#include <Eigen/Core>


SceneObject::SceneObject(Eigen::Vector3f _diffuse, Eigen::Vector3f _specular, float reflectivity, float transparency, float refractiveIndex) {
	diffuse = _diffuse * 0.5f;
	specular = _specular * 0.5f;
}


SceneObject::~SceneObject() {
}
