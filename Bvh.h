#ifndef BVH_H
#define BVH_H
#include"Shape.h"
#include"Scene.h"
#include <algorithm>
#include <iostream>
class Bvh : public Shape {
public:
    Bvh();

    Bvh(const Scene& list)
        : Bvh(list.objects, 0, list.objects.size())
    {}

    Bvh(
        const std::vector<shared_ptr<Shape>>& src_objects,
        size_t start, size_t end);

    virtual bool hit(
       Ray& r, double t_min, double t_max, hit_record& rec) const override;

   //virtual bool bounding_box(AABB& output_box) const override;
    shared_ptr<Shape> left;
    shared_ptr<Shape> right;
  //  AABB box;
};/*
inline bool box_compare(const shared_ptr<Shape> a, const shared_ptr<Shape> b, int axis) {
    AABB box_a;
    AABB box_b;

    if (!a->bounding_box(box_a) || !b->bounding_box(box_b))
        std::cerr << "No bounding box in Bvh constructor.\n";

    return box_a.min()[axis] < box_b.min()[axis];
}

bool box_x_compare(const shared_ptr<Shape> a, const shared_ptr<Shape> b) {
    return box_compare(a, b, 0);
}

bool box_y_compare(const shared_ptr<Shape> a, const shared_ptr<Shape> b) {
    return box_compare(a, b, 1);
}

bool box_z_compare(const shared_ptr<Shape> a, const shared_ptr<Shape> b) {
    return box_compare(a, b, 2);
}
Bvh::Bvh(
    const std::vector<shared_ptr<Shape>>& src_objects,
    size_t start, size_t end
) {
    auto objects = src_objects; // Create a modifiable array of the source scene objects

    int axis = random_int(0, 2);
    auto comparator = (axis == 0) ? box_x_compare
        : (axis == 1) ? box_y_compare
        : box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1) {
        left = right = objects[start];
    }
    else if (object_span == 2) {
        if (comparator(objects[start], objects[start + 1])) {
            left = objects[start];
            right = objects[start + 1];
        }
        else {
            left = objects[start + 1];
            right = objects[start];
        }
    }
    else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span / 2;
        left = make_shared<Bvh>(objects, start, mid);
        right = make_shared<Bvh>(objects, mid, end);
    }

   AABB box_left, box_right;

    if (!left->bounding_box(box_left)
        || !right->bounding_box(box_right)
        )
        std::cerr << "No bounding box in bvh_node constructor.\n";

    box = surrounding_box(box_left, box_right);
}


bool Bvh::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    if (!box.hit(r, t_min, t_max))
        return false;

    bool hit_left = left->hit(r,t_min, t_max, rec);
   
    bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}



bool Bvh::bounding_box(AABB& output_box) const {
    output_box = box;
    return true;
}


*/



#endif
