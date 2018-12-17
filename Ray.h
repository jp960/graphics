/***************************************************************************
 * Ray class to hold the vector for the ray's start point and its direction.
 */
#pragma once
#include <Eigen/Core>

class Ray {
public:
    Ray(Eigen::Vector3f point, Eigen::Vector3f direction);
    Ray();
    ~Ray();

    Eigen::Vector3f point;
    Eigen::Vector3f direction;
};


