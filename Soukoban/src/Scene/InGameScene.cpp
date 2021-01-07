#include "InGameScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

int Direction = 0;

enum
{
	STEP_START_JINGLE,//開始ジングル待ち
	STEP_INPUT,	 //入力待ち
	STEP_CLEAR_JINGLE, //クリアジングル待ち
	STEP_END,	 //シーン終了
};

const int g_SampleStage[STAGE_HEIGHT][STAGE_WIDTH] =
{
	9, 9, 9, 1, 1, 1, 1, 1, 9, 9, 9,
	9, 9, 9, 1, 3, 3, 3, 1, 9, 9, 9,
	9, 9, 9, 1, 0, 0, 0, 1, 9, 9, 9,				//0 = 床
	9, 9, 9, 1, 0, 0, 0, 1, 9, 9, 9,				//1 = 壁
	1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,				//2 = プレイヤー初期位置
	1, 0, 0, 4, 0, 0, 1, 0, 0, 0, 1,				//3 = 目標地点
	1, 0, 1, 0, 0, 4, 0, 4, 0, 0, 1,				//4 = 目標物
	1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,				//9 = エリア外
	1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,
	9, 9, 1, 0, 1, 0, 1, 0, 1, 9, 9,
	9, 9, 1, 0, 0, 0, 0, 0, 1, 9, 9,
	9, 9, 1, 0, 0, 2, 0, 0, 1, 9, 9,
	9, 9, 1, 1, 1, 0, 1, 1, 1, 9, 9,
	9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
};

const int g_DebugStage[STAGE_HEIGHT][STAGE_WIDTH] =
{
	9, 9, 9, 1, 1, 1, 1, 1, 9, 9, 9,
	9, 9, 9, 1, 3, 3, 3, 1, 9, 9, 9,
	9, 9, 9, 1, 4, 4, 4, 1, 9, 9, 9,				//0 = 床
	9, 9, 9, 1, 0, 0, 0, 1, 9, 9, 9,				//1 = 壁
	1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1,				//2 = プレイヤー初期位置
	1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,				//3 = 目標地点
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,				//4 = 目標物
	1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,				//9 = エリア外
	1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,
	9, 9, 1, 0, 1, 0, 1, 0, 1, 9, 9,
	9, 9, 1, 0, 0, 0, 0, 0, 1, 9, 9,
	9, 9, 1, 0, 0, 0, 0, 0, 1, 9, 9,
	9, 9, 1, 1, 1, 0, 1, 1, 1, 9, 9,
	9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
};

InGameScene::InGameScene() : m_PlayerX(0), m_PlayerY(0)
{
	Tex1 = LoadGraph("block1.png");
	Tex2 = LoadGraph("block2.png");
	Tex3 = LoadGraph("block3.png");
	Tex4 = LoadGraph("block4.png");
	Tex5 = LoadGraph("block5.png");
	Chara_up = LoadGraph("歩行ドットキャラ 2.png");
	Chara_down = LoadGraph("歩行ドットキャラ 1.png");
	Chara_left = LoadGraph("歩行ドットキャラ 4.png");
	Chara_right = LoadGraph("歩行ドットキャラ 3.png");
	Crear = LoadGraph("Clear.png");

	//ステージデータを初期化
	/*
		g_SampleStageの中身を
		m_StageDataへコピー(読み込み)する
		この時、配列の中身が ObjectType_Player だったら、
		その時のx, yをm_PlayerX(Y)へ代入し、m_StageDataへは ObjectType_Ground を代入する
	*/
	Reset();

	m_Step = STEP_START_JINGLE;
}

InGameScene::~InGameScene()
{

}

void InGameScene::Exec()
{
	InputManager* pInputMng = InputManager::GetInstance();

	if (pInputMng->IsPush(KeyType_Reset))
	{
		Reset();
	}
	if (pInputMng->IsOn(KeyType_Debug) && pInputMng->IsOn(KeyType_Space) && pInputMng->IsPush(KeyType_Enter))
	{
		Debug();
	}

	if (pInputMng->IsPush(KeyType_Up))
	{
		if (m_StageData[m_PlayerY - 1][m_PlayerX] == 1 || m_StageData[m_PlayerY - 1][m_PlayerX] == 9 || m_StageData[m_PlayerY - 1][m_PlayerX] == 7)
		{

		}
		else if (m_StageData[m_PlayerY - 1][m_PlayerX] == 4)
		{

		}
		else
		{
			m_PlayerY -= 1;
		}
	}
	if (pInputMng->IsPush(KeyType_Down))
	{
		if (m_StageData[m_PlayerY + 1][m_PlayerX] == 1 || m_StageData[m_PlayerY + 1][m_PlayerX] == 9 || m_StageData[m_PlayerY + 1][m_PlayerX] == 7)
		{

		}
		else if (m_StageData[m_PlayerY + 1][m_PlayerX] == 4)
		{

		}
		else
		{
			m_PlayerY += 1;
		}
	}
	if (pInputMng->IsPush(KeyType_Right))
	{
		if (m_StageData[m_PlayerY][m_PlayerX + 1] == 1 || m_StageData[m_PlayerY][m_PlayerX + 1] == 9 || m_StageData[m_PlayerY][m_PlayerX + 1] == 7)
		{

		}
		else if (m_StageData[m_PlayerY][m_PlayerX + 1] == 4)
		{

		}
		else
		{
			m_PlayerX += 1;
		}
	}
	if (pInputMng->IsPush(KeyType_Left))
	{
		if (m_StageData[m_PlayerY][m_PlayerX - 1] == 1 || m_StageData[m_PlayerY][m_PlayerX - 1] == 9 || m_StageData[m_PlayerY][m_PlayerX - 1] == 7)
		{

		}
		else if (m_StageData[m_PlayerY][m_PlayerX - 1] == 4)
		{

		}
		else
		{
			m_PlayerX -= 1;
		}
	}
	if (pInputMng->IsPush(KeyType_Space))
	{
		Move();
	}

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

void InGameScene::Draw()
{
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			//壁描画
			if (m_StageData[y][x] == 1)
			{
				DrawExtendGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, Tex1, false);
			}
			//ゴール描画
			if (m_StageData[y][x] == 3)
			{
				DrawExtendGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, Tex2, false);
			}
			//未配置クレート描画
			if (m_StageData[y][x] == 4)
			{
				DrawExtendGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, Tex4, false);
			}
			//配置クレート描画
			if (m_StageData[y][x] == 7)
			{
				DrawExtendGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, Tex3, false);
			}
			//床描画
			if (m_StageData[y][x] == 0)
			{
				DrawExtendGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, Tex5, false);
			}
		}
	}
	//プレイヤー位置描画
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPush(KeyType_Up))
	{
		Direction = 1;
	}
	else if(pInputMng->IsPush(KeyType_Down))
	{
		Direction = 2;
	}
	else if(pInputMng->IsPush(KeyType_Left))
	{
		Direction = 3;
	}
	else if(pInputMng->IsPush(KeyType_Right))
	{
		Direction = 4;
	}
	switch (Direction)
	{
	case 0:
		DrawExtendGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_PlayerX * CHIP_WIDTH + CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT + CHIP_HEIGHT, Chara_up, TRUE);
		break;
	case 1:
		DrawExtendGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_PlayerX * CHIP_WIDTH + CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT + CHIP_HEIGHT, Chara_up, TRUE);
		break;
	case 2:
		DrawExtendGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_PlayerX * CHIP_WIDTH + CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT + CHIP_HEIGHT, Chara_down, TRUE);
		break;
	case 3:
		DrawExtendGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_PlayerX * CHIP_WIDTH + CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT + CHIP_HEIGHT, Chara_left, TRUE);
		break;
	case 4:
		DrawExtendGraph(m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_PlayerX * CHIP_WIDTH + CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT + CHIP_HEIGHT, Chara_right, TRUE);
		break;
	default:
		break;
	}

	if (IsClear() == true)
	{
		DrawGraph(151, 221, Crear, true);
		m_Step = STEP_CLEAR_JINGLE;
	}

	//画面左上にデバッグ用の文字を黒で表示する
	DrawString(20, 20, "InGameScene", GetColor(0, 0, 0));
}

bool InGameScene::IsEnd() const
{
	return (m_Step == STEP_END);
}

//開始ジングル待ち
void InGameScene::step_Start_Jingle()
{
	m_Step = STEP_INPUT;
}

//入力受付
void InGameScene::step_Input()
{
	/*InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPush(KeyType_Enter))
	{
		m_Step = STEP_CLEAR_JINGLE;
	}*/
}

void InGameScene::step_Clear_Jingle()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPush(KeyType_Enter))
	{
		m_Step = STEP_END;
		SceneManager::GetInstance()->SetNextScene(SceneID_Result);
	}
}

void InGameScene::Move()
{
	if ((m_StageData[m_PlayerY - 1][m_PlayerX] == 4) && Direction == 1)
	{
		if (m_StageData[m_PlayerY - 2][m_PlayerX] == 0)
		{
			m_StageData[m_PlayerY - 1][m_PlayerX] = 0;
			m_StageData[m_PlayerY - 2][m_PlayerX] = 4;
		}
		else if (m_StageData[m_PlayerY - 2][m_PlayerX] == 3)
		{
			m_StageData[m_PlayerY - 1][m_PlayerX] = 0;
			m_StageData[m_PlayerY - 2][m_PlayerX] = 7;
		}
	}
	if ((m_StageData[m_PlayerY + 1][m_PlayerX] == 4) && Direction == 2)
	{
		if (m_StageData[m_PlayerY + 2][m_PlayerX] == 0)
		{
			m_StageData[m_PlayerY + 1][m_PlayerX] = 0;
			m_StageData[m_PlayerY + 2][m_PlayerX] = 4;
		}
		else if (m_StageData[m_PlayerY + 2][m_PlayerX] == 3)
		{
			m_StageData[m_PlayerY + 1][m_PlayerX] = 0;
			m_StageData[m_PlayerY + 2][m_PlayerX] = 7;
		}
	}
	if ((m_StageData[m_PlayerY][m_PlayerX + 1] == 4) && Direction == 4)
	{
		if (m_StageData[m_PlayerY][m_PlayerX + 2] == 0)
		{
			m_StageData[m_PlayerY][m_PlayerX + 1] = 0;
			m_StageData[m_PlayerY][m_PlayerX + 2] = 4;
		}
		else if (m_StageData[m_PlayerY][m_PlayerX + 2] == 3)
		{
			m_StageData[m_PlayerY][m_PlayerX + 1] = 0;
			m_StageData[m_PlayerY][m_PlayerX + 2] = 7;
		}
	}
	if ((m_StageData[m_PlayerY][m_PlayerX - 1] == 4) && Direction == 3)
	{
		if (m_StageData[m_PlayerY][m_PlayerX - 2] == 0)
		{
			m_StageData[m_PlayerY][m_PlayerX - 1] = 0;
			m_StageData[m_PlayerY][m_PlayerX - 2] = 4;
		}
		else if (m_StageData[m_PlayerY][m_PlayerX - 2] == 3)
		{
			m_StageData[m_PlayerY][m_PlayerX - 1] = 0;
			m_StageData[m_PlayerY][m_PlayerX - 2] = 7;
		}
	}
	IsClear();
}

bool InGameScene::IsClear() const
{
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			if (m_StageData[y][x] == 4)
			{
				return false;
			}
		}
	}
	
	return true;
}

void InGameScene::Reset()
{
	Direction = 1;
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			m_StageData[y][x] = g_SampleStage[y][x];
			if (m_StageData[y][x] == ObjectType_Player)
			{
				m_PlayerX = x;
				m_PlayerY = y;
				m_StageData[y][x] = ObjectType_Ground;
			}
		}
	}
}

void InGameScene::Debug()
{
	Direction = 1;
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			m_StageData[y][x] = g_DebugStage[y][x];
			if (m_StageData[y][x] == ObjectType_Player)
			{
				m_PlayerX = x;
				m_PlayerY = y;
				m_StageData[y][x] = ObjectType_Ground;
			}
		}
	}
}