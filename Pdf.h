#ifndef PDF_H
#define PDF_H
#include "onb.h"
#include <memory>
//#include"Utility.h"
#include"Shape.h"
//class Shape;
class pdf {
public:
    virtual ~pdf() {}

    virtual double value(const vec3& direction) const = 0;
    virtual vec3 generate() const = 0;
};

class hittable_pdf : public pdf {
public:
    hittable_pdf(std::shared_ptr<Shape> p, const vec3& origin) : ptr(p), o(origin) {}

    virtual double value(const vec3& direction) const override {
        return ptr->pdf_value(o, direction);
    }

    virtual vec3 generate() const override {
        return ptr->random(o);
    }

public:
    vec3 o;
    std::shared_ptr<Shape> ptr;
};





#endif
