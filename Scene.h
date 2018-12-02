#pragma once
#include <vector>
#include "opencv2/opencv.hpp"
#include <Eigen/Core>
#include "SceneObject.h"
#include "Light.h"
#include "Intersection.h"

class Scene {
public:
	int resH, resW;
	Eigen::Vector3f ambient;
	std::vector<SceneObject*> sceneObjects;
	std::vector<Light*> sceneLights;

	Scene(int resH, int resW, float _ambientIntensity, Eigen::Vector3f _ambientColour);
	~Scene();
	std::vector<cv::Mat> setupScene(void);
	Eigen::Vector3f getPixelColour(Eigen::Vector3f rayPoint, Eigen::Vector3f rayDirection);
	Eigen::Vector3f getPixelColourComponents(Intersection point, int closestObjIndex, Eigen::Vector3f rayDirection);
	bool checkShadow(Intersection point, Light light, int closestObjIndex);
};