#include "SceneObject.h"
#include <Eigen/Core>


SceneObject::SceneObject() {
}


SceneObject::~SceneObject() {
}

void SceneObject::setMaterial(Material m) {
	material = m;
	material.kd = material.kd * 0.5f;
	material.ks = material.ks * 0.5f;
	material.type = material.type;
}
