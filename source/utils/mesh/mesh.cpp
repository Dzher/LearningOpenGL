#include "mesh.h"
#include <QtGui/qopenglext.h>
#include <string>
#include "utils/common/common.h"

using namespace utils;

Mesh::Mesh(const std::vector<Vertex>& vertexes, const std::vector<unsigned int>& indices,
           const std::vector<Texture>& textures)
    : vertexes_(vertexes), indices_(indices), textures_(textures)
{
    initMesh();
}

void Mesh::initMesh()
{
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertexes_.size() * sizeof(Vertex), &vertexes_[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), &indices_[0], GL_STATIC_DRAW);

    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coord));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_bone_ids));
    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_weights));
    glBindVertexArray(0);
}

void Mesh::draw(Shader& shader)
{
    GLuint diffuse_suffix = 1;
    GLuint specular_suffix = 1;
    GLuint normal_suffix = 1;
    GLuint height_suffix = 1;

    for (int index = 0; index < textures_.size(); index++)
    {
        std::string texture_type = textures_[index].type;
        std::string suffix;
        if ("texture_diffuse" == texture_type)
        {
            suffix = std::to_string(diffuse_suffix);
            diffuse_suffix++;
        }
        else if ("texture_specular" == texture_type)
        {
            suffix = std::to_string(specular_suffix);
            specular_suffix++;
        }
        else if ("texture_normal" == texture_type)
        {
            suffix = std::to_string(normal_suffix);
            normal_suffix++;
        }
        else if ("texture_height" == texture_type)
        {
            suffix = std::to_string(height_suffix);
            height_suffix++;
        }

        glActiveTexture(GL_TEXTURE0 + index);
        shader.setIntUniform(texture_type + suffix, index);
        glBindTexture(GL_TEXTURE_2D, textures_[index].id);
    }
    // draw mesh
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices_.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}