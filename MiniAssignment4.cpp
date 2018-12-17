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
#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>

using namespace std;

void thread_method(int thread_id, int numRows, int resW, std::vector<cv::Mat> *sceneChannels, Camera cam, Scene scene){
    Eigen::Vector3f pixel;
    Eigen::Vector3f pixelColour;
    int start = thread_id*numRows;
    int end  = start + numRows;
    cout << "Thread " << thread_id << " taking rows " << start << "->" << end<< endl;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < resW; j++) {
            Ray ray;
            pixel = cam.getWorldCoordForPixel(i, j);
            ray.point = cam.focal_point;
            ray.direction = pixel - cam.focal_point;
            ray.direction = ray.direction / ray.direction.norm();
            pixelColour = scene.rayTrace(ray, 0);
            sceneChannels->at(2).at<float>(i, j) = pixelColour[0];
            sceneChannels->at(1).at<float>(i, j) = pixelColour[1];
            sceneChannels->at(0).at<float>(i, j) = pixelColour[2];
        }
    }
    cout << "Thread " << thread_id << " finished" << endl;

}
int main()
{
	int resH = 1080;
	int resW = 1920;
	Scene scene(resH, resW, 0.2f, Eigen::Vector3f{ 255, 255, 255 });
	cv::Mat image1;
	cv::Mat image2;
	Eigen::Vector3f lightVector(0.5f, -0.5f, 0.5f);
    int numThreads = thread::hardware_concurrency();
    int numRows = resH/numThreads;
    thread threads[numThreads];




	lightVector = (lightVector / lightVector.norm());
	Light light(lightVector, 0.4f, Eigen::Vector3f{ 255, 255, 255 });

	Camera cam(Eigen::Vector3f{ 0, 0, 0 }, 1, Eigen::Vector3f{ 0, 1, 0 }, Eigen::Vector3f{ 1, 0, 0 }, Eigen::Vector3f{ 0, 0, 1 }, 2, 2, resH, resW);
	Sphere glassSphere(Eigen::Vector3f{ 0, 0, 4 }, 1);
	Sphere shinySphere(Eigen::Vector3f{ -3, 0, 4 }, 1);
	Sphere globe(Eigen::Vector3f{ 3, 0, 4 }, 1);
	Sphere plainSphere(Eigen::Vector3f{ 0, -3 , 4 }, 1);
	Sphere perlinSphere(Eigen::Vector3f{ -3, 0 , 4 }, 1);
    Sphere marbleSphere(Eigen::Vector3f{ 0, 3 , 4 }, 1);

    Mesh plane("/home/donal/Documents/Graphics/Janhavi/Meshs/plane.obj", Eigen::Vector3f{ 0, 0, 0 }, 1);
	Mesh cube("/home/donal/Documents/Graphics/Janhavi/Meshs/cube-tri.obj", Eigen::Vector3f{ 0, 0, 8 }, 1);
	Mesh bunny("/home/donal/Documents/Graphics/Janhavi/Meshs/bunny2.obj", Eigen::Vector3f{ 0, 0, 3 }, 15);
    Mesh cube1("/home/donal/Documents/Graphics/Janhavi/Meshs/cube-tri.obj", Eigen::Vector3f{ -2, 2, 8 }, 1);
    Mesh cube2("/home/donal/Documents/Graphics/Janhavi/Meshs/cube-tri.obj", Eigen::Vector3f{ 2, -2, 8 }, 1);
    Mesh cube3("/home/donal/Documents/Graphics/Janhavi/Meshs/cube-tri.obj", Eigen::Vector3f{ -2, -2, 8 }, 1);
    Mesh cube4("/home/donal/Documents/Graphics/Janhavi/Meshs/cube-tri.obj", Eigen::Vector3f{ 2, 2, 8 }, 1);

    Material shinySpherem(Eigen::Vector3f{ 255, 255, 255 }, Eigen::Vector3f{ 231, 47, 99 }, Eigen::Vector3f{ 255, 255, 255 }, 1.0f, 1.0f, 1);
	Material glassSpherem(Eigen::Vector3f{ 255, 255, 255 }, Eigen::Vector3f{ 255, 255, 255 }, Eigen::Vector3f{ 255, 255, 255 }, 1.0f, 1.0f, 2);
	Material simplem(Eigen::Vector3f{ 255, 255, 255 }, Eigen::Vector3f{ 255, 48, 99 }, Eigen::Vector3f{ 255, 255, 255 }, 1.0f, 1.0f, 0);
	Material planem(Eigen::Vector3f{ 255, 255, 255 }, Eigen::Vector3f{ 122, 122, 255 }, Eigen::Vector3f{ 255, 255, 255 }, 1.0f, 1.0f, 0);
	glassSpherem.ri = 1.52f;

	shinySphere.setMaterial(shinySpherem);
	glassSphere.setMaterial(glassSpherem);
	globe.setMaterial(simplem);
	plane.setMaterial(shinySpherem);
	cube.setMaterial(simplem);
	cube1.setMaterial(simplem);
	cube2.setMaterial(simplem);
	cube3.setMaterial(simplem);
	cube4.setMaterial(simplem);
	plainSphere.setMaterial(simplem);
	perlinSphere.setMaterial(simplem);
	bunny.setMaterial(simplem);
    marbleSphere.setMaterial(simplem);
	Texture globeTexture;
	Texture noTexture;
	Texture perlinTexture;
	Texture marbleTexture;

	noTexture.flag = 0;
	globeTexture.flag = 1;
	perlinTexture.flag = 1;
	marbleTexture.flag = 1;



    cv::Mat emptyTexture(256, 256, CV_64F, 0.0);
    noTexture.texture =emptyTexture;
    noTexture.width = 256;
    noTexture.width = 256;



	globeTexture.loadTexture("/home/donal/Documents/Graphics/Janhavi/Meshs/earth.jpg");
	perlinTexture.generatePerlinTexture("/home/donal/Documents/Graphics/Janhavi/Meshs/perlin.png", 256, 256, 1, 5);
	perlinTexture.loadTexture("/home/donal/Documents/Graphics/Janhavi/Meshs/perlin.png");
	marbleTexture.generateMarbleTexture("/home/donal/Documents/Graphics/Janhavi/Meshs/marble.png", 512, 512, 1, 1);
	marbleTexture.loadTexture("/home/donal/Documents/Graphics/Janhavi/Meshs/marble.png");

//	cv::namedWindow("texture", CV_WINDOW_AUTOSIZE);
//	cv::imshow("texture", marbleTexture.texture);
//	cvWaitKey(0);
    marbleSphere.setTexture(marbleTexture);
	glassSphere.setTexture(noTexture);
	shinySphere.setTexture(noTexture);
	plane.setTexture(globeTexture);
	globe.setTexture(globeTexture);
	plainSphere.setTexture(noTexture);
	perlinSphere.setTexture(perlinTexture);
	bunny.setTexture(marbleTexture);

	globe.setTexture(globeTexture);
	cube1.setTexture(globeTexture);
	cube2.setTexture(perlinTexture);
	cube3.setTexture(marbleTexture);
	cube4.setTexture(noTexture);



    scene.sceneObjects.push_back(&glassSphere);
	scene.sceneObjects.push_back(&shinySphere);
	scene.sceneObjects.push_back(&plainSphere);
	scene.sceneObjects.push_back(&perlinSphere);
	scene.sceneObjects.push_back(&marbleSphere);
	scene.sceneObjects.push_back(&globe);
//	scene.sceneObjects.push_back(&cube);
	scene.sceneObjects.push_back(&cube1);
	scene.sceneObjects.push_back(&cube2);
	scene.sceneObjects.push_back(&cube3);
	scene.sceneObjects.push_back(&cube4);
	scene.sceneObjects.push_back(&bunny);
//	scene.sceneObjects.push_back(&plane);

	scene.sceneLights.push_back(&light);

	std::vector<cv::Mat> sceneChannels(scene.setupScene());

	Eigen::Vector3f pixel;
	Eigen::Vector3f pixelColour;

    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < numThreads; i++){
        threads[i] = std::thread(thread_method, i, numRows, resW, &sceneChannels, cam, scene);
    }
    for (int i = 0; i < numThreads; i++){
        threads[i].join();
    }
    auto end = std::chrono::system_clock::now();
    chrono::duration<double> diff = end-start;
    cout << "Threaded time: " << diff.count() << endl;

    merge(sceneChannels, image1);
    cv::imwrite("threaded.png", image1);


	return 0;
}