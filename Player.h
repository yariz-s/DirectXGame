#pragma once  
#include "KamataEngine.h"  
#include "vector"  

class Player {  
public:  
void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);  
void Update();  
void Draw();  

private:  
KamataEngine::WorldTransform worldTransform_;  
KamataEngine::Model* model_ = nullptr;  
/*uint32_t textureHandle_ = 0u;*/  
KamataEngine::Camera* camera_ = nullptr;  

KamataEngine::Vector3 velocity_{};  
static inline const float kAcceleration = 0.05f;  
static inline const float kAttenuation = 0.05f;  
static inline const float kLimitRunSpeed = 1.0f;  

// 左右  
enum class LRDirection {  
	kLeft,  
	kRight,  
};  
LRDirection lrDirection_ = LRDirection::kRight; // 左右の方向  

// 旋回角度の制限  
float sumEulerRotation_,Y = 0.0f;
//旋回タイマー  
float turnTimer_ = 0.0f;  
//　旋回時間  
static inline const float kTimeTurn = 0.5f; // 旋回時間  

float turnFirstRotationY_ = 0.0f; // 最初の旋回角度
	bool onGround_ = true; // 地面にいるかどうか  

//重力加速度 (下咆哮)  
static inline const float kGravityAcceleration = 0.1f; // 重力加速度  
//落下速度
static inline const float kLimitFallSpeed = 1.0f;
// ジャンプの初速
static inline const float JumpAcceleration = 1.0f;
};