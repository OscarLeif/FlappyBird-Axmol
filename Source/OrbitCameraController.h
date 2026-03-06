#pragma once
#include "axmol.h"

class OrbitCameraController : public ax::Node
{
public:
    static OrbitCameraController* create(ax::Camera* camera);
    bool init(ax::Camera* camera);

    void setDistance(float distance);
    void setTarget(const ax::Vec3& target);
    void setYaw(float yaw);
    void setPitch(float pitch);
    void setSensitivity(float sensitivity) { _sensitivity = sensitivity; }

private:
    void setupMouseListener();
    void setupTouchListener();
    void updateCameraPosition();

    void onDragBegin(const ax::Vec2& pos);
    void onDragMove(const ax::Vec2& pos);
    void onDragEnd();

    bool onMouseDown(ax::Event* event);
    bool onMouseUp(ax::Event* event);
    bool onMouseMove(ax::Event* event);
    bool onMouseScroll(ax::Event* event);

    ax::Camera* _camera = nullptr;
    ax::Vec3 _target    = ax::Vec3::ZERO;

    float _distance    = 500.0f;
    float _yaw         = 0.0f;
    float _pitch       = 30.0f;
    float _sensitivity = 0.5f;

    const float _pitchMin = -89.0f;
    const float _pitchMax = 89.0f;

    ax::Vec2 _lastDragPos;
    bool _isDragging = false;
};
