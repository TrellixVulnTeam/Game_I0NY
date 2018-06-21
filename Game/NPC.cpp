#include "stdafx.h"
#include "NPC.h"
#include "Level.h"
#include "MapChip.h"
#include "Game.h"
#include "Player.h"
#include "NpcMove.h"
#include "StageSeni.h"
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
	DeleteGO(effect);
}

bool NPC::Start()
{
	//m_npcMove.SetmoveSpeed(m_moveSpeed);
	int npcCflag = 1;
	m_game = FindGO<Game>("Game");
	m_player = FindGO<Player>("Player");
	//�G�t�F�N�g���쐬�B
	effect = NewGO<prefab::CEffect>(0);
	m_position.y = 0;
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_charaCon.Init(
		4.0,			//���a�B 
		100.0f,			//�����B
		m_position, 	//�����ʒu�B
		1
	);
	m_npcMove.SetPosition(m_position);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f });
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetShadowReceiverFlag(true);
//	effect->Play(L"effect/oko.efk");
	//@todo �X�e�[�W�ɂ���āA�������銴��R���g���[���̃C���X�^���X��؂�ւ���悤��.

	return true;
}

void NPC::Effect(CVector3 npcpos, CQuaternion npcrot)
{
	switch (npckanjou)
	{
	case delighted:
		//�G�t�F�N�g���Đ��B
		if (effect->IsPlay() == false) {
			effect = NewGO<prefab::CEffect>(0);
			effect->Play(L"effect/tanosii.efk");
		}
		effect->SetPosition(npcpos);
		effect->SetRotation(npcrot);
		break;
	case angry:
		if (effect->IsPlay() == false) {
			//�G�t�F�N�g���Đ��B
			effect = NewGO<prefab::CEffect>(0);
			effect->Play(L"effect/oko.efk");
		}
		effect->SetPosition(npcpos);
		effect->SetRotation(npcrot);
		break;
	}
}

void NPC::UpdateKanjouStage1()
{
	
	plpo = m_player->GetPosition() - m_position;


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
		if (plpo.Length() < 40.0f)
		{
			npcState = osou;
		}
		else
		{
			npcState = haikai;
		}
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
					m_player->Setplkan(true);
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
	movetime++;
	switch (npcState) {
	case haikai:
		//�p�j��Ԃ̏����B
		//@todo �n�� �����̃v���O������NPC�̜p�j�̎d���ɂ���āA�������킯�ā@��������悤��
		//�����ړ�

		//�����_���ړ�
		m_moveSpeed.z = m_npcMove.RandomMoveZ();
		m_moveSpeed.x = m_npcMove.RandomMoveX();
		if (m_charaCon.GetisHitWall() == true && movetime < 10) {
			m_moveSpeed.z *= -1;
			m_moveSpeed.x *= -1;
		}

		plpo.Normalize();
		if (m_moveSpeed.z < 0.0f || m_moveSpeed.x < 0.0f)
		{
			sevo = rand() % 3 + 1;
			switch (sevo)
			{
			case 1:
				if (m_soundSource == nullptr && plpo.Length() < 120.0f) {
					m_soundSource = NewGO<prefab::CSoundSource>(0);
					m_soundSource->Init("Assets/sprite/jyunkai01.wav");
					m_soundSource->SetPosition(m_position);
					m_soundSource->SetVolume(1.0f);
					m_soundSource->Play(false);
				}
				sevo = 0;
				break;
			case 2:
				if (m_soundSource == nullptr && plpo.Length() < 120.0f) {
					m_soundSource = NewGO<prefab::CSoundSource>(0);
					m_soundSource->Init("Assets/sprite/jyunkai02.wav");
					m_soundSource->SetPosition(m_position);
					m_soundSource->SetVolume(1.0f);
					m_soundSource->Play(false);
				}
				sevo = 0;
				break;
			case 3:
				if (m_soundSource == nullptr && plpo.Length() < 120.0f) {
					m_soundSource = NewGO<prefab::CSoundSource>(0);
					m_soundSource->Init("Assets/sprite/jyunkai03.wav");
					m_soundSource->SetPosition(m_position);
					m_soundSource->SetVolume(1.0f);
					m_soundSource->Play(false);
				}
				sevo = 0;
				break;
			}
		}


		break;
	case tuibi:
		//�ǔ���ԁB
		//�����Ƀv���C���[�ɒǔ�����v���O�����������B
		plpo.Normalize();
		m_moveSpeed.x = plpo.x *60.0f;
		m_moveSpeed.z = plpo.z *60.0f;
		break;
	case osou:
		if (plpo.Length() > 50.0f) {

			//�����_���ړ�
			m_moveSpeed.z = m_npcMove.RandomMoveZ();
			m_moveSpeed.x = m_npcMove.RandomMoveX();
			if (m_charaCon.GetisHitWall() == true && movetime < 10) {
				m_moveSpeed.z *= -1;
				m_moveSpeed.x *= -1;
			}
		}
		else {

			plpo.Normalize();
			m_moveSpeed.x = plpo.x * 30.0f;
			m_moveSpeed.z = plpo.z * 30.0f;

			switch (osouvo)
			{
			case 1:
				if (m_soundSource2 == nullptr) {
					m_soundSource2 = NewGO<prefab::CSoundSource>(0);
					m_soundSource2->Init("Assets/sprite/Mic3_52.wav");
					m_soundSource2->SetPosition(m_position);
					m_soundSource2->SetVolume(2.0f);
					m_soundSource2->Play(false);
				}
				else
					m_soundSource->SetPosition(m_position);
				osouvo = rand() % 3 + 1;
				break;
			case 2:
				if (m_soundSource2 == nullptr) {
					m_soundSource2 = NewGO<prefab::CSoundSource>(0);
					m_soundSource2->Init("Assets/sprite/osou01.wav");
					m_soundSource2->SetPosition(m_position);
					m_soundSource2->SetVolume(2.0f);
					m_soundSource2->Play(false);
				}
				else
					m_soundSource->SetPosition(m_position);
				osouvo = rand() % 3 + 1;
				break;
			case 3:
				if (m_soundSource2 == nullptr) {
					m_soundSource2 = NewGO<prefab::CSoundSource>(0);
					m_soundSource2->Init("Assets/sprite/osou02.wav");
					m_soundSource2->SetPosition(m_position);
					m_soundSource2->SetVolume(2.0f);
					m_soundSource2->Play(false);
				}
				else
					m_soundSource2->SetPosition(m_position);
				osouvo = rand() % 3 + 1;
				break;
			}
		}
		break;
	}

	m_moveSpeed.y -= 980.0f*GameTime().GetFrameDeltaTime();
	angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotation(CVector3::AxisY, angle);
	m_position = m_charaCon.Execute(
		GameTime().GetFrameDeltaTime(),
		m_moveSpeed
	);
}
void NPC::Update()
{
	//����̍X�V�B
	//����Ȋ����ł����̂ł́B
	if (m_stagesni->GetSNo() == 0) {

		UpdateKanjouStage1();
		}
	

	UpdateKanjouStage1();

	//��Ԃ��X�V�B
	UpdateState();

	//�G�t�F�N�g�Đ��B
	Effect(m_position, m_rotation);

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