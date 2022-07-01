#include "Utilities.h"

class MapGen{
public:
    FastNoiseLite noise;
    MapGen(int seed, int width, int height, int octaves, float lacunarity, float persistence){
        noise = FastNoiseLite(seed);
        noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        noise.SetFractalType(FastNoiseLite::FractalType_FBm);
        noise.SetFractalLacunarity(lacunarity);
        noise.SetFractalOctaves(octaves);
        noise.SetFractalWeightedStrength(persistence);
    }
    float getNoise(int x, int y){
        return noise.GetNoise((float)x, float(y));
    }
private:
};
