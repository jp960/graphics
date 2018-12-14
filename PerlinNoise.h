#include <Eigen/Core>

class PerlinNoise {
public:
    static const unsigned tableSize = 256;
    int permutationTable[tableSize];
    int noiseTable[tableSize*2];
    int seed;
    float noise[256][256];
    PerlinNoise();
    void setNoiseTable(int seed);
    float fade(float t);
    int increment(int num);
    float lerp(float a, float b, float x);
    float perlin(Eigen::Vector3f in);
    float gradient(int hash,  float x, float y, float z);
    float octavePerlin(float x, float y, float z, int octaves, float persistence);
    float turbulence(float x, float y, float z, float size);
    float smoothNoise(float x, float y);
    void generateNoise();

};