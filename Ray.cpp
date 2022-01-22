#include"Ray.h"
#include"Shape.h"
ObjMaterial* Ray::get_material() const
{
    if (hit_object != NULL)
    {
      auto mat =&hit_object->mat_ptr;
        return mat;
    }
    return NULL;
};