#ifndef OBJLOAD_H
#define OBJLOAD_H

#include <string>
#include <vector>
//#include "ObjMaterial.h"
#include "Shape.h"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"
/// Load a TriMesh from an OBJ file
class TriMeshObjLoader
{
public:
  //  Mesh mesh_obj;
    std::string & filename;
    TriMeshObjLoader(std::string& filename) :filename(filename) {};

    std::vector<Triangle>  obj_load(glm::mat4& o2w) {
        tinyobj::ObjReaderConfig reader_config;
        reader_config.mtl_search_path = "C:/models/";  // Path to material files

        tinyobj::ObjReader reader;

        if (!reader.ParseFromFile(filename, reader_config)) {
            if (!reader.Error().empty()) {
                std::cerr << "TinyObjReader: " << reader.Error();
            }
            exit(1);
        }

        if (!reader.Warning().empty()) {
            std::cout << "TinyObjReader: " << reader.Warning();
        }
        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();
        // Loop over shapes
        int triCounter;
        std::vector<Triangle> tris;
        for (size_t s = 0; s < shapes.size(); s++) {
            if (s > 0) {
                triCounter += shapes[s].mesh.num_face_vertices.size();
            }
            else if (s == 0) {
                triCounter = shapes[s].mesh.num_face_vertices.size();
            }
            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {

                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
                if (fv != 3) {
                    std::runtime_error("Only triangles allowed!");
                }

                Triangle tri;
                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++) {
                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                    tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                    tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
                    // tri.vertex[v] = glm::vec3(vx, vy, vz);
                       tri.vertex[v] = glm::vec3(o2w * vec4(vx, vy, vz, 1));

                    if (idx.normal_index >= 0) {
                        tri.hasnormal = true;
                        //std::cout<<" + normal"<<std::endl;
                        tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                        tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                        tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                        // tri.normal[v] = glm::vec3(nx, ny, nz);
                         tri.normal[v] = glm::vec3(transpose(inverse(o2w)) * vec4(nx, ny, nz, 0));

                    }
                    else {
                        
                        tri.hasnormal=false;
                     //   tinyobj::real_t e0 = ;
                    //   isct->normal = -normalize(cross(e0, e1));


                        std::runtime_error("Normals expected!");
                    }
                }
                index_offset += fv;
                if (materials.size() > 1) {
                    // per-face material
                    int materialID = shapes[s].mesh.material_ids[f];
                    tri.mat_ptr.ior = materials[materialID].ior;
                    tri.mat_ptr.diffuse = glm::vec3(materials[materialID].diffuse[0], materials[materialID].diffuse[1], materials[materialID].diffuse[2]);
                    tri.mat_ptr.specular = glm::vec3(materials[materialID].specular[0], materials[materialID].specular[1], materials[materialID].specular[2]);
                    tri.mat_ptr.ambient = glm::vec3(materials[materialID].ambient[0], materials[materialID].ambient[1], materials[materialID].ambient[2]);
                    tri.mat_ptr.transmission = glm::vec3(materials[materialID].transmittance[0], materials[materialID].transmittance[1], materials[materialID].transmittance[2]);
                    tri.mat_ptr.shininess = materials[materialID].shininess;
                    tri.mat_ptr.illum = materials[materialID].illum;
                    if (materials[materialID].ambient[0] + materials[materialID].ambient[1] + materials[materialID].ambient[2] > 1)
                        tri.mat_ptr.type = Light;
                    else if (materials[materialID].shininess > 1) {
                        tri.mat_ptr.type = kReflective;
                    }
                    else if ((materials[materialID].shininess == 1) and (materials[materialID].ior > 1)) {
                        tri.mat_ptr.type = kRefractive;
                    }
                    else if ((materials[materialID].shininess == 1) and (materials[materialID].ior == 1)) {
                        tri.mat_ptr.type = kDiffuse;
                    }
                }
                else
                    tri.mat_ptr = ObjMaterial();
                    

                tris.push_back(tri);

              //  mesh_obj = new Mesh(tris);
            }
        }
        std::cout << "Number of Triangles: " << triCounter << std::endl;
        return tris;
    };

    /// Load materials from an MTL file
    //void mtl_load(const std::string& filename, std::vector<ObjMaterial>& materials);
};
#endif // OBJLOAD_H