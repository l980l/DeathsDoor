#pragma once
#include "CState.h"
class CBatAttack    :
    public CState
    {
    private:
        float m_fTime;
    public:
        virtual void tick() override;
        virtual void Enter() override;
        virtual void Exit() override;

        CLONE(CBatAttack);

    public:
        CBatAttack();
        ~CBatAttack();
};

