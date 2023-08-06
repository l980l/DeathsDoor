#pragma once
#include "CState.h"

enum class SLASH
{
    LEFT,
    RIGHT,
    END,
};

class CPlyAttack :
    public CState
{
private:
    CGameObject*    m_pSlash[(UINT)SLASH::END];    // ���� �� ��µǴ� SlashMesh 
    UINT            m_iAttackCount;         // ���� ����Ƚ��(�� 3ȸ����)
    Vec3            m_vSlashPos;
    float           m_fRange;
    float           m_fAcctime;
    float           m_fDelay;
    float           m_fAfterAttack;         // ���ݸ���� ���� �� �ð�
    float           m_fTimeToIdle; // ���ݸ���� ���� �� Idle�� �ǵ��ư��� �ð�
    float           m_fAttackDir;
    Vec3            m_vMouseDir;

    // 
    float           m_fSlashStartTime;      // �̹� Slash ����Ʈ ���� �ð�.
    
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    UINT GetAttackCount() { return m_iAttackCount; }
    void CalcDir();
    void Slash();

    CLONE(CPlyAttack);

public:
    CPlyAttack();
    ~CPlyAttack();
};

