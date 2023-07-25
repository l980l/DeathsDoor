#pragma once
#include "CSingleton.h"

class dtNavMesh;

class CDetourMgr :
    public CSingleton<CDetourMgr>
{
    SINGLE(CDetourMgr);
private:
    CGameObject*    m_pPlayer;
    dtNavMesh*      m_pNaviMesh;

    const int NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET';
    const int NAVMESHSET_VERSION = 1;

public:
    void init();
    void ChangeLevel(LEVEL_TYPE _LevelType);
    void LoadNavMeshFromBinFile(const char* path);
    
    Vec3* GetPathtoTarget(Vec3 _vStartPos, int* ActualPathCount);
    Vec3* GetPathtoTarget(Vec3 _vStartPos, Vec3 _vTargetPos, int* ActualPathCount);
    float GetDirtoTarget(Vec3 vStartPos);

    CLONE(CDetourMgr);
};
