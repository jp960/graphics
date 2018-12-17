/***************************************************************************
 * This class holds all of the SceneObject's Material information
 */
#pragma once
#include <Eigen/Core>

class Material {
public:
    Eigen::Vector3f ka; // ambient
    Eigen::Vector3f kd; // diffuse
    Eigen::Vector3f ks; // specular
    float kr; // reflection
    int type; // 0 = just diffuse and specular, 1 = reflective, 2 = both reflection and refraction
    float kt; // transparency
    float ri; // refractive index
    int getType();
    Material( Eigen::Vector3f ka, Eigen::Vector3f kd, Eigen::Vector3f ks, float kr, float kt, int type);
    Material();
    ~Material();
};

