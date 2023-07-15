#pragma once

class CLevel;
class CLayer;
class CGameObject;


class CLevelSaveLoad
{
public:
	static int SaveLevel(CLevel* _Level);
	static int Play(const wstring& _LevelPath, CLevel* _Level);
	static int SaveGameObject(CGameObject* _Object, FILE* _File);

	static CLevel* LoadLevel(LEVEL_STATE _state);
	static CLevel* Stop(const wstring& _LevelPath, LEVEL_STATE _state);
	static CGameObject* LoadGameObject(FILE* _File);
};

