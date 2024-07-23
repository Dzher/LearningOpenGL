#include "model.h"
#include <iostream>
#include <vector>
#include "assimp/Importer.hpp"
#include "assimp/material.h"
#include "assimp/mesh.h"
#include "assimp/types.h"
#include "glm/fwd.hpp"
#include "utils/common/common.h"
#include "utils/mesh/mesh.h"
#include "utils/pathhelper/pathhelper.h"

using namespace utils;

Model::Model(const std::string& model_name)
{
    loadModel(model_name);
}

void Model::loadModel(const std::string& model_name)
{
    Assimp::Importer importer;

    std::string path = utils::PathHelper::getModelPath(model_name);
    const aiScene* scene = importer.ReadFile(
        path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
}

void Model::drawModel(Shader& shader)
{
    for (auto& each : meshes_)
    {
        each.draw(shader);
    }
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (int index = 0; index < node->mNumMeshes; ++index)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[index]];
        meshes_.push_back(processMesh(mesh, scene));
    }

    for (int child = 0; child < node->mNumChildren; ++child)
    {
        processNode(node->mChildren[child], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    for (int index = 0; index < mesh->mNumVertices; ++index)
    {
        Vertex vertex;
        if (mesh->HasPositions())
        {
            glm::vec3 position;
            position.x = mesh->mVertices[index].x;
            position.y = mesh->mVertices[index].y;
            position.z = mesh->mVertices[index].z;
            vertex.position = position;
        }
        if (mesh->HasNormals())
        {
            glm::vec3 normal;
            normal.x = mesh->mNormals[index].x;
            normal.y = mesh->mNormals[index].y;
            normal.z = mesh->mNormals[index].z;
            vertex.normal = normal;
        }
        if (mesh->HasTangentsAndBitangents())
        {
            glm::vec3 tangents_or_bitangents;
            tangents_or_bitangents.x = mesh->mTangents[index].x;
            tangents_or_bitangents.y = mesh->mTangents[index].y;
            tangents_or_bitangents.z = mesh->mTangents[index].z;
            vertex.tangent = tangents_or_bitangents;

            tangents_or_bitangents.x = mesh->mBitangents[index].x;
            tangents_or_bitangents.y = mesh->mBitangents[index].y;
            tangents_or_bitangents.z = mesh->mBitangents[index].z;
            vertex.bitangent = tangents_or_bitangents;
        }
        if (mesh->HasTextureCoords(0))
        {
            glm::vec2 coord;
            coord.x = mesh->mTextureCoords[0][index].x;
            coord.y = mesh->mTextureCoords[0][index].y;
            vertex.texture_coord = coord;
        }
        else
        {
            vertex.texture_coord = glm::vec2{0.0f, 0.0f};
        }

        vertices.push_back(vertex);
    }

    for (int index = 0; index < mesh->mNumFaces; ++index)
    {
        aiFace face = mesh->mFaces[index];
        for (int indice = 0; indice < face.mNumIndices; ++indice)
        {
            indices.push_back(face.mIndices[indice]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuse_maps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
    std::vector<Texture> specular_maps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
    std::vector<Texture> normal_maps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());
    std::vector<Texture> height_maps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), height_maps.begin(), height_maps.end());

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name)
{
    std::vector<Texture> textures;
    for (int texture_index = 0; texture_index < mat->GetTextureCount(type); ++texture_index)
    {
        aiString str;
        mat->GetTexture(type, texture_index, &str);
        bool skip = false;
        for (auto& each_texture : loaded_textures_)
        {
            if (str.data == each_texture.path)
            {
                skip = true;
                textures.push_back(each_texture);
                break;
            }
        }

        if (skip)
        {
            continue;
        }

        Texture texture;
        GLuint texture_id;
        utils::CommonFunc::configAndBindTexture(texture_id, str.data);
        texture.id = texture_id;
        texture.type = type_name;
        texture.path = str.data;
        textures.push_back(texture);
        loaded_textures_.push_back(texture);
    }
    return textures;
}
