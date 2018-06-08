#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "Level.h"


class Fade;
class StageSeni;
class Background;
class Player;
class GameCamera;
class NPC;

enum kanjou {
	flat,             //����
	delighted,        //���
	angry,            //�{��
	sad,              //������
	pleasant,         //�y����
	kanjouNum,        //����̐�
};

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
	std::vector<NPC*>	m_npcList;	//NPC�̉ϒ��z��B

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
	prefab::CSoundSource* m_soundSource = nullptr;
	Background* m_background = nullptr;
	GameCamera*m_gameCamera = nullptr;
	prefab::CDirectionLight* m_sunLig = nullptr;
	StageSeni* m_ss = nullptr;
	CLocData locData;
	int counter = 0;
};
