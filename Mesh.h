#pragma once
#include <iostream>
#include <Eigen/Core>
#include "SceneObject.h"
#include <string>

class Mesh : public SceneObject {
	using SceneObject::intersect;
public:
	Eigen::MatrixXf v;
	Eigen::MatrixXi f;
	std::string fileName;
	Eigen::Vector3f centre;
	float scale;

	Mesh(std::string fileName, Eigen::Vector3f centre, float scale, Eigen::Vector3f diffuseColour, Eigen::Vector3f specular);
	~Mesh();
	Intersection intersect(Eigen::Vector3f rayPoint, Eigen::Vector3f rayDirection);
private:
	void loadMesh();
	Eigen::MatrixXf apply_transform_to_list_of_vertices(Eigen::MatrixXf input_v, const Eigen::Transform <float, 3, Eigen::Affine > & t);
};