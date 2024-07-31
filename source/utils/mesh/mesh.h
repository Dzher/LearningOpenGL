#ifndef _UTILS_MESH_H_
#define _UTILS_MESH_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "utils/shader/shader.h"

namespace utils
{
static constexpr int kMaxBoneInfluence = 4;
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coord;
    glm::vec3 tangent;
    // bitangent
    glm::vec3 bitangent;
    // bone indexes which will influence this vertex
    int m_bone_ids[kMaxBoneInfluence];
    // weights from each bone
    float m_weights[kMaxBoneInfluence];
};

struct Texture
{
    GLuint id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    explicit Mesh(const std::vector<Vertex>& vertexes, const std::vector<unsigned int>& indices,
                  const std::vector<Texture>& textures);
    ~Mesh();

    void draw(Shader& shader);
    inline GLuint vao()
    {
        return vao_;
    }

    inline std::vector<unsigned int> indices()
    {
        return indices_;
    }

private:
    void initMesh();

private:
    std::vector<Vertex> vertexes_;
    std::vector<unsigned int> indices_;
    std::vector<Texture> textures_;

    GLuint vao_;
    GLuint vbo_;
    GLuint ebo_;
};
}  // namespace utils
#endif