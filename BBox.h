#ifndef __BBOX_H
#define __BBOX_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <vector>
//#include"Utility.h"
//const static float kInfinity= std::numeric_limits<float>::max();
const static float kInfinity = std::numeric_limits<float>::max();
class BBox
{
public:
    BBox() { min = glm::vec3(0.0f); max = glm::vec3(0.0f); }

    BBox(glm::vec3 min_, glm::vec3 max_)
    {
        bounds[0] = min_;
        bounds[1] = max_;
    }
    void get_Corners() {
      
       Corners[0] =glm:: vec3(min.x,min.y,min.z);
       Corners[1] =glm:: vec3(max.x, min.y, min.z);
       Corners[2] = glm::vec3(min.x, max.y, min.z);
       Corners[3] = glm::vec3(min.x, min.y, max.z);
       Corners[4] = glm::vec3(max.x, min.y, max.z);
       Corners[5] = glm::vec3(max.x, max.y, min.z);
       return;
    };
    glm::vec3 Corners[6];
    int get_longest_distant(glm::vec3 center);
 void extendBy(BBox exBox);
     glm::vec3 getMidpoint(const glm::vec3& p);
    int longest_axis() const;
   void computeBBoxFromOriginalPointSet(glm::vec3 vertices[3]);
   void extrameDistanceAlongDir(glm::vec3 dir, glm::vec3 vertices[3], unsigned int* min, unsigned int* max);
     bool bIntersect(const glm::vec3& orig, const glm::vec3& dir, glm::vec3* vcHit) const;
     void add_point(const glm::vec3 p);
    glm::vec3 min;
    glm::vec3 max;
    glm::vec3 bounds[2] = {glm::vec3(kInfinity, kInfinity, kInfinity), glm::vec3(-kInfinity, -kInfinity, -kInfinity)};
};


#endif

