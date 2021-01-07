#ifndef INGAMESCENE_H
#define INGAMESCENE_H

#include"SceneBase.h"
#include "../Definition.h"

enum DirType
{
	DirType_Up,		//上
	DirType_Down,	//下
	DirType_Left,	//左
	DirType_Right,	//右

	DirType_Max,	//画像読み込みで使用する
};

class InGameScene : public SceneBase
{
public:
	InGameScene();
	virtual ~InGameScene();
public:
	void Exec();
	void Draw();

	virtual bool IsEnd() const; //シーンが終了したかどうかを返す

private:
	//開始ジングル待ち
	void step_Start_Jingle();
	//入力受付
	void step_Input();
	//クリアジングル待ち
	void step_Clear_Jingle();

	//倉庫番に関係する関数群
private:
	//クリア判定
	bool IsClear() const;
	//リセット
	void Reset();
	//デバッグリセット
	void Debug();
	//移動処理
	void Move();

private:
	int m_StageData[STAGE_HEIGHT][STAGE_WIDTH];
	int m_PlayerX;	//配列上のX
	int m_PlayerY;	//配列上のY

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
