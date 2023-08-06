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


	//Prefab ����
	void SpawnPrefab(wstring _relativepath, int ind, Vec3 _vWorldPos, float time = -1);
	CGameObject* SpawnandReturnPrefab(wstring _relativepath, int ind, Vec3 _vWorldPos, float time = -1);

	//�ڸ��� ���
	int GetDigitCount(int money);

	//������ ���
	void ShowMoney(int money, int DigitCount, CGameObject* UI);
	void MoneyCount(int money, CGameObject* UI) { ShowMoney(money, GetDigitCount(money), UI); }//�̰� ����ϸ� �ʴ�.
	void AddChild(CGameObject* _owner, CGameObject* _child);
};

