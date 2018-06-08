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
	//�Q�b�^�[�A�Z�b�^�[
	int Getef_flag()
	{
		return ef_flag;
	}
	void Setef_flag()
	{
		ef_flag++;
	}
	int GetfollowerNum()
	{
		return followerNum;
	}
	void SetfollowerNump() 
	{
		followerNum++;
	}
	void SetfollowerNumm()
	{
		followerNum--;
	}
	////////////////////////////////////
	// �����o�ϐ��Ƃ�
	////////////////////////////////////
	
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero;	//���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	CCharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B
	CVector3 m_moveSpeed = CVector3::Zero;	//�ړ����x�B
			//�t���ė��Ă���l�Ԃ̐��B
	GameClear* m_gc = nullptr;
private:
	int ef_flag = 0;						//�G�t�F�N�g�̃t���O�B
	int followerNum = 0;			
};
