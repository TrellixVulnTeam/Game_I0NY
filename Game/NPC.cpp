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
	int npcCflag = 1;
	m_game = FindGO<Game>("Game");
	m_player = FindGO<Player>("Player");

	
	m_position.y=0;
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

	return true;
}

void NPC::Update()
{
	CVector3  plpo;
	CQuaternion  nprt;
	
	plpo = m_player->m_position - m_position;


	switch (npckanjou)
	{
	case flat:
		if (plpo.Length() > 50.0f&&flag == 0) {
			m_moveSpeed.x = 0;
			m_moveSpeed.z = 0;
		}
		else if (plpo.Length() > 50.0f&&flag == 1) {

			flag = 0;
		}
		else if (plpo.Length() < 50.0f) {
			npckanjou = delighted;
			m_player->SetfollowerNump();
		}

		break;
	case delighted:
		if (plpo.Length() < 50.0f) {
			plpo.Normalize();
			m_moveSpeed.x = plpo.x * 50;
			m_moveSpeed.z = plpo.z * 50;
		}
		if (plpo.Length() > 50.0f) {
			npckanjou = flat;
			m_player->SetfollowerNumm();
		}
		m_moveSpeed.y -= 980.0f*GameTime().GetFrameDeltaTime();
		m_position = m_charaCon.Execute(
			GameTime().GetFrameDeltaTime(),
			m_moveSpeed
		);
		angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(CVector3::AxisY, angle);
		break;
	}
		
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