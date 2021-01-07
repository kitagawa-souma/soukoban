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

	virtual bool IsEnd() const; //シーンが終了したかどうかを返す

private:
	//タイトルロ入場
	void step_Start_Jingle();
	//入力受付
	void step_Input();
	//クリアジングル待ち
	void step_Clear_Jingle();
};

#endif // !RESULTSCENE_H
