#include "Enemy.h"
#include "MyMath.h"
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;

void Enemy::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position) {
	assert(model);
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = - std::numbers::pi_v<float> / 2.0f;
	//速度設定
	velocity_ = {kWalkSpeed, 0.0f, 0.0f};
	walkTimer_ = 0.0f;

}

void Enemy::Update() {
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
	// 敵の移動
	worldTransform_.translation_ -= velocity_;
	//タイマー加算
	walkTimer_ += 1.0f/60.0f;
	//回転アニメーション
	worldTransform_.rotation_.x = std::sin(walkTimer_*5.0f);
}

void Enemy::Draw() {
	if (camera_ && model_) {
		model_->Draw(worldTransform_, *camera_);
	}
}
