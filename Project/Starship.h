//#pragma once
//#include <glm/glm.hpp>
//#include <GL/glew.h>
//#include <vector>
//
//#include "VertexService.h"
//
//constexpr auto PI = 3.1415927;
//
//const glm::vec3 tiles = glm::vec3(0.1f, 0.1f, 0.1f);
//const glm::vec3 steel = glm::vec3(0.56f, 0.62f, 0.65f);
//
//bool debug = false;
//
//class Starship {
//public:
//    static void SetStarship(std::vector<GLfloat>& vertices, std::vector<GLushort>& indices)
//    {   
//        SetCylinder(4.5f, 70.0f, vertices, indices);
//        SetCylinder(4.5f, 36.0f, vertices, indices, false, glm::vec3(0.0f, 75.0f, 0.0f));
//        //SetRearFlap(glm::vec3(4.5f, 75.0f, 0.0f), vertices, indices);
//        //SetRearFlap(glm::vec3(-4.5f, 75.0f, 0.0f), vertices, indices, /*Flip*/ true);
//    }
//
//private:
//    static void SetCylinder(GLfloat radius, GLfloat height, std::vector<GLfloat>& vertices, std::vector<GLushort>& indices, bool isBooster = true /* sorry Uncle Bob :( */, glm::vec3 transform = glm::vec3())
//    {
//        const GLfloat top = height + transform.y;
//        const GLfloat base = transform.y;
//        GLfloat x = 0.0;
//        GLfloat z = 0.0;
//        GLfloat angle = 0.0;
//        GLfloat angle_stepsize = 0.3142f; // 0.1f;
//        int colorSelection = 0;
//
//        while (angle < 2 * PI) {
//            GLushort index = indices.back() + 1;
//
//            x = radius * cos(angle) + transform.x;
//            z = radius * sin(angle) + transform.z;
//
//            VertexService::AddVector(vertices, x, top, z); // 0
//            VertexService::AddColor(vertices, GetColor(angle + angle_stepsize, colorSelection, isBooster));
//            VertexService::AddTextureCoordinate(vertices, 0.0f, height);
//
//            VertexService::AddVector(vertices, x, base, z); // 1
//            VertexService::AddColor(vertices, GetColor(angle + angle_stepsize, colorSelection, isBooster));
//            VertexService::AddTextureCoordinate(vertices, 0.0f, 0.0f);
//
//            angle = angle + angle_stepsize;
//
//            x = radius * cos(angle) + transform.x;
//            z = radius * sin(angle) + transform.z;
//
//            VertexService::AddVector(vertices, x, top, z); // 2
//            VertexService::AddColor(vertices, GetColor(angle, colorSelection, isBooster));
//            VertexService::AddTextureCoordinate(vertices, 20 * radius, height);
//
//            VertexService::AddVector(vertices, x, base, z); // 3
//            VertexService::AddColor(vertices, GetColor(angle, colorSelection, isBooster));
//            VertexService::AddTextureCoordinate(vertices, 20 * radius, 0.0f);
//
//            // Top center coordinate
//            VertexService::AddVector(vertices, 0.0f, top, 0.0f); // 4
//            VertexService::AddColor(vertices, GetColor(angle, colorSelection, isBooster));
//            VertexService::AddTextureCoordinate(vertices, 0.0f, 0.0f);
//
//            // Bottom center coordinate
//            VertexService::AddVector(vertices, 0.0f, base, 0.0f); // 5
//            VertexService::AddColor(vertices, GetColor(angle, colorSelection, isBooster));
//            VertexService::AddTextureCoordinate(vertices, 0.0f, 0.0f);
//
//            VertexService::SetTriangle(indices, index, index + 1, index + 2); // First side triangle
//            VertexService::SetTriangle(indices, index + 1, index + 2, index + 3); // Second side triangle
//            VertexService::SetTriangle(indices, index, index + 2, index + 4); // Top triangle
//            VertexService::SetTriangle(indices, index + 1, index + 3, index + 5); // Bottom triangle
//
//            colorSelection++;
//        }
//    }
//
//    static void SetRearFlap(glm::vec3 transform, std::vector<GLfloat>& vertices, std::vector<GLushort>& indices, bool flip = false)
//    {
//
//        GLfloat width = 4.0f * (flip ? -1 : 1);
//
//        GLushort index = indices.back() + 1;
//
//        // Steel side of the flap
//        {
//            VertexService::AddVector(vertices, transform.x, transform.y, transform.z - 0.2f); // 0
//            VertexService::AddColor(vertices, steel);
//
//            VertexService::AddVector(vertices, transform.x, transform.y + 10.0f, transform.z - 0.2f); // 1
//            VertexService::AddColor(vertices, steel);
//
//            VertexService::AddVector(vertices, transform.x + width, transform.y, transform.z - 0.1f); // 2
//            VertexService::AddColor(vertices, steel);
//
//            VertexService::AddVector(vertices, transform.x + width, transform.y + 10.0f, transform.z - 0.1f); // 3
//            VertexService::AddColor(vertices, steel);
//
//            VertexService::AddVector(vertices, transform.x, transform.y + 13.0f, transform.z - 0.2f); // 4
//            VertexService::AddColor(vertices, steel);
//
//            // Bottom inside
//            indices.push_back(index);
//            indices.push_back(index + 1);
//            indices.push_back(index + 2);
//
//            // Bottom outside
//            indices.push_back(index + 1);
//            indices.push_back(index + 2);
//            indices.push_back(index + 3);
//
//            // Top triangle
//            indices.push_back(index + 1);
//            indices.push_back(index + 3);
//            indices.push_back(index + 4);
//        }
//
//        // Tile side of the flap
//        {
//            VertexService::AddVector(vertices, transform.x, transform.y, transform.z + 0.2f); // 5
//            VertexService::AddColor(vertices, tiles);
//
//            VertexService::AddVector(vertices, transform.x, transform.y + 10.0f, transform.z + 0.2f); // 6
//            VertexService::AddColor(vertices, tiles);
//
//            VertexService::AddVector(vertices, transform.x + width, transform.y, transform.z + 0.1f); // 7
//            VertexService::AddColor(vertices, tiles);
//
//            VertexService::AddVector(vertices, transform.x + width, transform.y + 10.0f, transform.z + 0.1f); // 8
//            VertexService::AddColor(vertices, tiles);
//
//            VertexService::AddVector(vertices, transform.x, transform.y + 13.0f, transform.z + 0.2f); // 9
//            VertexService::AddColor(vertices, tiles);
//
//            // Bottom inside
//            indices.push_back(index + 5);
//            indices.push_back(index + 6);
//            indices.push_back(index + 7);
//
//            // Bottom outside
//            indices.push_back(index + 6);
//            indices.push_back(index + 7);
//            indices.push_back(index + 8);
//
//            // Top triangle
//            indices.push_back(index + 6);
//            indices.push_back(index + 8);
//            indices.push_back(index + 9);
//        }
//
//        // Flap edges
//        {
//            VertexService::AddVector(vertices, transform.x, transform.y, transform.z - 0.2f); // 10
//            VertexService::AddColor(vertices, tiles);
//
//            VertexService::AddVector(vertices, transform.x, transform.y + 10.0f, transform.z - 0.2f); // 11
//            VertexService::AddColor(vertices, tiles);
//
//            VertexService::AddVector(vertices, transform.x + width, transform.y, transform.z - 0.1f); // 12
//            VertexService::AddColor(vertices, tiles);
//
//            VertexService::AddVector(vertices, transform.x + width, transform.y + 10.0f, transform.z - 0.1f); // 13
//            VertexService::AddColor(vertices, tiles);
//
//            VertexService::AddVector(vertices, transform.x, transform.y + 13.0f, transform.z - 0.2f); // 14
//            VertexService::AddColor(vertices, tiles);
//
//            // Bottom
//            VertexService::SetTriangle(indices, index + 10, index + 5, index + 7);
//            VertexService::SetTriangle(indices, index + 10, index + 12, index + 7);
//
//            // Side
//            VertexService::SetTriangle(indices, index + 13, index + 12, index + 7);
//            VertexService::SetTriangle(indices, index + 13, index + 8, index + 7);
//
//            // Top
//            VertexService::SetTriangle(indices, index + 13, index + 14, index + 8);
//            VertexService::SetTriangle(indices, index + 8, index + 9, index + 14);
//        }
//    }
//
//    static glm::vec3 GetColor(GLfloat angle, int colorSelection, bool isBooster)
//    {
//        if (debug)
//            return VertexService::GetColor(colorSelection);
//
//        if (isBooster)
//            return steel;
//
//        return angle < PI + 0.1f ? tiles : steel;
//    }
//
//};