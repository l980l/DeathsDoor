#include "pch.h"
#include "CLevelSaveLoad.h"

#include <Engine\CPathMgr.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>
#include <Engine\CScript.h>
#include <Engine/CPrefab.h>
#include <Engine/CPhysXMgr.h>
#include "commdlg.h"

#include <Script\CScriptMgr.h>

int CLevelSaveLoad::Play(const wstring& _LevelPath, CLevel* _Level)
{
    if (_Level->GetState() != LEVEL_STATE::STOP)
        return E_FAIL;

    wstring strPath = CPathMgr::GetInst()->GetContentPath();
    strPath += _LevelPath;

    FILE* pFile = nullptr;

    _wfopen_s(&pFile, strPath.c_str(), L"wb");

    if (nullptr == pFile)
        return E_FAIL;

    // 레벨 이름 저장
    SaveWString(_Level->GetName(), pFile);

    int level_type = _Level->GetLevelType();
    fwrite(&level_type, sizeof(int), 1, pFile);

    // 레벨의 레이어들을 저장
    for (UINT i = 0; i < MAX_LAYER; ++i)
    {
        CLayer* pLayer = _Level->GetLayer(i);

        // 레이어 이름 저장
        SaveWString(pLayer->GetName(), pFile);

        // 레이어의 게임오브젝트들 저장
        const vector<CGameObject*>& vecParent = pLayer->GetParentObject();

        // 오브젝트 개수 저장
        size_t objCount = vecParent.size();
        fwrite(&objCount, sizeof(size_t), 1, pFile);

        // 각 게임오브젝트
        for (size_t i = 0; i < objCount; ++i)
        {
            SaveGameObject(vecParent[i], pFile);
        }
    }

    fclose(pFile);


    return S_OK;
}

CLevel* CLevelSaveLoad::Stop(const wstring& _LevelPath, LEVEL_STATE _state)
{
    CPhysXMgr::GetInst()->Clear();
    wstring strPath = CPathMgr::GetInst()->GetContentPath();
    strPath += _LevelPath;//상대경로

    FILE* pFile = nullptr;

    _wfopen_s(&pFile, strPath.c_str(), L"rb");

    if (nullptr == pFile)
        return nullptr;

    CLevel* NewLevel = new CLevel;

    // 레벨 이름
    wstring strLevelName;
    LoadWString(strLevelName, pFile);
    NewLevel->SetName(strLevelName);
    
    int level_type = 0;
    fread(&level_type, sizeof(int), 1, pFile);
    NewLevel->SetLevelType(level_type);

    for (UINT i = 0; i < MAX_LAYER; ++i)
    {
        CLayer* pLayer = NewLevel->GetLayer(i);

        // 레이어 이름
        wstring LayerName;
        LoadWString(LayerName, pFile);
        pLayer->SetName(LayerName);

        // 게임 오브젝트 개수
        size_t objCount = 0;
        fread(&objCount, sizeof(size_t), 1, pFile);

        // 각 게임오브젝트
        for (size_t j = 0; j < objCount; ++j)
        {
            CGameObject* pNewObj = LoadGameObject(pFile);
            NewLevel->AddGameObject(pNewObj, i, false);
        }
    }

    fclose(pFile);

    NewLevel->ChangeState(_state);

    return NewLevel;
}

int CLevelSaveLoad::SaveLevel(CLevel* _Level)
{
    if (_Level->GetState() != LEVEL_STATE::STOP) //stop상태일 때만 저장
        return E_FAIL;

    OPENFILENAME ofn = {};
    wstring strFolderpath = CPathMgr::GetInst()->GetContentPath();
    strFolderpath += L"Level\\";

    wchar_t szFilePath[256] = {};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFilePath;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 256;
    ofn.lpstrFilter = L"Level\0*.lv\0ALL\0*.*";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = strFolderpath.c_str();
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (false == GetSaveFileName(&ofn))
        E_FAIL;

    // 파일 입출력
    FILE* pFile = nullptr;
    errno_t iErrNum = _wfopen_s(&pFile, szFilePath, L"wb");

    if (nullptr == pFile)
        return E_FAIL;

    // 레벨 이름 저장
    SaveWString(_Level->GetName(), pFile);

    int level_type = _Level->GetLevelType();
    fwrite(&level_type, sizeof(int), 1, pFile);

    // 레벨의 레이어들을 저장
    for (UINT i = 0; i < MAX_LAYER; ++i)
    {
        CLayer* pLayer = _Level->GetLayer(i);

        // 레이어 이름 저장
        SaveWString(pLayer->GetName(), pFile);

        // 레이어의 부모게임오브젝트들 저장
        const vector<CGameObject*>& vecParent = pLayer->GetParentObject();

        size_t objCount = vecParent.size();
        fwrite(&objCount, sizeof(size_t), 1, pFile); // 오브젝트 개수 저장

        for (size_t i = 0; i < objCount; ++i)
        {
            SaveGameObject(vecParent[i], pFile); // 각 게임오브젝트 저장
        }
    }

    fclose(pFile);


    return S_OK;
}

int CLevelSaveLoad::SaveGameObject(CGameObject* _Object, FILE* _File)
{
    // 이름
    SaveWString(_Object->GetName(), _File);

    // 컴포넌트
    for (UINT i = 0; i <= (UINT)COMPONENT_TYPE::END; ++i)
    {
        if (i == (UINT)COMPONENT_TYPE::END)
        {
            // 컴포넌트 타입 저장
            fwrite(&i, sizeof(UINT), 1, _File);
            break;
        }

        CComponent* Com = _Object->GetComponent((COMPONENT_TYPE)i);
        if (nullptr == Com)
            continue;

        // 컴포넌트 타입 저장
        fwrite(&i, sizeof(UINT), 1, _File);

        // 컴포넌트 정보 저장
        Com->SaveToLevelFile(_File);
    }

    // 스크립트   
    const vector<CScript*>& vecScript = _Object->GetScripts();
    size_t ScriptCount = vecScript.size();
    fwrite(&ScriptCount, sizeof(size_t), 1, _File);

    for (size_t i = 0; i < vecScript.size(); ++i)
    {
        wstring ScriptName = CScriptMgr::GetScriptName(vecScript[i]);
        SaveWString(ScriptName, _File);
        vecScript[i]->SaveToLevelFile(_File);
    }


    // 자식 오브젝트
    const vector<CGameObject*>& vecChild = _Object->GetChild();
    size_t ChildCount = vecChild.size();
    fwrite(&ChildCount, sizeof(size_t), 1, _File);

    for (size_t i = 0; i < ChildCount; ++i)
    {
        SaveGameObject(vecChild[i], _File);
    }

    return 0;
}

CLevel* CLevelSaveLoad::LoadLevel(LEVEL_STATE _state)
{
    OPENFILENAME ofn = {};
    wstring strFolderpath = CPathMgr::GetInst()->GetContentPath();
    strFolderpath += L"Level\\";

    wchar_t szFilePath[256] = {};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFilePath;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 256;
    ofn.lpstrFilter = L"Level\0*.lv\0ALL\0*.*";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = strFolderpath.c_str();
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (false == GetSaveFileName(&ofn))
        E_FAIL;

    // 파일 입출력
    FILE* pFile = nullptr;
    errno_t iErrNum = _wfopen_s(&pFile, szFilePath, L"rb");

    if (nullptr == pFile)
        return nullptr;

    CLevel* NewLevel = new CLevel;

    // 레벨 이름
    wstring strLevelName;
    LoadWString(strLevelName, pFile);
    NewLevel->SetName(strLevelName);

    int level_type = 0;
    fread(&level_type, sizeof(int), 1, pFile);
    NewLevel->SetLevelType(level_type);

    for (UINT i = 0; i < MAX_LAYER; ++i)
    {
        CLayer* pLayer = NewLevel->GetLayer(i);

        // 레이어 이름
        wstring LayerName;
        LoadWString(LayerName, pFile);
        pLayer->SetName(LayerName);

        // 게임 오브젝트 개수
        size_t objCount = 0;
        fread(&objCount, sizeof(size_t), 1, pFile);

        // 각 게임오브젝트
        for (size_t j = 0; j < objCount; ++j)
        {
            CGameObject* pNewObj = LoadGameObject(pFile);
            NewLevel->AddGameObject(pNewObj, i, false);
        }
    }

    fclose(pFile);

    NewLevel->ChangeState(_state);

    return NewLevel;
}

CGameObject* CLevelSaveLoad::LoadGameObject(FILE* _File)
{
    CGameObject* pObject = new CGameObject;

    // 이름
    wstring Name;
    LoadWString(Name, _File);
    pObject->SetName(Name);

    // 컴포넌트
    while (true)
    {
        UINT ComponentType = 0;
        fread(&ComponentType, sizeof(UINT), 1, _File);

        // 컴포넌트 정보의 끝을 확인
        if ((UINT)COMPONENT_TYPE::END == ComponentType)
            break;

        CComponent* Component = nullptr;

        switch ((COMPONENT_TYPE)ComponentType)
        {
        case COMPONENT_TYPE::TRANSFORM:
            Component = new CTransform;
            break;
        case COMPONENT_TYPE::COLLIDER2D:
            Component = new CCollider2D;
            break;
        case COMPONENT_TYPE::COLLIDER3D:
            Component = new CCollider3D;
            break;
        case COMPONENT_TYPE::ANIMATOR2D:
            Component = new CAnimator2D;
            break;
        case COMPONENT_TYPE::ANIMATOR3D:
            Component = new CAnimator3D;
            break;
        case COMPONENT_TYPE::LIGHT2D:
            Component = new CLight2D;
            break;
        case COMPONENT_TYPE::LIGHT3D:
            Component = new CLight3D;
            break;
        case COMPONENT_TYPE::CAMERA:
            Component = new CCamera;
            break;
        case COMPONENT_TYPE::MESHRENDER:
            Component = new CMeshRender;
            break;
        case COMPONENT_TYPE::PARTICLESYSTEM:
            Component = new CParticleSystem;
            break;
        case COMPONENT_TYPE::TILEMAP:
            Component = new CTileMap;
            break;
        case COMPONENT_TYPE::SKYBOX:
            Component = new CSkyBox;
            break;
        case COMPONENT_TYPE::LANDSCAPE:
            Component = new CLandScape;
            break;
        case COMPONENT_TYPE::DECAL:
            Component = new CDecal;
            break;
        case COMPONENT_TYPE::RIGIDBODY:
            Component = new CRigidbody;
            break;
        }

        Component->LoadFromLevelFile(_File);
        pObject->AddComponent(Component);
        if (COMPONENT_TYPE::RIGIDBODY == Component->GetType())
        {
            CRigidbody* RigidbodyComponent = (CRigidbody*)Component;
            PxGeometryType::Enum Type = RigidbodyComponent->GetShapeType();
            Vec3 vSpawnPos = RigidbodyComponent->SetSpawnPos();
            Vec3 vRigidScale = RigidbodyComponent->GetRigidScale(); 
            switch (Type)
            {
            case PxGeometryType::Enum::eBOX:
                CPhysXMgr::GetInst()->CreateCube(vSpawnPos, vRigidScale, pObject);
                break;
            case PxGeometryType::Enum::eCAPSULE:
                CPhysXMgr::GetInst()->CreateCapsule(vSpawnPos, vRigidScale.x, vRigidScale.y, pObject);
                break;
            case PxGeometryType::Enum::eSPHERE:
                CPhysXMgr::GetInst()->CreateSphere(vSpawnPos, vRigidScale.x, pObject);
                break;
            }
        }        
    }

    // 스크립트   
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

    // 자식 오브젝트      
    size_t ChildCount = 0;
    fread(&ChildCount, sizeof(size_t), 1, _File);

    for (size_t i = 0; i < ChildCount; ++i)
    {
        CGameObject* ChildObject = LoadGameObject(_File);
        pObject->AddChild(ChildObject);
    }

    return pObject;
}

int CLevelSaveLoad::SavePrefab(const wstring& _strRelativePath, CPrefab* _Prefab)
{
    if (_Prefab->IsEngineRes())
        return E_FAIL;

    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    FILE* pFile = nullptr;
    _wfopen_s(&pFile, strFilePath.c_str(), L"wb");

    SaveGameObject(_Prefab->GetProtoObj(), pFile);

    fclose(pFile);

    return S_OK;
}

CGameObject* CLevelSaveLoad::LoadPrefab(const wstring& _strRelativePath)
{
    Ptr<CPrefab> pPrefab = new CPrefab;

    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    FILE* pFile = nullptr;
    _wfopen_s(&pFile, strFilePath.c_str(), L"rb");

    CGameObject* pNewObj = CLevelSaveLoad::LoadGameObject(pFile);
    fclose(pFile);

    return pNewObj;
}

void CLevelSaveLoad::SpawnPrefab(wstring _relativepath, int ind, Vec3 _vWorldPos, float time)
{
    wstring strFolderpath = CPathMgr::GetInst()->GetContentPath();
    wstring relativepath = _relativepath;
    strFolderpath += relativepath;

    FILE* pFile = nullptr;
    errno_t iErrNum = _wfopen_s(&pFile, strFolderpath.c_str(), L"rb");

    CGameObject* newObject = LoadGameObject(pFile);
    Vec3 prefpos = _vWorldPos;

    SpawnGameObject(newObject, _vWorldPos, ind);
    if (time >= 0.f)
        newObject->SetLifeSpan(time);
    fclose(pFile);
}
CGameObject* CLevelSaveLoad::SpawnandReturnPrefab(wstring _relativepath, int idx, Vec3 _vWorldPos, float time)
{
    wstring strFolderpath = CPathMgr::GetInst()->GetContentPath();
    wstring relativepath = _relativepath;
    strFolderpath += relativepath;

    FILE* pFile = nullptr;
    errno_t iErrNum = _wfopen_s(&pFile, strFolderpath.c_str(), L"rb");

    CGameObject* newObject = LoadGameObject(pFile);
    Vec3 prefpos = _vWorldPos;

    SpawnGameObject(newObject, _vWorldPos, idx);
    if (time >= 0.f)
        newObject->SetLifeSpan(time);
    fclose(pFile);
    return newObject;
}