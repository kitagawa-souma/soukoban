#ifndef KEYDEFINITION_H
#define KEYDEFINITION_H

#include "DxLib.h"

//キーの種類
enum KeyType
{
	KeyType_Up,		//上移動
	KeyType_Down,	//下移動
	KeyType_Left,	//左移動
	KeyType_Right,	//右移動
	KeyType_Enter,	//決定
	KeyType_Space,	//押す
	KeyType_Reset,	//リセット
	KeyType_Debug,	//デバッグ
	
	KeyType_Max		//キーの種類の数
};

//キーの種類に対応する、実際の入力配列
const int KEY_ASSIGN[KeyType_Max] =
{
	KEY_INPUT_UP,
	KEY_INPUT_DOWN,
	KEY_INPUT_LEFT,
	KEY_INPUT_RIGHT,
	KEY_INPUT_RETURN,
	KEY_INPUT_SPACE,
	KEY_INPUT_R,
	KEY_INPUT_DELETE,
};

#endif // !KEYDEFINITION_H