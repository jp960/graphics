//
// Created by janhavi on 11/12/18.
//

#include <random>
#include "PerlinNoise.h"


PerlinNoise::PerlinNoise() {
    unsigned seed = 2016;
    std::mt19937 generator(seed);
    std::uniform_real_distribution distribution;
    auto dice = std::bind(distribution, generator);
    float gradientLen2;
    for (unsigned i = 0; i < tableSize; ++i) {
        do {
            gradients[i] = Eigen::Vector3f(2 * (float)dice() - 1, 2 * (float)dice() - 1, 2 * (float)dice() - 1);
            gradientLen2 = gradients[i].squaredNorm();
        } while (gradientLen2 > 1);
        gradients[i] /= sqrtf(gradientLen2); // normalize gradient
        permutationTable[i] = i;
    }

    std::uniform_int_distribution distributionInt;
    auto diceInt = std::bind(distributionInt, generator);
    // create permutation table
    for (unsigned i = 0; i < tableSize; ++i) {
        std::swap(permutationTable[i], permutationTable[diceInt() & tableSizeMask]);
    }
    // extend the permutation table in the index range [256:512]
    for (unsigned i = 0; i < tableSize; ++i) {
        permutationTable[tableSize + i] = permutationTable[i];
    }
}

int PerlinNoise::hash(const int &x, const int &y, const int &z) { return permutationTable[permutationTable[permutationTable[x] + y] + z]; }

float PerlinNoise::smoothstep(const float &t) {
    return t * t * (3 - 2 * t);
}

float PerlinNoise::lerp(const float &lo, const float &hi, const float &t) {
    return lo * (1 - t) + hi * t;
}

float PerlinNoise::eval(const Eigen::Vector3f &p) {
    int xi0 = ((int)std::floor(p(0))) & tableSizeMask;
    int yi0 = ((int)std::floor(p(1))) & tableSizeMask;
    int zi0 = ((int)std::floor(p(2))) & tableSizeMask;

    int xi1 = (xi0 + 1) & tableSizeMask;
    int yi1 = (yi0 + 1) & tableSizeMask;
    int zi1 = (zi0 + 1) & tableSizeMask;

    float tx = p(0) - ((int)std::floor(p(0)));
    float ty = p(1) - ((int)std::floor(p(1)));
    float tz = p(2) - ((int)std::floor(p(2)));

    float u = smoothstep(tx);
    float v = smoothstep(ty);
    float w = smoothstep(tz);

    // gradients at the corner of the cell
    const Eigen::Vector3f &c000 = gradients[hash(xi0, yi0, zi0)];
    const Eigen::Vector3f &c100 = gradients[hash(xi1, yi0, zi0)];
    const Eigen::Vector3f &c010 = gradients[hash(xi0, yi1, zi0)];
    const Eigen::Vector3f &c110 = gradients[hash(xi1, yi1, zi0)];

    const Eigen::Vector3f &c001 = gradients[hash(xi0, yi0, zi1)];
    const Eigen::Vector3f &c101 = gradients[hash(xi1, yi0, zi1)];
    const Eigen::Vector3f &c011 = gradients[hash(xi0, yi1, zi1)];
    const Eigen::Vector3f &c111 = gradients[hash(xi1, yi1, zi1)];

    // generate vectors going from the grid points to p
    float x0 = tx, x1 = tx - 1;
    float y0 = ty, y1 = ty - 1;
    float z0 = tz, z1 = tz - 1;

    Eigen::Vector3f p000 = Eigen::Vector3f(x0, y0, z0);
    Eigen::Vector3f p100 = Eigen::Vector3f(x1, y0, z0);
    Eigen::Vector3f p010 = Eigen::Vector3f(x0, y1, z0);
    Eigen::Vector3f p110 = Eigen::Vector3f(x1, y1, z0);

    Eigen::Vector3f p001 = Eigen::Vector3f(x0, y0, z1);
    Eigen::Vector3f p101 = Eigen::Vector3f(x1, y0, z1);
    Eigen::Vector3f p011 = Eigen::Vector3f(x0, y1, z1);
    Eigen::Vector3f p111 = Eigen::Vector3f(x1, y1, z1);

    // linear interpolation
    float a = lerp(c000.dot(p000), c100.dot(p100), u);
    float b = lerp(c010.dot(p010), c110.dot(p110), u);
    float c = lerp(c001.dot(p001), c101.dot(p101), u);
    float d = lerp(c011.dot(p011), c111.dot(p111), u);

    float e = lerp(a, b, v);
    float f = lerp(c, d, v);

    return lerp(e, f, w); // g
}
