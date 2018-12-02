#include "Intersection.h"


Intersection::Intersection(float _shortest_distance_t, Eigen::Vector3f _normal, Eigen::Vector3f _intersectionPoint) {
	shortest_distance_t = _shortest_distance_t;
	normal = _normal;
	intersectionPoint = _intersectionPoint;
}

Intersection::Intersection()
{
}

Intersection::~Intersection()
{
}

float Intersection::getShortestDistancet() { 
	return shortest_distance_t; 
}

void Intersection::setShortestDistancet(float t) { 
	shortest_distance_t = t; 
}

Eigen::Vector3f Intersection::getNormal() { 
	return normal; 
}

void Intersection::setNormal(Eigen::Vector3f n) { 
	normal = n; 
}

Eigen::Vector3f Intersection::getIntersectionPoint() {
	return intersectionPoint;
}

void Intersection::setIntersectionPoint(Eigen::Vector3f p) {
	intersectionPoint = p;
}
