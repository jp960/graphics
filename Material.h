#pragma once
#include <Eigen/Core>

class Material {
public:
    Eigen::Vector3f ka;
    Eigen::Vector3f kd;
    Eigen::Vector3f ks;
    float kr;
    int type;
    float kt;
    float n;
    float ri;
    int getType();
    Material( Eigen::Vector3f ka, Eigen::Vector3f kd, Eigen::Vector3f ks, float kr, float kt, int type);
    Material();
    ~Material();
};

