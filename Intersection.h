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

	float getShortestDistancet();
	void setShortestDistancet(float t);
	Eigen::Vector3f getNormal();
	void setNormal(Eigen::Vector3f normal);
	Eigen::Vector3f getIntersectionPoint();
	void setIntersectionPoint(Eigen::Vector3f intersectionPoint);
};

