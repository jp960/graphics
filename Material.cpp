#include "Material.h"


Material::Material(Eigen::Vector3f _ka, Eigen::Vector3f _kd, Eigen::Vector3f _ks, float _kr, float _kt) {
    ka = _ka;
    kd = _kd;
    ks = _ks;
    kr = _kr;
    kt = _kt;
}

Material::Material() {
}

Material::~Material() {
}
