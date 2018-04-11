#include "stdafx.h"
#include "MapChip.h"




void MapChip::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}
void MapChip::Init(
	const wchar_t* modelFilePath,
	CVector3 pos,
	CVector3 scale,
	CQuaternion rotation
) {
	m_position = pos;
	m_rotation = rotation;
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(modelFilePath);
	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_physicsStaticObject.CreateMeshObject(m_skinModelRender, m_position, m_rotation);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}
