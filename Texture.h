#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include<glm/glm.hpp>
using namespace glm;
class Texture {
public:
    virtual vec3 value(double u, double v, const vec3& p) const = 0;
};

class Noise_texture : public Texture {
public:
    Noise_texture() {}
    Noise_texture(double sc) : scale(sc) {}

    virtual vec3 value(double u, double v, const vec3& p) const override {
        // return color(1,1,1)*0.5*(1 + noise.turb(scale * p));
        // return color(1,1,1)*noise.turb(scale * p);
        return vec3(1, 1, 1) * 0.5f * static_cast<float>(1 + sin(scale * p.z));
    }

public:
   // perlin noise;
    double scale;
};




#endif

