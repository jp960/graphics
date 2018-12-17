/***************************************************************************
 * Intersection class stores the shortest distance travelled (t) when
 * a ray hits an object, the coordinates of that point, its normal and the
 * index of the closest object for the Scene class.
 */
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

