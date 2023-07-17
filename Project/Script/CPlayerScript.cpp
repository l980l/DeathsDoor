#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>

#include "CMissileScript.h"
#include "CStateScript.h"
#include "PlayerStates.h"

#include <Detour\DetourNavMesh.h>
#include <Detour\DetourNavMeshBuilder.h>
#include <Detour\DetourNavMeshQuery.h>
#include <Engine\SimpleMath.h>


#include <Engine\CRenderMgr.h>

class NavMeshSetHeader;

struct NavMeshSetHeader
{
	int magic;
	int version;
	int numTiles;
	dtNavMeshParams params;
};

struct NavMeshTileHeader
{
	dtTileRef tileRef;
	int dataSize;
};

static const int NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET';
static const int NAVMESHSET_VERSION = 1;

dtNavMesh* CPlayerScript::loadNavMeshFromBinFile(const char* path)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	std::wstring wpath = converter.from_bytes(path);
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += wpath;

	FILE* fp = nullptr;
	errno_t err = _wfopen_s(&fp, strFilePath.c_str(), L"rb");
	if (err != 0 || !fp)
	{
		return 0;
	}
	// Read header.
	NavMeshSetHeader header;
	fread(&header, sizeof(NavMeshSetHeader), 1, fp);
	if (header.magic != NAVMESHSET_MAGIC)
	{
		fclose(fp);
		return 0;
	}
	if (header.version != NAVMESHSET_VERSION)
	{
		fclose(fp);
		return 0;
	}

	dtNavMesh* navMesh = dtAllocNavMesh();
	if (!navMesh)
	{
		fclose(fp);
		return 0;
	}

	dtStatus status = navMesh->init(&header.params);
	if (dtStatusFailed(status))
	{
		fclose(fp);
		return 0;
	}

	// Read tiles.
	for (int i = 0; i < header.numTiles; ++i)
	{
		NavMeshTileHeader tileHeader;
		fread(&tileHeader, sizeof(tileHeader), 1, fp);
		if (!tileHeader.tileRef || !tileHeader.dataSize)
			break;

		unsigned char* data = (unsigned char*)dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
		if (!data) break;
		memset(data, 0, tileHeader.dataSize);
		fread(data, tileHeader.dataSize, 1, fp);

		navMesh->addTile(data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0);
	}

	fclose(fp);

	return navMesh;

}

float speed = 100.0f;
int currentPathIndex = 0;

CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, m_pState(nullptr)
	, m_fSpeed(0.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fSpeed, "Speed");
}

CPlayerScript::~CPlayerScript()
{
	if (nullptr == m_pState)
		delete m_pState;
}

void CPlayerScript::begin()
{
	m_pState = GetOwner()->GetScript<CStateScript>();
	m_pState->AddState(L"Idle", new CPlyIdle);
	m_pState->AddState(L"Walk", new CPlyWalk);
	m_pState->ChangeState(L"Idle");
	MeshRender()->GetDynamicMaterial(0);
}

void CPlayerScript::tick()
{
	if (KEY_TAP(KEY::TAB))
	{
		dtNavMesh* navMesh = loadNavMeshFromBinFile("Navi\\all_tiles_navmesh.bin");
		if (!navMesh)
		{
			printf("Error loading navmesh\n");
			return;
		}

		for (int i = 0; i < 256 * 3; i++)
			actualPath[i] = 0.0f;

		currentPathIndex = 0;
		actualPathCount = 0;

		// Query 객체를 생성합니다. 이것은 NavMesh와 함께 경로 계획을 수행합니다.
		dtNavMeshQuery* navQuery = dtAllocNavMeshQuery();
		navQuery->init(navMesh, 4866);
		// 시작 위치와 끝 위치를 설정합니다.
		Vec3 Pos = Transform()->GetRelativePos();

		startpos[0] = Pos.x; // 시작 위치
		startpos[1] = Pos.y;
		startpos[2] = -Pos.z;

		endpos[0] = 0.f; // 시작 위치
		endpos[1] = 0.f;
		endpos[2] = 0.f;

		dtPolyRef startRef, endRef;
		float polyPickExt[3] = { 3000,3000,3000 }; // 범위를 제한하기 위한 벡터

		dtQueryFilter filter;
		filter.setIncludeFlags(0xFFFF); // Include all polygons in pathfinding.
		filter.setExcludeFlags(0); // Exclude none of the polygons.

		//// Set cost for area. Area values are usually defined in the Recast/Detour code.
		//// Let's assume that 1 is ground, 2 is water, and 3 is a wall.
		//filter.setAreaCost(1, 1.0f); // Set cost for ground area.
		//filter.setAreaCost(2, 10.0f); // Set high cost for water area.
		//filter.setAreaCost(3, FLT_MAX); // Set infinite cost for wall area.
		//이거 땅,벽, 물 이런 메쉬 종류에따라 넘을수 있는 정도? 를 설정해주는 필터값인데
		//우리 메쉬에는 아마 그정보가 없는 것 같음.

		navQuery->findNearestPoly(startpos, polyPickExt, &filter, &startRef, 0);
		navQuery->findNearestPoly(endpos, polyPickExt, &filter, &endRef, 0);

		// 시작과 끝 위치를 찾습니다.
		float nearestStartPos[3], nearestEndPos[3];
		navQuery->closestPointOnPoly(startRef, startpos, nearestStartPos, 0);
		navQuery->closestPointOnPoly(endRef, endpos, nearestEndPos, 0);

		// 경로를 계획합니다.
		dtPolyRef path[256];
		int pathCount;
		navQuery->findPath(startRef, endRef, nearestStartPos, nearestEndPos, &filter, path, &pathCount, 256);

		// 경로를 따라 실제 이동 경로를 생성합니다.
		navQuery->findStraightPath(nearestStartPos, nearestEndPos, path, pathCount, actualPath, 0, 0, &actualPathCount, 256);
	}

	if (currentPathIndex < actualPathCount)
	{
		// 다음 타겟 위치
		Vec3 targetPos(actualPath[3 * currentPathIndex], actualPath[3 * currentPathIndex + 1], actualPath[3 * currentPathIndex + 2]);

		// 현재 오브젝트 위치
		Vec3 ObjPos = Transform()->GetRelativePos();
		Vec3 currentPos = Vec3(ObjPos.x, ObjPos.y, -ObjPos.z);

		// 이동할 방향 벡터 계산
		Vec3 direction = targetPos - currentPos;

		// 방향 벡터를 정규화합니다.
		direction = direction.Normalize();

		// 새로운 위치 계산
		Vec3 newPos = currentPos + speed * direction * DT;

		// 새 위치를 오브젝트에 적용합니다.
		Transform()->SetRelativePos(Vec3(newPos.x, newPos.y, -newPos.z));

		// 만약 타겟 위치에 도달했다면, 다음 경로 인덱스로 이동합니다.
		float distanceToTarget = (targetPos - newPos).Length();
		if (distanceToTarget < speed * DT)
		{
			currentPathIndex++;
		}
	}
}

void CPlayerScript::Shoot()
{
}



void CPlayerScript::BeginOverlap(CCollider2D* _Other)
{
	
}


void CPlayerScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
}

void CPlayerScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_fSpeed, sizeof(float), 1, _File);
}