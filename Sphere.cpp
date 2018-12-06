#include <cfloat>
#include "Sphere.h"


Sphere::Sphere(Eigen::Vector3f _centre, int _radius, Eigen::Vector3f _diffuse, Eigen::Vector3f _specular, float _reflectivity, float _transparency, float _refractiveIndex) : SceneObject(_diffuse, _specular, _reflectivity, _transparency, _refractiveIndex) {
	centre = _centre;
	radius = _radius;
	diffuse = _diffuse;
	specular = _specular;
	reflectivity = _reflectivity;
	transparency = _transparency;
	refractiveIndex = _refractiveIndex;
}


Sphere::~Sphere()
{
}

Intersection Sphere::intersect(Eigen::Vector3f rayPoint, Eigen::Vector3f rayDirection) {
	Eigen::Vector3f modified_ray_point(rayPoint - centre);
	Eigen::Vector3f intersectionPoint(0, 0, 0);
	Eigen::Vector3f normal(0, 0, 0);

	float b(2.0f * (rayDirection.dot(modified_ray_point)));
	float c(modified_ray_point.dot(modified_ray_point) - (float)pow(radius, 2));
	float discriminant(pow(b, 2) - 4.0f * c);
	float t;

	if (discriminant > 0) {
		t = std::min((-1 * b + sqrt(discriminant)), ((-1 * b - sqrt(discriminant))));
		t = t / 2;
		intersectionPoint = rayPoint + (t * rayDirection);
		normal = (intersectionPoint - centre) / (intersectionPoint - centre).norm();
		return Intersection{ t, normal, intersectionPoint };
	}
	return Intersection{ FLT_MAX, normal, intersectionPoint };
}
