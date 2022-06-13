#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "VertexService.h"

using namespace std;

constexpr auto PI = 3.1415927;

const glm::vec3 tiles = glm::vec3(0.1f, 0.1f, 0.1f);
const glm::vec3 steel = glm::vec3(0.56f, 0.62f, 0.65f);

bool debug = false;

class Starship {
public:
    static void SetStarshipTiledSection(GLMesh& mesh)
    {   
        std::vector<GLfloat> vertices;
        vertices.clear();
        std::vector<GLushort> indices;
        indices.clear();
        //SetCylinder(4.5f, 70.0f, vertices, indices);
        SetCylinder(4.5f, 36.0f, vertices, indices, 0.0f, PI, glm::vec3(0.0f, 75.0f, 0.0f));
        //SetRearFlap(glm::vec3(4.5f, 75.0f, 0.0f), vertices, indices);
        //SetRearFlap(glm::vec3(-4.5f, 75.0f, 0.0f), vertices, indices, /*Flip*/ true);

        mesh.UCreateMesh(vertices, indices);
    }

private:
    static void SetCylinder(GLfloat radius, GLfloat height, std::vector<GLfloat>& vertices, std::vector<GLushort>& indices, GLfloat start, GLfloat end, glm::vec3 transform = glm::vec3())
    {
        const GLfloat top = height + transform.y;
        const GLfloat base = transform.y;
        GLfloat x = 0.0;
        GLfloat z = 0.0;
        GLfloat x2 = 0.0;
        GLfloat z2 = 0.0;
        GLfloat angle = start;
        GLfloat angle_stepsize = 0.3142f;

        while (angle < end) {
            x = radius * cos(angle) + transform.x;
            z = radius * sin(angle) + transform.z;

            glm::vec3 northWest = glm::vec3(x, top, z);
            glm::vec2 nwTexture = glm::vec2(0.0f, height);
            glm::vec3 southWest = glm::vec3(x, base, z);
            glm::vec2 swTexture = glm::vec2(0.0f, 0.0f);

            angle = angle + angle_stepsize;

            x2 = radius * cos(angle) + transform.x;
            z2 = radius * sin(angle) + transform.z;

            glm::vec3 northEast = glm::vec3(x2, top, z2);
            glm::vec2 neTexture = glm::vec2(PI * radius / 10, height);
            glm::vec3 southEast = glm::vec3(x2, base, z2);
            glm::vec2 seTexture = glm::vec2(PI * radius / 10, 0.0f);

            VertexService::AddFace(vertices, indices, southWest, swTexture, northWest, nwTexture, northEast, neTexture);
            VertexService::AddFace(vertices, indices, southWest, swTexture, northEast, neTexture, southEast, seTexture);
        }
    }

    //static void SetRearFlap(glm::vec3 transform, std::vector<GLfloat>& vertices, std::vector<GLushort>& indices, bool flip = false)
    //{

    //    GLfloat width = 4.0f * (flip ? -1 : 1);

    //    GLushort index = indices.back() + 1;

    //    // Steel side of the flap
    //    {
    //        VertexService::AddVector(vertices, transform.x, transform.y, transform.z - 0.2f); // 0
    //        VertexService::AddColor(vertices, steel);

    //        VertexService::AddVector(vertices, transform.x, transform.y + 10.0f, transform.z - 0.2f); // 1
    //        VertexService::AddColor(vertices, steel);

    //        VertexService::AddVector(vertices, transform.x + width, transform.y, transform.z - 0.1f); // 2
    //        VertexService::AddColor(vertices, steel);

    //        VertexService::AddVector(vertices, transform.x + width, transform.y + 10.0f, transform.z - 0.1f); // 3
    //        VertexService::AddColor(vertices, steel);

    //        VertexService::AddVector(vertices, transform.x, transform.y + 13.0f, transform.z - 0.2f); // 4
    //        VertexService::AddColor(vertices, steel);

    //        // Bottom inside
    //        indices.push_back(index);
    //        indices.push_back(index + 1);
    //        indices.push_back(index + 2);

    //        // Bottom outside
    //        indices.push_back(index + 1);
    //        indices.push_back(index + 2);
    //        indices.push_back(index + 3);

    //        // Top triangle
    //        indices.push_back(index + 1);
    //        indices.push_back(index + 3);
    //        indices.push_back(index + 4);
    //    }

    //    // Tile side of the flap
    //    {
    //        VertexService::AddVector(vertices, transform.x, transform.y, transform.z + 0.2f); // 5
    //        VertexService::AddColor(vertices, tiles);

    //        VertexService::AddVector(vertices, transform.x, transform.y + 10.0f, transform.z + 0.2f); // 6
    //        VertexService::AddColor(vertices, tiles);

    //        VertexService::AddVector(vertices, transform.x + width, transform.y, transform.z + 0.1f); // 7
    //        VertexService::AddColor(vertices, tiles);

    //        VertexService::AddVector(vertices, transform.x + width, transform.y + 10.0f, transform.z + 0.1f); // 8
    //        VertexService::AddColor(vertices, tiles);

    //        VertexService::AddVector(vertices, transform.x, transform.y + 13.0f, transform.z + 0.2f); // 9
    //        VertexService::AddColor(vertices, tiles);

    //        // Bottom inside
    //        indices.push_back(index + 5);
    //        indices.push_back(index + 6);
    //        indices.push_back(index + 7);

    //        // Bottom outside
    //        indices.push_back(index + 6);
    //        indices.push_back(index + 7);
    //        indices.push_back(index + 8);

    //        // Top triangle
    //        indices.push_back(index + 6);
    //        indices.push_back(index + 8);
    //        indices.push_back(index + 9);
    //    }

    //    // Flap edges
    //    {
    //        VertexService::AddVector(vertices, transform.x, transform.y, transform.z - 0.2f); // 10
    //        VertexService::AddColor(vertices, tiles);

    //        VertexService::AddVector(vertices, transform.x, transform.y + 10.0f, transform.z - 0.2f); // 11
    //        VertexService::AddColor(vertices, tiles);

    //        VertexService::AddVector(vertices, transform.x + width, transform.y, transform.z - 0.1f); // 12
    //        VertexService::AddColor(vertices, tiles);

    //        VertexService::AddVector(vertices, transform.x + width, transform.y + 10.0f, transform.z - 0.1f); // 13
    //        VertexService::AddColor(vertices, tiles);

    //        VertexService::AddVector(vertices, transform.x, transform.y + 13.0f, transform.z - 0.2f); // 14
    //        VertexService::AddColor(vertices, tiles);

    //        // Bottom
    //        VertexService::SetTriangle(indices, index + 10, index + 5, index + 7);
    //        VertexService::SetTriangle(indices, index + 10, index + 12, index + 7);

    //        // Side
    //        VertexService::SetTriangle(indices, index + 13, index + 12, index + 7);
    //        VertexService::SetTriangle(indices, index + 13, index + 8, index + 7);

    //        // Top
    //        VertexService::SetTriangle(indices, index + 13, index + 14, index + 8);
    //        VertexService::SetTriangle(indices, index + 8, index + 9, index + 14);
    //    }
    //}
};