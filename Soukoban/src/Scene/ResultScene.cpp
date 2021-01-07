#include "ResultScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "InGameScene.h"

enum
{
	STEP_START_JINGLE,//開始ジングル待ち
	STEP_INPUT,	 //入力待ち
	STEP_CLEAR_JINGLE, //クリアジングル待ち
	STEP_END,	 //シーン終了
};

ResultScene::ResultScene()
{
	m_Step = STEP_START_JINGLE;
}

ResultScene::~ResultScene()
{

}

void ResultScene::Exec()
{
	switch (m_Step)
	{
	case STEP_START_JINGLE:
		step_Start_Jingle();
		break;
	case STEP_INPUT:
		step_Input();
		break;
	case STEP_CLEAR_JINGLE:
		step_Clear_Jingle();
		break;
	default:
		break;
	}
}

void ResultScene::Draw()
{
	//画面左上にデバッグ用の文字を黒で表示する
	//DrawString(20, 20, "ResultScene", GetColor(0, 0, 0));
	printfDx("掛かった手数：%d手", InGameScene::Count);
}

bool ResultScene::IsEnd() const
{
	return (m_Step == STEP_END);
}

//開始ジングル待ち
void ResultScene::step_Start_Jingle()
{
	m_Step = STEP_INPUT;
}

//入力受付
void ResultScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPush(KeyType_Enter))
	{
		m_Step = STEP_CLEAR_JINGLE;
	}
}

//クリアジングル待ち
void ResultScene::step_Clear_Jingle()
{
	m_Step = STEP_END;
	SceneManager::GetInstance()->SetNextScene(SceneID_Title);
}
