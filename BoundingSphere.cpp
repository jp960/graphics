#include <cfloat>
#include <iostream>
#include "BoundingSphere.h"

using namespace std;

BoundingSphere::BoundingSphere() {

}

void BoundingSphere::setupBoundingSphere(float _diameter, Eigen::Vector3f _centre) {
    diameter = _diameter;
    centre = _centre;
}

void BoundingSphere::setupBoundingSphere(Eigen::MatrixXf v) {
    Eigen::Vector3f max{ 0.0f,0.0f,0.0f };
    Eigen::Vector3f min{ FLT_MAX,FLT_MAX,FLT_MAX };

    for (int i = 0; i < v.rows(); i++) {
        for (int j = 0; j < 3; j++) {
            if (v.row(i)[j] < min[j]) min[j] = v.row(i)[j];
            if (v.row(i)[j] > max[j]) max[j] = v.row(i)[j];
        }
    }
    Eigen::Vector3f dimension(max-min);
    diameter = sqrt(dimension[0]*dimension[0] + dimension[1]*dimension[1] + dimension[2]*dimension[2]);
    centre = (max+min)/2;
}

Intersection BoundingSphere::intersect(Ray ray) {
    Eigen::Vector3f modified_ray_point(ray.point - centre);
    Eigen::Vector3f intersectionPoint(0, 0, 0);
    Eigen::Vector3f normal(0, 0, 0);

    float b(2.0f * (ray.direction.dot(modified_ray_point)));
    float c(modified_ray_point.dot(modified_ray_point) - (float)pow(diameter/2, 2));
    float discriminant(pow(b, 2) - 4.0f * c);
    float t;

    if (discriminant > 0) {
        t = std::min((-1 * b + sqrt(discriminant)), ((-1 * b - sqrt(discriminant))));
        t = t / 2;
        intersectionPoint = ray.point + (t * ray.direction);
        normal = (intersectionPoint - centre) / (intersectionPoint - centre).norm();
        return Intersection{ t, normal, intersectionPoint };
    }
    return Intersection{ FLT_MAX, normal, intersectionPoint };
}
