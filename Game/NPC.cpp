#include "stdafx.h"
#include "NPC.h"
#include "Level.h"
#include "MapChip.h"
#include "Game.h"


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
	//NPC�z�u�̃R�[�h
	/*Game *m_game = FindGO<Game>("Game");
	MapChip* a = *m_game->m_level.itr;
	m_position=a->m_position;
	m_position.y += 30.0;*/
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f });
	return true;
}

void NPC::Update()
{
	//�㉺���E�̃L�[���͂ɂ��ړ������B
	if (Pad(0).IsPress(enButtonRight)) {
		m_position.x -= 5.0f;
	}
	else if (Pad(0).IsPress(enButtonLeft)) {
		m_position.x += 5.0f;
	}
	else if (Pad(0).IsPress(enButtonUp)) {
		m_position.y += 5.0f;
	}
	else if (Pad(0).IsPress(enButtonDown)) {
		m_position.y -= 5.0f;
	}
	//���W��ݒ�B
	m_skinModelRender->SetPosition(m_position);
}

void NPC::Render(CRenderContext& rc)
{
}