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
	int MAX_DEPTH = 2;

	Scene(int resH, int resW, float _ambientIntensity, Eigen::Vector3f _ambientColour);
	~Scene();
	std::vector<cv::Mat> setupScene(void);
	bool getClosestObj(Eigen::Vector3f rayPoint, Eigen::Vector3f rayDirection, Intersection &closestPoint);
	Eigen::Vector3f rayTrace(Eigen::Vector3f rayPoint, Eigen::Vector3f rayDirection, int depth);
	bool checkShadow(Intersection point, Light light);
	Eigen::Vector3f reflect(Eigen::Vector3f ray, Intersection point);
	Eigen::Vector3f refract(Eigen::Vector3f ray, Intersection point, float ri);
    float fresnel(const Eigen::Vector3f ray, Intersection point, float ri);
};