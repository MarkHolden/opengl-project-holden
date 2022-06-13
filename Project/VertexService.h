#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

class VertexService
{
public:
    static void AddFace(std::vector<GLfloat>& vertices, std::vector<GLushort>& indices,
        glm::vec3 vertex1, glm::vec2 vertex1TextureCoordinates,
        glm::vec3 vertex2, glm::vec2 vertex2TextureCoordinates,
        glm::vec3 vertex3, glm::vec2 vertex3TextureCoordinates)
    {
        GLushort index = indices.size() > 0 ? indices.back() : -1;
        glm::vec3 faceNormal = GetFaceNormal(vertex1, vertex2, vertex3);
        AddVector(vertices, vertex1);
        AddVector(vertices, faceNormal);
        AddTextureCoordinate(vertices, vertex1TextureCoordinates);
        indices.push_back(index + 1);

        AddVector(vertices, vertex2);
        AddVector(vertices, faceNormal);
        AddTextureCoordinate(vertices, vertex2TextureCoordinates);
        indices.push_back(index + 2);
        
        AddVector(vertices, vertex3);
        AddVector(vertices, faceNormal);
        AddTextureCoordinate(vertices, vertex3TextureCoordinates);
        indices.push_back(index + 3);
    }

private:
    static glm::vec3 GetFaceNormal(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3)
    {
        glm::vec3 edge1 = vertex1 - vertex2;
        glm::vec3 edge2 = vertex3 - vertex2;
        glm::vec3 cross = glm::cross(edge1, edge2);
        return glm::normalize(cross);
    }

    static void AddVector(std::vector<GLfloat>& vertices, glm::vec3 vector)
    {
        AddVector(vertices, vector.x, vector.y, vector.z);
    }

    static void AddVector(std::vector<GLfloat>& vertices, GLfloat x, GLfloat y, GLfloat z)
    {
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
    }

    static void AddTextureCoordinate(std::vector<GLfloat>& verts, GLfloat s, GLfloat t)
    {
        verts.push_back(s);
        verts.push_back(t);
    }

    static void AddTextureCoordinate(std::vector<GLfloat>& verts, glm::vec2 texture)
    {
        AddTextureCoordinate(verts, texture.s, texture.t);
    }
};