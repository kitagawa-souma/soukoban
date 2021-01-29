#include "InGameScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

int Direction = 0;
int InGameScene::Count = 0;

enum
{
	STEP_START_JINGLE,//�J�n�W���O���҂�
	STEP_INPUT,	 //���͑҂�
	STEP_CLEAR_JINGLE, //�N���A�W���O���҂�
	STEP_END,	 //�V�[���I��
};

const int g_SampleStage[STAGE_HEIGHT][STAGE_WIDTH] =
{
	9, 9, 9, 1, 1, 1, 1, 1, 9, 9, 9,
	9, 9, 9, 1, 3, 3, 3, 1, 9, 9, 9,
	9, 9, 9, 1, 0, 0, 0, 1, 9, 9, 9,				//0 = ��
	9, 9, 9, 1, 0, 0, 0, 1, 9, 9, 9,				//1 = ��
	1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,				//2 = �v���C���[�����ʒu
	1, 0, 0, 4, 0, 0, 1, 0, 0, 0, 1,				//3 = �ڕW�n�_
	1, 0, 1, 0, 0, 4, 0, 4, 0, 0, 1,				//4 = �ڕW��
	1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,				//9 = �G���A�O
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
	9, 9, 9, 1, 4, 4, 4, 1, 9, 9, 9,				//0 = ��
	9, 9, 9, 1, 0, 0, 0, 1, 9, 9, 9,				//1 = ��
	1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1,				//2 = �v���C���[�����ʒu
	1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,				//3 = �ڕW�n�_
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,				//4 = �ڕW��
	1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,				//9 = �G���A�O
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
	Chara_up = LoadGraph("���s�h�b�g�L���� 2.png");
	Chara_down = LoadGraph("���s�h�b�g�L���� 1.png");
	Chara_left = LoadGraph("���s�h�b�g�L���� 4.png");
	Chara_right = LoadGraph("���s�h�b�g�L���� 3.png");
	Crear = LoadGraph("Clear.png");

	//�X�e�[�W�f�[�^��������
	/*
		g_SampleStage�̒��g��
		m_StageData�փR�s�[(�ǂݍ���)����
		���̎��A�z���̒��g�� ObjectType_Player ���������A
		���̎���x, y��m_PlayerX(Y)�֑������Am_StageData�ւ� ObjectType_Ground ����������
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
			Count++;
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
			Count++;
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
			Count++;
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
			Count++;
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
			//�Ǖ`��
			if (m_StageData[y][x] == 1)
			{
				DrawExtendGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, Tex1, false);
			}
			//�S�[���`��
			if (m_StageData[y][x] == 3)
			{
				DrawExtendGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, Tex2, false);
			}
			//���z�u�N���[�g�`��
			if (m_StageData[y][x] == 4)
			{
				DrawExtendGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, Tex4, false);
			}
			//�z�u�N���[�g�`��
			if (m_StageData[y][x] == 7)
			{
				DrawExtendGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, Tex3, false);
			}
			//���`��
			if (m_StageData[y][x] == 0)
			{
				DrawExtendGraph(x * CHIP_WIDTH, y * CHIP_HEIGHT, x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, Tex5, false);
			}
		}
	}
	//�v���C���[�ʒu�`��
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

	//���ʍ����Ƀf�o�b�O�p�̕��������ŕ\������
	DrawString(20, 20, "InGameScene", GetColor(0, 0, 0));
}

bool InGameScene::IsEnd() const
{
	return (m_Step == STEP_END);
}

//�J�n�W���O���҂�
void InGameScene::step_Start_Jingle()
{
	m_Step = STEP_INPUT;
}

//���͎��t
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
	bool clear;
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
			Count++;
		}
		else if (m_StageData[m_PlayerY - 2][m_PlayerX] == 3)
		{
			m_StageData[m_PlayerY - 1][m_PlayerX] = 0;
			m_StageData[m_PlayerY - 2][m_PlayerX] = 7;
			Count++;
		}
	}
	if ((m_StageData[m_PlayerY + 1][m_PlayerX] == 4) && Direction == 2)
	{
		if (m_StageData[m_PlayerY + 2][m_PlayerX] == 0)
		{
			m_StageData[m_PlayerY + 1][m_PlayerX] = 0;
			m_StageData[m_PlayerY + 2][m_PlayerX] = 4;
			Count++;
		}
		else if (m_StageData[m_PlayerY + 2][m_PlayerX] == 3)
		{
			m_StageData[m_PlayerY + 1][m_PlayerX] = 0;
			m_StageData[m_PlayerY + 2][m_PlayerX] = 7;
			Count++;
		}
	}
	if ((m_StageData[m_PlayerY][m_PlayerX + 1] == 4) && Direction == 4)
	{
		if (m_StageData[m_PlayerY][m_PlayerX + 2] == 0)
		{
			m_StageData[m_PlayerY][m_PlayerX + 1] = 0;
			m_StageData[m_PlayerY][m_PlayerX + 2] = 4;
			Count++;
		}
		else if (m_StageData[m_PlayerY][m_PlayerX + 2] == 3)
		{
			m_StageData[m_PlayerY][m_PlayerX + 1] = 0;
			m_StageData[m_PlayerY][m_PlayerX + 2] = 7;
			Count++;
		}
	}
	if ((m_StageData[m_PlayerY][m_PlayerX - 1] == 4) && Direction == 3)
	{
		if (m_StageData[m_PlayerY][m_PlayerX - 2] == 0)
		{
			m_StageData[m_PlayerY][m_PlayerX - 1] = 0;
			m_StageData[m_PlayerY][m_PlayerX - 2] = 4;
			Count++;
		}
		else if (m_StageData[m_PlayerY][m_PlayerX - 2] == 3)
		{
			m_StageData[m_PlayerY][m_PlayerX - 1] = 0;
			m_StageData[m_PlayerY][m_PlayerX - 2] = 7;
			Count++;
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
	Count = 0;
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
