#pragma once
#include <Engine\CScript.h>

class CStateScript;
class dtNavMesh;

class CPlayerScript :
    public CScript
{
private:
    CStateScript*   m_pState;
    float           m_fSpeed;
    float       MoveTime;
    int     actualPathCount;
    float   actualPath[256 * 3];
    float startpos[3];
    float endpos[3];

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;

private:
    void Shoot();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    dtNavMesh* loadNavMeshFromBinFile(const char* path);

    CLONE(CPlayerScript);
public:
    CPlayerScript();
    ~CPlayerScript();
};

