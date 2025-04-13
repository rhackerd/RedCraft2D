#ifndef TERRAIN_H
#define TERRAIN_H

#include "../../blocks/blocks.h"
#include "../../definitions.h"
#include <vector>
#include <memory>


// Controls the terrain voxels. 
// ✅ rendering
// ❌ updating
class Terrain
{
private:
    std::vector<std::unique_ptr<Voxel>> m_voxels;
    std::vector<Voxel*> m_renderVoxels;

    
    
public:
    Terrain();
    ~Terrain();

    // getters
    std::vector<Voxel*> getRenderVoxels() { return m_renderVoxels; } // not recommended
    Voxel* getVoxel(int id) { return m_voxels.at(id).get(); } // not recommended

    // setters
    void addVoxel(std::unique_ptr<Voxel> voxel) {
        m_voxels.push_back(std::move(voxel));
    } // recommended
    //FIXME: void addVoxelEx(std::unique_ptr<Voxel> voxel, int id) { m_voxels.push_back({std::move(voxel), id}); } // harder avoid
    
    //FIXME: void removeVoxel(int id) { m_voxels.erase(std::remove_if(m_voxels.begin(), m_voxels.end(), [id](const VoxelEntry& entry) { return entry.id == id; }), m_voxels.end()); }

    void draw(int x, int y); // draw m_renderVoxels
    void update(float centerX, float centerY, float renderRadius); // assings from m_voxels to m_renderVoxels
};




#endif // TERRAIN_H