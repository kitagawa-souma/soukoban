#ifndef DEFINITION_H
#define DEFINITION_H

enum SceneID
{
	SceneID_Title,		//タイトル
	SceneID_InGame,		//インゲーム
	SceneID_Result,		//リザルト

	SceneID_Max,
	SceneID_Invalid,	//無効値
};

//-----------------------------------
//倉庫番用の定義
//ステージ情報
const int STAGE_WIDTH = 11;
const int STAGE_HEIGHT = 14;

//マップチップの縦横サイズ
const int CHIP_WIDTH = 32;
const int CHIP_HEIGHT = 32;

//オブジェクト種類
//	0	地面
//	1	壁
//	2	プレイヤーの初期位置
//	3	クレートの配置場所
//	4	未配置のクレート
//	7	配置済みのクレート
//		(配置場所'3'+未配置クレート'4' = 7)

enum ObjectType
{
	ObjectType_Ground,			//0
	ObjectType_Wall,			//1
	ObjectType_Player,			//2
	ObjectType_Target,			//3
	ObjectType_UnsetCrate,		//4
	ObjectType_SetCrate = 7,	//7
};

#endif // !DEFINITION_H
