#include "stdafx.h"
#include "NPC.h"
#include "Level.h"
#include "MapChip.h"
#include "Game.h"
#include "Player.h"


NPC::NPC()
{
}


NPC::~NPC()
{  
}

void NPC::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}

bool NPC::Start()
{
	//int npcCflag = 1;
	m_game = FindGO<Game>("Game");
	m_player = FindGO<Player>("Player");


	m_position.y = 0;
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_charaCon.Init(
		4.0,			//���a�B 
		6.0f,			//�����B
		m_position, 	//�����ʒu�B
		1
	);

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f });

	//@todo �X�e�[�W�ɂ���āA�������銴��R���g���[���̃C���X�^���X��؂�ւ���悤��.
	
	
	return true;
}
//Stage1�̊���X�V�֐��B
void NPC::UpdateKanjouStage1()
{
	plpo = m_player->m_position - m_position;
	switch (npckanjou)
	{
	case flat:
		if (plpo.Length() < 4.0) {
			npckanjou = delighted;
			npcState = tuibi;
			m_player->SetfollowerNump();
		}
		break;
	case delighted:
		if (plpo.Length() > 50.0f) //��
		{
			npcState = haikai;
			npckanjou = flat;
		}
	case angry:
		if (plpo.Length() < 4.0&&m_player->GetfollowerNum()==7
			/*�@�v���C���[���A��Ă���l�������l�ȏ�ɂȂ�����A�������я�Ԃɂ���B*/
			) {
			npckanjou = delighted;
			npcState = tuibi;
		}
		break;
	}
	
}
//Stage2�̊���X�V�֐��B
void NPC::UpdateKanjouStage2()
{
}
//Stage3�̊���X�V�֐��B
void NPC::UpdateKanjouStage3()
{

}
void NPC::UpdateState()
{
	plpo = m_player->m_position - m_position;
	switch (npcState) {
	case haikai:
		//�p�j��Ԃ̏����B
		//@todo �n�� �����̃v���O������NPC�̜p�j�̎d���ɂ���āA�������킯�ā@��������悤��
		break;
	case tuibi:
		//�ǔ���ԁB
		//�����Ƀv���C���[�ɒǔ�����v���O�����������B
		plpo.Normalize();
		m_moveSpeed.x = plpo.x *50 ;
		m_moveSpeed.z = plpo.z *50 ;
		break;
	}
	m_position = m_charaCon.Execute(
		GameTime().GetFrameDeltaTime(),
		m_moveSpeed);
}
void NPC::Update()
{
	//����̍X�V�B
	//����Ȋ����ł����̂ł́B
	/*if (stageNo == 0) {

		UpdateKanjouStage1();
	}*/
	UpdateKanjouStage1();

	//��Ԃ��X�V�B
	UpdateState();

	//UpdateKanjou();

	CQuaternion  nprt;
	
	//���W��ݒ�B
	//���[���h�s����X�V�B
	nprt.SetRotationDeg(CVector3::AxisX, 0.0f);//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������B
	nprt.Multiply(m_rotation, nprt);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(nprt);
}
void NPC::Render(CRenderContext& rc)
{
}