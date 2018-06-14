#include "stdafx.h"
#include "Background.h"
#include "StageSeni.h"


void Background::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}
bool Background::Start()
{
	//�s�N�Z���V�F�[�_�[�����[�h�B
	
	m_psShader.Load("shader/model.fx", "PSSkyMain", CShader::EnType::PS);
	StageSeni* m_ss = FindGO<StageSeni>("ss");
	//�P�X�e�[�W
	if (m_ss->GetSNo() == 0) {
		//���f�������[�h�B
		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/saisyo.cmo");
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
	m_skinModelRender->FindMaterial([&](auto mat) {
		if (mat->EqualMaterialName( L"sky" ) == true ) {
			mat->SetRender3DModelPSShader(m_psShader);
		}
	});
	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_phyStaticObject.CreateMeshObject(m_skinModelRender, CVector3::Zero, CQuaternion::Identity);
	m_skinModelRender->SetShadowReceiverFlag(true);
	return true;
}
