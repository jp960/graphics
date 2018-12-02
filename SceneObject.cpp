#include "SceneObject.h"
#include <Eigen/Core>


SceneObject::SceneObject(Eigen::Vector3f _diffuseColour, Eigen::Vector3f _specular) {
	diffuseColour = _diffuseColour * 0.5f;
	specular = _specular * 0.5f;
}


SceneObject::~SceneObject() {
}
