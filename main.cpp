/// #include <Windows.h>
#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
#include "GameScene.h"
// ゲームシーン
class Gamescene {};
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// エンジンの初期化
	KamataEngine::Initialize(L"GC2D_04_ヤリミズ_シオン_AL3");
	// DirectXcommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	// ゲームシーンのインスタンス生成
	GameScene* gameScene = new GameScene();
	// ゲームシーンの初期化
	gameScene->Initialize();

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}
		// ゲームシーンの更新
		gameScene->Update();
		// 描画開始
		dxCommon->PreDraw();
		// ゲームシーンの描画
		gameScene->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}
	// ゲームシーンの解放
	delete gameScene;
	// nullptrの代入
	gameScene = nullptr;
	// エンジンの終了処理
	KamataEngine::Finalize();
	return 0;
}
