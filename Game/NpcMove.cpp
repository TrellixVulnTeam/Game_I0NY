#include "stdafx.h"
#include "NpcMove.h"
#include <time.h>
//#include "NPC.h"

NpcMove::NpcMove()
{
	//m_position = m_npc->m_position;
}

NpcMove::~NpcMove()
{
}
	

//�����ړ�
float NpcMove::RoundTripMove()
{
	timer++;
	m_moveSpeed = m_position;
	m_moveSpeed.y = 0.0f;
		m_moveSpeed.Normalize();
		if (timer > 0 && timer <= 20) {
			//�ړ��̕��������߂�B
			m_position.x += m_moveSpeed.x * fugou;
			if (timer == 20) {
				//�ړ������ϊ�
				fugou *= -1;
				//�ȈՃ^�C�}�[���Z�b�g
				timer = 0;
			}
		}
		//�ړ��̌v�Z��Ԃ��B
		return m_moveSpeed.x * 100.0f * fugou;
}

//�����_���ړ�X��
float NpcMove::RandomMoveX()
{
	timer++;
	m_moveSpeed = m_position;
	m_moveSpeed.Normalize();
	if (randomX == 1 || randomX == 5 || randomX == 9) {
		if (timer > 0 && timer <= 7) {
			//�ړ��̌���
			fugou = 1;
			//�ړ��̕��������߂�B
			m_position.x += m_moveSpeed.x * fugou;
			if (timer == 7) {
				//�ȈՃ^�C�}�[���Z�b�g
				timer = 0;
				//1�`9�̗����擾
				randomX = rand() % 9 + 1;
			}
		}
	}
	if (randomX == 2 || randomX == 4 || randomX == 7) {
		if (timer > 0 && timer <= 7) {
			//�ړ��̌���
			fugou = -1;
			//�ړ��̕��������߂�B
			m_position.x += m_moveSpeed.x * fugou;
			if (timer == 7) {
				//�ȈՃ^�C�}�[���Z�b�g
				timer = 0;
				//1�`9�̗����擾
				randomX = rand() % 9 + 1;
			}
		}
	}
	if (randomX == 3 || randomX == 6 || randomX == 8) {

		if (timer > 0 && timer <= 7) {
			//�ړ��̌���
			fugou = 0;
			//�ړ��̕��������߂�B
			m_position.x += m_moveSpeed.x * fugou;
			if (timer == 7) {
				//�ȈՃ^�C�}�[���Z�b�g
				timer = 0;
				//1�`9�̗����擾
				randomX = rand() % 9 + 1;
			}
		}
	}
	//�ړ��̌v�Z��Ԃ��B
	return m_moveSpeed.x * 100.0 * fugou;
}

//�����_���ړ�Z��
float NpcMove::RandomMoveZ()
{
	timer2++;
	m_moveSpeed = m_position;
	m_moveSpeed.Normalize();
	if (randomZ == 1 || randomZ == 5 || randomZ == 9) {
		if (timer2 > 0 && timer2 <= 7) {
			//�ړ��̌���
			fugou = 1;
			//�ړ��̕��������߂�B
			m_position.z += m_moveSpeed.z * fugou;
			if (timer2 == 7) {
				//�ȈՃ^�C�}�[���Z�b�g
				timer2 = 0;
				//1�`9�̗����擾
				randomZ = rand() % 9 + 1;
			}
		}
	}
	if (randomZ == 2 || randomZ == 6 || randomZ == 7) {
		if (timer2 > 0 && timer2 <= 7) {
			//�ړ��̌���
			fugou = -1;
			//�ړ��̕��������߂�B
			m_position.z += m_moveSpeed.z * fugou;
			if (timer2 == 7) {
				//�ȈՃ^�C�}�[���Z�b�g
				timer2 = 0;
				//1�`9�̗����擾
				randomZ = rand() % 9 + 1;
			}
		}
	}
	if (randomZ == 3 || randomZ == 4 || randomZ == 8) {

		if (timer2 > 0 && timer2 <= 7) {
			//�ړ��̌���
			fugou = 0;
			//�ړ��̕��������߂�B
			m_position.z += m_moveSpeed.z * fugou;
			if (timer2 == 7) {
				//�ȈՃ^�C�}�[���Z�b�g
				timer2 = 0;
				//1�`9�̗����擾
				randomZ = rand() % 9 + 1;
			}
		}
	}
	//�ړ��̌v�Z��Ԃ��B
	return m_moveSpeed.z * 100.0 * fugou;
}

