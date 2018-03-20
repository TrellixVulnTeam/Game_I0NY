#include "stdafx.h"
#include "GameClearControl.h"
#include "Game.h"
#include "Fade.h"

GameClearControl::GameClearControl()
{
}
GameClearControl::~GameClearControl()
{
}
void GameClearControl::Awake()
{
}
bool GameClearControl::Start()
{
	return true;
}
void GameClearControl::Update()
{
	if (!m_isWaitFade) {
		m_timer += GameTime().GetFrameDeltaTime();
		//�X�R�A���ړ�������B

		if (m_timer > 3.0f) {
			//�Q�[���I���B
			m_isEnd = true;
		}
		if (m_isEnd &&
			Pad(0).IsPress(enButtonA)) {
			m_isWaitFade = true;
			FindGO<Fade>("Fade")->StartFadeOut();
		}
	}
	else {
		if (!FindGO<Fade>("Fade")->IsFade()) {
			DeleteGO(m_game);
		}
	}

}
void GameClearControl::OnDestroy()
{
}
void GameClearControl::PostRender(CRenderContext& rc)
{
	if (m_isEnd) {
		//press any key��\���B
		m_font.Begin(rc);
		m_font.Draw(L"PRESS ANY KEY", CVector2::Zero, CVector4::Yellow);
		m_font.End(rc);
	}
}