#pragma once
class Fade;
class StageSeni;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void PostRender(CRenderContext& rc) override;
private:
	//�t�F�C�h�A�E�g�@�Q�[��
	bool m_isWaitFadeout = false;
	//�t�F�C�h�A�E�g�@�e�X�g
	bool m_isWaitFadeout2 = false;
	CShaderResourceView m_texture;
	CSprite m_sprite;
	Fade* m_fade = nullptr;
	StageSeni* m_ss = nullptr;
	CFont m_font;
	float m_intiBgmVolume = 0.0f;
};


