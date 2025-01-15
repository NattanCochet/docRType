/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** CreateEntity
*/

#include "../../include/ECS/CreateEntity.hpp"

Entity CreateEntity::createLaser(
    sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong, bool inThePlayerTeam, bool toTheRight
)
{
    Entity newLaser = r.spawn_entity();
    r.add_component(newLaser, Position(pos.x, pos.y + 50));
    if (toTheRight)
        r.add_component(newLaser, Velocity(sf::Vector2i(30, 0), 0.2, 0.0));
    else
        r.add_component(newLaser, Velocity(sf::Vector2i(-30, 0), 0.2, 0.0));
    r.add_component(newLaser, Projectile(20.0f, false, false, 0.4f, entityIDBelong));
    r.add_component(newLaser, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(pos.x, pos.y + 50), Vector<int, 2>(30, 10), entityIDBelong, inThePlayerTeam));
    return (newLaser);
}

Entity CreateEntity::createLaserBoss(
    sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong, float damage, sf::Vector2i newVelocity, Vector<int, 2> size
)
{
    Entity newLaser = r.spawn_entity();
    r.add_component(newLaser, Position(pos.x - 30, pos.y));
    r.add_component(newLaser, Velocity(newVelocity, 0.2, 0.0));
    r.add_component(newLaser, Projectile(damage, false, false, 0.4f, entityIDBelong));
    r.add_component(newLaser, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(pos.x, pos.y), size, entityIDBelong, false));
    return (newLaser);
}

Entity CreateEntity::createBomb(
    sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong, bool isInPlayerTeam
)
{
    Entity newBomb = r.spawn_entity();
    r.add_component(newBomb, Position(pos.x + 50, pos.y));
    r.add_component(newBomb, Velocity(sf::Vector2i(0, 30), 0.2, 0.0));
    r.add_component(newBomb, Projectile(20.0f, false, false, 0.4f, entityIDBelong));
    r.add_component(newBomb, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(pos.x + 50, pos.y), Vector<int, 2>(20, 10), entityIDBelong, isInPlayerTeam));
    return (newBomb);
}

Entity CreateEntity::createBossBomb(
    sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong
)
{
    Entity newBomb = r.spawn_entity();
    r.add_component(newBomb, Position(pos.x + 50, pos.y));
    r.add_component(newBomb, Velocity(sf::Vector2i(0, 18), 0.2, 0.0));
    r.add_component(newBomb, Projectile(10.0f, false, false, 0.4f, entityIDBelong));
    r.add_component(newBomb, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(pos.x, pos.y), Vector<int, 2>(75, 75), entityIDBelong, false));
    return (newBomb);
}

Entity CreateEntity::createBeam(
    sf::Vector2f pos, Registry &r, float damageDependHolding, const std::size_t &entityIDBelong, bool toTheRight, bool isInPlayerTeam
)
{
    Entity newBeam = r.spawn_entity();
    r.add_component(newBeam, Position(pos.x, pos.y + 50));
    if (toTheRight)
        r.add_component(newBeam, Velocity(sf::Vector2i(18, 0), 0.5, 0.0));
    else
        r.add_component(newBeam, Velocity(sf::Vector2i(-18, 0), 0.5, 0.0));
    r.add_component(newBeam, Projectile(damageDependHolding, false, true, 0.2f, entityIDBelong));
    r.add_component(newBeam, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(pos.x, pos.y + 50), Vector<int, 2>(40, 20), entityIDBelong, isInPlayerTeam));
    return (newBeam);
}

Entity CreateEntity::createKamikaze(
    sf::Vector2f pos, Registry &r, float damage, const std::size_t &entityIDBelong, bool toTheRight
)
{
    Entity newKamikaze = r.spawn_entity();
    r.add_component(newKamikaze, Position(pos));
    if (toTheRight)
        r.add_component(newKamikaze, Velocity(sf::Vector2i(40, 0), 0.0, 0.01));
    else
        r.add_component(newKamikaze, Velocity(sf::Vector2i(-40, 0), 0.0, 0.01));
    r.add_component(newKamikaze, Projectile(damage, false, false, 0.2f, entityIDBelong));
    r.add_component(newKamikaze, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(pos.x, pos.y), Vector<int, 2>(33, 33), entityIDBelong, false));
    return (newKamikaze);
}

Entity CreateEntity::createDecor(sf::Vector2f pos, Registry &r)
{
    Entity newDecor = r.spawn_entity();
    r.add_component(newDecor, Position(pos));
    r.add_component(newDecor, Velocity(sf::Vector2i(-1, 0), 4.0, 0.01));
    r.add_component(newDecor, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(pos.x, pos.y), Vector<int, 2>(50, 50), newDecor, false));
    return (newDecor);
}

Entity CreateEntity::createPlayer(sf::Vector2f pos, std::size_t clientID, Registry &r)
{
    Entity newPlayer = r.spawn_entity();
    r.add_component(newPlayer, Position(pos));
    r.add_component(newPlayer, Vitality(60, 0, 100));
    r.add_component(newPlayer, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(pos.x, pos.y), Vector<int, 2>(99, 99), newPlayer, true));
    r.add_component(newPlayer, Drawable::Drawable(
        "Player", true, sf::Vector2f(3.0f, 3.0f), {Drawable::FrameRect(0, 0, 33, 33)}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f
        )
    );
    r.add_component(newPlayer, Controllable(true, clientID));
    r.add_component(newPlayer, Clock("movePlayer", "keyPressingShoot", "spamProtectionShoot", "keyPressingForce", "spamProtectionForce"));
    r.add_component(newPlayer, Area(70.0));
    return (newPlayer);
}

Entity CreateEntity::createLinearShooterHorizontal(sf::Vector2f pos, Registry &r)
{
    Entity newLinearShooterHorizontal = r.spawn_entity();
    r.add_component(newLinearShooterHorizontal, Position(pos));
    r.add_component(newLinearShooterHorizontal, Vitality(20, 3, 20));
    r.add_component(newLinearShooterHorizontal, Ennemy(3, std::make_shared<LinearShooter>(1.5f, true)));
    r.add_component(newLinearShooterHorizontal, Velocity(sf::Vector2i(-1, 0), 4.0, 0.01));
    r.add_component(newLinearShooterHorizontal, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(pos.x, pos.y), Vector<int, 2>(33, 33), newLinearShooterHorizontal, false));
    r.add_component(newLinearShooterHorizontal, Drawable::Drawable(
        "LinearShooterHorizontal", true, sf::Vector2f(10.0f, 10.0f), {Drawable::FrameRect(0, 0, 33, 33)}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f
        )
    );
    return (newLinearShooterHorizontal);
}

Entity CreateEntity::createLinearShooterHorizontalShinny(sf::Vector2f pos, Registry &r, std::size_t idAfterDead)
{
    Entity newLinearShooterHorizontalShinny = this->createLinearShooterHorizontal(pos, r);
    r.add_component(newLinearShooterHorizontalShinny, SpawnAfterDead(idAfterDead));
    return (newLinearShooterHorizontalShinny);
}

Entity CreateEntity::createLinearShooterVertical(sf::Vector2f pos, Registry &r)
{
    Entity newLinearShooterVertical = r.spawn_entity();
    r.add_component(newLinearShooterVertical, Position(pos));
    r.add_component(newLinearShooterVertical, Vitality(20, 2, 20));
    r.add_component(newLinearShooterVertical, Ennemy(2, std::make_shared<LinearShooter>(1.5f, false, 4)));
    r.add_component(newLinearShooterVertical, Velocity(sf::Vector2i(-1, 0), 4.0, 0.01));
    r.add_component(newLinearShooterVertical, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(pos.x, pos.y), Vector<int, 2>(33, 33), newLinearShooterVertical, false));
    r.add_component(newLinearShooterVertical, Drawable::Drawable(
        "LinearShooterVertical", true, sf::Vector2f(10.0f, 10.0f), {Drawable::FrameRect(0, 0, 33, 33)}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f
        )
    );
    return (newLinearShooterVertical);
}

Entity CreateEntity::createLinearShooterVerticalShinny(sf::Vector2f pos, Registry &r, std::size_t idAfterDead)
{
    Entity newLinearShooterVerticalShinny = this->createLinearShooterVertical(pos, r);
    r.add_component(newLinearShooterVerticalShinny, SpawnAfterDead(idAfterDead));
    return (newLinearShooterVerticalShinny);
}

Entity CreateEntity::createTpShooter(sf::Vector2f pos, Registry &r)
{
    Entity newTpShooter = r.spawn_entity();
    r.add_component(newTpShooter, Position(pos));
    r.add_component(newTpShooter, Vitality(20, 4, 20));
    r.add_component(newTpShooter, Ennemy(4, std::make_shared<TpShooter>(0.6, 3)));
    r.add_component(newTpShooter, Velocity(sf::Vector2i(-1, 0), 4.0, 0.01));
    r.add_component(newTpShooter, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(pos.x, pos.y), Vector<int, 2>(33, 33), newTpShooter, false));
    r.add_component(newTpShooter, Drawable::Drawable(
        "TPShooter", true, sf::Vector2f(10.0f, 10.0f), {Drawable::FrameRect(0, 0, 33, 33)}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f
        )
    );
    return (newTpShooter);
}

Entity CreateEntity::createTpShooterShinny(sf::Vector2f pos, Registry &r, std::size_t idAfterDead)
{
    Entity newTpShooterShinny = this->createTpShooter(pos, r);
    r.add_component(newTpShooterShinny, SpawnAfterDead(idAfterDead));
    return (newTpShooterShinny);
}

Entity CreateEntity::createSinusoidaleShooter(sf::Vector2f pos, Registry &r)
{
    Entity newSinusoidaleShooter = r.spawn_entity();
    r.add_component(newSinusoidaleShooter, Position(pos));
    r.add_component(newSinusoidaleShooter, Vitality(20, 5, 20));
    r.add_component(newSinusoidaleShooter, Ennemy(5, std::make_shared<SinusoidalShooter>(1.6f, 6.0f, 0.08f, -8.0f)));
    r.add_component(newSinusoidaleShooter, Velocity(sf::Vector2i(-1, 0), 4.0, 0.01));
    r.add_component(newSinusoidaleShooter, Hitbox(Hitbox::RECTANGLE, Vector<int, 2>(pos.x, pos.y), Vector<int, 2>(99, 99), newSinusoidaleShooter, false));
    r.add_component(newSinusoidaleShooter, Drawable::Drawable(
        "SinusoidalShooter", true, sf::Vector2f(10.0f, 10.0f), {Drawable::FrameRect(0, 0, 33, 33)}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f
        )
    );
    return (newSinusoidaleShooter);
}

Entity CreateEntity::createSinusoidaleShooterShinny(sf::Vector2f pos, Registry &r, std::size_t idAfterDead)
{
    Entity newSinusoidaleShooterShinny = this->createSinusoidaleShooter(pos, r);
    r.add_component(newSinusoidaleShooterShinny, SpawnAfterDead(idAfterDead));
    return (newSinusoidaleShooterShinny);
}

Entity CreateEntity::createForce(sf::Vector2f pos, Registry &r)
{
    Entity newForce = r.spawn_entity();

    r.add_component(newForce, Position(-33, pos.y));
    r.add_component(newForce, Velocity(sf::Vector2i(2, 0), 4.0, 0.01));
    r.add_component(newForce, Drawable::Drawable(
        "Force", true, sf::Vector2f(3.0f, 3.0f), {Drawable::FrameRect(0, 0, 33, 33)}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f
        ));
    r.add_component(newForce, Force(pos.x));
    r.add_component(newForce, Area(70.0));
    return (newForce);
}
