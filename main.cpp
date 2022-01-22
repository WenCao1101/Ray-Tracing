#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include"camera.h"
#include "glm/gtc/matrix_transform.hpp"
//#include <glm/glm.hpp>
#include"Scene.h"
//#include"KdNode.h"
#include"ObjLoad.h"
using namespace cv;

#ifndef M_PI
#define M_PI             3.14159265358979323846  /* pi */
#endif


int main()
{
	
	// loading gemetry
//	
	//scene = simple_light();
	//scene.creat_scene();
	//Bvh bvh(scene.objects,0,1);
 /*auto white = make_shared<Lambertian>(vec3(.8, .8, .8));
  auto a= make_shared<Box>(vec3(130, 0, 65), vec3(295, 165, 230), white);
	auto b=make_shared<Box>(vec3(265, 0, 295), vec3(430, 330, 460), white);*/
//	auto light = make_shared<Diffuse_light>(vec3(15, 15, 15));
	//shared_ptr<Shape> lights = make_shared<xz_rect>(213, 343, 227, 332, 554, light);
	std::vector<Mesh*> meshes;
	std::vector<PointLight*> lights;
	PointLight* pointlight = new PointLight(glm::vec3(40.f, 40.f, 40.f), glm::vec3(10.f, 10.f, 10.f));
	lights.push_back(pointlight);
	glm::mat4 mtx(1);
	/*std::string filename="C:/models/cube.obj";*/
	
	/*td::string filename = "C:/models/CornellBox.obj";
//	mtx = glm::translate(mtx, glm::vec3(-1,-1,-1));
	mtx = glm::scale(mtx, glm::vec3(0.0250f, 0.0250f,0.0250f));
   mtx = glm::rotate(mtx, static_cast<float>(M_PI), glm::vec3(0, 1, 0));*/
	std::string filename = "C:/models/scene01.obj";
	mtx = glm::translate(mtx, glm::vec3(-4, -4, -4));
//	mtx = glm::scale(mtx, glm::vec3(0.5f, 0.5f, 0.5f));
//	mtx = glm::rotate(mtx, static_cast<float>(M_PI), glm::vec3(0, 1, 0));
	/*std::string filename = "C:/models/bunny.obj";
	mtx = glm::translate(mtx, glm::vec3(-3.0f, -0.85f, -8.0f));
	mtx = glm::scale(mtx, glm::vec3(20.0f, 20.0f,20.0f));
	//mtx = glm::rotate(mtx, static_cast<float>(M_PI), glm::vec3(0, 1, 0));*/
   TriMeshObjLoader triss(filename);
   

	//mtx = glm::translate(mtx, glm::vec3(2, 2, 2));
    //mtx = glm::scale(mtx, glm::vec3(1, 1, 1));
	// 	 
	//triss.obj_load(mtx);
	Mesh* onemesh = new Mesh(triss.obj_load(mtx));
	BBox* obj_box= new BBox(onemesh->get_bounding_box());
	 vec3 pos_min=obj_box->min;
	 vec3 pos_max = obj_box->max;

	// int a = obj_box->longest_axis();
	// int height =abs(pos_min[a] - pos_max[a]);
	// int radius = obj_box->get_longest_distant(middle);
	 vec3 middle = 0.5f * (pos_max + pos_min);
	 int radius = obj_box->get_longest_distant(middle);
	 cout << "BBox value" << pos_min[0] << pos_min[1] << pos_min[2]<<endl;
	 cout << "BBox value" << pos_max[0] << pos_max[1] << pos_max[2]<<endl;
	 glm::mat4 mtx1(1);
	/* std::string filename1 = "C:/models/cube.obj";
	mtx1 = glm::translate(mtx1, glm::vec3(-6, -1, -3.0));
	 mtx1 = glm::scale(mtx1, glm::vec3(2.0000f, 2.0050f, 2.0000f));
	mtx1 = glm::rotate(mtx1, static_cast<float>(M_PI), glm::vec3(0, 1, 0));
	//TriMeshObjLoader triss(filename1);
	 triss.filename = filename1;
	 Mesh* onemesh1 = new Mesh(triss.obj_load(mtx1));
	 BBox* obj_box1 = new BBox(onemesh1->get_bounding_box());
	 vec3 pos_min1 = obj_box1->min;
	 vec3 pos_max1 = obj_box1->max;
	 vec3 middle1 = 0.5f * (pos_max1 + pos_min1);
	 vec3 distant = middle - middle1;*/

	/*glm::mat4 mtx1(1);
	 std::string filename1 = "C:/models/CornellBlocks.obj";
	 mtx1 = glm::translate(mtx1, glm::vec3(-3, 4, -3.0));
	 mtx1 = glm::scale(mtx1, glm::vec3(0.0050f, 0.0050f, 0.0050f));
	 mtx1 = glm::rotate(mtx1, static_cast<float>(M_PI), glm::vec3(0, 1, 0));
	
	 triss.filename = filename1;
	 Mesh* onemesh1 = new Mesh(triss.obj_load(mtx1));
	 BBox* obj_box1 = new BBox(onemesh1->get_bounding_box());
	 vec3 pos_min1 = obj_box1->min;
	 vec3 pos_max1 = obj_box1->max;
	 vec3 middle1 = 0.5f * (pos_max1 + pos_min1);
	 vec3 distant = middle - middle1;*/
	// obj_box->extendBy(*obj_box1);
	if (onemesh != nullptr)
		meshes.push_back(onemesh);
//	meshes.push_back(onemesh1);
	//cout <<"the nunmber of mesh1: "<<onemesh->triangles.size()<<endl ;
	//cout << onemesh->triangles[0].vertex[0].x << onemesh->triangles[0].vertex[1].y << onemesh->triangles[0].vertex[2].z << endl;

	/*std::string filename1 = "C:/models/low-poly-fox-by-pixelmannen.obj";
	//TriMeshObjLoader triss2(filename1, onemesh1);
	triss.filename =filename1;
	mtx = glm::translate(mtx, glm::vec3(1, -3, 0));
	mtx = glm::rotate(mtx, static_cast<float>(M_PI/ 4), glm::vec3(0, 1, 0));
	mtx = glm::scale(mtx, glm::vec3(.03, .03, .03));
	Mesh* onemesh1 = new Mesh(triss.obj_load(mtx));
	if (onemesh1 != nullptr)
		meshes.push_back(onemesh1);
	cout << "the nunmber of mesh2: " << onemesh1->triangles.size() << endl;*/
	KDNode* KDTree = new KDNode(meshes);
//	KDNode KDTree (meshes);
	KDTree->init();
	//KDNode* KDTree2 = new KDNode();
	KDTree=KDTree->build(0);
	cout << KDTree->meshes->triangles.size()<<endl;
	Scene scene(KDTree);
	//scene.add(KDTree);
	Tracer tracer(scene,lights);

	/*glm::mat4 w2c = glm::mat4(0, 2.5, 6.5, 1,
		0, 0, 0, 1,
		0, 1, 0, 1,
		0, 1, 0, 1);*/
		//auto 2w = glm::inverse(w2c);
	 float aspect_ratio = 9.0 / 16.0;
	 aspect_ratio =(obj_box->Corners[0]- obj_box->Corners[1]).length()/ (obj_box->Corners[0] - obj_box->Corners[2]).length();
	 int WIDTH =600;
	const vec3 vup(0, -1, 0);
	const auto dist_to_focus = 10.0;
	//const int HEIGHT = static_cast<int>(WIDTH / aspect_ratio);
	
	 int SAMPLES_PER_PIXEL =20;
	vec3 lookfrom;
	vec3 lookat;
	float vfov;
	vfov = 50.0;
	lookat = middle;
//	auto dist = abs(0.5*height/tan(M_PI*vfov/360))+(height/2);
	auto dist = abs(2.0 * radius / tan(M_PI * vfov / 360)) + radius*1.5;
	lookfrom = vec3(lookat[0] , lookat[1] , float(lookat[2] + dist * 1.1));
	/*lookfrom = vec3(1,1,-1);  // for cube
	lookat = vec3(0,-9,0);*/ 
	//aspect_ratio = 1.0;
	//WIDTH = 600;
	//lookfrom = vec3(0,0,0);  // for cornell box
	//lookat = vec3(0,0,-1);
	
	//lookfrom = vec3(-3,3,3);  // for scenen 1
	//lookat =vec3(-15, -15, -15);
	//vfov =80.0;
//	vfov = 20.0;
	//auto dist =length(middle - lookfrom);
	//vfov = 2*atan(height/(2*dist))*(180/M_PI)+3;// in degrees
	Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, WIDTH, SAMPLES_PER_PIXEL, tracer);

   // Camera cam(WIDTH, HEIGHT, SAMPLES_PER_PIXEL, 0.001f, 10000.f, w2c,tracer);
	auto background = vec3(0.70, 0.80, 1.00);
	cam.render(background);
	/*Mat rgb = imread("1.jpg");

	imshow("rgb",rgb);
	Mat img(100,100, CV_8UC1);
	namedWindow("Test");
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			img.at<uchar>(i, j) = i * j / 20;
		}
	}*/
	imshow("test image", cam.get_img());
	cv::imwrite("test.png", cam.get_img());
//	imshow("Test", img);
	waitKey(0);
	return 0;
}
