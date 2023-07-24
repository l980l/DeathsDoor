#include "pch.h"
#include "CLevelSaveLoadInScript.h"

#include <Engine\CPathMgr.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>
#include <Engine\CScript.h>
#include <Engine/CEventMgr.h>
#include "commdlg.h"

#include "CScriptMgr.h"


int CLevelSaveLoadInScript::Play(const wstring& _LevelPath, CLevel* _Level)
{
    if (_Level->GetState() != LEVEL_STATE::STOP)
        return E_FAIL;

    wstring strPath = CPathMgr::GetInst()->GetContentPath();
    strPath += _LevelPath;

    FILE* pFile = nullptr;

    _wfopen_s(&pFile, strPath.c_str(), L"wb");

    if (nullptr == pFile)
        return E_FAIL;

    // ���� �̸� ����
    SaveWString(_Level->GetName(), pFile);


    // ������ ���̾���� ����
    for (UINT i = 0; i < MAX_LAYER; ++i)
    {
        CLayer* pLayer = _Level->GetLayer(i);

        // ���̾� �̸� ����
        SaveWString(pLayer->GetName(), pFile);

        // ���̾��� ���ӿ�����Ʈ�� ����
        const vector<CGameObject*>& vecParent = pLayer->GetParentObject();

        // ������Ʈ ���� ����
        size_t objCount = vecParent.size();
        fwrite(&objCount, sizeof(size_t), 1, pFile);

        // �� ���ӿ�����Ʈ
        for (size_t i = 0; i < objCount; ++i)
        {
            SaveGameObject(vecParent[i], pFile);
        }
    }

    fclose(pFile);


    return S_OK;
}

CLevel* CLevelSaveLoadInScript::Stop(const wstring& _LevelPath, LEVEL_STATE _state)
{
    wstring strPath = CPathMgr::GetInst()->GetContentPath();
    strPath += _LevelPath;//�����

    FILE* pFile = nullptr;

    _wfopen_s(&pFile, strPath.c_str(), L"rb");

    if (nullptr == pFile)
        return nullptr;

    CLevel* NewLevel = new CLevel;

    // ���� �̸�
    wstring strLevelName;
    LoadWString(strLevelName, pFile);
    NewLevel->SetName(strLevelName);


    for (UINT i = 0; i < MAX_LAYER; ++i)
    {
        CLayer* pLayer = NewLevel->GetLayer(i);

        // ���̾� �̸�
        wstring LayerName;
        LoadWString(LayerName, pFile);
        pLayer->SetName(LayerName);

        // ���� ������Ʈ ����
        size_t objCount = 0;
        fread(&objCount, sizeof(size_t), 1, pFile);

        // �� ���ӿ�����Ʈ
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

int CLevelSaveLoadInScript::SaveLevel(CLevel* _Level)
{
    if (_Level->GetState() != LEVEL_STATE::STOP) //stop������ ���� ����
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

    // ���� �����
    FILE* pFile = nullptr;
    errno_t iErrNum = _wfopen_s(&pFile, szFilePath, L"wb");

    if (nullptr == pFile)
        return E_FAIL;

    // ���� �̸� ����
    SaveWString(_Level->GetName(), pFile);


    // ������ ���̾���� ����
    for (UINT i = 0; i < MAX_LAYER; ++i)
    {
        CLayer* pLayer = _Level->GetLayer(i);

        // ���̾� �̸� ����
        SaveWString(pLayer->GetName(), pFile);

        // ���̾��� �θ���ӿ�����Ʈ�� ����
        const vector<CGameObject*>& vecParent = pLayer->GetParentObject();

        size_t objCount = vecParent.size();
        fwrite(&objCount, sizeof(size_t), 1, pFile); // ������Ʈ ���� ����

        for (size_t i = 0; i < objCount; ++i)
        {
            SaveGameObject(vecParent[i], pFile); // �� ���ӿ�����Ʈ ����
        }
    }

    fclose(pFile);


    return S_OK;
}

int CLevelSaveLoadInScript::SaveGameObject(CGameObject* _Object, FILE* _File)
{
    // �̸�
    SaveWString(_Object->GetName(), _File);

    // ������Ʈ
    for (UINT i = 0; i <= (UINT)COMPONENT_TYPE::END; ++i)
    {
        if (i == (UINT)COMPONENT_TYPE::END)
        {
            // ������Ʈ Ÿ�� ����
            fwrite(&i, sizeof(UINT), 1, _File);
            break;
        }

        CComponent* Com = _Object->GetComponent((COMPONENT_TYPE)i);
        if (nullptr == Com)
            continue;

        // ������Ʈ Ÿ�� ����
        fwrite(&i, sizeof(UINT), 1, _File);

        // ������Ʈ ���� ����
        Com->SaveToLevelFile(_File);
    }

    // ��ũ��Ʈ   
    const vector<CScript*>& vecScript = _Object->GetScripts();
    size_t ScriptCount = vecScript.size();
    fwrite(&ScriptCount, sizeof(size_t), 1, _File);

    for (size_t i = 0; i < vecScript.size(); ++i)
    {
        wstring ScriptName = CScriptMgr::GetScriptName(vecScript[i]);
        SaveWString(ScriptName, _File);
        vecScript[i]->SaveToLevelFile(_File);
    }


    // �ڽ� ������Ʈ
    const vector<CGameObject*>& vecChild = _Object->GetChild();
    size_t ChildCount = vecChild.size();
    fwrite(&ChildCount, sizeof(size_t), 1, _File);

    for (size_t i = 0; i < ChildCount; ++i)
    {
        SaveGameObject(vecChild[i], _File);
    }

    return 0;
}

CLevel* CLevelSaveLoadInScript::LoadLevel(LEVEL_STATE _state)
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

    // ���� �����
    FILE* pFile = nullptr;
    errno_t iErrNum = _wfopen_s(&pFile, szFilePath, L"rb");

    if (nullptr == pFile)
        return nullptr;

    CLevel* NewLevel = new CLevel;

    // ���� �̸�
    wstring strLevelName;
    LoadWString(strLevelName, pFile);
    NewLevel->SetName(strLevelName);


    for (UINT i = 0; i < MAX_LAYER; ++i)
    {
        CLayer* pLayer = NewLevel->GetLayer(i);

        // ���̾� �̸�
        wstring LayerName;
        LoadWString(LayerName, pFile);
        pLayer->SetName(LayerName);

        // ���� ������Ʈ ����
        size_t objCount = 0;
        fread(&objCount, sizeof(size_t), 1, pFile);

        // �� ���ӿ�����Ʈ
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

CGameObject* CLevelSaveLoadInScript::LoadGameObject(FILE* _File)
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

        // ������Ʈ ������ ���� Ȯ��
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

    // �ڽ� ������Ʈ      
    size_t ChildCount = 0;
    fread(&ChildCount, sizeof(size_t), 1, _File);

    for (size_t i = 0; i < ChildCount; ++i)
    {
        CGameObject* ChildObject = LoadGameObject(_File);
        pObject->AddChild(ChildObject);
    }

    return pObject;
}

int CLevelSaveLoadInScript::SavePrefab(const wstring& _strRelativePath, CPrefab* _Prefab)
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

CGameObject* CLevelSaveLoadInScript::LoadPrefab(const wstring& _strRelativePath)
{
    Ptr<CPrefab> pPrefab = new CPrefab;

    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    FILE* pFile = nullptr;
    _wfopen_s(&pFile, strFilePath.c_str(), L"rb");

    CGameObject* pNewObj = CLevelSaveLoadInScript::LoadGameObject(pFile);
    fclose(pFile);

    return pNewObj;
}

void CLevelSaveLoadInScript::SpawnPrefab(wstring _relativepath, int ind, Vec3 _vWorldPos, float time)
{
    wstring strFolderpath = CPathMgr::GetInst()->GetContentPath();
    wstring relativepath = _relativepath;
    strFolderpath += relativepath;

    FILE* pFile = nullptr;
    errno_t iErrNum = _wfopen_s(&pFile, strFolderpath.c_str(), L"rb");

    CGameObject* newPrefab = LoadGameObject(pFile);
    Vec3 prefpos = _vWorldPos;

    SpawnGameObject(newPrefab, _vWorldPos, ind);
    if (time != -1)
        newPrefab->SetLifeSpan(time);
    fclose(pFile);
}

CGameObject* CLevelSaveLoadInScript::SpawnandReturnPrefab(wstring _relativepath, int ind, Vec3 _vWorldPos, float time)
{
    wstring strFolderpath = CPathMgr::GetInst()->GetContentPath();
    wstring relativepath = _relativepath;
    strFolderpath += relativepath;

    FILE* pFile = nullptr;
    errno_t iErrNum = _wfopen_s(&pFile, strFolderpath.c_str(), L"rb");

    CGameObject* newPrefab = LoadGameObject(pFile);
    Vec3 prefpos = _vWorldPos;

    SpawnGameObject(newPrefab, _vWorldPos, ind);
    if (time != -1)
        newPrefab->SetLifeSpan(time);
    fclose(pFile);
    return newPrefab;
}
