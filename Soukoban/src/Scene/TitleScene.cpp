#include "TitleScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

enum
{
	STEP_LOGO_IN,//���S����҂�
	STEP_INPUT,	 //���͑҂�
	STEP_END,	 //�V�[���I��
};

TitleScene::TitleScene()
{
	m_Step = STEP_LOGO_IN;
}

TitleScene::~TitleScene()
{

}

void TitleScene::Exec()
{
	switch (m_Step)
	{
	case STEP_LOGO_IN:
		step_LogoIn();
		break;
	case STEP_INPUT:
		step_Input();
		break;
	default:
		break;
	}
}

void TitleScene::Draw()
{
	//��ʍ���Ƀf�o�b�O�p�̕��������ŕ\������
	DrawString(20, 20, "TitleScene", GetColor(0, 0, 0));
}

bool TitleScene::IsEnd() const
{
	return (m_Step == STEP_END);
}

//���S����
void TitleScene::step_LogoIn()
{
	m_Step = STEP_INPUT;
}

//���͎�t
void TitleScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if (pInputMng->IsPush(KeyType_Enter))
	{
		m_Step = STEP_END;
		SceneManager::GetInstance()->SetNextScene(SceneID_InGame);
	}
}