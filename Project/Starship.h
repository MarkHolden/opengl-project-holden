#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

#include "VertexService.h"

constexpr auto PI = 3.1415927;


class Starship {
public:
    static void SetCylinder(GLfloat radius, GLfloat height, std::vector<GLfloat>& verts, std::vector<GLushort>& indices, glm::vec3 transform = glm::vec3())
    {
        const GLfloat top = height + transform.y;
        const GLfloat base = transform.y;
        GLfloat x = 0.0;
        GLfloat z = 0.0;
        GLfloat angle = 0.0;
        GLfloat angle_stepsize = 0.3142f; // 0.1f;
        int colorSelection = 0;

        while (angle < 2 * PI) {
            GLushort index = indices.back() + 1;

            x = radius * cos(angle) + transform.x;
            z = radius * sin(angle) + transform.z;

            VertexService::AddCoordinate(verts, x, top, z); // 0
            VertexService::AddColor(verts, VertexService::GetColor(colorSelection));

            VertexService::AddCoordinate(verts, x, base, z); // 1
            VertexService::AddColor(verts, VertexService::GetColor(colorSelection));

            angle = angle + angle_stepsize;

            x = radius * cos(angle) + transform.x;
            z = radius * sin(angle) + transform.z;

            VertexService::AddCoordinate(verts, x, top, z); // 2
            VertexService::AddColor(verts, VertexService::GetColor(colorSelection));

            VertexService::AddCoordinate(verts, x, base, z); // 3
            VertexService::AddColor(verts, VertexService::GetColor(colorSelection));

            // Top center coordinate
            VertexService::AddCoordinate(verts, 0.0f, top, 0.0f); // 4
            VertexService::AddColor(verts, VertexService::GetColor(colorSelection));

            // Bottom center coordinate
            VertexService::AddCoordinate(verts, 0.0f, base, 0.0f); // 5
            VertexService::AddColor(verts, VertexService::GetColor(colorSelection));

            // First side triangle
            indices.push_back(index); // 0
            indices.push_back(index + 1); // 1
            indices.push_back(index + 2); // 2

            // Second side triangle
            indices.push_back(index + 1); // 1
            indices.push_back(index + 2); // 2
            indices.push_back(index + 3); // 3

            // Top triangle
            indices.push_back(index); // 0
            indices.push_back(index + 2); // 2
            indices.push_back(index + 4); // 4

            // Bottom triangle
            indices.push_back(index + 1); // 1
            indices.push_back(index + 3); // 3
            indices.push_back(index + 5); // 5

            colorSelection++;
        }
    }

    static void SetRearFlap(std::vector<GLfloat>& verts, std::vector<GLushort>& indices, glm::vec3 transform, bool flip = false)
    {
        const glm::vec3 tiles = glm::vec3(0.1f, 0.1f, 0.1f);
        const glm::vec3 steel = glm::vec3(0.56f, 0.62f, 0.65f);
        GLfloat width = 4.0f * (flip ? -1 : 1);

        GLushort index = indices.back() + 1;

        VertexService::AddCoordinate(verts, transform.x, transform.y, transform.z - 0.2f); // 0
        VertexService::AddColor(verts, tiles);

        VertexService::AddCoordinate(verts, transform.x, transform.y + 10.0f, transform.z - 0.2f); // 1
        VertexService::AddColor(verts, tiles);

        VertexService::AddCoordinate(verts, transform.x + width, transform.y, transform.z - 0.1f); // 2
        VertexService::AddColor(verts, tiles);

        VertexService::AddCoordinate(verts, transform.x + width, transform.y + 10.0f, transform.z - 0.1f); // 3
        VertexService::AddColor(verts, tiles);

        VertexService::AddCoordinate(verts, transform.x, transform.y + 13.0f, transform.z - 0.2f); // 4
        VertexService::AddColor(verts, tiles);

        // Bottom inside
        indices.push_back(index);
        indices.push_back(index + 1);
        indices.push_back(index + 2);

        // Bottom outside
        indices.push_back(index + 1);
        indices.push_back(index + 2);
        indices.push_back(index + 3);

        // Top triangle
        indices.push_back(index + 1);
        indices.push_back(index + 3);
        indices.push_back(index + 4);
    }
};