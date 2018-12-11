#pragma once
#include <Eigen/Core>

class Intersection
{
public:
	Intersection(float shortest_distance_t, Eigen::Vector3f normal, Eigen::Vector3f intersectionPoint);
	Intersection();
	~Intersection();

	float shortest_distance_t;
	Eigen::Vector3f normal;
	Eigen::Vector3f intersectionPoint;
	int closestObjIndex;
};

