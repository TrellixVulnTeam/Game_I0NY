#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "Level.h"


class Fade;
class StageSeni;
class Background;
class Player;
class GameCamera;
class NPC;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void OnDestroy();
	void Render(CRenderContext& rc);
	Level m_level;		//���x���B
	//modelData m_modelData;
	const CLocData& GetLocData()
	{
		return locData;
	}
private:
	enum EnState {
		enState_FadeIn,	//!<�t�F�[�h�C�����B
		enState_InGame,	//!<�C���Q�[�����B
	};
	bool m_isWaitFadeout = false;
	CVector3 m_pos = CVector3::Zero;
	EnState m_state = enState_FadeIn;
	Fade* m_fade = nullptr;
	Player*m_player = nullptr;
	Background* m_background = nullptr;
	GameCamera*m_gameCamera = nullptr;
	std::vector<NPC*>	m_npcList;	//NPC�̉ϒ��z��B
	StageSeni* m_ss = nullptr;
	CLocData locData;
};
