#ifndef PHYSICS_H
#define PHYSICS_H

#include <box2d/box2d.h>

class MyContactListener : public b2ContactListener{
private:
    virtual void BeginContact(b2Contact *contact) override;
    // void EndContact(b2Contact *contact) override;
    // void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
    // void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) override;

};


class MyRayCastCallback : public b2RayCastCallback{
private:
    virtual float ReportFixture (b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction) override;
};

#endif