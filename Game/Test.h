#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"

class Fade;
class NPC;
class Test : public IGameObject
{
public:
	Test();
	~Test();
	bool Start();
	void Update();
private:
	enum EnState {
		enState_FadeIn,	//!<�t�F�[�h�C�����B
		enState_InGame,	//!<�C���Q�[�����B
	};
	bool m_isWaitFadeout = false;
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	//CAnimationClip m_animClip[1];							//�A�j���[�V�����N���b�v�B
	//CAnimation m_animation;
	CVector3 m_pos = CVector3::Zero;
	EnState m_state = enState_FadeIn;
	Fade* m_fade = nullptr;
	NPC * m_npc = nullptr;
};


