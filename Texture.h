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
    float turbulence();
};
