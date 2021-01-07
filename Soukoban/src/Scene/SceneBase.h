#ifndef SCENEBASE_H
#define SCENEBASE_H

//シーン基底クラス
class SceneBase
{
public:
	int m_Step = 0;
	SceneBase();
	virtual ~SceneBase();

	//処理内容は派生クラス毎に違うので、
	//純粋仮想関数として宣言しておく
	virtual void Exec() = 0;	//処理を行う
	virtual void Draw() = 0;	//描画を行う
	
	virtual bool IsEnd() const = 0; //シーンが終了したかどうかを返す
};

#endif // !SCENEBASE_H
