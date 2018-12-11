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
#include "Ray.h"
#include "Material.h"

using namespace std;

int main()
{
	int resH = 512;
	int resW = 512;
	Scene scene(resH, resW, 0.2f, Eigen::Vector3f{ 255, 255, 255 });
	cv::Mat image;
	Eigen::Vector3f lightVector(0.5f, -0.5f, 0.5f);

	lightVector = (lightVector / lightVector.norm());

	Material shinySpherem(Eigen::Vector3f{ 255, 255, 255 }, Eigen::Vector3f{ 231, 47, 99 }, Eigen::Vector3f{ 255, 255, 255 }, 1.0f, 1.0f, 0);
	Material glassSpherem(Eigen::Vector3f{ 255, 255, 255 }, Eigen::Vector3f{ 255, 255, 255 }, Eigen::Vector3f{ 255, 255, 255 }, 1.0f, 1.0f, 2);
	Material behindSpherem(Eigen::Vector3f{ 255, 255, 255 }, Eigen::Vector3f{ 231, 47, 99 }, Eigen::Vector3f{ 255, 255, 255 }, 1.0f, 1.0f, 0);
	Material planem(Eigen::Vector3f{ 255, 255, 255 }, Eigen::Vector3f{ 122, 122, 255 }, Eigen::Vector3f{ 255, 255, 255 }, 1.0f, 1.0f, 1);

	glassSpherem.ri = 1.52f;
	Sphere glassSphere(Eigen::Vector3f{ 2, 1, 4 }, 1);
	Sphere shinySphere(Eigen::Vector3f{ -2, 1, 5 }, 1);
	Sphere behindSphere(Eigen::Vector3f{ -1, -1, 8 }, 1);
	shinySphere.setMaterial(shinySpherem);
	glassSphere.setMaterial(glassSpherem);
	behindSphere.setMaterial(behindSpherem);
	Camera cam(Eigen::Vector3f{ 0, 0, 0 }, 1, Eigen::Vector3f{ 0, 1, 0 }, Eigen::Vector3f{ 1, 0, 0 }, Eigen::Vector3f{ 0, 0, 1 }, 2, 2, resH, resW);
	Mesh plane("/home/janhavi/Documents/Final Year/graphics/plane.obj", Eigen::Vector3f{ 0, 0, 0 }, 1);
	Mesh cube("/home/janhavi/Documents/Final Year/graphics/cube-tri.obj", Eigen::Vector3f{ 1, 1, 8 }, 1);
	plane.setMaterial(planem);
	cube.setMaterial(behindSpherem);
	Light light(lightVector, 0.4f, Eigen::Vector3f{ 255, 255, 255 });

	scene.sceneObjects.push_back(&glassSphere);
	scene.sceneObjects.push_back(&shinySphere);
//	scene.sceneObjects.push_back(&behindSphere);
	scene.sceneObjects.push_back(&plane);
	scene.sceneObjects.push_back(&cube);
	scene.sceneLights.push_back(&light);

	std::vector<cv::Mat> sceneChannels(scene.setupScene());

	Eigen::Vector3f pixel;
	Eigen::Vector3f pixelColour;


	for (int i = 0; i < resH; i++) {
		for (int j = 0; j < resW; j++) {
		    Ray ray;
			pixel = cam.getWorldCoordForPixel(i, j);
			ray.point = cam.focal_point;
			ray.direction = pixel - cam.focal_point;
			ray.direction = ray.direction / ray.direction.norm();
			pixelColour = scene.rayTrace(ray, 0);
			sceneChannels.at(2).at<float>(i, j) = pixelColour[0];
			sceneChannels.at(1).at<float>(i, j) = pixelColour[1];
			sceneChannels.at(0).at<float>(i, j) = pixelColour[2];
		}
	}

	merge(sceneChannels, image);
	cv::imwrite("test.png", image);
	return 0;
}