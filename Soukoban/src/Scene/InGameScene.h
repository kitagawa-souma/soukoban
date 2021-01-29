#ifndef INGAMESCENE_H
#define INGAMESCENE_H

#include"SceneBase.h"
#include "../Definition.h"

enum DirType
{
	DirType_Up,		//��
	DirType_Down,	//��
	DirType_Left,	//��
	DirType_Right,	//�E

	DirType_Max,	//�摜�ǂݍ��݂Ŏg�p����
};

class InGameScene : public SceneBase
{
public:
	InGameScene();
	virtual ~InGameScene();

	static int Count;

public:
	void Exec();
	void Draw();

	virtual bool IsEnd() const; //�V�[�����I���������ǂ������Ԃ�

private:
	//�J�n�W���O���҂�
	void step_Start_Jingle();
	//���͎��t
	void step_Input();
	//�N���A�W���O���҂�
	void step_Clear_Jingle();

	//�q�ɔԂɊ֌W�����֐��Q
private:
	//�N���A����
	bool IsClear() const;
	//���Z�b�g
	void Reset();
	//�f�o�b�O���Z�b�g
	void Debug();
	//�ړ�����
	void Move();

private:
	int m_StageData[STAGE_HEIGHT][STAGE_WIDTH];
	int m_PlayerX;	//�z������X
	int m_PlayerY;	//�z������Y

	int next_x;
	int next_y;
	int next2_x;
	int next2_y;

	int Tex1;
	int Tex2;
	int Tex3;
	int Tex4;
	int Tex5;
	int Chara_up;
	int Chara_down;
	int Chara_left;
	int Chara_right;
	int Crear;

};



#endif // !INGAMESCENE_H
