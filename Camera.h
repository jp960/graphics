#pragma once
#include <Eigen/Core>

class Camera
{
public:
	Camera(Eigen::Vector3f focal_point, int focal_length, Eigen::Vector3f up, Eigen::Vector3f right, Eigen::Vector3f forward, int image_h, int image_w, int resH, int resW);
	~Camera();
	Eigen::Vector3f focal_point;
	int focal_length;
	Eigen::Vector3f up;
	Eigen::Vector3f right;
	Eigen::Vector3f forward;
	Eigen::Vector3f top_left_centre;
	int image_h;
	int image_w;
	int resH;
	int resW;
	float pixelH;
	float pixelW;

	Eigen::Vector3f getWorldCoordForPixel(int i, int j);
};

