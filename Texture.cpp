#define OPENCV_TRAITS_ENABLE_DEPRECATED
#include <opencv2/imgcodecs.hpp>
#include <Eigen/Core>
#include <iostream>
#include "Texture.h"
#include "PerlinNoise.h"

using namespace std;

Texture::Texture() {}

void Texture::loadTexture(std::string _fileName) {
    texture = cv::imread(_fileName);
    width = texture.cols;
    height = texture.rows;
}

Eigen::Vector3f Texture::getColourFromTexture(float u, float v) {
    cv::Vec3b pixel = texture.at<cv::Vec3b>(cv::Point((int)(width - u*width), (int)(height - v*height)));
    Eigen::Vector3f colour(pixel[2], pixel[1], pixel[0]);
    return colour;
}

float Texture::getMarbleTexture(float x, float y, float z){
    PerlinNoise pn;
    pn.setNoiseTable(1);
    cv::Vec3b val = {255,255, 255};
    float xPeriod = 1.0f; //defines repetition of marble lines in x direction
    float yPeriod = 1.0f; //defines repetition of marble lines in y direction
    //turbPower = 0 ==> it becomes a normal sine pattern
    float turbPower = 4.0f; //makes twists
    float noise = pn.turbulence(fabs(x), fabs(y), fabs(z), 8);
//    float noise = pn.turbulence(x, y, z, 16);
    float xyzValue = x* xPeriod / width + y * yPeriod / height + (turbPower * noise);
    float sineValue = fabs(sin(xyzValue * 2* 3.14f));
    return 255*sineValue;
}

void Texture::generatePerlinTexture(std::string _fileName, int _width, int _height, int _depth, int seed) {
    // texture = width * height * depth
    PerlinNoise pn;
    pn.generateNoise();
    pn.setNoiseTable(seed);
    width = _width;
    height = _height;
    depth = _depth;
    int size[3] = {width, height, depth};
    cv::Mat tempTexture(3, size, cv::Vec3b::type);
    cv::Mat tt(width, height, cv::Vec3b::type);
    cv::Vec3b val = {255, 255, 255};
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < depth; k++) {
//                Eigen::Vector3f point = {(float) i/width, (float) j/height, (float) k/depth};
                Eigen::Vector3f point = {(float)i, (float)j, (float)k};

                float noise = pn.turbulence(point[0], point[1], point[2], 8)/256;
//                float noise = pn.perlin(point);
                float n;
//                n= 20*noise;
//                n = n - floor(n);
                n = noise;
                tt.at<cv::Vec3b>(cv::Point(i, j)) = n * val;

            }
        }
    }

    texture = tt;
    cv::Mat out;
    cv::Mat flip;
    cv::flip(tt, flip, 1);
//    hconcat(tt, flip, out);
    hconcat(tt, tt, out);
    cv::imwrite(_fileName, out);
}

void Texture::generateMarbleTexture(std::string _fileName, int _width, int _height, int _depth, int seed) {
    PerlinNoise pn;
    pn.setNoiseTable(seed);
    pn.generateNoise();
    width = _width;
    height = _height;
    depth = 2;
    int size[3] = {width, height, depth};
    cv::Mat tempTexture(3, size, cv::Vec3b::type);
    cv::Mat tt(width, height, cv::Vec3b::type);
    cv::Vec3b val = {255,255, 255};


    float xPeriod = 10.0f; //defines repetition of marble lines in x direction
    float yPeriod = 15.0f; //defines repetition of marble lines in y direction
    //turbPower = 0 ==> it becoms a normal sine pattern
    float turbPower = 5.0f; //makes twists

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < depth; k++) {
//                Eigen::Vector3f point = {(float) i/width, (float) j/height, (float) k/depth};
                Eigen::Vector3f point = {(float)i, (float)j, (float)k};
                float noise = pn.turbulence(point[0], point[1], point[2], 64);
//                float noise = pn.octavePerlin(point[0], point[1], point[2], 4, 0.5f );
//                float xyValue = i* xPeriod / width + j * yPeriod / height + (turbPower * noise);
//                float xyValue = point[0]* xPeriod / width + point[1] * yPeriod / height;
                float xValue = point[0]* xPeriod / width + turbPower * noise;
//                float xyValue = (point[0]* xPeriod /width)  + (point[1] * yPeriod /height);// + (turbPower * noise);
                float xyValue = (point[0]* xPeriod /width)  + (point[1] * yPeriod /height) + (turbPower * noise)/256;
//                float sineValue = fabs(sin((xValue  + (turbPower * noise))* 3.14159f));
//                float sineValue = fabs(sin(((yPeriod*3.14)*point[1] + turbPower*noise)));
                float sineValue = fabs(sin(2*xyValue* 3.14f));
;                tt.at<cv::Vec3b>(cv::Point(i, j)) = sineValue * val;

            }
        }
    }

    texture = tt;
    cv::Mat out;
    cv::Mat flip;
    cv::flip(tt, flip, 1);
//    hconcat(tt, flip, out);
    hconcat(tt, tt, out);
    cv::imwrite(_fileName, out);
}
