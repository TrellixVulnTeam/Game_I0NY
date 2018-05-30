#pragma once
//�L�����N�^�[�R���g���[���[���g�p����ꍇ�́A���L�̃w�b�_�[�t�@�C���̃C���N���[�h���K�v�B
#include "tkEngine/character/tkCharacterController.h"

class Game;
class Player;


class NPC : public IGameObject
{
private:
	void UpdateState();
public:
	NPC(); 
	~NPC();
	void OnDestroy() override;
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc);
	prefab::CSkinModelRender* m_skinModelRender;	        //�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero;                   //���W�B
	CVector3 m_moveSpeed;                                   //�ړ����x�B
	CVector3 plpo;
	CQuaternion m_rotation = CQuaternion::Identity;         //��]�B
	CCharacterController m_charaCon; 
	Game *m_game = nullptr;
	Player *m_player = nullptr;
	NPC*pNpc;



//virtual void haikai() = 0;
	float angle=0.0f;
	int flag = 0;
	enum kanjou {
		flat,             //����
		delighted,        //���
		angry,            //�{��
		sad,              //������
		pleasant,         //�y����
		kanjouNum,        //����̐�
	};
	enum state {
		haikai,			//�p�j
		tuibi,			//�ǔ��B
	};
	enum kanjou npckanjou =flat;
	enum state npcState = haikai;
private:
	void UpdateKanjouStage1();
	void UpdateKanjouStage2();
	void UpdateKanjouStage3();

};

