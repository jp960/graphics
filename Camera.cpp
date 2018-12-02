#include "Camera.h"
#include <iostream>

using namespace std;
Camera::Camera(Eigen::Vector3f _focal_point, int _focal_length, Eigen::Vector3f _up, Eigen::Vector3f _right, Eigen::Vector3f _forward, int _image_h, int _image_w, int _resH, int _resW) {
	focal_point = _focal_point;
	focal_length = _focal_length;
	up = _up;
	right = _right;
	forward = _forward;
	image_h = _image_h;
	image_w = _image_w;
	resH = _resH;
	resW = _resW;
	pixelH = (float)image_h / (float)resH;
	pixelW = (float)image_w / (float)resW;
}


Camera::~Camera()
{
}

Eigen::Vector3f  Camera::getWorldCoordForPixel(int i, int j) {
	float r = ((0.5f - ((0.5f + (float)j) / resW))*image_w);
	float b = ((0.5f - ((0.5f + (float)i) / resH))*image_h);

	return (focal_point + (focal_length*forward) + (b*up) - (r*right));
}
