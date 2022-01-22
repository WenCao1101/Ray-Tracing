#include"Onb.h"
void Onb::build_from_w(const vec3& n) {
    axis[2] = normalize(n);
    vec3 a = (fabs(w().x) > 0.9) ? vec3(0, 1, 0) : vec3(1, 0, 0);
    axis[1] = normalize(cross(w(), a));
    axis[0] = cross(w(), v());
}