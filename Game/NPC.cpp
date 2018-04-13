#include "stdafx.h"
#include "NPC.h"
#include "Level.h"
#include "MapChip.h"
#include "Game.h"
#include "Test.h"
#include "Player.h"


NPC::NPC()
{
}


NPC::~NPC()
{
}

void NPC::OnDestroy()
{
	for (i = 0; i < m_game->m_level.m_mapChipList.size(); i++) {
		DeleteGO(m_skinModelRender[i]);
	}
}

bool NPC::Start()
{
	//NPC�z�u�̃R�[�h
	m_game = FindGO<Game>("Game");
	m_player = FindGO<Player>("Player");
	std::list<MapChip*>::iterator a= m_game->m_level.itr;
	int h = 1;
	for (i = 0; i < m_game->m_level.m_mapChipList.size(); i++) {
		MapChip* f = *a;
		m_position[i] = f->m_position;
		m_position[i].y += 30.0;
		m_position[i].x += h;
		m_skinModelRender[i] = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender[i]->Init(L"modelData/unityChan.cmo");
		//�L�����N�^�[�R���g���[���[���������B
		m_charaCon[i].Init(
			4.0,			//���a�B 
			6.0f,			//�����B
			m_position[i] 	//�����ʒu�B
		);
		m_skinModelRender[i]->SetPosition(m_position[i]);
		m_skinModelRender[i]->SetScale({ 0.1f, 0.1f, 0.1f });
		h += 1;
		a++;
	}
	return true;
}

void NPC::Update()
{
	CVector3 plp[30];
	CQuaternion qRot[30];
	for (i = 0; i < m_game->m_level.m_mapChipList.size(); i++) {
		m_moveSpeed[i].y -= 980.0f * GameTime().GetFrameDeltaTime();
		plp[i] = m_player->m_position - m_position[i];
		if (plp[i].Length() < 100.0f) {
			plp[i].Normalize();
			m_moveSpeed[i].x = plp[i].x * 50;
			m_moveSpeed[i].z = plp[i].z * 50;
			//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
			//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
			//atan2���g�p���āA�p�x�����߂Ă���B
			//���ꂪ��]�p�x�ɂȂ�B
			angle[i] = atan2(m_moveSpeed[i].x, m_moveSpeed[i].z);
			//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
			//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
			m_rotation[i].SetRotation(CVector3::AxisY, angle[i]);
		}
		m_position[i] = m_charaCon[i].Execute(
			GameTime().GetFrameDeltaTime(),
			m_moveSpeed[i]
		);
		//���W��ݒ�B
		//���[���h�s����X�V�B
		qRot[i].SetRotationDeg(CVector3::AxisX, 0.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������B
		qRot[i].Multiply(m_rotation[i], qRot[i]);
		m_skinModelRender[i]->SetPosition(m_position[i]);
		m_skinModelRender[i]->SetRotation(qRot[i]);
	}
}

void NPC::Render(CRenderContext& rc)
{
}