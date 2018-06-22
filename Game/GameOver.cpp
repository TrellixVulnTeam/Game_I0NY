#include "stdafx.h"
#include "GameOver.h"
#include "Player.h"
#include "Title.h"
#include "Fade.h"
#include "StageSeni.h"
#include "Game.h"

GameOver::GameOver()
{
}


GameOver::~GameOver()
{


}
bool GameOver::Start()
{
	pl = FindGO<Player>("Player");
	game = FindGO<Game>("Game");
	m_fade = FindGO<Fade>("Fade");
	m_ss = FindGO<StageSeni>("ss");
	
	position =pl->GetPosition();
	return true;
}
void GameOver::Update()
{
	taim++;
	
				
	if (taim <= 60) {
		if (GOflag == true) {
			m_ss->SetGameOver();
			CQuaternion kaku = pl->GetRotation();
			CQuaternion kakud;
			kakud.SetRotationDeg(CVector3::AxisY, 100.0f);
			kaku.Multiply(kakud);
			pl->Setrotation(kaku);
		}
	}
	else {
		 a = 1;
		//�t�F�[�h�A�E�g
		if (m_isWaitFadeout) {
			if (!m_fade->IsFade()) {
				DeleteGO(game);
				DeleteGO(this);
				NewGO<Title>(0, "Title");
			}
		}
		else {
			if (a == 1) {
				m_isWaitFadeout = true;
				m_fade->StartFadeOut();
			}
		}
		//�����Ƀt�F�[�h��^�C�g���Ȃǂ��ǂ���
	}
}
