#include "Scene.h"
#include <vector>
#include <Eigen/Core>
#include "Mesh.h"
#include "opencv2/core/eigen.hpp"
#include "Intersection.h"

using namespace std;

Scene::Scene(int _resH, int _resW, float _ambientIntensity, Eigen::Vector3f _ambientColour) {
	resH = _resH;
	resW = _resW;
	ambient = _ambientIntensity * _ambientColour;
}


Scene::~Scene()
{
}

std::vector<cv::Mat> Scene::setupScene(void) {
	Eigen::MatrixXf sceneR(Eigen::MatrixXf::Ones(resH, resW) * 0);
	Eigen::MatrixXf sceneG(Eigen::MatrixXf::Ones(resH, resW) * 0);
	Eigen::MatrixXf sceneB(Eigen::MatrixXf::Ones(resH, resW) * 0);
	std::vector<cv::Mat> channels;

	cv::Mat matR, matG, matB;

	cv::eigen2cv(sceneR, matR);
	cv::eigen2cv(sceneG, matG);
	cv::eigen2cv(sceneB, matB);

	channels.push_back(matR);
	channels.push_back(matG);
	channels.push_back(matB);

	return channels;
}

Eigen::Vector3f Scene::getPixelColour(Eigen::Vector3f rayPoint, Eigen::Vector3f rayDirection) {
	float closest = FLT_MAX;
	int closestObjIndex = -1;
	float current_t;
	Eigen::Vector3f test;
	Intersection point;
	Intersection closestPoint;
	for (int obj_index = 0; obj_index < sceneObjects.size(); obj_index++) {
		point = (sceneObjects.at(obj_index)->intersect(rayPoint, rayDirection));
		current_t = point.shortest_distance_t;
		if (current_t > 0 && current_t < closest) {
			closest = current_t;
			closestObjIndex = obj_index;
			closestPoint = point;
		}
	}
	if (closestObjIndex != -1) {
		return getPixelColourComponents(closestPoint, closestObjIndex, rayDirection);
	}
	return Eigen::Vector3f{ 0, 0, 0 };
}

Eigen::Vector3f Scene::getPixelColourComponents(Intersection point, int closestObjIndex, Eigen::Vector3f rayDirection) {
	Light light;
	SceneObject* obj = sceneObjects.at(closestObjIndex);
	Eigen::Vector3f n(point.getNormal()*-1);
	Eigen::Vector3f objDiffuseColour(obj->diffuseColour);
	Eigen::Vector3f objSpecularColour(obj->specular);
	Eigen::Vector3f reflection;
	Eigen::Vector3f ray(rayDirection/rayDirection.norm());
	float diffuseComponent;
	float specularComponent;
	Eigen::Vector3f returnColour(0, 0, 0);

	for (int light_index = 0; light_index < sceneLights.size(); light_index++) {
		light = *sceneLights.at(light_index);
		if (checkShadow(point, light, closestObjIndex)) {
			Eigen::Vector3f l((light.direction *-1));
			diffuseComponent = n.dot(l*-1);
			reflection = l - (2.0*(l.dot(n)*n));
			if (reflection.dot(ray) > 0) {
				specularComponent = pow(reflection.dot(ray), 20);
				returnColour(0) = returnColour(0) + (light.local(0) * specularComponent * objSpecularColour(0));
				returnColour(1) = returnColour(1) + (light.local(1) * specularComponent * objSpecularColour(1));
				returnColour(2) = returnColour(2) + (light.local(2) * specularComponent * objSpecularColour(2));
			}
			else {
				specularComponent = 0;
			}

			if (diffuseComponent >= 0) {
				returnColour(0) = returnColour(0) + (light.local(0) * diffuseComponent * objDiffuseColour(0));
				returnColour(1) = returnColour(1) + (light.local(1) * diffuseComponent * objDiffuseColour(1));
				returnColour(2) = returnColour(2) + (light.local(2) * diffuseComponent * objDiffuseColour(2));
			}
		}
		returnColour += ambient;
	}
	return returnColour;
}


bool Scene::checkShadow(Intersection point, Light light, int closestObjIndex) {
	Intersection returnedPoint;
	float closest = FLT_MAX;
	float current_t = FLT_MAX;
	
	for (int obj_index = 0; obj_index < sceneObjects.size(); obj_index++) {
		returnedPoint = (sceneObjects.at(obj_index)->intersect(point.getIntersectionPoint(), (light.direction * -1)));
		current_t = returnedPoint.shortest_distance_t;
		if (current_t < closest && obj_index != closestObjIndex && current_t > 0.0002) {
			return false;
		}
	}
	return true;
}