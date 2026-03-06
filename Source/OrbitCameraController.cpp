#include "OrbitCameraController.h"

using namespace ax;

OrbitCameraController* OrbitCameraController::create(Camera* camera)
{
    auto ret = new OrbitCameraController();
    if (ret->init(camera))
    {
        ret->autorelease();
        return ret;
    }
    AX_SAFE_DELETE(ret);
    return nullptr;
}

bool OrbitCameraController::init(Camera* camera)
{
    if (!Node::init())
        return false;

    _camera = camera;

    setupMouseListener();
    setupTouchListener();
    updateCameraPosition();

    return true;
}

// ─────────────────────────────────────────
// Shared drag logic
// ─────────────────────────────────────────

void OrbitCameraController::onDragBegin(const Vec2& pos)
{
    _isDragging  = true;
    _lastDragPos = pos;
}

void OrbitCameraController::onDragMove(const Vec2& pos)
{
    if (!_isDragging)
        return;

    Vec2 delta   = pos - _lastDragPos;
    _lastDragPos = pos;

    _yaw += delta.x * _sensitivity;
    _pitch -= delta.y * _sensitivity;
    _pitch = std::clamp(_pitch, _pitchMin, _pitchMax);

    updateCameraPosition();
}

void OrbitCameraController::onDragEnd()
{
    _isDragging = false;
}

// ─────────────────────────────────────────
// Mouse (desktop)
// ─────────────────────────────────────────

void OrbitCameraController::setupMouseListener()
{
    auto _mouseListener = EventListenerMouse::create();

    _mouseListener->onMouseMove   = AX_CALLBACK_1(OrbitCameraController::onMouseMove, this);
    _mouseListener->onMouseDown   = AX_CALLBACK_1(OrbitCameraController::onMouseDown, this);
    _mouseListener->onMouseUp     = AX_CALLBACK_1(OrbitCameraController::onMouseUp, this);
    _mouseListener->onMouseScroll = AX_CALLBACK_1(OrbitCameraController::onMouseScroll, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

// CORRECT - takes Event* not EventMouse*
bool OrbitCameraController::onMouseDown(ax::Event* event)
{
    auto e = (EventMouse*)event;
    onDragBegin(Vec2(e->getCursorX(), e->getCursorY()));
    return true;
}

bool OrbitCameraController::onMouseUp(ax::Event* event)
{
    auto e = (EventMouse*)event;
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
        onDragEnd();
    return true;
}

bool OrbitCameraController::onMouseMove(ax::Event* event)
{
    auto e = (EventMouse*)event;
    onDragMove(Vec2(e->getCursorX(), e->getCursorY()));
    return true;
}

bool OrbitCameraController::onMouseScroll(ax::Event* event)
{
    auto e = (EventMouse*)event;
    _distance -= e->getScrollY() * 20.0f;
    _distance = std::max(_distance, 50.0f);
    updateCameraPosition();
    return true;
}

// ─────────────────────────────────────────
// Touch (mobile)
// ─────────────────────────────────────────

void OrbitCameraController::setupTouchListener()
{
    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = [this](Touch* touch, Event*) -> bool {
        onDragBegin(touch->getLocation());
        return true;  // consume the touch
    };

    listener->onTouchMoved = [this](Touch* touch, Event*) { onDragMove(touch->getLocation()); };

    listener->onTouchEnded = [this](Touch* touch, Event*) { onDragEnd(); };

    listener->onTouchCancelled = [this](Touch* touch, Event*) { onDragEnd(); };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// ─────────────────────────────────────────
// Camera math
// ─────────────────────────────────────────

void OrbitCameraController::updateCameraPosition()
{
    float yawRad   = AX_DEGREES_TO_RADIANS(_yaw);
    float pitchRad = AX_DEGREES_TO_RADIANS(_pitch);

    // Spherical to cartesian
    Vec3 offset(_distance * cosf(pitchRad) * sinf(yawRad), _distance * sinf(pitchRad),
                _distance * cosf(pitchRad) * cosf(yawRad));

    _camera->setPosition3D(_target + offset);
    _camera->lookAt(_target);
}

// ─────────────────────────────────────────
// Setters
// ─────────────────────────────────────────

void OrbitCameraController::setDistance(float distance)
{
    _distance = std::max(distance, 50.0f);
    updateCameraPosition();
}

void OrbitCameraController::setTarget(const Vec3& target)
{
    _target = target;
    updateCameraPosition();
}

void OrbitCameraController::setYaw(float yaw)
{
    _yaw = yaw;
    updateCameraPosition();
}

void OrbitCameraController::setPitch(float pitch)
{
    _pitch = std::clamp(pitch, _pitchMin, _pitchMax);
    updateCameraPosition();
}
