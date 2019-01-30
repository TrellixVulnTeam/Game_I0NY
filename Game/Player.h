#pragma once
//�L�����N�^�[�R���g���[���[���g�p����ꍇ�́A���L�̃w�b�_�[�t�@�C���̃C���N���[�h���K�v�B
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/effect/tkEffect.h"

class GameClear;
class StageSeni;
class NPC;
class GameOver;

class Player :public IGameObject
{
public:
	Player();
	~Player();
	void OnDestroy() override;
	bool Start() override;
	void Update() override;
	//����ɍ��킹���G�t�F�N�g�Đ��B
	//void Effect(CVector3 npcpos, CQuaternion npcrot);
	//�X�e�[�W�ɍ��킹������̈ڂ�ς��
	void UpdatekanjouSt1();

	//�ړ������B
	void Move();
	void Turn();
	//�Q�b�^�[�A�Z�b�^�[
	int GetfollowerNum()
	{
		return followerNum;
	}
	int Getef_flag()
	{
		return ef_flag;
	}
	
	CVector3 GetPosition()
	{
		return m_position;
	}
	CQuaternion GetRotation()
	{
		return m_rotation;
	}
	CVector3 GetPlforward()
	{
		return m_plforward;
	}
	void Setef_flag()
	{
		ef_flag++;
	}
	void SetfollowerNump() 
	{
		followerNum++;
	}
	void Setrotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	void SetfollowerNum(int a)
	{
		followerNum = a;
	}
	void SetfollowerNumm()
	{
		followerNum--;
	}

	void Setplkan(bool k)
	{
		plkan = k;
	}
	////////////////////////////////////
	// �����o�ϐ��Ƃ�
	////////////////////////////////////
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero;	//���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	CCharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B
	enum EnAnimationClip {
		enAnimationClip_idle,	//�ҋ@�A�j���[�V�����B
		enAnimationClip_run,	//����A�j���[�V�����B
		enAnimationClip_walk,	//�����A�j���[�V�����B
		enAnimationClip_Num,	//�A�j���[�V�����N���b�v�̐��B
	};
	//CAnimationClip m_animClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v�B
	CVector3 m_moveSpeed = CVector3::Zero;	//�ړ����x�B
	//�t���ė��Ă���l�Ԃ̐��B
	GameClear* m_gc = nullptr;
	CVector3 m_plforward = CVector3::Zero;
	NPC* m_npc = nullptr;
	//�G�t�F�N�g���쐬�B
	prefab::CEffect* effect = nullptr;
	StageSeni* m_ss = nullptr;
	GameOver* m_gameover = nullptr;
	enum kanjou plkanjou;
	bool plkan = false;
	int ef_flag = 0;						//�G�t�F�N�g�̃t���O�B
	int followerNum = 0;			
	int clearNum = 19;
	bool a = true;
	bool gof = false;
	bool gcf = false;
};
