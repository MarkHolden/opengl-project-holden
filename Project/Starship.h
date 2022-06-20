#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "VertexService.h"

using namespace std;

constexpr auto PI = 3.1415927;

class Starship {
public:
    static void SetStarshipTiledSection(GLMesh& mesh)
    {   
        std::vector<GLfloat> vertices;
        vertices.clear();
        std::vector<GLushort> indices;
        indices.clear();

        GLfloat tileStart = 0.0f;
        GLfloat tileEnd = PI;
        SetCylinder(4.5f, 36.0f, vertices, indices, glm::vec3(0.0f, 75.0f, 0.0f), tileStart, tileEnd);
        
        SetNoseCone(vertices, indices, glm::vec3(0.0f, 111.0f, 0.0f), tileStart, tileEnd);
        
        SetRearFlap(glm::vec3(4.5f, 75.0f, 0.0f), vertices, indices);
        SetRearFlap(glm::vec3(-4.5f, 75.0f, 0.0f), vertices, indices, /*isFlipped*/ true);

        mesh.UCreateMesh(vertices, indices);
    }

    static void SetBoosterReinforcedSection(GLMesh& mesh)
    {
        std::vector<GLfloat> vertices;
        vertices.clear();
        std::vector<GLushort> indices;
        indices.clear();

        SetCylinder(4.5f, 5.0f, vertices, indices, glm::vec3(0.0f, 65.0f, 0.0f));

        mesh.UCreateMesh(vertices, indices);
    }

    static void SetStarshipSteelSection(GLMesh& mesh)
    {
        std::vector<GLfloat> vertices;
        vertices.clear();
        std::vector<GLushort> indices;
        indices.clear();

        GLfloat steelStart = PI;
        SetCylinder(4.5f, 36.0f, vertices, indices, glm::vec3(0.0f, 75.0f, 0.0f), steelStart);
        SetNoseCone(vertices, indices, glm::vec3(0.0f, 111.0f, 0.0f), steelStart);

        SetRearFlap(glm::vec3(4.5f, 75.0f, 0.0f), vertices, indices, /*isFlipped*/ false, /*isTiles*/ false);
        SetRearFlap(glm::vec3(-4.5f, 75.0f, 0.0f), vertices, indices, /*isFlipped*/ true, /*isTiles*/ false);

        mesh.UCreateMesh(vertices, indices);
    }

    static void SetBoosterSmoothSection(GLMesh& mesh)
    {
        std::vector<GLfloat> vertices;
        vertices.clear();
        std::vector<GLushort> indices;
        indices.clear();

        SetCylinder(4.5f, 65.0f, vertices, indices);

        mesh.UCreateMesh(vertices, indices);
    }



private:
    static void SetCylinder(GLfloat radius, GLfloat height, std::vector<GLfloat>& vertices, std::vector<GLushort>& indices, glm::vec3 transform = glm::vec3(), GLfloat start = 0.0f, GLfloat end = 2 * PI)
    {
        const GLfloat top = height + transform.y;
        const GLfloat base = transform.y;
        GLfloat x = 0.0;
        GLfloat z = 0.0;
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

            x = radius * cos(angle) + transform.x;
            z = radius * sin(angle) + transform.z;

            glm::vec3 northEast = glm::vec3(x, top, z);
            glm::vec2 neTexture = glm::vec2(PI * radius / 10, height);
            glm::vec3 southEast = glm::vec3(x, base, z);
            glm::vec2 seTexture = glm::vec2(PI * radius / 10, 0.0f);

            VertexService::AddFace(vertices, indices, southWest, swTexture, northWest, nwTexture, northEast, neTexture);
            VertexService::AddFace(vertices, indices, southWest, swTexture, northEast, neTexture, southEast, seTexture);
        }
    }

    static void SetNoseCone(std::vector<GLfloat>& vertices, std::vector<GLushort>& indices, glm::vec3 transform = glm::vec3(), GLfloat start = 0.0f, GLfloat end = 2 * PI)
    {
        SetConeSection(4.5f, 4.4f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(4.4f, 4.3f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(4.3f, 4.2f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(4.2f, 4.1f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(4.1f, 4.0f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(4.0f, 3.8f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(3.8f, 3.6f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(3.6f, 3.4f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(3.4f, 3.2f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(3.2f, 3.0f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(3.0f, 2.7f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(2.7f, 2.4f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(2.4f, 2.0f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(2.0f, 1.6f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(1.6f, 1.1f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(1.1f, 0.5f, 1.0f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 1.0f, 0.0f);
        SetConeSection(0.5f, 0.1f, 0.3f, vertices, indices, transform, start, end);
        transform = transform + glm::vec3(0.0f, 0.3f, 0.0f);
        SetConeSection(0.1f, 0.0f, 0.05f, vertices, indices, transform, start, end);
    }

    static void SetConeSection(GLfloat radius1, GLfloat radius2, GLfloat height, std::vector<GLfloat>&vertices, std::vector<GLushort>&indices, glm::vec3 transform = glm::vec3(), GLfloat start = 0.0f, GLfloat end = 2 * PI)
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
            x = radius1 * cos(angle) + transform.x;
            z = radius1 * sin(angle) + transform.z;
            x2 = radius2 * cos(angle) + transform.x;
            z2 = radius2 * sin(angle) + transform.z;

            glm::vec3 northWest = glm::vec3(x2, top, z2);
            glm::vec2 nwTexture = glm::vec2(0.0f, height);
            glm::vec3 southWest = glm::vec3(x, base, z);
            glm::vec2 swTexture = glm::vec2(0.0f, 0.0f);

            angle = angle + angle_stepsize;

            x = radius1 * cos(angle) + transform.x;
            z = radius1 * sin(angle) + transform.z;
            x2 = radius2 * cos(angle) + transform.x;
            z2 = radius2 * sin(angle) + transform.z;

            glm::vec3 northEast = glm::vec3(x2, top, z2);
            glm::vec2 neTexture = glm::vec2(PI * radius2 / 10, height);
            glm::vec3 southEast = glm::vec3(x, base, z);
            glm::vec2 seTexture = glm::vec2(PI * radius1 / 10, 0.0f);

            VertexService::AddFace(vertices, indices, southWest, swTexture, northWest, nwTexture, northEast, neTexture);
            VertexService::AddFace(vertices, indices, southWest, swTexture, northEast, neTexture, southEast, seTexture);
        }
    }

        // Tile side of the flap
        {
            glm::vec3 northWest = glm::vec3(transform.x, transform.y + 10.0f, transform.z + 0.2f);
            glm::vec2 nwTexture = glm::vec2(0.0f, 10.0f);
            glm::vec3 southWest = glm::vec3(transform.x, transform.y, transform.z + 0.2f);
            glm::vec2 swTexture = glm::vec2(0.0f, 0.0f);

            glm::vec3 northEast = glm::vec3(transform.x + width, transform.y + 10.0f, transform.z + 0.1f);
            glm::vec2 neTexture = glm::vec2(width, 10.0f);
            glm::vec3 southEast = glm::vec3(transform.x + width, transform.y, transform.z + 0.1f);
            glm::vec2 seTexture = glm::vec2(width, 0.0f);

            VertexService::AddFace(vertices, indices, southWest, swTexture, northWest, nwTexture, northEast, neTexture);
            VertexService::AddFace(vertices, indices, southWest, swTexture, northEast, neTexture, southEast, seTexture);

            southEast = northEast;
            southWest = northWest;
            northEast = glm::vec3(transform.x, transform.y + 16.0f, transform.z + 0.2f);
            neTexture = glm::vec2(width, 6.0f);
            VertexService::AddFace(vertices, indices, southWest, swTexture, northEast, neTexture, southEast, seTexture);

            //VertexService::AddVector(vertices, transform.x, transform.y, transform.z + 0.2f); // 5

            //VertexService::AddVector(vertices, transform.x, transform.y + 10.0f, transform.z + 0.2f); // 6

            //VertexService::AddVector(vertices, transform.x + width, transform.y, transform.z + 0.1f); // 7

    static void SetRearFlap(glm::vec3 transform, std::vector<GLfloat>&vertices, std::vector<GLushort>&indices, bool isFlipped = false, bool isTiles = true)
    {
        GLfloat width = 4.0f * (isFlipped ? -1 : 1);
        int offsetDirection = isTiles ? 1 : -1;

        glm::vec3 northWest = glm::vec3(transform.x, transform.y + 10.0f, transform.z + 0.2f * offsetDirection);
        glm::vec2 nwTexture = glm::vec2(0.0f, 10.0f);
        glm::vec3 southWest = glm::vec3(transform.x, transform.y, transform.z + 0.2f * offsetDirection);
        glm::vec2 swTexture = glm::vec2(0.0f, 0.0f);

        glm::vec3 northEast = glm::vec3(transform.x + width, transform.y + 10.0f, transform.z + 0.1f * offsetDirection);
        glm::vec2 neTexture = glm::vec2(width, 10.0f);
        glm::vec3 southEast = glm::vec3(transform.x + width, transform.y, transform.z + 0.1f * offsetDirection);
        glm::vec2 seTexture = glm::vec2(width, 0.0f);

        VertexService::AddFace(vertices, indices, southWest, swTexture, northWest, nwTexture, northEast, neTexture);
        VertexService::AddFace(vertices, indices, southWest, swTexture, northEast, neTexture, southEast, seTexture);

        glm::vec3 bottom = southWest; // set these before they get reassigned.
        glm::vec3 wingtip1 = southEast;

        southEast = northEast;
        southWest = northWest;
        northWest = glm::vec3(transform.x, transform.y + 16.0f, transform.z + 0.2f * offsetDirection);
        nwTexture = glm::vec2(0.0f, 6.0f);
        VertexService::AddFace(vertices, indices, southWest, swTexture, northWest, nwTexture, southEast, seTexture);

        // Flap edges
        if (isTiles)
        {
            glm::vec3 wingtip2 = northEast;
            glm::vec3 wingtip3 = northWest;
            glm::vec3 wingtip1Back = wingtip1 + glm::vec3(0.0f, 0.0f, -0.2f);
            glm::vec3 wingtip2Back = wingtip2 + glm::vec3(0.0f, 0.0f, -0.2f);

            swTexture = glm::vec2(0.0f, 0.0f);
            seTexture = glm::vec2(0.2f, 0.0f);
            neTexture = glm::vec2(0.2f, 10.0f);
            nwTexture = glm::vec2(0.0f, 10.0f);

            // Side edge
            VertexService::AddFace(vertices, indices, wingtip1Back, swTexture, wingtip1, seTexture, wingtip2, neTexture);
            VertexService::AddFace(vertices, indices, wingtip1Back, swTexture, wingtip2, neTexture, wingtip2Back, nwTexture);

            glm::vec3 wingtip3Back = wingtip3 + glm::vec3(0.0f, 0.0f, -0.4f);
            neTexture = glm::vec2(0.4f, 7.2f);
            nwTexture = glm::vec2(0.0f, 7.2f);

            // Top edge
            VertexService::AddFace(vertices, indices, wingtip2Back, swTexture, wingtip2, seTexture, wingtip3, neTexture);
            VertexService::AddFace(vertices, indices, wingtip2Back, swTexture, wingtip3, neTexture, wingtip3Back, nwTexture);

            glm::vec3 bottomBack = bottom + glm::vec3(0.0f, 0.0f, -0.4f);
            seTexture = glm::vec2(0.4f, 0.0f);
            neTexture = glm::vec2(0.4f, width);
            nwTexture = glm::vec2(0.0f, width);

            // Bottom
            VertexService::AddFace(vertices, indices, bottomBack, swTexture, bottom, seTexture, wingtip1, neTexture);
            VertexService::AddFace(vertices, indices, bottomBack, swTexture, wingtip1, neTexture, wingtip1Back, nwTexture);
        }
    }
};