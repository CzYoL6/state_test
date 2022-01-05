#include "physics.h"
#include "Player.h"

void MyContactListener::BeginContact(b2Contact *contact) {
    //printf("contact.\n");
    auto fixture_a = contact->GetFixtureA();
    auto fixture_b = contact->GetFixtureB();
    auto body_a = fixture_a->GetBody();
    auto body_b = fixture_b->GetBody();

    b2Body *map_obj = nullptr;
    b2Body *other_obj = nullptr;

    b2WorldManifold manifold;
    contact->GetWorldManifold(&manifold);
    b2Vec2 normal = manifold.normal;

    if(body_a->GetType() == b2BodyType::b2_staticBody){
        map_obj = body_a;
        other_obj = body_b;
    }
    else if(body_b->GetType() == b2BodyType::b2_staticBody){
        map_obj = body_b;
        other_obj = body_a;
        normal *= -1;
    }

    if(map_obj == nullptr) return;
    b2Vec2 impulse = normal;
    printf("normal:(%lf,%lf)\n", impulse.x, impulse.y);
    impulse *= 10;
    other_obj->ApplyLinearImpulseToCenter(impulse, true);

    Player *player = reinterpret_cast<Player*>(other_obj->GetUserData().pointer);
    if(player != nullptr){
        printf("player %d collided with walls.\n", player->GetSlotid());
        if(player->IsAI()){
            player->AIChangeDir(true);
        }
    }
}


float MyRayCastCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction){
    //printf("hit something.\n");
    b2Body *body = fixture->GetBody();
    Player *player = reinterpret_cast<Player*>(body->GetUserData().pointer);

    if(player != nullptr){
        printf("hit player %d.\n", player->GetSlotid());
        Update_ShooterTest::HitAcknowledged_S_TO_C hit;
        hit.set_attacker_slotid(Game::GetInstance().GetCurAttackerSlotid());
        hit.set_damage(10);
        hit.set_dead(false);
        hit.set_e_pos_x(player->GetPos().x);
        hit.set_e_pos_y(player->GetPos().y);
        hit.set_e_rot(player->GetRotation());
        hit.set_enemy_slotid(player->GetSlotid());
        Game::GetInstance().AddIntoHitInfos(hit);
    }

    //return the fraction value so find the nearest point
    return fraction;
}

