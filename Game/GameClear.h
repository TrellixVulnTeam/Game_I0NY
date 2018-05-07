#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class Test;
class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();

	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CAnimationClip m_animClip[1];					//�A�j���[�V�����N���b�v�B

	CVector3 m_pos = CVector3::Zero;
};