/***************************************************************************
 *  This class holds the Texture information for a SceneObject. This is the
 *  mat contiaining the texture itself, a flag to state if said object has
 *  a texture and the dimensions of the texture, It also has methods to
 *  load and generate different textures.
 */
#pragma once
#include <opencv2/core/mat.hpp>
#include <Eigen/src/Core/Matrix.h>

class Texture {
public:
    cv::Mat texture;
    int flag;
    int width;
    int height;
    int depth;

    Texture();
    void loadTexture(std::string _fileName);
    Eigen::Vector3f getColourFromTexture(float u, float v);
    void generatePerlinTexture(std::string _fileName, int width, int height, int depth, int seed);
    void generateMarbleTexture(std::string _fileName, int width, int height, int depth, int seed);
    float getMarbleTexture(float x, float y, float z);
};
