#ifndef SCENE_H
#define SCENE_H
#include"kDNode.h"

#include"Texture.h"
#include"Aarect.h"

using namespace std;
//class kDNode;

class Scene {

public:
    Scene(KDNode *object): kdNode(object) {};
   ~ Scene() {};
	//Scene(vector<KDNode*> kdNodes1):kdNodes(kdNodes1) {}
	//void clear() { kdNodes.clear(); }
	//void add(KDNode object) { KDNode object; }
  /* void create_scene(std::vector<KDNode*> KDTree) {
       for (int i = 0; i < KDTree.size(); i++) {
           kdNodes[i] = KDTree[i];
       
       }
      
   
   };*/
 bool hit(Ray& r, double t_min, double t_max, IsectInfo& rec) const;
 KDNode *kdNode;
	//vector<shared_ptr<Shape>> objects;

   // virtual bool bounding_box( AABB& output_box) const override;
};

bool Scene::hit(Ray& r, double t_min, double t_max, IsectInfo& rec) const {
  //  IsectInfo *temp_rec=new IsectInfo();
    bool hit_anything = false;
    auto closest_so_far =t_max;

 //   for (const auto& kdNode1 : kdNodes) {
      //  if (kdNode1->kIntersect(r, t_min, closest_so_far,temp_rec)) {
            if (kdNode->kIntersect(kdNode, r.orig, r.dir, &rec)) {
            hit_anything = true;
            closest_so_far = rec.t;
          //  rec = *temp_rec;
       // }
    }

    return hit_anything;
}
/*void Scene::create_scene(const KDNode*& KDTree) {

}*/


/*bool Scene::bounding_box(AABB& output_box) const {
    if (objects.empty()) return false;

    AABB temp_box;
    bool first_box = true;

    for (const auto& object : objects) {
        if (!object->bounding_box(temp_box)) return false;
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}*/
/*Scene simple_light() {
    Scene objects;

    auto pertext = make_shared<Noise_texture>(4);
    objects.add(make_shared<Sphere>(vec3(0, -1000, 0), 1000, make_shared<Lambertian>(vec3(1, 1, 1))));
    objects.add(make_shared<Sphere>(vec3(0, 2, 0), 2, make_shared<Lambertian>(vec3(1, 0, 1))));

    auto difflight = make_shared<Diffuse_light>(vec3(4, 4, 4));
    objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));
    objects.add(make_shared<Sphere>(vec3(0, 7, 0), 2, difflight));
    return objects;
}*/





/*void Scene::creat_scene() {
  //  auto R = cos(pi / 4);
 //  auto material_right = make_shared<Metal>(vec3(0.8, 0.6, 0.2), 1.0);
  /* auto material_right = make_shared<Lambertian>(vec3(0.5, 0.5, 0.5));
  auto difflight = make_shared<Diffuse_light>(vec3(4, 4, 4));
    
   add(make_shared<Sphere>(vec3(1.0, 0.0, -1.0),3, material_right));
  add(make_shared<Sphere>(vec3(0, -400.1, 0), 400, material_right));
add(make_shared<Sphere>(vec3(0, 2.0, 0), 2.1, material_right));

  //  auto difflight = make_shared<Diffuse_light>(vec3(4, 4, 4));
   add(make_shared<xy_rect>(3, 5, 1, 3, -2.0, difflight));
  add(make_shared<Sphere>(vec3(0, 7, 0), 2.1, material_right));*/











  /* auto material_ground = make_shared<Lambertian>(vec3(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(vec3(0.1, 0.2, 0.5));
    auto material_left = make_shared<Dielectric>(1.5);
    auto material_right = make_shared<Metal>(vec3(0.8, 0.6, 0.2),1.0);
   /* auto material_left = make_shared<Lambertian>(vec3(256, 256, 256));
    auto material_right = make_shared<Lambertian>(vec3(1, 0,0));
    auto difflight = make_shared<Diffuse_light>(vec3(4, 4, 4));
  // add(make_shared<Sphere>(vec3(0.0, -100.5, -1.0), 100.0, material_ground));
    //add(make_shared<Sphere>(vec3(0.0, 0.0, -1.0), 0.5, material_center));
    add(make_shared<Sphere>(vec3(-1.0, 0.0, -1.0), -0.4, difflight));
    add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));
      add(make_shared<Sphere>(vec3(1.0, 0.0, -1.0), 0.5, material_right));
  //  add(make_shared<xy_rect>(3, 5, 1, 3, -2, material_left));
  add(make_shared<Sphere>(vec3(0, -1000, 0), 1000, material_right));
   // add(make_shared<Sphere>(vec3(0, 2, 0), 2, material_right));*/


  /*auto red = make_shared<Lambertian>(vec3(.05, .05, .65));
  auto white = make_shared<Lambertian>(vec3(.8, .8, .8));
  auto green = make_shared<Lambertian>(vec3(.15, .45, .12));
  auto color = make_shared<Lambertian>(vec3(.15, .75, .72));
  auto light = make_shared<Diffuse_light>(vec3(20, 20, 20));
  shared_ptr<Material> aluminum = make_shared<Metal>(vec3(0.8, 0.85, 0.88), 0.0);
  auto glass = make_shared<Dielectric>(1.5);

  add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
  add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
  add(make_shared<xz_rect>(210, 360, 220, 360, 554, light));
  add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
  add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
  add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));
 // add(make_shared<Box>(vec3(130, 0, 65), vec3(295, 165, 230), white));
  
  add(make_shared<Sphere>(vec3(190, 90, 190), 90, color));

  add(make_shared<Sphere>(vec3(450, 330, 165), 90, glass));








    
}*/

#endif 
