// MiniAssignment4.cpp : Defines the entry point for the console application.
//

#include "math.h"
#include <algorithm>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "opencv2/core/eigen.hpp"
#include "opencv2/opencv.hpp"
#include "Scene.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"

using namespace std;

int main()
{
	int resH = 256;
	int resW = 256;
	Scene scene(resH, resW, 0.2f, Eigen::Vector3f{ 255, 255, 255 });
	cv::Mat image;
	Eigen::Vector3f lightVector(1, -1, 1);

	lightVector = (lightVector / lightVector.norm());

	Sphere sphere(Eigen::Vector3f{ 0, 1, 3 }, 1.5, Eigen::Vector3f{ 47, 231, 99 }, Eigen::Vector3f{ 255, 255, 255 });
	Sphere sphere2(Eigen::Vector3f{ -2, 1, 6 }, 1, Eigen::Vector3f{ 231, 47, 99 }, Eigen::Vector3f{ 255, 255, 255 });
	Camera cam(Eigen::Vector3f{ 0, 0, 0 }, 1, Eigen::Vector3f{ 0, 1, 0 }, Eigen::Vector3f{ 1, 0, 0 }, Eigen::Vector3f{ 0, 0, 1 }, 2, 2, resH, resW);
	Mesh mesh("/home/donal/Documents/Graphics/Janhavi/Meshs/plane.obj", Eigen::Vector3f{ 0, 0, 0 }, 1, Eigen::Vector3f{ 122, 122, 255 }, Eigen::Vector3f{ 255, 255, 255 });
	Light light(lightVector, 0.4f, Eigen::Vector3f{ 255, 255, 255 });

	scene.sceneObjects.push_back(&sphere);
	//scene.sceneObjects.push_back(&sphere2);
	scene.sceneObjects.push_back(&mesh);
	scene.sceneLights.push_back(&light);

	std::vector<cv::Mat> sceneChannels(scene.setupScene());

	Eigen::Vector3f pixel;
	Eigen::Vector3f rayPoint;
	Eigen::Vector3f rayDirection;
	Eigen::Vector3f pixelColour;


	for (int i = 0; i < resH; i++) {
		for (int j = 0; j < resW; j++) {
			pixel = cam.getWorldCoordForPixel(i, j);
			rayPoint = cam.focal_point;
			rayDirection = pixel - cam.focal_point;
			rayDirection = rayDirection / rayDirection.norm();
			pixelColour = scene.getPixelColour(rayPoint, rayDirection);
			sceneChannels.at(2).at<float>(i, j) = pixelColour[0];
			sceneChannels.at(1).at<float>(i, j) = pixelColour[1];
			sceneChannels.at(0).at<float>(i, j) = pixelColour[2];
		}
	}

	merge(sceneChannels, image);
	cv::imwrite("test.png", image);
	//std::getchar();
	return 0;
}