#include "pch.h"
#include "CDetourMgr.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CCamera.h"
#include "CTransform.h"
#include "CRenderMgr.h"

#include <Detour\DetourNavMesh.h>
#include <Detour\DetourNavMeshBuilder.h>
#include <Detour\\DetourNavMeshQuery.h>

#include <fstream>

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

CDetourMgr::CDetourMgr()
{

}
CDetourMgr::~CDetourMgr()
{

}

void CDetourMgr::LoadNavMeshFromBinFile(const char* path)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	std::wstring wpath = converter.from_bytes(path);
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += wpath;

	FILE* fp = nullptr;
	errno_t err = _wfopen_s(&fp, strFilePath.c_str(), L"rb");
	if (err != 0 || !fp)
	{
		return;
	}
	// Read header.
	NavMeshSetHeader header;
	fread(&header, sizeof(NavMeshSetHeader), 1, fp);
	if (header.magic != NAVMESHSET_MAGIC)
	{
		fclose(fp);
		return;
	}
	if (header.version != NAVMESHSET_VERSION)
	{
		fclose(fp);
		return;
	}

	NaviMesh = dtAllocNavMesh();
	if (!NaviMesh)
	{
		fclose(fp);
		return;
	}

	dtStatus status = NaviMesh->init(&header.params);
	if (dtStatusFailed(status))
	{
		fclose(fp);
		return;
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

		NaviMesh->addTile(data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0);
	}

	fclose(fp);

	if(!NaviMesh)
	{
		printf("NaviMesh Load Error!!!");
		return;
	}
}

int currentPathIndex = 0;

Vec3* CDetourMgr::GetPathtoTarget(Vec3 _vStartPos)
{
	if (NaviMesh == nullptr)
		LoadNavMeshFromBinFile("Navi\\all_tiles_navmesh.bin");
	float actualPath[256] = { 0.f, };
	for (int i = 0; i < 256 * 3; i++)
		actualPath[i] = 0.0f;

	actualPathCount = 0;

	// NavMesh�� �Բ� ��� ��ȹ�� �����ϴ� Query ��ü ����
	dtNavMeshQuery* navQuery = dtAllocNavMeshQuery();
	navQuery->init(NaviMesh, 4866);

	// ����, �� ��ġ ����
	float startpos[3] = {};
	startpos[0] = _vStartPos.x;
	startpos[1] = _vStartPos.y;
	startpos[2] = -_vStartPos.z;

	float endpos[3] = {};
	Vec3 vEndPos = m_pPlayer->Transform()->GetWorldPos();
	endpos[0] = vEndPos.x;
	endpos[1] = vEndPos.y;
	endpos[2] = -vEndPos.z;

	dtPolyRef startRef, endRef;
	float polyPickExt[3] = { 3000,3000,3000 }; // ������ �����ϱ� ���� ����

	dtQueryFilter filter;
	filter.setIncludeFlags(0xFFFF); // Include all polygons in pathfinding.
	filter.setExcludeFlags(0); // Exclude none of the polygons.


	// ��, ��, �� ���� Mesh ������ ���� ���� �� �ִ� ������ �����ϴ� ���Ͱ�
	// ���� ��� �Ұ���
	//// Set cost for area. Area values are usually defined in the Recast/Detour code.
	//// Let's assume that 1 is ground, 2 is water, and 3 is a wall.
	//filter.setAreaCost(1, 1.0f); // Set cost for ground area.
	//filter.setAreaCost(2, 10.0f); // Set high cost for water area.
	//filter.setAreaCost(3, FLT_MAX); // Set infinite cost for wall area.

	navQuery->findNearestPoly(startpos, polyPickExt, &filter, &startRef, 0);
	navQuery->findNearestPoly(endpos, polyPickExt, &filter, &endRef, 0);

	// ���۰� �� ��ġ�� Ž��
	float nearestStartPos[3], nearestEndPos[3];
	navQuery->closestPointOnPoly(startRef, startpos, nearestStartPos, 0);
	navQuery->closestPointOnPoly(endRef, endpos, nearestEndPos, 0);

	// ��θ� ��ȹ.
	dtPolyRef path[256];
	int pathCount;
	navQuery->findPath(startRef, endRef, nearestStartPos, nearestEndPos, &filter, path, &pathCount, 256);

	// ��θ� ���� ���� �̵� ��θ� ����
	navQuery->findStraightPath(nearestStartPos, nearestEndPos, path, pathCount, actualPath, 0, 0, &actualPathCount, 256);


	Vec3 Path[256] = {};
	for (int i = 0; i < 256; ++i)
	{
		Path[i] = Vec3(actualPath[i * 3], actualPath[i * 3 + 1], actualPath[i * 3 + 2]);
	}

	return Path;
}
