#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "../Definition.h"
#include "../Singleton.h"

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

public:
	void Exec();	//�V�[���̎��s
	void Draw();	//�V�[���̎��s

	//���̃V�[����ݒ肷��֐���static�֐��ɂ��邱�Ƃ�
	//���̂��ǂ��ɂ����Ă��悢��Ԃ����
	void SetNextScene(SceneID next_);	//���̃V�[���ݒ�

private:
	class SceneBase* create_NextScene();		//���̃V�[�����쐬

private:
	class SceneBase* m_pScene;				//���s���̃V�[��
	static SceneID		m_NextSceneID;			//���ɍ��V�[����ID
#if 0
//---------------------------------------------------------------
//�V���O���g���f�U�C���p�^�[��

private:
	//�������g�̃|�C���^�ϐ�(�������g�̗B��̎���)
	static SceneManager* m_pInstance;

public:
	//���̂����֐�
	static void CreateInstance()
	{
		//���łɍ���Ă���Ȃ�V�������Ȃ����Ƃ�ۏ�
		if (m_pInstance == nullptr)
		{
			m_pInstance = new SceneManager();
		}
	}

	//���̂�j������֐�
	static SceneManager* GetInstance()
	{
		return m_pInstance;
	}

	//���̂����݂��Ȃ����m�F����
	static bool IsNull()
	{
		return (m_pInstance == nullptr);
	}
};
SceneManager* SceneManager::m_pInstance = nullptr;
#endif // !0
};
#endif // !SCENEMANAGER_H