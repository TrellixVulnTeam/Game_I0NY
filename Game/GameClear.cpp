#include "stdafx.h"
#include "GameClear.h"
#include "Game.h"
#include "Player.h"
#include "StageSeni.h"
#include "Title.h"

GameClear::GameClear()
{
}
GameClear::~GameClear()
{
}
void GameClear::OnDestroy()
{
}
bool GameClear::Start()
{
	m_fade = FindGO<Fade>("Fade");
	pl = FindGO<Player>("Player");
	m_ss = FindGO<StageSeni>("ss");
	game = FindGO<Game>("Game");
	//エフェクトを作成。
	m_effect = NewGO<prefab::CEffect>(0);
	return true;
}
void GameClear::Update()
{
	
	Gtime++;
	CQuaternion qRot;
	qRot = pl->GetRotation();
	m_pos = pl->GetPosition();
	if (pl->Getef_flag() == 0) {
		pl->Setef_flag();
		
		//エフェクトを再生。
		m_effect->Play(L"effect/hanabi.efk");
		CVector3 emitPos = m_pos;
		emitPos.y += 30.0f;
		m_effect->SetPosition(emitPos);
		m_effect->SetRotation(qRot);
		
	}
	else if (pl->Getef_flag() == 1 && Gtime > 90) {
		//m_ss->SetSNo();
		m_ss->SetGameOver();
		pl->Setef_flag();
		DeleteGO(this);
	}

	//フェードアウト
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Title>(0, "Title");
			DeleteGO(game);
			DeleteGO(this);
		}
	}
	else {
		if (pl->Getef_flag() == 2) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
}