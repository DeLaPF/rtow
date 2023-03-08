#pragma once

#include "Math/Ray.h"
#include "Math/Vec.h"

class SceneComponent {
public:
    SceneComponent();
    SceneComponent(Vec3 location, int materialIndex);
    SceneComponent(Vec3 location, Vec3 rotation, int materialIndex);

    virtual Vec3 GetWorldLocation() const { return m_WorldLocation; }
    virtual void SetWorldLocation(Vec3 location) { m_WorldLocation = location; }

    virtual Vec3 GetWorldRotation() const { return m_WorldRotation; }
    virtual void SetWorldRotation(Vec3 rotation);

    virtual int GetMaterialIndex() const { return m_MaterialIndex; }
    virtual void SetMaterialIndex(int index) { m_MaterialIndex = index; }
protected:
    Vec3 m_WorldLocation;
    Vec3 m_WorldRotation; // X: Psi, Y: Theta, Z: Phi
    int m_MaterialIndex;

    double m_SinPsi, m_CosPsi;
    double m_SinTheta, m_CosTheta;
    double m_SinPhi, m_CosPhi;
};
