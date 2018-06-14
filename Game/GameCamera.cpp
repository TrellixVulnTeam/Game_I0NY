#include "stdafx.h"
#include "GameCamera.h"


//�J�����f�[�^�B
struct SCameraData {
	float targetToPosition;		//�����_���王�_�܂ł̋����B
	int humanLimit;				//���̃J�����f�[�^���g�p�ł���l�Ԃ̐��̏���B
};
//�J�����f�[�^�̃e�[�u���B
SCameraData cameraDataTbl[] = {
	{ 15.0f, 5 },			//�l�Ԃ̐����T�l�ȉ��̎��̃J�����f�[�^�B
	{ 20.0f, 10 },			//�l�Ԃ̐���10�l�ȉ��̎��̃J�����f�[�^�B
	{ 30.0f, 20 },			//�l�Ԃ̐���20�l�ȉ��̎��̃J�����f�[�^�B
	{ 40.0f, 100},
	{ 100.0f, 10000},		//�l�Ԃ̐���10000�l�ȉ��̎��̃J�����f�[�^�B
};

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(0.0f, 15.0f, 30.0f);
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("Player");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);

	//�΂˃J�����̏������B
	m_springCamera.Init(
		MainCamera(),		//�΂˃J�����̏������s���J�������w�肷��B
		1000.0f,			//�J�����̈ړ����x�̍ő�l�B
		false,					//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
		5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
	);
	return true;
}
void GameCamera::Update()
{
	//�J�������X�V�B
	//�����_���v�Z����B
	CVector3 target = m_player->GetPosition();
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 10.0f;

	CVector3 toCameraPosOld = m_toCameraPos;
	//�p�b�h�̓��͂��g���ăJ�������񂷁B
	float x = Pad(0).GetRStickXF();
	float y = Pad(0).GetRStickYF();
	//Y������̉�]
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY, 6.0f * x);
	qRot.Multiply(m_toCameraPos);
	//X������̉�]�B
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 6.0f * y);
	qRot.Multiply(m_toCameraPos);
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//�J����������������B
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//�J�����������������B
		m_toCameraPos = toCameraPosOld;
	}/*
	if (m_player->GetfollowerNum() > 2) {
		float angle = 0.0f;
		angle += 3.0f;
		qRot.SetRotationDeg(CVector3::AxisY, angle);
		qRot.Multiply(m_player->GetPlforward());
	}*/
	//���ė��Ă���l�Ԃ̐��ŁA�g�p����J�����f�[�^�����߂�B
	SCameraData* cameraData = nullptr;
	int arraySize = ARRAYSIZE(cameraDataTbl);
	for (int i = 0; i < arraySize; i++) {
		if (m_player->GetfollowerNum() < cameraDataTbl[i].humanLimit) {
			//�g�p����J�����f�[�^�����������B
			cameraData = &cameraDataTbl[i];
			break;
		}
	}
	//�����_���王�_�ւ̃x�N�g���𐳋K�����āA�傫���P�ɂ���B
	m_toCameraPos.Normalize();
	m_toCameraPos *= cameraData->targetToPosition;
	////�V���������_���王�_�܂ł̃x�N�g�������܂����̂ŁA�V�������_���v�Z����B
	CVector3 pos = target + m_toCameraPos;
	//�o�l�J�����ɒ����_�Ǝ��_��ݒ肷��B
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);

	//�o�l�J�����̍X�V�B
	m_springCamera.Update();
}