#include "Utilities.h"

class MapGen{
public:
    FastNoiseLite noise;
    float * index;
    MapGen(int seed, int width, int height, int octaves, float lacunarity, float persistence){
        noise = FastNoiseLite(seed);
        noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        noise.SetFractalType(FastNoiseLite::FractalType_FBm);
        noise.SetFractalLacunarity(lacunarity);
        noise.SetFractalOctaves(octaves);
        noise.SetFractalWeightedStrength(persistence);
        index = (float *)malloc(width * height * sizeof(index));
        for (int y = 0; y < height; ++y){
            for (int x = 0; x < width; ++x){
                index[y * width + x] = noise.GetNoise((float)x, float(y));
                // for (int octave = 0; octave < std::max(octaves - 1, 0); ++octave){
                //     index[y * width + x] += noise.GetNoise((float)x * std::pow(lacunarity, octave + 1), float(y) * std::pow(lacunarity, octave + 1)) * std::pow(persistence, octave);
                // }
            }
        }
    }
    float getNoise(int x, int y){
        return noise.GetNoise((float)x, float(y));
    }
private:
};