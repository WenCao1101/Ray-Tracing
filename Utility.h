#ifndef UTILITY
#define UTILITY
#include <iostream>
#include <limits>
#include <glm/glm.hpp>
#include <memory>
#include <random>
#include <vector>
using namespace glm;





const double infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

//const static float kInfinity = std::numeric_limits<float>::max();

// Random
/*inline double random_double() {
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0, 1);
    return distribution(generator);
}*/

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(random_double(min, max + 1));
}

inline static vec3 random(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

inline vec3 random_cosine_direction() {
    auto r1 = random_double();
    auto r2 = random_double();
    auto z = sqrt(1 - r2);

    auto phi = 2 * PI * r1;
    auto x = cos(phi) * sqrt(r2);
    auto y = sin(phi) * sqrt(r2);

    return vec3(x, y, z);
}

/*inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = random(-1, 1);
        if (p[0] * p[0] + p[1] * p[1] + p[2] * p[2] >= 1) continue;
        return p;
    }
}*/


inline float degrees_to_radians(float degrees) {
    return degrees * PI / 180.0;
}


inline vec3 random_in_unit_sphere() {
    
    while (true) {
        auto p = random(-1, 1);
        if (p[0] * p[0] + p[1] * p[1] + p[2] * p[2] >= 1) continue;
        return p;
       //  std::cout << p[0] << std::endl<<p[1]<< std::endl <<p[2];
       }
   
    }


inline vec3 random_unit_vector() {
    return normalize(random_in_unit_sphere());
}
inline bool near_zero(vec3 e) {
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

/*inline vec3 refract(const vec3& uv, const vec3& n, float etai_over_etat) {
    float cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel =static_cast<float>(-sqrt(fabs(1.0 - (r_out_perp[0]* r_out_perp[0]+ r_out_perp[1] * r_out_perp[1]+ r_out_perp[2] * r_out_perp[2])))) * n;
    return r_out_perp + r_out_parallel;
}*/

/*inline bool trace_refracted(const Ray& in, Ray& out, double& R) const
{
    vec3 normal, direction;
    double cos_theta_in;
    out.ior = get_ior_out(in, direction, normal, cos_theta_in);
    double eta = in.ior / out.ior;
    double cos_theta_out_sqr = 1.0 - eta * eta * (1.0 - cos_theta_in * cos_theta_in);
    if (cos_theta_out_sqr < 0.0)
    {
        out.direction = Vec3f(0.0f);
        R = 1.0;
        return false;
    }

    double cos_theta_out = std::sqrt(cos_theta_out_sqr);
    out.origin = in.hit_pos;
    out.direction = eta * (normal * cos_theta_in - direction) - normal * cos_theta_out;
    out.trace_depth = in.trace_depth + 1;
    out.did_hit_diffuse = in.did_hit_diffuse;
    R = fresnel_R(cos_theta_in, cos_theta_out, in.ior, out.ior);
    return trace(out);
}*/
// Evaluate Fresnel equation (ration of reflected light for a given incident direction and surface normal)
// Compute refraction direction
inline float clamp(const float& lo, const float& hi, const float& v)
{
    return std::max(lo, std::min(hi, v));
}
inline glm::vec3 refract(const glm::vec3& I, const glm::vec3& N, const float& ior)
{
    float cosi = clamp(-1, 1, dot(I, N));
    float etai = 1, etat = ior;
    glm::vec3 n = N;
    if (cosi < 0) { cosi = -cosi; }
    else { std::swap(etai, etat); n = -N; }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? glm::vec3(1, 0, 0) : eta * I + (eta * cosi - sqrtf(k)) * n;
}

inline void fresnel(const glm::vec3& I, const glm::vec3& N, const float& ior, float& kr)
{
    float cosi = clamp(-1, 1, dot(I, N));
    float etai = 1, etat = ior;
    if (cosi > 0) { std::swap(etai, etat); }
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1) {
        kr = 1;
    }
    else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        kr = (Rs * Rs + Rp * Rp) / 2;
    }
}


#define GLM_FORCE_RADIANS


#endif
