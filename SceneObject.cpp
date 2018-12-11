#include "SceneObject.h"
#include <Eigen/Core>


SceneObject::SceneObject(Material _m) {
	material.kd = _m.kd * 0.5f;
	material.ks = _m.ks * 0.5f;
	material.type = _m.type;
}


SceneObject::~SceneObject() {
}
