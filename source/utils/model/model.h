#ifndef _UTILS_MODEL_H_
#define _UTILS_MODEL_H_

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <vector>

#include "utils/mesh/mesh.h"

namespace utils
{
class Model
{
public:
    Model(const std::string& model_name);

private:
    void loadModel(const std::string& model_name);
    void drawModel(const Shader& shader);

private:
    std::vector<Texture> loaded_textures_;
    std::vector<Mesh> meshes_;
};
}  // namespace utils

#endif