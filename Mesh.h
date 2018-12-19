#pragma once
#include <iostream>
#include <string>
#include <Eigen/Core>
#include "SceneObject.h"

class Mesh : public SceneObject {
public:
	using SceneObject::intersect;
	using SceneObject::setMaterial;
	Eigen::MatrixXf v;
	Eigen::MatrixXi f;
	std::string fileName;
	Eigen::Vector3f centre;
    Eigen::Vector3f rotate;
	float scale;

    Mesh(std::string fileName, Eigen::Vector3f centre, Eigen::Vector3f rotate, float scale);
	~Mesh();
	Intersection intersect(Ray ray);
private:
	void loadMesh();
	Eigen::MatrixXf apply_transform_to_list_of_vertices(Eigen::MatrixXf input_v, const Eigen::Transform <float, 3, Eigen::Affine > & t);
};