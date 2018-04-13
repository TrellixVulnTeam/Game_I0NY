#pragma once
//�L�����N�^�[�R���g���[���[���g�p����ꍇ�́A���L�̃w�b�_�[�t�@�C���̃C���N���[�h���K�v�B
#include "tkEngine/character/tkCharacterController.h"

class Game;
class Player;
class NPC : public IGameObject
{
public:
	NPC(); 
	~NPC();
	void OnDestroy() override;
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc);
	////////////////////////////////////
	// �����o�ϐ��Ƃ�
	////////////////////////////////////
	//enum EnAnimationClip {
	//	enAnimationClip_idle,	//�ҋ@�A�j���[�V�����B
	//	enAnimationClip_run,	//����A�j���[�V�����B
	//	enAnimationClip_walk,	//�����A�j���[�V�����B
	//	enAnimationClip_num,	//�A�j���[�V�����N���b�v�̑����B
	//};
	//CAnimationClip m_animationClip[enAnimationClip_num];	//�A�j���[�V�����N���b�v�B
	prefab::CSkinModelRender* m_skinModelRender[30];	//�X�L�����f�������_���[�B
	CVector3 m_position[30];	//���W�B
	CQuaternion m_rotation[30];	//��]�B
	CCharacterController m_charaCon[30];		//�L�����N�^�[�R���g���[���[�B
	CVector3 m_moveSpeed[30];	//�ړ����x�B
	Game *m_game = nullptr;
	Player *m_player = nullptr;
	int i = 0;
	float angle[30];
};

