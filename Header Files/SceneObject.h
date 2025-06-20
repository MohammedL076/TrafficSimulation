#pragma once

class SceneObject {
public:
    virtual void update(float deltaTime) = 0;
    virtual void draw() = 0;
    virtual ~SceneObject() {}
};
