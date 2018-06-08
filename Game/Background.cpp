#include "stdafx.h"
#include "Background.h"
#include "StageSeni.h"


void Background::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}
bool Background::Start()
{
	StageSeni* m_ss = FindGO<StageSeni>("ss");
	//�P�X�e�[�W
	if (m_ss->GetSNo() == 0) {
		//���f�������[�h�B
		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/zimen3.cmo");
	}
	//2�X�e�[�W
	if (m_ss->GetSNo() == 1) {
		//���f�������[�h�B
		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/karisute2.cmo");
	}
	//3�X�e�[�W
	if (m_ss->GetSNo() >= 2) {
		//���f�������[�h�B
		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/karisute3.cmo");
	}
	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_phyStaticObject.CreateMeshObject(m_skinModelRender, CVector3::Zero, CQuaternion::Identity);
	return true;
}
