#ifndef TITLESCENE_H
#define TITLESCENE_H

#include"SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();
public:
	void Exec();
	void Draw();

	virtual bool IsEnd() const; //�V�[�����I���������ǂ�����Ԃ�

private:
	//�^�C�g��������
	void step_LogoIn();
	//���͎�t
	void step_Input();
};

#endif // !TITLESCENE_H