#include "stdafx.h"
#include "Player.h"
#include "GameClear.h"
#include "NPC.h"
#include "StageSeni.h"

Player::Player()
{
}


Player::~Player()
{
}
void Player::OnDestroy()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_gc);
}

bool Player::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f });
	m_position.y = 40;
	m_position.x = 200.0f;
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		4.0,			//���a�B 
		100.0f,			//�����B
		m_position, 	//�����ʒu�B
		0			//0���v���C���[�̃t���O�B
	);
	//�G�t�F�N�g���쐬�B
	effect = NewGO<prefab::CEffect>(0);
	m_npc = FindGO<NPC>("npc");
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
	plkanjou = delighted;

	//�A�j���[�V�����N���b�v�̃��[�h�B
	//m_animClips[enAnimationClip_idle].Load(L"animData/idle.tka");
	//m_animClips[enAnimationClip_run].Load(L"animData/run.tka");
	//m_animClips[enAnimationClip_walk].Load(L"animData/walk.tka");
	////���[�v�t���O��ݒ肷��B<-����A�j���[�V�����̓��[�v�t���O��ݒ肵�Ă��Ȃ��̂�
	////�����V���b�g�Đ��Œ�~����B
	//m_animClips[enAnimationClip_run].SetLoopFlag(true);
	//m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	//m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	return true;
}

//void Player::Effect(CVector3 npcpos, CQuaternion npcrot)
//{
//	switch (plkanjou)
//	{
//	case delighted:
//		//�G�t�F�N�g���Đ��B
//		if (effect->IsPlay() == false) {
//			effect = NewGO<prefab::CEffect>(0);
//			effect->Play(L"effect/tanosii.efk");
//		}
//		effect->SetPosition(npcpos);
//		effect->SetRotation(npcrot);
//		break;
//	case angry:
//		if (effect->IsPlay() == false) {
//			//�G�t�F�N�g���Đ��B
//			effect = NewGO<prefab::CEffect>(0);
//			effect->Play(L"effect/okoru.efk");
//		}
//		effect->SetPosition(npcpos);
//		effect->SetRotation(npcrot);
//		break;
//	}
//}
void Player::UpdatekanjouSt1()
{
	switch (plkanjou)
	{
	case flat:
		go = true;
		break;
	case delighted:
		if (plkan == true) {
			plkanjou = flat;
		}
		break;
	}
}

void Player::Move()
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = Pad(0).GetLStickXF();
	float lStick_y = Pad(0).GetLStickYF();
	//�J�����̑O�������ƉE�������擾�B
	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y -= 980.0f * GameTime().GetFrameDeltaTime();
	m_moveSpeed += cameraForward * lStick_y * 60.0f;	//�������ւ̈ړ����x�����B
	m_moveSpeed += cameraRight * lStick_x * 60.0f;		//�E�����ւ̈ړ����x�����Z�B
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	//�v���C���[�̑O�����B
	m_plforward = m_moveSpeed;
	/*if (m_moveSpeed.x > 0.01f || m_moveSpeed.y > 0.01f) {
		m_skinModelRender->PlayAnimation(enAnimationClip_run, 2.0f);
	}
	else {
		m_skinModelRender->PlayAnimation(enAnimationClip_idle, 2.0f);
	}*/

}

void Player::Turn()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rotation.SetRotation(CVector3::AxisY, angle);
}

void Player::Update()
{
	//�ړ������B
	Move();
	//���񏈗��B
	Turn();

	//Effect(m_position, m_rotation);

	UpdatekanjouSt1();

	if (followerNum > clearNum && ef_flag == 0) {
		m_gc = NewGO<GameClear>(0);
	}
	//���[���h�s����X�V�B
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX, 0.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������B
	qRot.Multiply(m_rotation, qRot);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(qRot);
}