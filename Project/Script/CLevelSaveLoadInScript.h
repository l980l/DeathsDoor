#pragma once

class CLevel;
class CLayer;
class CGameObject;
class CPrefab;


class CLevelSaveLoadInScript
{
public:
	static int SaveLevel(CLevel* _Level);
	static int Play(const wstring& _LevelPath, CLevel* _Level);
	static int SaveGameObject(CGameObject* _Object, FILE* _File);
	static int SavePrefab(const wstring& _strRelativePath, CPrefab* _Prefab);

	static CLevel* LoadLevel(LEVEL_STATE _state);
	static CLevel* Stop(const wstring& _LevelPath, LEVEL_STATE _state);
	static CGameObject* LoadGameObject(FILE* _File);
	static CGameObject* LoadPrefab(const wstring& _strRelativePath);

	void SpawnPrefab(wstring _relativepath, int _ind, Vec3 _vWorldPos, float time);
	CGameObject* SpawnPrefab(wstring _relativepath, int _ind, Vec3 _vWorldPos);
	void SpawnGameObject(CGameObject* _NewObject, Vec3 _vWorldPos, int _LayerIdx);
};

