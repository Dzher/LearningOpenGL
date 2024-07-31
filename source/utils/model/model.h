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

    void drawModel(Shader& shader);
    inline std::vector<Texture> textures()
    {
        return loaded_textures_;
    }

    inline std::vector<Mesh> meshes()
    {
        return meshes_;
    }

private:
    void loadModel();
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name);

private:
    std::vector<Texture> loaded_textures_;
    std::vector<Mesh> meshes_;
    std::string model_folder_;
};
}  // namespace utils

#endif