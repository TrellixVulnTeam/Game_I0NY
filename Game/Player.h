#pragma once
//�L�����N�^�[�R���g���[���[���g�p����ꍇ�́A���L�̃w�b�_�[�t�@�C���̃C���N���[�h���K�v�B
#include "tkEngine/character/tkCharacterController.h"
class GameClear;
class Player :public IGameObject
{
public:
	Player();
	~Player();
	void OnDestroy() override;
	bool Start() override;
	void Update() override;

	//�ړ������B
	void Move();
	void Turn();
	////////////////////////////////////
	// �����o�ϐ��Ƃ�
	////////////////////////////////////
	
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero;	//���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	CCharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B
	CVector3 m_moveSpeed = CVector3::Zero;	//�ړ����x�B
	GameClear* m_gc = nullptr;
	int followerNum = 0;					//�t���ė��Ă���l�Ԃ̐��B
	int ef_flag = 0;
};
