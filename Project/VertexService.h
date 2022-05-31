#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

class VertexService
{
public:
    static void AddCoordinate(std::vector<GLfloat>& verts, GLfloat x, GLfloat y, GLfloat z)
    {
        verts.push_back(x);
        verts.push_back(y);
        verts.push_back(z);
    }

    static void AddColor(std::vector<GLfloat>& verts, glm::vec3 rgb, GLfloat a = 1.0f)
    {
        verts.push_back(rgb.r);
        verts.push_back(rgb.g);
        verts.push_back(rgb.b);
        verts.push_back(a);
    }

    static glm::vec3 GetColor(int selection)
    {
        switch (selection % 8)
        {
        case 0: // Red
            return glm::vec3(1.0f, 0.0f, 0.0f);

        case 1: // Orange
            return glm::vec3(1.0f, 0.5f, 0.0f);

        case 2: // Yellow
            return glm::vec3(1.0f, 1.0f, 0.0f);

        case 3: // Green
            return glm::vec3(0.0f, 1.0f, 0.0f);

        case 4: // Blue Green
            return glm::vec3(0.0f, 1.0f, 1.0f);

        case 5: // Blue
            return glm::vec3(0.0f, 0.0f, 1.0f);

        case 6: // Violet
            return glm::vec3(0.5f, 0.0f, 1.0f);

        case 7: // Purple
            return glm::vec3(1.0f, 0.0f, 1.0f);

        default:
            return glm::vec3();
        }
    }
};