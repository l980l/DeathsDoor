#include "pch.h"
#include "CMeshData.h"

#include "CPathMgr.h"
#include "CResMgr.h"

#include "CGameObject.h"
#include "components.h"
#include "CFBXLoader.h"

#include "CMesh.h"
#include "CMaterial.h"


CMeshData::CMeshData(bool _bEngine)
	: CRes(RES_TYPE::MESHDATA, _bEngine)
{
}

CMeshData::~CMeshData()
{
}


CGameObject* CMeshData::Instantiate()
{
	CGameObject* pNewObj = new CGameObject;
	pNewObj->AddComponent(new CTransform);
	pNewObj->AddComponent(new CMeshRender);

	pNewObj->MeshRender()->SetMesh(m_pMesh);

	for (UINT i = 0; i < m_vecMtrl.size(); ++i)
	{
		pNewObj->MeshRender()->SetMaterial(m_vecMtrl[i], i);
	}	

	// Animation ��Ʈ �߰�
	if (false == m_pMesh->IsAnimMesh())
		return pNewObj;

	CAnimator3D* pAnimator = new CAnimator3D;
	pNewObj->AddComponent(pAnimator);

	pAnimator->SetBones(m_pMesh->GetBones());
	pAnimator->SetAnimClip(m_pMesh->GetAnimClip());

	return pNewObj;
}


CMeshData* CMeshData::LoadFromFBX(const wstring& _strPath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContentPath();
	strFullPath += _strPath;

	CFBXLoader loader;
	loader.init();
	loader.LoadFbx(strFullPath);

	CMesh::CreateFromContainer(loader, loader.GetContainerCount());

	// �޽� ��������
	vector<CMesh*> vecMesh = CResMgr::GetInst()->GetMeshs();

	for (size_t i = 0; i < vecMesh.size(); ++i)
	{
		// ResMgr �� �޽� ���
		wstring strMeshName = L"mesh\\";
		strMeshName += path(strFullPath).stem();
		strMeshName += std::to_wstring(i);
		strMeshName += L".mesh";

		vecMesh[i]->SetName(strMeshName);
		vecMesh[i]->SetRelativePath(strMeshName);

		CResMgr::GetInst()->AddRes<CMesh>(vecMesh[i]->GetName(), vecMesh[i]);

		vector<Ptr<CMaterial>> vecMtrl;

		// ���׸��� ��������
		for (UINT j = 0; j < loader.GetContainer(j).vecMtrl.size(); ++j)
		{
			// ����ó�� (material �̸��� �Է� �ȵǾ����� ���� �ִ�.)
			Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(loader.GetContainer(i).vecMtrl[j].strMtrlName);
			vecMtrl.push_back(pMtrl);
		}

		CMeshData* pMeshData = new CMeshData;
		pMeshData->m_pMesh = vecMesh[i];
		pMeshData->m_vecMtrl = vecMtrl;

		CResMgr::GetInst()->GetMeshDatas().push_back(pMeshData);
	}
	return CResMgr::GetInst()->FindRes<CMeshData>(_strPath).Get();
}

int CMeshData::Save(const wstring& _strRelativePath)
{
	SetRelativePath(_strRelativePath);

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath() + _strRelativePath;

	FILE* pFile = nullptr;
	errno_t err = _wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);

	// Mesh Key ����	
	// Mesh Data ����
	SaveResRef(m_pMesh.Get(), pFile);

	// material ���� ����
	UINT iMtrlCount = (UINT)m_vecMtrl.size();
	fwrite(&iMtrlCount, sizeof(UINT), 1, pFile);

	UINT i = 0;
	wstring strMtrlPath = CPathMgr::GetInst()->GetContentPath();
	strMtrlPath += L"material\\";

	for (; i < iMtrlCount; ++i)
	{
		if (nullptr == m_vecMtrl[i])
			continue;

		// Material �ε���, Key, Path ����
		fwrite(&i, sizeof(UINT), 1, pFile);
		SaveResRef(m_vecMtrl[i].Get(), pFile);
	}

	i = -1; // ���� ��
	fwrite(&i, sizeof(UINT), 1, pFile);

	fclose(pFile);

	return S_OK;
}

int CMeshData::Load(const wstring& _strFilePath)
{
	FILE* pFile = NULL;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");

	assert(pFile);

	// Mesh Load
	LoadResRef<CMesh>(m_pMesh, pFile);
	assert(m_pMesh.Get());

	// material ���� �б�
	UINT iMtrlCount = 0;
	fread(&iMtrlCount, sizeof(UINT), 1, pFile);

	m_vecMtrl.resize(iMtrlCount);

	for (UINT i = 0; i < iMtrlCount; ++i)
	{
		UINT idx = -1;
		fread(&idx, 4, 1, pFile);
		if (idx == -1)
			break;

		wstring strKey, strPath;

		Ptr<CMaterial> pMtrl;
		LoadResRef<CMaterial>(pMtrl, pFile);

		m_vecMtrl[i] = pMtrl;
	}

	fclose(pFile);

	return S_OK;
}