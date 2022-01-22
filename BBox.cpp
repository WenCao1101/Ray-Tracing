#include "BBox.h"
//#include "Objects.h"
#include <iostream>

void BBox::extendBy(BBox exBox)
{
    this->max.x = this->max.x > exBox.max.x ? this->max.x : exBox.max.x;
    this->max.y = this->max.y > exBox.max.y ? this->max.y : exBox.max.y;
    this->max.z = this->max.z > exBox.max.z ? this->max.z : exBox.max.z;
    this->min.x = this->min.x < exBox.min.x ? this->min.x : exBox.min.x;
    this->min.y = this->min.y < exBox.min.y ? this->min.y : exBox.min.y;
    this->min.z = this->min.z < exBox.min.z ? this->min.z : exBox.min.z;
}
void BBox::add_point(const glm::vec3 p)
{
    this->max.x = this->max.x > p.x ? this->max.x : p.x;
    this->max.y = this->max.y > p.y ? this->max.y : p.y;
    this->max.z = this->max.z > p.z ? this->max.z : p.z;
    this->min.x = this->min.x < p.x ? this->min.x : p.x;
    this->min.y = this->min.y < p.y ? this->min.y : p.y;
    this->min.z = this->min.z < p.z ? this->min.z : p.z;
}

glm::vec3 BBox::getMidpoint(const glm::vec3& p)
{

    return glm::vec3((bounds[0][0] + bounds[1][0]) / 2, (bounds[0][1] + bounds[1][1]) / 2, (bounds[0][2] + bounds[1][2]) / 2);
}

int BBox::longest_axis() const {

    if (((bounds[1] - bounds[0]).x) > ((bounds[1] - bounds[0]).y) && ((bounds[1] - bounds[0]).x) > ((bounds[1] - bounds[0]).z)) {
        return 0;
    }
    else if (((bounds[1] - bounds[0]).y) > ((bounds[1] - bounds[0]).z)) {
        return 1;
    }
    else {
        return 2;
    }
}

int BBox::get_longest_distant(glm::vec3 center) {
    
    int length1 = 0;
    for (int i = 0; i < 5; i++) {
        int length = (Corners[i] - center).length();
        if (length > length1)
            length1 = length;
    
    }
    return length1;
}
void BBox::computeBBoxFromOriginalPointSet(glm::vec3 vertices[3])
{
    unsigned int minX_i = 0, maxX_i = 0;
    extrameDistanceAlongDir(glm::vec3(1, 0, 0), vertices, &minX_i, &maxX_i);
    min.x = vertices[minX_i].x;
    max.x = vertices[maxX_i].x;

    unsigned int minY_i = 0, maxY_i = 0;
    extrameDistanceAlongDir(glm::vec3(0, 1, 0), vertices, &minY_i, &maxY_i);
    min.y = vertices[minY_i].y;
    max.y = vertices[maxY_i].y;

    unsigned int minZ_i = 0, maxZ_i = 0;
    extrameDistanceAlongDir(glm::vec3(0, 0, 1), vertices, &minZ_i, &maxZ_i);
    min.z = vertices[minZ_i].z;
    max.z = vertices[maxZ_i].z;
}

void BBox::extrameDistanceAlongDir(glm::vec3 dir, glm::vec3 vertices[3], unsigned int* min, unsigned int* max)
{
    float maxProj = -kInfinity, minProj = kInfinity;
    for (unsigned int i = 0; i < 3; i++)
    {
        float proj = 0;

        proj = dot(vertices[i], dir);

        if (proj > maxProj)
        {
            maxProj = proj;
            *max = i;
        }

        if (proj < minProj)
        {
            minProj = proj;
            *min = i;
        }
    }
}

bool BBox::bIntersect(const glm::vec3& orig, const glm::vec3& dir, glm::vec3* vcHit) const
{
    float tmin = 0.0f;
    float tmax = kInfinity;
  //  std::cout << "ray orig" << orig.x << orig.y << orig.z << dir.x << dir.y << dir.z << std::endl;
    // std::cout << "ray dir" << dir.x << dir.y << dir.z << std::endl;
    // std::cout << "bbox min" << min.x << min.y << min.z << std::endl;
    // std::cout << "bbox max" << max.x << max.y << max.z << std::endl;
    //The plane perpendicular to x-axie  
    if (abs(dir.x) < 0.0000001) //If the ray parallel to the plane  
    {
        //If the ray is not within AABB box, then not intersecting  
        if (orig.x < min.x || orig.x > max.x)
            return false;
    }
    else
    {
        //Compute the distance of ray to the near plane and far plane  
        float ood = 1.0f / dir.x;
        float t1 = (min.x - orig.x) * ood;
        float t2 = (max.x - orig.x) * ood;

        //Make t1 be intersecting with the near plane, t2 with the far plane  
        if (t1 > t2)
        {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        //Compute the intersection of slab intersection intervals  
        if (t1 > tmin) tmin = t1;
        if (t2 < tmax) tmax = t2;

        //Exit with no collision as soon as slab intersection becomes empty  
        if (tmin > tmax) return false;
    }// end for perpendicular to x-axie  

     //The plane perpendicular to y-axie  
    if (abs(dir.y) < 0.0000001) //If the ray parallel to the plane  
    {
        //If the ray is not within AABB box, then not intersecting  
        if (orig.y < min.y || orig.y > max.y)
            return false;
    }
    else
    {
        //Compute the distance of ray to the near plane and far plane  
        float ood = 1.0f / dir.y;
        float t1 = (min.y - orig.y) * ood;
        float t2 = (max.y - orig.y) * ood;

        //Make t1 be intersecting with the near plane, t2 with the far plane  
        if (t1 > t2)
        {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        //Compute the intersection of slab intersection intervals  
        if (t1 > tmin) tmin = t1;
        if (t2 < tmax) tmax = t2;

        //Exit with no collision as soon as slab intersection becomes empty  
        if (tmin > tmax) return false;
    }// end for perpendicular to y-axie  

     //The plane perpendicular to z-axie  
    if (abs(dir.z) < 0.0000001) //If the ray parallel to the plane  
    {
        //If the ray is not within AABB box, then not intersecting  
        if (orig.z < min.z || orig.z > max.z)
            return false;
    }
    else
    {
        //Compute the distance of ray to the near plane and far plane  
        float ood = 1.0f / dir.z;
        float t1 = (min.z - orig.z) * ood;
        float t2 = (max.z - orig.z) * ood;

        //Make t1 be intersecting with the near plane, t2 with the far plane  
        if (t1 > t2)
        {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        //Compute the intersection of slab intersection intervals  
        if (t1 > tmin) tmin = t1;
        if (t2 < tmax) tmax = t2;

        //Exit with no collision as soon as slab intersection becomes empty  
        if (tmin > tmax) return false;
    }// end for perpendicular to z-axie  

    vcHit->x = orig.x + tmin * dir.x;
    vcHit->y = orig.y + tmin * dir.y;
    vcHit->z = orig.z + tmin * dir.z;
    return true;
}