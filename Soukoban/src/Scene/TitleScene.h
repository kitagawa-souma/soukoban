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

	virtual bool IsEnd() const; //シーンが終了したかどうかを返す

private:
	//タイトルロ入場
	void step_LogoIn();
	//入力受付
	void step_Input();
};

#endif // !TITLESCENE_H