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
	void Exec();	//シーンの実行
	void Draw();	//シーンの実行

	//次のシーンを設定する関数をstatic関数にすることで
	//実体がどこにあってもよい状態を作る
	void SetNextScene(SceneID next_);	//次のシーン設定

private:
	class SceneBase* create_NextScene();		//次のシーンを作成

private:
	class SceneBase* m_pScene;				//実行中のシーン
	static SceneID		m_NextSceneID;			//次に作るシーンのID
#if 0
//---------------------------------------------------------------
//シングルトンデザインパターン

private:
	//自分自身のポインタ変数(自分自身の唯一の実体)
	static SceneManager* m_pInstance;

public:
	//実体を作る関数
	static void CreateInstance()
	{
		//すでに作られているなら新しく作らないことを保証
		if (m_pInstance == nullptr)
		{
			m_pInstance = new SceneManager();
		}
	}

	//実体を破棄する関数
	static SceneManager* GetInstance()
	{
		return m_pInstance;
	}

	//実体が存在しないか確認する
	static bool IsNull()
	{
		return (m_pInstance == nullptr);
	}
};
SceneManager* SceneManager::m_pInstance = nullptr;
#endif // !0
};
#endif // !SCENEMANAGER_H