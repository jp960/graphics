#include <Eigen/Core>

class PerlinNoise {
public:
    static const unsigned tableSize = 256;
    static const unsigned tableSizeMask = tableSize - 1;
    Eigen::Vector3f gradients[tableSize];
    unsigned permutationTable[tableSize * 2];

    PerlinNoise();
    int hash(const int &x, const int &y, const int &z);
    float eval(const Eigen::Vector3f &p);
    float smoothstep(const float &t);
    float lerp(const float &lo, const float &hi, const float &t);
};