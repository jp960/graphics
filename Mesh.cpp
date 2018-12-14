#include <iostream>
#include <Eigen/Geometry>
#include <igl/readOBJ.h>
#include <cfloat>
#include "Mesh.h"

using namespace std;

Mesh::Mesh(std::string _fileName, Eigen::Vector3f _centre, float _scale) : SceneObject() {
	fileName = _fileName;
	centre = _centre;
	scale = _scale;
	loadMesh();
}

Mesh::~Mesh()
{
}

void Mesh::loadMesh() {
	igl::readOBJ(fileName, v, f);
	Eigen::Transform <float, 3, Eigen::Affine > t = Eigen::Transform <float, 3, Eigen::Affine >::Identity();
	t.translate(centre);
	t.scale(scale);
	v = apply_transform_to_list_of_vertices(v, t);

	bs.setupBoundingSphere(v);
}

Eigen::MatrixXf Mesh::apply_transform_to_list_of_vertices(Eigen::MatrixXf input_v, const Eigen::Transform <float, 3, Eigen::Affine > & t) {
	Eigen::MatrixXf v_ht(input_v);
	v_ht.conservativeResizeLike(Eigen::MatrixXf::Ones(v_ht.rows(), (v_ht.cols() + 1)));

	Eigen::MatrixXf v_homo(t.matrix() * (v_ht.transpose()));
	Eigen::MatrixXf v_homo_smol(v_homo.colwise().hnormalized());

	return v_homo_smol.transpose();
}

Intersection Mesh::intersect(Ray ray) {
	Eigen::Vector3i face;
	Eigen::Vector3f v1, v2, v3;
	Eigen::Vector3f v1v2, v1v3, v2v3, v3v1;
	Eigen::Vector3f cross1, cross2, cross3;
	Eigen::Vector3f normal(0, 0, 0);
	Eigen::Vector3f intersectionPoint(0, 0, 0);
	Eigen::Vector3f n;
	Eigen::Vector3f intersection;
	float nd;
	float t;
	float c1c2, c2c3, c3c1;

	float closest_t = FLT_MAX;
	int closestFaceIndex = -1;
	for (int faceIndex = 0; faceIndex < Mesh::f.rows(); faceIndex++) {
		face = f.row(faceIndex);
		v1 = v.row(face[0]);
		v2 = v.row(face[1]);
		v3 = v.row(face[2]);

		v1v2 = v2 - v1;
		v1v3 = v3 - v1;

		n = v1v2.cross(v1v3);
		n = n / n.norm();

		nd = n.dot(ray.direction);

		if (nd < 0) {
			t = abs((v1 - ray.point).dot(n) / nd);
			if (t >= closest_t) {
				continue;
			}
			intersection = ray.point + (t*ray.direction);

			v2v3 = v3 - v2;
			v3v1 = v1 - v3;
			cross1 = (intersection - v1).cross(v1v2);
			cross2 = (intersection - v2).cross(v2v3);
			cross3 = (intersection - v3).cross(v3v1);

			c1c2 = cross1.dot(cross2);
			c2c3 = cross2.dot(cross3);
			c3c1 = cross3.dot(cross1);

			if (c1c2 >= 0 && c2c3 >= 0 && c3c1 >= 0) {
				closest_t = t;
				closestFaceIndex = faceIndex;
				normal = n;
				intersectionPoint = intersection;
			}
		}
	}
	if (closestFaceIndex == -1) {
		return Intersection{ FLT_MAX, normal, intersectionPoint };
	}
	return Intersection{ closest_t, normal, intersectionPoint };
}