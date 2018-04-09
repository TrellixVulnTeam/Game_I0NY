#pragma once
class NPC : public IGameObject
{
public:
	NPC(); 
	~NPC();
	void OnDestroy() override;
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc);
	////////////////////////////////////
	// �����o�ϐ��Ƃ�
	////////////////////////////////////
	//enum EnAnimationClip {
	//	enAnimationClip_idle,	//�ҋ@�A�j���[�V�����B
	//	enAnimationClip_run,	//����A�j���[�V�����B
	//	enAnimationClip_walk,	//�����A�j���[�V�����B
	//	enAnimationClip_num,	//�A�j���[�V�����N���b�v�̑����B
	//};
	//CAnimationClip m_animationClip[enAnimationClip_num];	//�A�j���[�V�����N���b�v�B
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero;	//���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	//CCharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B
	CVector3 m_moveSpeed = CVector3::Zero;	//�ړ����x�B
};

