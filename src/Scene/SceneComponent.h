#pragma once

#include "Math/Ray.h"
#include "Math/Vec.h"

class SceneComponent {
public:
    SceneComponent() : m_WorldLocation(Vec3()), m_MaterialIndex(0) {}
    SceneComponent(Vec3 location, int materialIndex)
        : m_WorldLocation(location), m_MaterialIndex(materialIndex) {}

    virtual Vec3 GetWorldLocation() const { return m_WorldLocation; }
    virtual void SetWorldLocation(const Vec3& location) { m_WorldLocation = location; }

    virtual int GetMaterialIndex() const { return m_MaterialIndex; }
    virtual void SetMaterialIndex(int index) { m_MaterialIndex = index; }
protected:
    Vec3 m_WorldLocation;
    int m_MaterialIndex;
};
