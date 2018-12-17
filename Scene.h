/***************************************************************************
 * Scene class holds a list of lights and SceneObjects alsongside the
 * scene dimensions and the max recursion depth. Implements methods for
 * raytracing, finding the next closest object in the scene, checking for
 * shadows, getting the refection and refraction vectors, the fresnel
 * calculations and getting the uv coords for a given pixel
 */
#pragma once
#include <vector>
#include "opencv2/opencv.hpp"
#include <Eigen/Core>
#include "SceneObject.h"
#include "Light.h"
#include "Ray.h"
#include "Intersection.h"

class Scene {
public:
	int resH, resW;
	Eigen::Vector3f ambient;
	std::vector<SceneObject*> sceneObjects;
	std::vector<Light*> sceneLights;
	int MAX_DEPTH = 4;

	Scene(int resH, int resW, float _ambientIntensity, Eigen::Vector3f _ambientColour);
	~Scene();
	std::vector<cv::Mat> setupScene(void);
	bool getClosestObj(Ray ray, Intersection &closestPoint, Intersection &closestBoundingSpherePoint, int depth);
	Eigen::Vector3f rayTrace(Ray ray, int depth);
	bool checkShadow(Intersection point, Light light);
	Eigen::Vector3f reflect(Eigen::Vector3f ray, Intersection point);
	Eigen::Vector3f refract(Eigen::Vector3f ray, Intersection point, float ri);
    void fresnel(const Eigen::Vector3f ray, Intersection point, float ri, float &kr, float &kt);
    void getUVCoords(Intersection point, BoundingSphere boundingSphere, float &u, float &v);
};