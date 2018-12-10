#pragma once
#include <Eigen/Core>

class Material {
public:
    Eigen::Vector3f ka;
    Eigen::Vector3f kd;
    Eigen::Vector3f ks;
    float kr;
    float kt;
    float n;
    float ri;
    Material( Eigen::Vector3f ka, Eigen::Vector3f kd, Eigen::Vector3f ks, float kr, float kt);
    Material();
    ~Material();
};

