#include "Scene.h"
#include <vector>
#include <Eigen/Core>
#include "Mesh.h"
#include "opencv2/core/eigen.hpp"
#include "Intersection.h"
#include <limits>

using namespace std;

const float SMALL_E = 1e-2;

Scene::Scene(int _resH, int _resW, float _ambientIntensity, Eigen::Vector3f _ambientColour) {
	resH = _resH;
	resW = _resW;
	ambient = _ambientIntensity * _ambientColour;
}


Scene::~Scene() = default;

std::vector<cv::Mat> Scene::setupScene() {
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

bool Scene::getClosestObj(Ray ray, Intersection &closestPoint) {
	float closest = FLT_MAX;
	int closestObjIndex = -1;
	float current_t;
	Eigen::Vector3f test;
	Intersection point;
	for (int obj_index = 0; obj_index < sceneObjects.size(); obj_index++) {
		point = (sceneObjects.at(obj_index)->intersect(ray));
		current_t = point.shortest_distance_t;
		if (current_t > 0 && current_t < closest) {
			closest = current_t;
			closestObjIndex = obj_index;
			closestPoint = point;
		}
	}
	if (closestObjIndex != -1) {
	    closestPoint.closestObjIndex = closestObjIndex;
		return true;
	}
	return false;
}

Eigen::Vector3f Scene::rayTrace(Ray ray, int depth) {
	if (depth > MAX_DEPTH) {
		return Eigen::Vector3f{ 0, 0, 0 };
	}
	Intersection point;
	if (getClosestObj(ray, point)) {
		SceneObject* obj = sceneObjects.at(point.closestObjIndex);
		Eigen::Vector3f objDiffuseColour(obj->material.kd);
		Eigen::Vector3f objSpecularColour(obj->material.ks);

		Light light;
		Eigen::Vector3f n(point.normal*-1);
		Eigen::Vector3f lightReflection;
		float diffuseComponent;
		float specularComponent;

		Eigen::Vector3f returnColour(0, 0, 0);
		for (auto &sceneLight : sceneLights) {
			light = *sceneLight;
			if (checkShadow(point, light)) {
				Eigen::Vector3f l((light.direction *-1));
				diffuseComponent = n.dot(l*-1);
				lightReflection = l - (2.0*(l.dot(n)*n));
				if (lightReflection.dot(ray.direction) > 0) {
					specularComponent = powf(lightReflection.dot(ray.direction), 20);
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
		Eigen::Vector3f refractionColour;
		Eigen::Vector3f reflectionColour;
		float kr = fresnel(ray.direction, point, obj->material.ri);

		if (kr < 1) {
			point.intersectionPoint = point.intersectionPoint + SMALL_E * ray.direction;
			Ray refractionRay(point.intersectionPoint, refract(ray.direction, point, obj->material.ri));
			refractionColour = rayTrace(refractionRay, depth+1);
		}
		Ray reflectionRay(point.intersectionPoint, reflect(ray.direction, point));
		reflectionColour = obj->material.kr * rayTrace(reflectionRay, depth+1);
		returnColour += reflectionColour * kr + refractionColour * (1 - kr);
		return returnColour;
	}
	return Eigen::Vector3f{ 0, 0, 0 };
}


bool Scene::checkShadow(Intersection point, Light light) {
	Intersection returnedPoint;
	float closest = FLT_MAX;
	float current_t;
	
	for (int obj_index = 0; obj_index < sceneObjects.size(); obj_index++) {
		Ray shadowRay(point.intersectionPoint, (light.direction * -1));
		returnedPoint = (sceneObjects.at(obj_index)->intersect(shadowRay));
		current_t = returnedPoint.shortest_distance_t;
		if (current_t < closest && obj_index != point.closestObjIndex && current_t > 0.0002) {
			return false;
		}
	}
	return true;
}

Eigen::Vector3f Scene::reflect(Eigen::Vector3f ray, Intersection point) {
    Eigen::Vector3f new_ray;

    new_ray = ray - 2 * point.normal.dot(ray) * point.normal;
    return new_ray;
}

Eigen::Vector3f Scene::refract(Eigen::Vector3f ray, Intersection point, float ri)
{
	ray = ray/ray.norm();
//	Eigen::Vector3f n = point.normal/point.normal.norm();
	Eigen::Vector3f n = point.normal;
	float cosi = ray.dot(point.normal);
	if (cosi > 1) cosi = 1.0f;
	if (cosi < -1) cosi = -1.0f;
	float etai = 1, etat = ri;
	if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= -point.normal; }
	float eta = etai / etat;
	float k = 1 - eta * eta * (1 - cosi * cosi);

	if (k < 0) {
	    return Eigen::Vector3f{ 0, 0, 0 };
	}
	else {
        eta * ray + (eta * cosi - sqrtf(k)) * n;
	}
}

float Scene::fresnel(const Eigen::Vector3f ray, Intersection point, float ri)
{
	float kr;
	float cosi = ray.dot(point.normal);
	if (cosi > 1) cosi = 1.0f;
	if (cosi < -1) cosi = -1.0f;
	float etai = 1, etat = ri;
	if (cosi > 0) { std::swap(etai, etat); }
	// Compute sini using Snell's law
	float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
	// Total internal reflection
	if (sint >= 1) {
		kr = 1;
	}
	else {
		float cost = sqrtf(std::max(0.f, 1 - sint * sint));
		cosi = fabsf(cosi);
		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		kr = (Rs * Rs + Rp * Rp) / 2;
	}
	return kr;
	// As a consequence of the conservation of energy, transmittance is given by:
	// kt = 1 - kr;
}