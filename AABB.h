#ifndef AABB_H
#define AABB_H

#include"Ray.h"
using namespace glm;
class AABB {
public:
    AABB() {}
    AABB(const vec3& a, const vec3& b) { minimum = a; maximum = b; }

    vec3 min() const { return minimum; }
    vec3 max() const { return maximum; }

    bool hit(const Ray& r, double t_min, double t_max) const {

        for (int a = 0; a < 3; a++) {
            if (abs(r.direction()[a]) < 0.00001) //If the ray parallel to the plane  
            {
                //If the ray is not within AABB box, then not intersecting  
                if (r.origin()[a] < minimum[a] || r.origin()[a] > maximum[a])
                    return false;
            }else
            {
            auto t0 = fmin((minimum[a] - r.origin()[a]) / r.direction()[a],
                (maximum[a] - r.origin()[a]) / r.direction()[a]);
            auto t1 = fmax((minimum[a] - r.origin()[a]) / r.direction()[a],
                (maximum[a] - r.origin()[a]) / r.direction()[a]);
            t_min = fmax(t0, t_min);
            t_max = fmin(t1, t_max);
            if (t_max <= t_min)
                return false;
            }
        }
        //The plane perpendicular to z-axie  
        
       /* vcHit->x = r.origin().x + t_min * r.direction().x;
        vcHit->y = r.origin().y + t_min * r.direction().y;
        vcHit->z = r.origin().z + t_min * r.direction().z;*/
        return true;
    }

   float area() const {
        auto a = maximum.x - minimum.x;
        auto b = maximum.y - minimum.y;
        auto c = maximum.z - minimum.z;
        return 2 * (a * b + b * c + c * a);
    }

    int longest_axis() const {
        auto a = maximum.x - minimum.x;
        auto b = maximum.y - minimum.y;
        auto c = maximum.z - minimum.z;
        if (a > b && a > c)
            return 0;
        else if (b > c)
            return 1;
        else
            return 2;
    }
    void expand(const AABB& other)
    {
        minimum.x = minimum.x>other.minimum.x? minimum.x : other.minimum.x;
        minimum.y = minimum.y > other.minimum.y ? minimum.y : other.minimum.y;
        minimum.z = minimum.z > other.minimum.z ? minimum.z : other.minimum.z;
        maximum.x = maximum.x > other.maximum.x? maximum.x: other.maximum.x;
        maximum.y = maximum.y > other.maximum.y ? maximum.y : other.maximum.y;
        maximum.z = maximum.z > other.maximum.z ? maximum.z : other.maximum.z;
    }

public:
    vec3 minimum;
    vec3 maximum;
};

AABB surrounding_box(AABB box0, AABB box1) {
    vec3 small(fmin(box0.min().x, box1.min().x),
        fmin(box0.min().y, box1.min().y),
        fmin(box0.min().z, box1.min().z));

    vec3 big(fmax(box0.max().x, box1.max().x),
        fmax(box0.max().y, box1.max().y),
        fmax(box0.max().z, box1.max().z));

    return AABB(small, big);
}



#endif
