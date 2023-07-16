#pragma once
#include "CSingleton.h"


class dtNavMesh;

class CDetourMgr :
    public CSingleton<CDetourMgr>
{
    SINGLE(CDetourMgr);
private:
    CGameObject*    m_pPlayer;
    dtNavMesh*      NaviMesh;

public:
    void LoadNavMeshFromBinFile(const char* path);
    
    Vec3* GetPathtoTarget(Vec3 _vStartPos, int* ActualPathCount);

    CLONE(CDetourMgr);
};
