#ifndef RESULTSCENE_H
#define RESULTSCENE_H

#include"SceneBase.h"

class ResultScene : public SceneBase
{
public:
	ResultScene();
	~ResultScene();
public:
	void Exec();
	void Draw();

	virtual bool IsEnd() const; //�V�[�����I���������ǂ�����Ԃ�

private:
	//�^�C�g��������
	void step_Start_Jingle();
	//���͎�t
	void step_Input();
	//�N���A�W���O���҂�
	void step_Clear_Jingle();
};

#endif // !RESULTSCENE_H
