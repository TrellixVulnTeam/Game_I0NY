#pragma once

class Player;
class Fade;
class Title;
class StageSeni:public IGameObject
{
public:
	StageSeni();
	~StageSeni();
	int GetSNo() 
	{
		return StageNo;
	}
	void SetSNo()
	{
		if (StageNo <= 1) {
			StageNo += 1;
		}
		else {
			StageNo = 0;
		}
	}
	void SetGameOver() 
	{
		StageNo = 0;
	}
private:
	//�X�e�[�W�J�ڂ̔ԍ�
	int StageNo = 0;
};
	

