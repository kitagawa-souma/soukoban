#include "ResultScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "InGameScene.h"

enum
{
	STEP_START_JINGLE,//�J�n�W���O���҂�
	STEP_INPUT,	 //���͑҂�
	STEP_CLEAR_JINGLE, //�N���A�W���O���҂�
	STEP_END,	 //�V�[���I��
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
	//���ʍ����Ƀf�o�b�O�p�̕��������ŕ\������
	//DrawString(20, 20, "ResultScene", GetColor(0, 0, 0));
	printfDx("�|�������萔�F%d��", InGameScene::Count);
}

bool ResultScene::IsEnd() const
{
	return (m_Step == STEP_END);
}

//�J�n�W���O���҂�
void ResultScene::step_Start_Jingle()
{
	m_Step = STEP_INPUT;
}

//���͎��t
void ResultScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPush(KeyType_Enter))
	{
		m_Step = STEP_CLEAR_JINGLE;
	}
}

//�N���A�W���O���҂�
void ResultScene::step_Clear_Jingle()
{
	m_Step = STEP_END;
	SceneManager::GetInstance()->SetNextScene(SceneID_Title);
}
