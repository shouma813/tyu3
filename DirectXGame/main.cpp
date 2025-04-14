#include <Windows.h>
#include"KamataEngine.h"
#include "GameScene.h"

using namespace KamataEngine;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	//ゲームシーンのインスタント生成
	GameScene* gamScene = new GameScene();
	// ゲームシーンの初期化
	gamScene->Initiailize();
	//エンジンの初期化
	KamataEngine::Initialize(L"GC2D_07_ミヤガワ_ショウマ_AL3");
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	//メインループ
	while (true) {
	   //エンジンの更新
		if (KamataEngine::Update()) {
		   break;
		}


		//ゲームシーンの更新
		gamScene->Update();


	    //描画開始
		dxCommon->PreDraw();


		//ゲームシーンの描画
		gamScene->Update();


		//描画終了
		dxCommon->PostDraw();
	}
	//ゲームシーンの解放
	delete gamScene;
	//nullptrの代入
	gamScene = nullptr;
	//エンジンの終了処理
	KamataEngine::Finalize();
	return 0;
}
