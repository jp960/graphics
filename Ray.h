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


