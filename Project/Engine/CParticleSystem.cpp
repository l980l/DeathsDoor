#include "pch.h"
#include "CParticleSystem.h"

#include "CDevice.h"
#include "CStructuredBuffer.h"

#include "CResMgr.h"
#include "CTransform.h"
#include "CTimeMgr.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_RWBuffer(nullptr)
	, m_ModuleData{}
	, m_AccTime(0.f)
	, m_iEmissive(0)
{

	//================
	// �ǹ̾��� �ʱ⼼��
	//================
	m_ModuleData.iMaxParticleCount = 1000;

	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = true;
	m_ModuleData.SpawnRate = 20;
	m_ModuleData.vSpawnColor = Vec3(0.4f, 0.4f, 0.4f);
	m_ModuleData.vSpawnScaleMin = Vec3(15.f, 15.f, 15.f);
	m_ModuleData.vSpawnScaleMax = Vec3(20.f, 20.f, 20.f);

	m_ModuleData.SpawnShapeType = 0;
	m_ModuleData.vBoxShapeScale = Vec3(200.f, 200.f, 200.f);	
	//m_ModuleData.Space = 0; // �ùķ��̼� ��ǥ��

	m_ModuleData.MinLifeTime = 3.f;
	m_ModuleData.MaxLifeTime = 5.f;

	//========================================================

	//SetName(L"ParticleSystem");
	// ���� �޽�
	SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"PointMesh"));

	// ��ƼŬ ���� ����
	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ParticleRenderMtrl"), 0);

	// ��ƼŬ ������Ʈ ��ǻƮ ���̴�	
	m_UpdateCS = (CParticleUpdateShader*)CResMgr::GetInst()->FindRes<CComputeShader>(L"ParticleUpdateCS").Get();

	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_ModuleData.iMaxParticleCount, SB_TYPE::READ_WRITE, false);

	m_RWBuffer = new CStructuredBuffer;
	m_RWBuffer->Create(sizeof(tRWParticleBuffer), 1, SB_TYPE::READ_WRITE, true);

	m_ModuleDataBuffer = new CStructuredBuffer;
	m_ModuleDataBuffer->Create(sizeof(tParticleModule), 1, SB_TYPE::READ_ONLY, true);
}

CParticleSystem::CParticleSystem(const CParticleSystem& _Other)
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ModuleData(_Other.m_ModuleData)
	, m_Tex(_Other.m_Tex)
{
	// ���� �޽�
	SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"PointMesh"));

	// ��ƼŬ ���� ����
	SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ParticleRenderMtrl"), 0);

	// ��ƼŬ ������Ʈ ��ǻƮ ���̴�	
	m_UpdateCS = (CParticleUpdateShader*)CResMgr::GetInst()->FindRes<CComputeShader>(L"ParticleUpdateCS").Get();

	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_ModuleData.iMaxParticleCount, SB_TYPE::READ_WRITE, false);

	m_RWBuffer = new CStructuredBuffer;
	m_RWBuffer->Create(sizeof(tRWParticleBuffer), 1, SB_TYPE::READ_WRITE, true);

	m_ModuleDataBuffer = new CStructuredBuffer;
	m_ModuleDataBuffer->Create(sizeof(tParticleModule), 1, SB_TYPE::READ_ONLY, true);
}

CParticleSystem::~CParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
	{
		m_ParticleBuffer = {};
		delete m_ParticleBuffer;
		m_ParticleBuffer = nullptr;
	}

	if (nullptr != m_RWBuffer)
	{
		m_RWBuffer = {};
		delete m_RWBuffer;
		m_RWBuffer = nullptr;
	}

	if (nullptr != m_ModuleDataBuffer)
	{
		m_ModuleDataBuffer = {};
		delete m_ModuleDataBuffer;
		m_ModuleDataBuffer = nullptr;
	}
}


void CParticleSystem::finaltick()
{
	// ���� ����Ʈ ���
	// 1�� ���� �ð�
	float fTimePerCount = 1.f / (float)m_ModuleData.SpawnRate;
	m_AccTime += DT;

	// �����ð��� ���� �����ð��� �Ѿ��
	if (fTimePerCount < m_AccTime)
	{
		// �ʰ� ���� ==> ���� ����
		float fData = m_AccTime / fTimePerCount;

		// �������� ���� �ð�
		m_AccTime = fTimePerCount * (fData - floor(fData));

		// RW������ �������� ���������� ���ٸ� ���� ����� �÷���.
		if (m_RWBuffer->GetElementCount() < (UINT)fData)
			m_RWBuffer->Create(sizeof(tRWParticleBuffer), (UINT)fData, SB_TYPE::READ_WRITE, true);
		// ���ۿ� ����ī��Ʈ ����
		tRWParticleBuffer rwbuffer = { (int)fData };
		m_RWBuffer->SetData(&rwbuffer);
	}


	// ��ƼŬ ������Ʈ ��ǻƮ ���̴�
	m_ModuleDataBuffer->SetData(&m_ModuleData);

	m_UpdateCS->SetParticleBuffer(m_ParticleBuffer);
	m_UpdateCS->SetRWParticleBuffer(m_RWBuffer);
	m_UpdateCS->SetModuleData(m_ModuleDataBuffer);
	m_UpdateCS->SetNoiseTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\noise\\noise_01.png"));
	m_UpdateCS->SetParticleObjectPos(Transform()->GetWorldPos());

	m_UpdateCS->Execute();
}

void CParticleSystem::render()
{
	Transform()->UpdateData();

	// ��ƼŬ���� t20 �� ���ε�
	m_ParticleBuffer->UpdateData(20, PIPELINE_STAGE::PS_ALL);

	// ��� ������ t21 �� ���ε�
	m_ModuleDataBuffer->UpdateData(21, PIPELINE_STAGE::PS_GEOMETRY);

	// Particle Render	
	GetMaterial(0)->SetTexParam(TEX_0, m_Tex);
	// Emissive ����
	GetMaterial(0)->SetScalarParam(INT_0, &m_iEmissive);

	GetMaterial(0)->UpdateData();
	GetMesh()->render_particle(m_ModuleData.iMaxParticleCount);

	// ��ƼŬ ���� ���ε� ����
	m_ParticleBuffer->Clear();
	m_ModuleDataBuffer->Clear();
}

void CParticleSystem::render(UINT _iSubset)
{
	render();
}

void CParticleSystem::SpawnModule(int _MaxParticle, int _SpawnRate, Vec3 _SpawnColor, Vec3 SpawnMinScale
	, Vec3 SpawnMaxScale, Vec3 _SpawnBoxScale, float _MinLifeTime, float _MaxLifeTime)
{
	for (UINT i = 0; i < (UINT)PARTICLE_MODULE::END; ++i)
	{
		m_ModuleData.ModuleCheck[i] = false;
	}
	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = true;
	m_ModuleData.iMaxParticleCount = _MaxParticle;
	m_ModuleData.SpawnRate = _SpawnRate;
	m_ModuleData.vSpawnColor = _SpawnColor / 255;
	m_ModuleData.vSpawnScaleMin = SpawnMinScale;
	m_ModuleData.vSpawnScaleMax = SpawnMaxScale;
	m_ModuleData.SpawnShapeType = 0;
	m_ModuleData.vBoxShapeScale = _SpawnBoxScale;
	m_ModuleData.Space = 0; // �ùķ��̼� ��ǥ��
	m_ModuleData.MinLifeTime = _MinLifeTime;
	m_ModuleData.MaxLifeTime = _MaxLifeTime;

}

void CParticleSystem::ColorChangeModule(Vec3 _vStartColor, Vec3 _vEndColor)
{
	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::COLOR_CHANGE] = true;
	m_ModuleData.vStartColor = _vStartColor / 255.f;
	m_ModuleData.vEndColor = _vEndColor / 255;
}

void CParticleSystem::ScaleChangeModule(float _vStartScale, float _vEndScale)
{
	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::SCALE_CHANGE] = true;
	m_ModuleData.StartScale = _vStartScale;
	m_ModuleData.EndScale = _vEndScale;
}

void CParticleSystem::AddVelocityModule(float _fSpeed, int _iVelocityType, Vec3 _vVelocityDir, float _fAngle)
{
	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = true;
	m_ModuleData.AddVelocityType = _iVelocityType;
	m_ModuleData.Speed = _fSpeed;
	m_ModuleData.vVelocityDir = _vVelocityDir;
	m_ModuleData.OffsetAngle = _fAngle;
}

void CParticleSystem::DragModule(float _fStartDrag, float _fEndDrag)
{
	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::DRAG] = true;
	m_ModuleData.StartDrag = _fStartDrag;
	m_ModuleData.EndDrag = -_fEndDrag;
}

void CParticleSystem::RandomForceModule(float _fForceTerm, float _fForce)
{
	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = true;
	m_ModuleData.fNoiseTerm = _fForceTerm;
	m_ModuleData.fNoiseForce = _fForce;
}

void CParticleSystem::VelocityAlignmentModule()
{
	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::RENDER] = true;
	m_ModuleData.VelocityAlignment = true;
}

void CParticleSystem::VelocityScaleModule(float _fMaxSpeed, Vec3 _vMaxVelocityScale)
{
	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::RENDER] = true;
	m_ModuleData.VelocityScale = true;
	m_ModuleData.vMaxVelocityScale = _vMaxVelocityScale;
	m_ModuleData.vMaxSpeed = _fMaxSpeed;
}

void CParticleSystem::AnimationModule(int _iFrmCount, int _iXCount, Vec2 _vLeftTop, Vec2 _vSlice, Vec2 _vOffset)
{
	Vec2 Resolution = Vec2(m_Tex->Width(), m_Tex->Height());

	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::ANIMATION] = true;
	m_ModuleData.iFrmCount = _iFrmCount;
	m_ModuleData.iXCount = _iXCount;
	m_ModuleData.vLeftTop = _vLeftTop / Resolution;
	m_ModuleData.vSlice = _vSlice / Resolution;
	m_ModuleData.vOffset = _vOffset / Resolution;
}

void CParticleSystem::OnOff(bool _Onff)
{
	m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = _Onff;
	m_AccTime = 0.f;
}

void CParticleSystem::SaveToLevelFile(FILE* _File)
{
	CRenderComponent::SaveToLevelFile(_File);

	fwrite(&m_iEmissive, sizeof(int), 1, _File);
	fwrite(&m_ModuleData, sizeof(tParticleModule), 1, _File);
	SaveResRef(m_UpdateCS.Get(), _File);
	SaveResRef(m_Tex.Get(), _File);
}

void CParticleSystem::LoadFromLevelFile(FILE* _File)
{
	CRenderComponent::LoadFromLevelFile(_File);

	fread(&m_iEmissive, sizeof(int), 1, _File);
	fread(&m_ModuleData, sizeof(tParticleModule), 1, _File);

	int i = 0;
	fread(&i, sizeof(i), 1, _File);

	if (i)
	{
		wstring strKey, strRelativePath;
		LoadWString(strKey, _File);
		LoadWString(strRelativePath, _File);

		m_UpdateCS = (CParticleUpdateShader*)CResMgr::GetInst()->FindRes<CComputeShader>(strKey).Get();

	}
	LoadResRef(m_Tex, _File);
	//m_Tex = CResMgr::GetInst()->FindRes<CTexture>(m_Tex);
}
