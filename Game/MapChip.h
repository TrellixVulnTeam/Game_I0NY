#pragma once

#include "tkEngine/physics/tkPhysicsStaticObject.h"

class MapChip : public IGameObject
{
public:
	void OnDestroy() override;
	void Init(
		const wchar_t* modelFilePath,
		CVector3 pos,
		CVector3 scale,
		CQuaternion rotation
	);


	//////////////////////////////////////////////////
	// �������烁���o�ϐ��B
	//////////////////////////////////////////////////
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CPhysicsStaticObject m_physicsStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B
	CVector3 m_position;				//!<���W�B
	CQuaternion m_rotation;				//!<��]�B
};



