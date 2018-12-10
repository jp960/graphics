#include "Ray.h"

Ray::Ray(Eigen::Vector3f _point, Eigen::Vector3f _direction) {
    point = _point;
    direction = _direction;
}

Ray::Ray(){}
Ray::~Ray(){}

