#pragma once
//�L�����N�^�[�R���g���[���[���g�p����ꍇ�́A���L�̃w�b�_�[�t�@�C���̃C���N���[�h���K�v�B
#include "tkEngine/character/tkCharacterController.h"
#include "NpcMove.h"
#include "Game.h"
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
	CVector3 plpo;                                          //NPC��Player�̋����B
	CQuaternion m_rotation = CQuaternion::Identity;         //��]�B
	CCharacterController m_charaCon; 
	NpcMove m_npcMove;

	Game *m_game = nullptr;
	Player *m_player = nullptr;
	prefab::CSoundSource* m_soundSource = nullptr;
	prefab::CSoundSource* m_soundSource2 = nullptr;
	NPC*pNpc;
	int soundflag = 0;
	bool HitWall = false;
	int movetime = 0;

	float angle= 0.0f;
	int flag = 0;
	int sevo = 0;
	int osouvo = rand() % 3 + 1;
	
	enum state {
		haikai,			//�p�j
		tuibi,			//�ǔ��B
		osou,           //�P���B
	};
	enum kanjou npckanjou =flat;
	enum state npcState = haikai;
private:
	void UpdateKanjouStage1();
	void UpdateKanjouStage2();
	void UpdateKanjouStage3();

};

