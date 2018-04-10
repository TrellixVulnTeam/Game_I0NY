#include "stdafx.h"
#include "Level.h"
#include "MapChip.h"

Level::Level()
{
}


Level::~Level()
{
	for (auto& mapChip : m_mapChipList) {
		DeleteGO(mapChip);
	}
}
/*!
*@brief	���x���̍쐬�B
*@param[in]	levelDataFilePath	�ǂݍ��ރ��x���f�[�^�̃t�@�C���p�X�B
*/
void Level::Build(const wchar_t* levelDataFilePath)
{
	//����͔z�u�f�[�^�Ƃ��ăX�P���g���𗘗p����B
	CLocData locData;
	locData.Load(levelDataFilePath);

	for (int i = 0; i < locData.GetNumObject(); i++) {

		//���s�ړ��A��]���擾����B
		CVector3 position, scale;
		CQuaternion rotation;
		position = locData.GetObjectPosition(i);
		rotation = locData.GetObjectRotation(i);

		//�{�[�������烂�f���f�[�^�̃t�@�C���p�X���쐬����B
		const wchar_t* boneName = locData.GetObjectName(i);
		wchar_t modelDataFilePath[256];
		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
		MapChip* mapChip = NewGO<MapChip>(0);
		mapChip->Init(modelDataFilePath, position, CVector3::One, rotation);
		m_mapChipList.push_back(mapChip);
	}
}