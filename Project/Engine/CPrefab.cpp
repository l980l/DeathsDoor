#include "pch.h"
#include "CPrefab.h"

#include "CGameObject.h"
#include <Script/CScriptMgr.h>
#include "components.h"
#include "CScript.h"

CPrefab::CPrefab()
	: CRes(RES_TYPE::PREFAB)
	, m_ProtoObj(nullptr)
{
}

CPrefab::~CPrefab()
{
	if (nullptr != m_ProtoObj)
		delete m_ProtoObj;
}

CGameObject* CPrefab::Instantiate()
{
	return m_ProtoObj->Clone();	
}

int CPrefab::Save(const wstring& _strRelativePath)
{
	if (IsEngineRes())
		return E_FAIL;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	// Entity
	SaveWString(GetName(), pFile);

	// Res
	SaveWString(GetKey(), pFile);

	// obj
	SaveProtoObj(m_ProtoObj, pFile);

	fclose(pFile);

	return S_OK;
}

int CPrefab::Load(const wstring& _strFilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");

	// Entity
	wstring strName;
	LoadWString(strName, pFile);
	SetName(strName);

	// Res
	wstring strKey;
	LoadWString(strKey, pFile);
	// obj
	m_ProtoObj = LoadProtoObj(pFile);

	fclose(pFile);

	return S_OK;
}

void CPrefab::SaveProtoObj(CGameObject* _Obj, FILE* _File)
{// obj �̸�
	SaveWString(_Obj->GetName(), _File);

	// ������Ʈ
	for (UINT i = 0; i <= (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (i == (UINT)COMPONENT_TYPE::END)
		{
			// ������Ʈ ������ �����ٸ� (UINT)COMPONENT_TYPE::END�� ���
			fwrite(&i, sizeof(UINT), 1, _File);
			break;
		}

		CComponent* Com = _Obj->GetComponent((COMPONENT_TYPE)i);
		// ������Ʈ�� ���ٸ� �Ѿ��
		if (nullptr == Com)
			continue;

		// ������Ʈ Ÿ�� ����
		fwrite(&i, sizeof(UINT), 1, _File);

		// ������Ʈ �������� ���� ȣ��
		Com->SaveToLevelFile(_File);
	}

	// ��ũ��Ʈ
	const vector<CScript*>& vecScript = _Obj->GetScripts();
	size_t ScriptCount = vecScript.size();
	fwrite(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		wstring ScriptName = CScriptMgr::GetScriptName(vecScript[i]);
		SaveWString(ScriptName, _File);
		vecScript[i]->SaveToLevelFile(_File);
	}

	// �ڽ� obj
	const vector<CGameObject*>& vecChild = _Obj->GetChild();
	size_t ChildCount = vecChild.size();
	fwrite(&ChildCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ChildCount; ++i)
	{
		SaveProtoObj(vecChild[i], _File);
	}
}

CGameObject* CPrefab::LoadProtoObj(FILE* _File)
{
	CGameObject* pObject = new CGameObject;

	// �̸�
	wstring Name;
	LoadWString(Name, _File);
	pObject->SetName(Name);

	// ������Ʈ
	while (true)
	{
		UINT ComponentType = 0;
		fread(&ComponentType, sizeof(UINT), 1, _File);

		if ((UINT)COMPONENT_TYPE::END == ComponentType)
			break;

		CComponent* Component = nullptr;

		switch ((COMPONENT_TYPE)ComponentType)
		{
		case COMPONENT_TYPE::TRANSFORM:
			Component = new CTransform();
			break;
		case COMPONENT_TYPE::COLLIDER2D:
			Component = new CCollider2D();
			break;
		case COMPONENT_TYPE::COLLIDER3D:
			//Component = new Collider3D();
			break;
		case COMPONENT_TYPE::ANIMATOR2D:
			Component = new CAnimator2D();
			break;
		case COMPONENT_TYPE::ANIMATOR3D:
			//Component = new CAnimator3D();
			break;
		case COMPONENT_TYPE::LIGHT2D:
			Component = new CLight2D();
			break;
		case COMPONENT_TYPE::LIGHT3D:
			Component = new CLight3D();
			break;
		case COMPONENT_TYPE::CAMERA:
			Component = new CCamera();
			break;
		case COMPONENT_TYPE::MESHRENDER:
			Component = new CMeshRender();
			break;
		case COMPONENT_TYPE::PARTICLESYSTEM:
			Component = new CParticleSystem;
			break;
		case COMPONENT_TYPE::TILEMAP:
			Component = new CTileMap();
			break;
		case COMPONENT_TYPE::LANDSCAPE:
			Component = new CLandScape();
			break;
		case COMPONENT_TYPE::DECAL:
			Component = new CDecal();
			break;
		}
		Component->LoadFromLevelFile(_File);
		pObject->AddComponent(Component);
	}

	// ��ũ��Ʈ
	size_t ScriptCount = 0;
	fread(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		wstring ScriptName;
		LoadWString(ScriptName, _File);
		CScript* pScript = CScriptMgr::GetScript(ScriptName);
		pObject->AddComponent(pScript);
		pScript->LoadFromLevelFile(_File);
	}

	// �ڽ� obj
	size_t ChildCount = 0;
	fread(&ChildCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ChildCount; ++i)
	{
		CGameObject* ChildObject = LoadProtoObj(_File);
		pObject->AddChild(ChildObject);
	}


	return pObject;
}

void CPrefab::RegisterProtoObject(CGameObject* _Proto)
{
	// ���� ������Ʈ�� ���� �Ҽ��� �ƴϿ��� �Ѵ�.
	assert(-1 == _Proto->GetLayerIndex());

	m_ProtoObj = _Proto;
}