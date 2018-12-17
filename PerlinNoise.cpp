#include <random>
#include <iostream>
#include "PerlinNoise.h"

using namespace std;

PerlinNoise::PerlinNoise() {
}

void PerlinNoise::setNoiseTable(int seed){
    int perm[tableSize];

    vector<int> permvec;
    permvec.resize(256);
    iota(permvec.begin(), permvec.end(), 0);
    default_random_engine e(seed);
    shuffle(permvec.begin(), permvec.end(), e);
    permvec.insert(permvec.end(), permvec.begin(), permvec.end());
    for(int x=0;x<512;x++) {
        noiseTable[x] = permvec[x%256];
    }

}

float PerlinNoise::fade(float t) {
    // Fade function as defined by Ken Perlin.  This eases coordinate values
    // so that they will "ease" towards integral values.  This ends up smoothing
    // the final output.
    // 6t^5 - 15t^4 + 10t^3
    return t*t*t*(t*(t*6-15)+10);
}

int PerlinNoise::increment(int num) {
    num++;
//    if (repeat > 0) num %= repeat;

    return num;
}

float PerlinNoise::lerp(float a, float b, float x) {
    return a + x * (b - a);
}

float PerlinNoise::perlin(Eigen::Vector3f in) {
//    if(repeat > 0) {									// If we have any repeat on, change the coordinates to their "local" repetitions
//        x = x%repeat;
//        y = y%repeat;
//        z = z%repeat;
//    }
    int xi = (int)in[0] & 255;								// Calculate the "unit cube" that the point asked will be located in
    int yi = (int)in[1] & 255;								// The left bound is ( |_x_|,|_y_|,|_z_| ) and the right bound is that
    int zi = (int)in[2] & 255;								// plus 1.  Next we calculate the location (from 0.0 to 1.0) in that cube.

    float xf = in[0]-(int)in[0];								// We also fade the location to smooth the result.
    float yf = in[1]-(int)in[1];
    float zf = in[2]-(int)in[2];

    float u = fade(xf);
    float v = fade(yf);
    float w = fade(zf);

    int aaa, aba, aab, abb, baa, bba, bab, bbb;
    aaa = noiseTable[noiseTable[noiseTable[xi]+yi]+ zi];
    aba = noiseTable[noiseTable[noiseTable[xi]+increment(yi)]+zi];
    aab = noiseTable[noiseTable[noiseTable[xi]+yi]+increment(zi)];
    abb = noiseTable[noiseTable[noiseTable[xi]+increment(yi)]+increment(zi)];
    baa = noiseTable[noiseTable[noiseTable[increment(xi)]+yi]+zi];
    bba = noiseTable[noiseTable[noiseTable[increment(xi)]+increment(yi)]+zi];
    bab = noiseTable[noiseTable[noiseTable[increment(xi)]+yi]+increment(zi)];
    bbb = noiseTable[noiseTable[noiseTable[increment(xi)]+increment(yi)]+increment(zi)];

    float x1, x2, y1, y2;
    // The gradient function calculates the dot product between a pseudorandom
    // gradient vector and the vector from the input coordinate to the 8
    // surrounding points in its unit cube.
    // This is all then lerped together as a sort of weighted average based on the faded (u,v,w)
    // values we made earlier.
    x1 = lerp(gradient(aaa,xf, yf, zf), gradient(baa, xf-1, yf  , zf), u);
    x2 = lerp(gradient(aba,xf, yf, zf), gradient(bba, xf-1, yf-1, zf), u);
    y1 = lerp(x1, x2, v);

    x1 = lerp(gradient(aab,xf, yf, zf-1), gradient(bab, xf-1, yf  , zf-1), u);
    x2 = lerp(gradient(abb,xf, yf, zf-1), gradient(bbb, xf-1, yf-1, zf-1), u);
    y2 = lerp (x1, x2, v);


    return (lerp (y1, y2, w)+1)/2;						// For convenience we bound it to 0 - 1 (theoretical min/max before is -1 - 1)
}

// Take the hashed value and take the first 4 bits of it (15 == 0b1111)
// If the most significant bit (MSB) of the hash is 0 then set u = x.  Otherwise y.
// In Ken Perlin's original implementation this was another conditional operator (?:).  I
// If the first and second significant bits are 0 set v = y
// If the first and second significant bits are 1 set v = x
// If the first and second significant bits are not equal (0/1, 1/0) set v = z
// Use the last 2 bits to decide if u and v are positive or negative.  Then return their addition.
float PerlinNoise::gradient(int hash, float x, float y, float z) {
    int h = hash & 15;
    /*  8 = 0b1000 */
    /* 4 = 0b0100 */
    /* 12 = 0b1100 */
    /* 14 = 0b1110*/
    float u = h < 8 ? x : y;

    float v;
    if(h < 4) v = y;
    else if(h == 12  || h == 14 ) v = x;
    else v = z;
    float g = ((h&1) == 0 ? u : -u)+((h&2) == 0 ? v : -v);
    return g;
}

float PerlinNoise::octavePerlin(float x, float y, float z, int octaves, float persistence) {
    float total = 0;
    float frequency = 4;
    float amplitude = 16;
    float maxValue = 0;			// Used for normalizing result to 0.0 - 1.0

    for(int i=0;i<octaves;i++) {
        Eigen::Vector3f point = {x * frequency, y * frequency, z * frequency};
        total += perlin(point) * amplitude;

        maxValue += amplitude;

        amplitude *= persistence;
        frequency *= 2;
    }
//    cout << maxValue << endl;
    return total/maxValue;
}


float PerlinNoise::turbulence(float x, float y, float z, float size)
{
    float value = 0.0f, initialSize = size;

    while(size >= 1) {

        value += smoothNoise(x/size, y/size) * size;
//        value += perlin(Eigen::Vector3f {x / size, y / size, 1}) * size;
        size /= 2.0f;
    }

    return( 128.0f * value / initialSize);
}

float PerlinNoise::smoothNoise(float x, float y)
{
    //get fractional part of x and y
    float fractX = x - int(x);
    float fractY = y - int(y);
    
    //wrap around
    int x1 = (int(x) + 256) % 256;
    int y1 = (int(y) + 256) % 256;

    //neighbor values
    int x2 = (x1 + 256 - 1) % 256;
    int y2 = (y1 + 256 - 1) % 256;

    //smooth the noise with bilinear interpolation
    float value = 0.0;
    value += fractX     * fractY     * noise[y1][x1];
    value += (1 - fractX) * fractY     * noise[y1][x2];
    value += fractX     * (1 - fractY) * noise[y2][x1];
    value += (1 - fractX) * (1 - fractY) * noise[y2][x2];

    return value;
}


void PerlinNoise::generateNoise()
{
    for (int y = 0; y < 256 ; y++) {
        for (int x = 0; x < 256; x++) {
            noise[y][x] = (rand() % 32768) / 32768.0f;
        }
    }
}
