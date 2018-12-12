#include <opencv2/imgcodecs.hpp>
#include <Eigen/Core>
#include <iostream>
#include "Texture.h"

using namespace std;

Texture::Texture() {}

void Texture::generateTexture(int _width, int _height) {

}

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

