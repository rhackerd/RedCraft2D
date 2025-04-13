#include "terrain.h"
#include <fmt/core.h>


Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::draw(int x, int y) {
    for (const auto& voxel : m_renderVoxels) {
        // Remove the additional offset here if you already handle it inside the voxel class
        voxel->display(x,y); // Or adjust this based on how your display method is supposed to handle positioning
    }
}



void Terrain::update(float centerX, float centerY, float renderRadius) {
    m_renderVoxels.clear(); // Clear previously visible voxels

    float radiusSquared = renderRadius * renderRadius;

    for (const auto& voxel : m_voxels) {
        float dx = voxel->getX() - centerX;
        float dy = voxel->getY() - centerY;
        if ((dx * dx + dy * dy) <= radiusSquared) {
            m_renderVoxels.push_back(voxel.get());
        }
    }
}
