#pragma once
#include "KamataEngine.h"

class Player {
public:
    void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);
    void Update();
    void Draw();

private:
    // ワールド変換
    KamataEngine::WorldTransform worldTransform_;
    // モデル
    KamataEngine::Model* model_ = nullptr;
    // カメラ
    KamataEngine::Camera* camera_ = nullptr;

    // 移動速度
    KamataEngine::Vector3 velocity_ = {};
    static inline const float kAcceleration = 0.05f;
    static inline const float kAttenuation = 0.05f;
    static inline const float kLimitRunSpeed = 1.0f;

    // 左右
    enum class LrDirection {
        kRight,
        kLeft,
    };
    LrDirection lrDirection_ = LrDirection::kRight;

    // 回転関連
    float turnFirstRotationY_ = 0.0f;
    float turnTimer_ = 0.0f;
    static inline const float kTimeTurn = 0.3f;

    // 接地
    bool onGround_ = true;

    // ジャンプ＆落下
    static inline const float kGravityAcceleration = 0.1f;
    static inline const float kLimitFallSpeed = 1.0f;
    static inline const float kJumpAcceleration = 1.0f;
};
