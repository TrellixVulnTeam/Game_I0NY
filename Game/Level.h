#pragma once

#include "MapChip.h"

//���x���B
class Level
{
public:
	Level();
	~Level();
	/*!
	*@brief	���x���̍\�z�B
	*@param[in]	levelDataFilePath	�ǂݍ��ރ��x���f�[�^�̃t�@�C���p�X�B
	*/
	void Build(const wchar_t* levelDataFilePath);
	///////////////////////////////////////////////
	// �������烁���o�ϐ��B
	///////////////////////////////////////////////
	std::list<MapChip*> m_mapChipList;		//�}�b�v�`�b�v�̃��X�g�B
};

