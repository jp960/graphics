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
