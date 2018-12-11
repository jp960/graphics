#include <cfloat>
#include "Sphere.h"


Sphere::Sphere(Eigen::Vector3f _centre, int _radius, Material _m) : SceneObject(_m) {
	centre = _centre;
	radius = _radius;
}


Sphere::~Sphere()
{
}

Intersection Sphere::intersect(Ray ray) {
	Eigen::Vector3f modified_ray_point(ray.point - centre);
	Eigen::Vector3f intersectionPoint(0, 0, 0);
	Eigen::Vector3f normal(0, 0, 0);

	float b(2.0f * (ray.direction.dot(modified_ray_point)));
	float c(modified_ray_point.dot(modified_ray_point) - (float)pow(radius, 2));
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
