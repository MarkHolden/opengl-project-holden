#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <math.h> 

#include "VertexService.h"
#include "GLMesh.h"

using namespace std;
const GLfloat SectionHeight = 6.0f;
const GLfloat LegOffset = 8.0f;
const int SectionCount = 24;

class Mechazilla {
public:
    static void SetTower(GLMesh& mesh)
    {
        std::vector<GLfloat> vertices;
        vertices.clear();
        std::vector<GLushort> indices;
        indices.clear();

        //Base
        SetBase(vertices, indices);
        
        // 24 sections
        for (int i = 0; i < SectionCount; ++i)
            SetSection(vertices, indices, i, i > 0);

        SetTop(vertices, indices);

        // American Flag

        mesh.UCreateMesh(vertices, indices);
    }
private:
    static void SetSection(std::vector<GLfloat>& vertices, std::vector<GLushort>& indices, int sectionNumber, bool hasCrossbeam)
    {
        glm::vec3 baseTransform = glm::vec3(20.0f, SectionHeight * sectionNumber, 20.0f);
        glm::vec3 pillar1Center = baseTransform + glm::vec3(0.0f, 0.0f, -LegOffset);
        glm::vec3 pillar2Center = baseTransform + glm::vec3(LegOffset, 0.0f, 0.0f);
        glm::vec3 pillar3Center = baseTransform + glm::vec3(0.0f, 0.0f, LegOffset);
        glm::vec3 pillar4Center = baseTransform + glm::vec3(-LegOffset, 0.0f, 0.0f);

        SetPillar(vertices, indices, pillar1Center);
        SetPillar(vertices, indices, pillar2Center);
        SetPillar(vertices, indices, pillar3Center);
        SetPillar(vertices, indices, pillar4Center);
        
        // crossbeam
        if (hasCrossbeam)
        {
            SetBeam(vertices, indices, pillar1Center, pillar2Center);
            SetBeam(vertices, indices, pillar2Center, pillar3Center);
            SetBeam(vertices, indices, pillar3Center, pillar4Center);
            SetBeam(vertices, indices, pillar4Center, pillar1Center);
        }

        // v
        SetV(vertices, indices, pillar1Center, pillar2Center);
        SetV(vertices, indices, pillar2Center, pillar3Center);
        SetV(vertices, indices, pillar3Center, pillar4Center);
        SetV(vertices, indices, pillar4Center, pillar1Center);
    }

    static void SetPillar(std::vector<GLfloat>& vertices, std::vector<GLushort>& indices, glm::vec3 transform = glm::vec3())
    {
        // pillar
        // 
        //   h______g
        //   /    / |
        // e/____/f |
        //  |  | |  |
        //  | d|_|__|c
        //  | /  | /
        // a|/___|/b

        GLfloat width = 0.75f;
        glm::vec3 a = glm::vec3(transform.x - width, transform.y,                 transform.z - width);
        glm::vec3 b = glm::vec3(transform.x + width, transform.y,                 transform.z - width);
        glm::vec3 c = glm::vec3(transform.x + width, transform.y,                 transform.z + width);
        glm::vec3 d = glm::vec3(transform.x - width, transform.y,                 transform.z + width);
        glm::vec3 e = glm::vec3(transform.x - width, SectionHeight + transform.y, transform.z - width);
        glm::vec3 f = glm::vec3(transform.x + width, SectionHeight + transform.y, transform.z - width);
        glm::vec3 g = glm::vec3(transform.x + width, SectionHeight + transform.y, transform.z + width);
        glm::vec3 h = glm::vec3(transform.x - width, SectionHeight + transform.y, transform.z + width);

        glm::vec2 swTexture = glm::vec2(0.0f, 0.0f);
        glm::vec2 nwTexture = glm::vec2(0.0f, SectionHeight);
        glm::vec2 seTexture = glm::vec2(1.0f, 0.0f);
        glm::vec2 neTexture = glm::vec2(1.0f, SectionHeight);

        // AB Face
        VertexService::AddFace(vertices, indices, a, swTexture, e, nwTexture, f, neTexture);
        VertexService::AddFace(vertices, indices, a, swTexture, f, neTexture, b, seTexture);

        // BC Face
        VertexService::AddFace(vertices, indices, b, swTexture, f, nwTexture, g, neTexture);
        VertexService::AddFace(vertices, indices, b, swTexture, g, neTexture, c, seTexture);

        // CD Face
        VertexService::AddFace(vertices, indices, c, swTexture, g, nwTexture, h, neTexture);
        VertexService::AddFace(vertices, indices, c, swTexture, h, neTexture, d, seTexture);

        // DA Face
        VertexService::AddFace(vertices, indices, d, swTexture, h, nwTexture, e, neTexture);
        VertexService::AddFace(vertices, indices, d, swTexture, e, neTexture, a, seTexture);
    }

    static void SetBeam(std::vector<GLfloat>& vertices, std::vector<GLushort>& indices, glm::vec3 start, glm::vec3 end)
    {
        // beam
        // 
        //            h_________g
        //            /|       /|
        //         e/________/f |
        // start ---|  |     | ----end
        //          | d|_____|__|c
        //          | /      | /
        //         a|/_______|/b

        GLfloat width = 0.125f;
        GLfloat slope = (start.z - end.z) / (start.x - end.x);
        if (isinf(slope))
            slope = 0;
        if (isnan(slope))
            slope = 1;

        GLfloat length = sqrt(pow((start.x - end.x), 2) + pow((start.y - end.y), 2) + pow((start.z - end.z), 2));
        glm::vec3 a = start + glm::vec3(+width, -width * 2, -width * slope);
        glm::vec3 b = end + glm::vec3(  +width, -width * 2, -width * slope);
        glm::vec3 c = end + glm::vec3(  -width, -width * 2, +width * slope);
        glm::vec3 d = start + glm::vec3(-width, -width * 2, +width * slope);
        glm::vec3 e = start + glm::vec3(+width, +width * 2, -width * slope);
        glm::vec3 f = end + glm::vec3(  +width, +width * 2, -width * slope);
        glm::vec3 g = end + glm::vec3(  -width, +width * 2, +width * slope);
        glm::vec3 h = start + glm::vec3(-width, +width * 2, +width * slope);

        glm::vec2 swTexture = glm::vec2(0.0f, 0.0f);
        glm::vec2 nwTexture = glm::vec2(0.0f, 1.0);
        glm::vec2 seTexture = glm::vec2(length, 0.0f);
        glm::vec2 neTexture = glm::vec2(length, 1.0);

        // AB Face
        VertexService::AddFace(vertices, indices, a, swTexture, e, nwTexture, f, neTexture);
        VertexService::AddFace(vertices, indices, a, swTexture, f, neTexture, b, seTexture);

        // Top Face
        VertexService::AddFace(vertices, indices, e, swTexture, h, nwTexture, g, neTexture);
        VertexService::AddFace(vertices, indices, e, swTexture, g, neTexture, f, seTexture);

        // CD Face
        VertexService::AddFace(vertices, indices, c, swTexture, g, nwTexture, h, neTexture);
        VertexService::AddFace(vertices, indices, c, swTexture, h, neTexture, d, seTexture);

        // Bottom Face
        VertexService::AddFace(vertices, indices, a, swTexture, d, nwTexture, c, neTexture);
        VertexService::AddFace(vertices, indices, a, swTexture, c, neTexture, b, seTexture);
    }

    static void SetV(std::vector<GLfloat>& vertices, std::vector<GLushort>& indices, glm::vec3 pillarA, glm::vec3 pillarB)
    {
        glm::vec3 midpoint = glm::vec3((pillarA.x + pillarB.x) / 2, (pillarA.y + pillarB.y) / 2, (pillarA.z + pillarB.z) / 2);
        SetBeam(vertices, indices, midpoint, pillarA + glm::vec3(0.0f, SectionHeight, 0.0f));
        SetBeam(vertices, indices, midpoint, pillarB + glm::vec3(0.0f, SectionHeight, 0.0f));
    }

    static void SetInvertedV(std::vector<GLfloat>& vertices, std::vector<GLushort>& indices, glm::vec3 pillarA, glm::vec3 pillarB)
    {
        glm::vec3 midpoint = 
            glm::vec3((pillarA.x + pillarB.x) / 2,
                (pillarA.y + pillarB.y) / 2,
                (pillarA.z + pillarB.z) / 2)
            + glm::vec3(0.0f, SectionHeight, 0.0f);
        SetBeam(vertices, indices, midpoint, pillarA);
        SetBeam(vertices, indices, midpoint, pillarB);
    }

    static void SetTop(std::vector<GLfloat>& vertices, std::vector<GLushort>& indices)
    {
        // top
        // 
        //   h______g
        //   /    / |
        // e/____/f |
        //  |  | |  |
        //  | d|_|__|c
        //  | /  | /\
        // a|/___|/b \
        //   \________X   

        glm::vec3 baseTransform = glm::vec3(20.0f, SectionHeight * SectionCount, 20.0f);
        glm::vec3 topTransform = glm::vec3(0.0f, SectionHeight, 0.0f);
        glm::vec3 pillar1Center = baseTransform + glm::vec3(0.0f, 0.0f, -LegOffset);
        glm::vec3 pillar2Center = baseTransform + glm::vec3(LegOffset, 0.0f, 0.0f);
        glm::vec3 pillar3Center = baseTransform + glm::vec3(0.0f, 0.0f, LegOffset);
        glm::vec3 pillar4Center = baseTransform + glm::vec3(-LegOffset, 0.0f, 0.0f);
        glm::vec3 nose1 = baseTransform + glm::vec3(-LegOffset - 6.0f, 0.0f, -1.5f);
        glm::vec3 nose2 = baseTransform + glm::vec3(-LegOffset - 6.0f, 0.0f, 1.5f);
        glm::vec3 nose1Top = nose1 + topTransform;
        glm::vec3 nose2Top = nose2 + topTransform;
        glm::vec3 pillar1CenterTop = pillar1Center + topTransform;
        glm::vec3 pillar3CenterTop = pillar3Center + topTransform;


        SetPillar(vertices, indices, pillar1Center);
        SetPillar(vertices, indices, pillar2Center);
        SetPillar(vertices, indices, pillar3Center);
        SetPillar(vertices, indices, pillar4Center);

        // crossbeams
        SetBeam(vertices, indices, pillar1Center, pillar2Center);
        SetBeam(vertices, indices, pillar2Center, pillar3Center);
        SetBeam(vertices, indices, pillar3Center, pillar4Center);
        SetBeam(vertices, indices, pillar4Center, pillar1Center);
        SetBeam(vertices, indices, pillar1Center, nose1);
        SetBeam(vertices, indices, pillar3Center, nose2);
        SetBeam(vertices, indices, nose1, nose2);
        SetBeam(vertices, indices, nose1Top, nose2Top);
        SetBeam(vertices, indices, nose1, nose1Top);
        SetBeam(vertices, indices, nose2, nose2Top);
        SetBeam(vertices, indices, pillar1CenterTop, nose1Top);
        SetBeam(vertices, indices, pillar3CenterTop, nose2Top);
        

        // v
        SetInvertedV(vertices, indices, pillar1Center, pillar2Center);
        SetInvertedV(vertices, indices, pillar2Center, pillar3Center);
        SetInvertedV(vertices, indices, pillar3Center, pillar4Center);
        SetInvertedV(vertices, indices, pillar4Center, pillar1Center);
    }

    static void SetBase(std::vector<GLfloat>& vertices, std::vector<GLushort>& indices)
    {

        glm::vec3 baseTransform = glm::vec3(20.0f, 0.0f, 20.0f);
        glm::vec3 toGroundTransform = glm::vec3(0.0f, -5.0f, 0.0f);
        
        // base
        // 
        //   h______g
        //   /    / |
        // e/____/f |
        //  |  | |  |
        //  | d|_|__|c
        //  | /  | /
        // a|/___|/b

        GLfloat width = 0.75f;
        glm::vec3 e = baseTransform + glm::vec3(0.0f, 0.0f, -LegOffset - 2.0f);
        glm::vec3 f = baseTransform + glm::vec3(LegOffset + 2.0f, 0.0f, 0.0f);
        glm::vec3 g = baseTransform + glm::vec3(0.0f, 0.0f, LegOffset + 2.0f);
        glm::vec3 h = baseTransform + glm::vec3(-LegOffset - 2.0f, 0.0f, 0.0f);
        glm::vec3 a = e + toGroundTransform;
        glm::vec3 b = f + toGroundTransform;
        glm::vec3 c = g + toGroundTransform;
        glm::vec3 d = h + toGroundTransform;

        glm::vec2 swTexture = glm::vec2(0.0f, 0.0f);
        glm::vec2 nwTexture = glm::vec2(0.0f, 1.0f);
        glm::vec2 seTexture = glm::vec2(1.0f, 0.0f);
        glm::vec2 neTexture = glm::vec2(1.0f, 1.0f);

        // Top face
        VertexService::AddFace(vertices, indices, e, swTexture, h, nwTexture, g, neTexture);
        VertexService::AddFace(vertices, indices, e, swTexture, g, neTexture, f, seTexture);

        // AB Face
        VertexService::AddFace(vertices, indices, a, swTexture, e, nwTexture, f, neTexture);
        VertexService::AddFace(vertices, indices, a, swTexture, f, neTexture, b, seTexture);

        // BC Face
        VertexService::AddFace(vertices, indices, b, swTexture, f, nwTexture, g, neTexture);
        VertexService::AddFace(vertices, indices, b, swTexture, g, neTexture, c, seTexture);

        // CD Face
        VertexService::AddFace(vertices, indices, c, swTexture, g, nwTexture, h, neTexture);
        VertexService::AddFace(vertices, indices, c, swTexture, h, neTexture, d, seTexture);

        // DA Face
        VertexService::AddFace(vertices, indices, d, swTexture, h, nwTexture, e, neTexture);
        VertexService::AddFace(vertices, indices, d, swTexture, e, neTexture, a, seTexture);
    }
};