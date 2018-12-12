#include <opencv2/core/mat.hpp>
#include <Eigen/src/Core/Matrix.h>

class Texture {
public:
    cv::Mat texture;
    int flag;
    int width;
    int height;

    Texture();
    void generateTexture(int width, int height);
    void loadTexture(std::string _fileName);
    Eigen::Vector3f getColourFromTexture(float u, float v);
};
