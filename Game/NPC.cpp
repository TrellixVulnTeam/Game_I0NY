#include "stdafx.h"
#include "NPC.h"
#include "Level.h"
#include "MapChip.h"
#include "Game.h"
#include "Player.h"
#include "tkEngine/Sound/tkSoundSource.h"
#include "tkEngine/Sound/tkSoundEngine.h"

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
		if (plpo.Length() < 5.0f) {
			npckanjou = delighted;
			npcState = tuibi;
			m_player->SetfollowerNump();
		}
		break;
	case delighted:
		//���ł���
		if (plpo.Length() < 5.0f && npcState != tuibi)
		{
			npckanjou = delighted;
			npcState = tuibi;
			m_player->SetfollowerNump();
		}
		break;
	case angry:
		if (plpo.Length() <= 5.0f&&m_player->GetfollowerNum() >= 2 )
			//�v���C���[���A��Ă���l�������l�ȏ�ɂȂ�����A�������я�Ԃɂ���B
		{
			npckanjou = delighted;
			npcState = tuibi;
			m_player->SetfollowerNump();
		}
		else if (plpo.Length() <= 5.0f) {
			//�{���Ă���l�Ԃƃv���C���[���Ԃ������B
			//���Ă��Ă���NPC���ׂĂ̊����ύX����B
			for (int i = 0; i < m_game->m_npcList.size(); i++) {
				if(m_game->m_npcList[i]->npcState == tuibi){
					m_game->m_npcList[i]->npckanjou = flat;
					m_game->m_npcList[i]->npcState = haikai;
					m_player->SetfollowerNumm();
				}	
			}
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
	
	switch (npcState) {
	case haikai:
		//�p�j��Ԃ̏����B
		//@todo �n�� �����̃v���O������NPC�̜p�j�̎d���ɂ���āA�������킯�ā@��������悤��
		m_moveSpeed.x = 0;
		m_moveSpeed.z = 0;
		break;
	case tuibi:
		//�ǔ���ԁB
		//�����Ƀv���C���[�ɒǔ�����v���O�����������B
		plpo.Normalize();
		m_moveSpeed.x = plpo.x *50 ;
		m_moveSpeed.z = plpo.z *50 ;
		angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(CVector3::AxisY, angle);
		break;
	case osou:
		if (plpo.Length() < 60.0) {
			plpo.Normalize();
			m_moveSpeed.x = plpo.x * 40;
			m_moveSpeed.z = plpo.z * 40;
			//angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
			//m_rotation.SetRotation(CVector3::AxisY, angle);
			if (m_soundSource == nullptr) {
				m_soundSource = NewGO<prefab::CSoundSource>(0);
				m_soundSource->Init("Assets/sprite/Mic3_52.wav",true);
				m_soundSource->SetPosition(m_position);
				m_soundSource->SetVolume(1.0f);
				m_soundSource->Play(true);
			}
			else {
				m_soundSource->SetPosition(m_position);
			}
		}
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
	/*if (GetSNo->stageNo == 0) {

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