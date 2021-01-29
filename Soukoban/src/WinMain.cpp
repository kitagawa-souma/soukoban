#include "DxLib.h"
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"
#include "Manager/InputManager.h"

//�萔��`
const int WINDOW_W = 640;
const int WINDOW_H = 480;
const int COLOR_BIT = 32;

//�v���O������ WinMain ����n�܂�܂�
//�x��C28251��������邽�߂�WinMAin�̈����ɒ��߂�ǋL
//https://dxlib.xsrv.jp/cgi/patiobbs/patio.cgi?mode=view&no=4947
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//DX���C�u��������������
	SetOutApplicationLogValidFlag(FALSE);	//���O�o��
	ChangeWindowMode(true);					//�E�C���h�E���[�h
	SetGraphMode(WINDOW_W, WINDOW_H, COLOR_BIT);				//��ʃ��[�h�̕ύX
	SetBackgroundColor(125, 125, 125);		//�w�i�F
	SetMainWindowText("My�q�ɔ�");			//���j���[�o�[�̃^�C�g��

	if (DxLib_Init() == -1)
	{
		return -1;		//�G���[���N�����璼���ɏI��
	}

	//�`���𗠂̉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//�Ǘ��N���X�̍쐬
	GameManager::CreateInstance();
	InputManager::CreateInstance();
	SceneManager::CreateInstance();

	//�Q�[�����[�v
	while (true)
	{
		//Windows�̃��b�Z�[�W�����Ɏ��s�������A����ꂽ��I��
		if (ProcessMessage() != 0)
		{
			break;
		}

		//DxLib�̂���:��ʃN���A
		ClearDrawScreen();
		clsDx();

		//����
		InputManager::GetInstance()->Update();
		SceneManager::GetInstance()->Exec();

		//�`��
		SceneManager::GetInstance()->Draw();

		//DxLib�̂���:��ʍX�V
		ScreenFlip();
	}

	//�Ǘ��N���X�̌�n��
	SceneManager::DestroyInstance();
	InputManager::DestroyInstance();
	GameManager::DestroyInstance();
		
	DxLib_End();						//DX���C�u�����d�l�̏I������

	return 0;							//�\�t�g�̏I��
}