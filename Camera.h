#ifndef CAMERAS_H
#define CAMERAS_H
#include <opencv2/core.hpp>
//#include "Utility.h"

//#include"Ray.h"
#include"Tracer.h"
//#include<iostream>

using namespace std;
class Camera {
public:
	Camera(
		vec3 lookfrom,
		vec3 lookat,
		vec3  vup,
		float vfov, // vertical field-of-view in degrees
		float aspect_ratio, int width, int samples, Tracer& tracer):width(width), samples(samples),aspect_ratio(aspect_ratio),tracer(tracer) {
		auto theta = degrees_to_radians(vfov);
		auto h = tan(theta / 2);
		 viewport_height = 2.0 * h;
		 auto w = normalize(lookfrom - lookat);
		 auto u = normalize(cross(vup, w));
		 auto v = cross(w, u);
		 origin = lookfrom;
		 auto viewport_width = aspect_ratio * viewport_height;
		 horizontal = viewport_width * u;
		 vertical = viewport_height * v;
		 lower_left_corner = origin - horizontal *0.5f - vertical *0.5f -w;

		//auto viewport_width = aspect_ratio * viewport_height;
		//auto focal_length = 1.0;
		height = static_cast<int>(width / aspect_ratio);
		img=cv::Mat::zeros(height, width, CV_32FC3);
		//origin = vec3(0, 0, 0);
	//	horizontal = vec3(viewport_width, 0.0, 0.0);
		//vertical = vec3(0.0, viewport_height, 0.0);
		//lower_left_corner = origin - horizontal*0.5f - vertical*0.5f - vec3(0, 0, focal_length);
	     t_min=0.001f;
		 t_max= infinity;
	
	}

	Camera(int width, int height, int samples, float t_min, float t_max, glm::mat4 cam2world, Tracer& tracer) : width(width), height(height), samples(samples), t_min(t_min), t_max(t_max), img(cv::Mat::zeros(height, width, CV_32FC3)), cam2world(cam2world),tracer(tracer) {
		aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
	}
	
	void render(const vec3& background) {
		int depth = 1;
		float s2 = 1.f / samples;
		for (int i = 0; i <height; ++i) {
			for (int j = 0; j < width; ++j) {
				
				//auto& pt = img.at<cv::Vec3f>(cv::Point(x, y));
				for (int s = 0; s < samples; ++s) {
					float u = (i + random_double()) / (height-1);
					float v = (j + random_double()) / (width-1);
					Ray ray = this->ray(v, u);
					//cv::Vec3f& pt = img.at<cv::Vec3f>((i, j));
					//auto& pt = img.at<cv::Vec3f>((i, j));
				//	cout << "Ray origin=" << endl <<ray.origin().x<<ray.origin().y<< ray.origin().z<<endl;
				//	cout << "Ray direciton=" << endl << ray.direction().x << ray.direction().y << ray.direction().z << endl;
					auto li = tracer.Li(ray,background,depth);
					if (li != li) li = vec3(0.0, 0.0, 0.0);
			        //auto& pt = img.at<cv::Vec3f>(u, v);
					img.at<cv::Vec3f>(i, j)[0] += sqrt(li[0] *s2*s2);
					img.at<cv::Vec3f>(i, j)[1] += sqrt(li[1] *s2*s2);
					img.at<cv::Vec3f>(i, j)[2] += sqrt(li[2] *s2*s2);
			
  //  cout << "M=" << endl << "" << li[0] <<endl<< i<<endl<< j << endl<<u << v << endl;
				}
				
			}
		}
	}
	cv::Mat& get_img() {
		return img;
	}
	Ray ray(float x, float y) const {
		
		int focal_length = 1.0;
	//	float viewport_height = 2.0;
		float viewport_width = aspect_ratio * viewport_height;


		// origin = glm::vec3(0, 0, 0);
		/*vec3 horizontal = glm::vec3(viewport_width, 0.0, 0.0);
		vec3 vertical = glm::vec3(0.0, viewport_height, 0.0);
		vec3 lower_left_corner = origin - 0.5f * horizontal - 0.5f * vertical - glm::vec3(0, 0, focal_length);*/

		return Ray(origin, glm::normalize(glm::vec3(lower_left_corner + x * horizontal + y * vertical - origin)));
	}

protected:
	vec3 origin = glm::vec3(0, 0, 0);
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
//	int focal_length;
	float viewport_height;
	int width;
	int height;
	int samples;
	float t_min;
	float t_max;
	cv::Mat img;
	glm::mat4 cam2world;
	float aspect_ratio;
	Tracer &tracer;
};


#endif
