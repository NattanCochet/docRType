/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** CreateEntity
*/

#include "../../include/ECS/CreateEntity.hpp"

Entity CreateEntity::createBomb(sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong, Hitbox::TEAM team)
{
    Entity newBomb = r.spawn_entity();
    r.add_component(newBomb, Position(pos.x + 50, pos.y));
    r.add_component(newBomb, Velocity(sf::Vector2i(0, 30), 0.2, 0.0));
    r.add_component(newBomb, Projectile(20.0f, false, false, 0.4f, entityIDBelong));
    r.add_component(newBomb,
        Hitbox::Hitbox(pos.x + 50, pos.y, {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos.x + 50, pos.y, 4, 11, 0.0f)},
            entityIDBelong, team));
    r.add_component(newBomb, Drawable::Drawable("B", true, sf::Vector2f(1.0f, 1.0f),
                                 {Drawable::FrameRect(0, 0, 4, 11), Drawable::FrameRect(4, 0, 4, 11)}, 0.1, {}, 0.0, {},
                                 0.0, {}, 0.0, {}, 0.0));
    return (newBomb);
}

Entity CreateEntity::createBossBomb(sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong)
{
    Entity newBomb = r.spawn_entity();
    r.add_component(newBomb, Position(pos.x + 50, pos.y));
    r.add_component(newBomb, Velocity(sf::Vector2i(0, 18), 0.2, 0.0));
    r.add_component(newBomb, Projectile(20.0f, false, false, 0.4f, entityIDBelong));
    r.add_component(newBomb, Hitbox::Hitbox(pos.x + 50, pos.y,
                                 {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos.x + 50, pos.y, 30, 30, 0.0f)},
                                 entityIDBelong, Hitbox::TEAM::ENNEMY));
    r.add_component(newBomb, Drawable::Drawable("BB", true, sf::Vector2f(1.0f, 1.0f),
                                 {Drawable::FrameRect(0, 0, 30, 30), Drawable::FrameRect(30, 0, 30, 30),
                                     Drawable::FrameRect(60, 0, 30, 30), Drawable::FrameRect(90, 0, 30, 30)},
                                 0.1, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
    return (newBomb);
}

Entity CreateEntity::createBeam(
    const sf::Vector2f &pos, Registry &r, const float damageDependHolding, const std::size_t &entityIDBelong)
{
    Entity newBeam = r.spawn_entity();
    r.add_component(newBeam, Position(pos.x + 82.5, pos.y + 21.25));
    r.add_component(newBeam, Velocity(sf::Vector2i(18, 0), 0.0, 0.0));
    r.add_component(newBeam, Projectile(damageDependHolding, false, true, 0.2f, entityIDBelong));
    r.add_component(
        newBeam, Hitbox::Hitbox(pos.x + 82.5, pos.y + 21.25,
                     {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos.x + 82.5, pos.y + 21.25, 80, 16, 0.0f)},
                     entityIDBelong, Hitbox::TEAM::PLAYER));
    r.add_component(newBeam, Drawable::Drawable("BE", true, sf::Vector2f(1.0f, 1.0f),
                                 {Drawable::FrameRect(0, 0, 80, 16), Drawable::FrameRect(80, 0, 80, 16)}, 0.1, {}, 0.0,
                                 {}, 0.0, {}, 0.0, {}, 0.0));
    return (newBeam);
}

Entity CreateEntity::createKamikazeShooter(sf::Vector2f pos, Registry &r)
{
    Entity newKamikazeShooter = r.spawn_entity();

    r.add_component(newKamikazeShooter, Position(pos));
    r.add_component(newKamikazeShooter, Ennemy(18, std::make_shared<KamikazeShooter>()));
    r.add_component(newKamikazeShooter, Velocity(sf::Vector2i(-1, 0), 4.0, 0.01));
    r.add_component(newKamikazeShooter, Vitality(20, 4));
    r.add_component(newKamikazeShooter, Drawable::Drawable("KS", true, sf::Vector2f(1, 1),
                                            {Drawable::FrameRect(0, 0, 33, 29), Drawable::FrameRect(33, 0, 33, 29),
                                                Drawable::FrameRect(66, 0, 33, 29), Drawable::FrameRect(99, 0, 33, 29)},
                                            0.0, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
    return (newKamikazeShooter);
}

Entity CreateEntity::createKamikaze(
    sf::Vector2f pos, Registry &r, float damage, const std::size_t &entityIDBelong, bool toTheRight)
{
    Entity newKamikaze = r.spawn_entity();
    r.add_component(newKamikaze, Position(pos));
    if (toTheRight)
        r.add_component(newKamikaze, Velocity(sf::Vector2i(40, 0), 0.0, 0.01));
    else
        r.add_component(newKamikaze, Velocity(sf::Vector2i(-40, 0), 0.0, 0.01));
    r.add_component(newKamikaze, Projectile(damage, false, false, 0.2f, entityIDBelong));
    r.add_component(newKamikaze, Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos, 33, 29, 0.0f)},
                                     entityIDBelong, Hitbox::TEAM::ENNEMY));
    return (newKamikaze);
}

Entity CreateEntity::createDecor(sf::Vector2f pos, Registry &r)
{
    Entity newDecor = r.spawn_entity();
    r.add_component(newDecor, Position(pos));
    r.add_component(newDecor, Velocity(sf::Vector2i(-1, 0), 0.0, 0.01));
    r.add_component(newDecor, Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos, 60, 60, 0.0f)},
                                  newDecor, Hitbox::TEAM::NEITHER));
    r.add_component(newDecor, Drawable::Drawable("D", true, sf::Vector2f(1, 1),
                                  {Drawable::FrameRect(0, 0, 60, 60), Drawable::FrameRect(60, 0, 60, 60),
                                      Drawable::FrameRect(120, 0, 60, 60), Drawable::FrameRect(180, 0, 60, 60)},
                                  0.05, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
    return (newDecor);
}

Entity CreateEntity::createPlayer(sf::Vector2f pos, std::size_t clientID, Registry &r, const std::size_t rowSkin)
{
    Entity newPlayer = r.spawn_entity();
    r.add_component(newPlayer, Position(pos));
    r.add_component(newPlayer, Vitality(60, 0, 100));
    r.add_component(newPlayer, Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos, 82.5, 42.5, 0.0f)},
                                   newPlayer, Hitbox::TEAM::PLAYER));
    r.add_component(newPlayer,
        Drawable::Drawable("Player", true, sf::Vector2f(2.5f, 2.5f), {Drawable::FrameRect(66, 17 * rowSkin, 33, 17)},
            0.2f, {Drawable::FrameRect(132, 17 * rowSkin, 33, 17)}, 0.2f,
            {Drawable::FrameRect(0, 17 * rowSkin, 33, 17)}, 0.2f, {}, 0.2f, {}, 0.2f));
    r.add_component(newPlayer, Controllable(true, clientID));
    r.add_component(newPlayer,
        Clock("movePlayer", "keyPressingShoot", "spamProtectionShoot", "keyPressingForce", "spamProtectionForce"));
    r.add_component(newPlayer, Area(60.0));
    return (newPlayer);
}

Entity CreateEntity::createPlayerAI(sf::Vector2f pos, std::size_t clientID, Registry &r, const std::size_t rowSkin)
{
    Entity newPlayerAI = r.spawn_entity();
    r.add_component(newPlayerAI, Position(pos));
    r.add_component(newPlayerAI, Vitality(60, 0, 100));
    r.add_component(
        newPlayerAI, Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos, 82.5, 42.5, 0.0f)},
                         newPlayerAI, Hitbox::TEAM::PLAYER));
    r.add_component(newPlayerAI,
        Drawable::Drawable("Player", true, sf::Vector2f(2.5f, 2.5f), {Drawable::FrameRect(66, 17 * rowSkin, 33, 17)},
            0.2f, {Drawable::FrameRect(132, 17 * rowSkin, 33, 17)}, 0.2f,
            {Drawable::FrameRect(0, 17 * rowSkin, 33, 17)}, 0.2f, {}, 0.2f, {}, 0.2f));
    r.add_component(newPlayerAI, Controllable(true, clientID));
    r.add_component(newPlayerAI,
        Clock("movePlayer", "keyPressingShoot", "spamProtectionShoot", "keyPressingForce", "spamProtectionForce"));
    r.add_component(newPlayerAI, Area(70.0));
    r.add_component(newPlayerAI, PlayerAI());
    return (newPlayerAI);
}

Entity CreateEntity::createShootPlayer(const sf::Vector2f &pos, Registry &r, const std::size_t &entityIDBelong)
{
    Entity newShootPlayer = r.spawn_entity();
    r.add_component(newShootPlayer, Position(pos.x + 82.5, pos.y + 21.25));
    r.add_component(newShootPlayer, Velocity(sf::Vector2i(30, 0), 0.2, 0.0));
    r.add_component(newShootPlayer, Drawable::Drawable("PS", false, sf::Vector2f(1, 1),
                                        {Drawable::FrameRect(0, 0, 16, 4)}, 80.0, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
    r.add_component(newShootPlayer, Projectile(20.0f, false, false, 0.4f, entityIDBelong));
    r.add_component(newShootPlayer, Vitality(2, 0, 2));
    r.add_component(
        newShootPlayer, Hitbox::Hitbox(pos.x + 82.5, pos.y + 21.25,
                            {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos.x + 82.5, pos.y + 21.25, 16, 4, 0.0f)},
                            entityIDBelong, Hitbox::TEAM::PLAYER));
    return (newShootPlayer);
}

Entity CreateEntity::createShootEnnemy(const sf::Vector2f &pos, Registry &r, const std::size_t &entityIDBelong)
{
    Entity newShootEnnemy = r.spawn_entity();
    r.add_component(newShootEnnemy, Position(pos));
    r.add_component(newShootEnnemy, Velocity(sf::Vector2i(-20, 0), 0.2, 0.0));
    r.add_component(newShootEnnemy, Drawable::Drawable("ES", true, sf::Vector2f(1, 1),
                                        {Drawable::FrameRect(0, 0, 7, 6), Drawable::FrameRect(7, 0, 7, 6),
                                            Drawable::FrameRect(14, 0, 7, 6), Drawable::FrameRect(21, 0, 7, 6)},
                                        0.2, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
    r.add_component(newShootEnnemy, Projectile(20.0f, false, false, 0.4f, entityIDBelong));
    r.add_component(newShootEnnemy, Vitality(2, 0, 2));
    r.add_component(newShootEnnemy, Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos, 7, 6, 0.0f)},
                                        entityIDBelong, Hitbox::TEAM::ENNEMY));
    return (newShootEnnemy);
}

Entity CreateEntity::createShootEnnemy(const sf::Vector2f &pos, Registry &r, const std::size_t &entityIDBelong,
    const float damage, const sf::Vector2i &newVelocity)
{
    Entity newShootEnnemy = r.spawn_entity();
    r.add_component(newShootEnnemy, Position(pos.x - 30, pos.y));
    r.add_component(newShootEnnemy, Velocity(newVelocity, 0.2, 0.0));
    r.add_component(newShootEnnemy, Drawable::Drawable("ES", true, sf::Vector2f(1, 1),
                                        {Drawable::FrameRect(0, 0, 7, 6), Drawable::FrameRect(7, 0, 7, 6),
                                            Drawable::FrameRect(14, 0, 7, 6), Drawable::FrameRect(21, 0, 7, 6)},
                                        0.2, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
    r.add_component(newShootEnnemy, Projectile(damage, false, false, 0.4f, entityIDBelong));
    r.add_component(newShootEnnemy, Vitality(2, 0, 2));
    r.add_component(newShootEnnemy, Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos, 7, 6, 0.0f)},
                                        entityIDBelong, Hitbox::TEAM::ENNEMY));
    return (newShootEnnemy);
}

Entity CreateEntity::createBigLaser(sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong,
    const float damage, const sf::Vector2i &newVelocity)
{
    Entity newLaser = r.spawn_entity();
    r.add_component(newLaser, Position(pos.x - 30, pos.y));
    r.add_component(newLaser, Velocity(newVelocity, 0.2, 0.0));
    r.add_component(newLaser, Projectile(damage, false, false, 0.4f, entityIDBelong));
    r.add_component(newLaser, Drawable::Drawable("EBL", true, sf::Vector2f(1, 1),
                                  {Drawable::FrameRect(0, 0, 48, 4), Drawable::FrameRect(48, 0, 48, 4),
                                      Drawable::FrameRect(96, 0, 48, 4), Drawable::FrameRect(144, 0, 48, 4)},
                                  0.2, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
    r.add_component(newLaser, Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos, 48, 4, 0.0f)},
                                  entityIDBelong, Hitbox::TEAM::ENNEMY));
    return (newLaser);
}

Entity CreateEntity::createShootForce(const sf::Vector2f &pos, Registry &r, const std::size_t &entityIDBelong,
    const bool toTheRight, const std::size_t level)
{
    Entity newForceShot = r.spawn_entity();
    if (toTheRight) {
        r.add_component(newForceShot, Velocity(sf::Vector2i(25, 0), 0.2, 0.0));
        switch (level) {
        case 0:
            {
                r.add_component(newForceShot, Position(pos.x + 24, pos.y + 9));
                r.add_component(
                    newForceShot, Drawable::Drawable("FS1R", false, sf::Vector2f(1, 1),
                                      {Drawable::FrameRect(0, 0, 16, 4)}, 15.0, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
                r.add_component(newForceShot, Projectile(10.0f, false, false, 0.4f, entityIDBelong));
                r.add_component(newForceShot, Vitality(2, 0, 2));
                r.add_component(
                    newForceShot, Hitbox::Hitbox(pos.x + 24, pos.y + 9,
                                      {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos.x + 24, pos.y + 9, 16, 4, 0.0f)},
                                      entityIDBelong, Hitbox::TEAM::PLAYER));
                break;
            }
        case 1:
            {
                r.add_component(newForceShot, Position(pos.x + 28, pos.y + 3));
                r.add_component(newForceShot, Drawable::Drawable("FS2RT", true, sf::Vector2f(1, 1),
                                                  {Drawable::FrameRect(0, 0, 34, 4), Drawable::FrameRect(34, 0, 34, 4)},
                                                  0.1, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
                r.add_component(newForceShot, Projectile(20.0f, false, false, 0.4f, entityIDBelong));
                r.add_component(newForceShot, Vitality(2, 0, 2));
                r.add_component(newForceShot,
                    Hitbox::Hitbox(pos.x + 28, pos.y + 12,
                        {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos.x + 28, pos.y + 12, 34, 4, 0.0f)},
                        entityIDBelong, Hitbox::TEAM::PLAYER));

                Entity newForceShotBottom = r.spawn_entity();
                r.add_component(newForceShotBottom, Velocity(sf::Vector2i(25, 0), 0.2, 0.0));
                r.add_component(newForceShotBottom, Position(pos.x + 28, pos.y + 21));
                r.add_component(
                    newForceShotBottom, Drawable::Drawable("FS2RB", true, sf::Vector2f(1, 1),
                                            {Drawable::FrameRect(0, 0, 34, 4), Drawable::FrameRect(34, 0, 34, 4)}, 0.1,
                                            {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
                r.add_component(newForceShotBottom, Projectile(20.0f, false, false, 0.4f, entityIDBelong));
                r.add_component(newForceShotBottom, Vitality(2, 0, 2));
                r.add_component(newForceShotBottom,
                    Hitbox::Hitbox(pos.x + 28, pos.y + 12,
                        {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos.x + 28, pos.y + 12, 34, 4, 0.0f)},
                        entityIDBelong, Hitbox::TEAM::PLAYER));
                break;
            }
        case 2:
            {
                r.add_component(newForceShot, Position(pos.x + 32, pos.y + 17));
                r.add_component(
                    newForceShot, Drawable::Drawable("FS3R", true, sf::Vector2f(1, 1),
                                      {Drawable::FrameRect(0, 0, 66, 32), Drawable::FrameRect(66, 0, 66, 32),
                                          Drawable::FrameRect(132, 0, 66, 32), Drawable::FrameRect(198, 0, 66, 32),
                                          Drawable::FrameRect(264, 0, 66, 32), Drawable::FrameRect(330, 0, 66, 32)},
                                      0.2, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
                r.add_component(newForceShot, Projectile(20.0f, false, true, 0.4f, entityIDBelong));
                r.add_component(newForceShot, Vitality(20, 0, 2));
                r.add_component(newForceShot,
                    Hitbox::Hitbox(pos.x + 32, pos.y + 17,
                        {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos.x + 32, pos.y + 17, 66, 32, 0.0f)},
                        entityIDBelong, Hitbox::TEAM::PLAYER));
                break;
            }

        default:
            break;
        }
    } else {
        r.add_component(newForceShot, Velocity(sf::Vector2i(-25, 0), 0.2, 0.0));
        switch (level) {
        case 0:
            {
                r.add_component(newForceShot, Position(pos.x - 24, pos.y - 9));
                r.add_component(
                    newForceShot, Drawable::Drawable("FS1L", false, sf::Vector2f(1, 1),
                                      {Drawable::FrameRect(0, 0, 16, 4)}, 15.0, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
                r.add_component(newForceShot, Projectile(10.0f, false, false, 0.4f, entityIDBelong));
                r.add_component(newForceShot, Vitality(2, 0, 2));
                r.add_component(
                    newForceShot, Hitbox::Hitbox(pos.x - 24, pos.y - 9,
                                      {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos.x - 24, pos.y - 9, 16, 4, 0.0f)},
                                      entityIDBelong, Hitbox::TEAM::PLAYER));
                break;
            }
        case 1:
            {
                r.add_component(newForceShot, Position(pos.x - 28, pos.y + 3));
                r.add_component(newForceShot, Drawable::Drawable("FS2LT", true, sf::Vector2f(1, 1),
                                                  {Drawable::FrameRect(0, 0, 34, 4), Drawable::FrameRect(34, 0, 34, 4)},
                                                  0.1, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
                r.add_component(newForceShot, Projectile(20.0f, false, false, 0.4f, entityIDBelong));
                r.add_component(newForceShot, Vitality(2, 0, 2));
                r.add_component(
                    newForceShot, Hitbox::Hitbox(pos.x - 28, pos.y + 3,
                                      {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos.x - 28, pos.y + 3, 34, 4, 0.0f)},
                                      entityIDBelong, Hitbox::TEAM::PLAYER));

                Entity newForceShotBottom = r.spawn_entity();
                r.add_component(newForceShotBottom, Velocity(sf::Vector2i(-25, 0), 0.2, 0.0));
                r.add_component(newForceShotBottom, Position(pos.x - 28, pos.y + 21));
                r.add_component(
                    newForceShotBottom, Drawable::Drawable("FS2LB", true, sf::Vector2f(1, 1),
                                            {Drawable::FrameRect(0, 0, 34, 4), Drawable::FrameRect(34, 0, 34, 4)}, 0.1,
                                            {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
                r.add_component(newForceShotBottom, Projectile(20.0f, false, false, 0.4f, entityIDBelong));
                r.add_component(newForceShotBottom, Vitality(2, 0, 2));
                r.add_component(newForceShotBottom,
                    Hitbox::Hitbox(pos.x - 28, pos.y + 21,
                        {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos.x - 28, pos.y + 21, 34, 4, 0.0f)},
                        entityIDBelong, Hitbox::TEAM::PLAYER));
                break;
            }
        case 2:
            {
                r.add_component(newForceShot, Position(pos.x - 32, pos.y - 17));
                r.add_component(
                    newForceShot, Drawable::Drawable("FS3L", true, sf::Vector2f(1, 1),
                                      {Drawable::FrameRect(0, 0, 66, 32), Drawable::FrameRect(66, 0, 66, 32),
                                          Drawable::FrameRect(132, 0, 66, 32), Drawable::FrameRect(198, 0, 66, 32),
                                          Drawable::FrameRect(264, 0, 66, 32), Drawable::FrameRect(330, 0, 66, 32)},
                                      0.2, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
                r.add_component(newForceShot, Projectile(20.0f, false, true, 0.4f, entityIDBelong));
                r.add_component(newForceShot, Vitality(2, 0, 2));
                r.add_component(newForceShot,
                    Hitbox::Hitbox(pos.x - 32, pos.y - 17,
                        {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos.x - 32, pos.y - 17, 66, 32, 0.0f)},
                        entityIDBelong, Hitbox::TEAM::PLAYER));
                break;
            }

        default:
            break;
        }
    }
    return (newForceShot);
}

Entity CreateEntity::createLinearShooterHorizontal(sf::Vector2f pos, Registry &r)
{
    Entity newLinearShooterHorizontal = r.spawn_entity();
    r.add_component(newLinearShooterHorizontal, Position(pos));
    r.add_component(newLinearShooterHorizontal, Vitality(20, 3, 20));
    r.add_component(newLinearShooterHorizontal, Ennemy(3, std::make_shared<LinearShooter>(1.5f, true)));
    r.add_component(newLinearShooterHorizontal, Velocity(sf::Vector2i(-1, 0), 0.0, 0.01));
    r.add_component(newLinearShooterHorizontal,
        Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos, 33, 28, 0.0f)},
            newLinearShooterHorizontal, Hitbox::TEAM::ENNEMY));
    r.add_component(newLinearShooterHorizontal,
        Drawable::Drawable("LSH", true, sf::Vector2f(1.0f, 1.0f),
            {Drawable::FrameRect(0, 0, 33, 28), Drawable::FrameRect(33, 0, 33, 28), Drawable::FrameRect(66, 0, 33, 28)},
            0.1f, {}, 0.1f, {}, 0.1f, {}, 0.1f, {}, 0.1f));
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
    r.add_component(newLinearShooterVertical, Velocity(sf::Vector2i(-1, 0), 0.0, 0.01));
    r.add_component(
        newLinearShooterVertical, Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos, 33, 22, 0.0f)},
                                      newLinearShooterVertical, Hitbox::TEAM::ENNEMY));
    r.add_component(
        newLinearShooterVertical, Drawable::Drawable("LSV", true, sf::Vector2f(1.0f, 1.0f),
                                      {Drawable::FrameRect(0, 0, 33, 22), Drawable::FrameRect(33, 0, 33, 22),
                                          Drawable::FrameRect(66, 0, 33, 22), Drawable::FrameRect(99, 0, 33, 22),
                                          Drawable::FrameRect(132, 0, 33, 22), Drawable::FrameRect(165, 0, 33, 22),
                                          Drawable::FrameRect(198, 0, 33, 22), Drawable::FrameRect(231, 0, 33, 22)},
                                      0.1f, {}, 0.1f, {}, 0.1f, {}, 0.1f, {}, 0.1f));
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
    r.add_component(newTpShooter, Velocity(sf::Vector2i(-1, 0), 0.0, 0.01));
    r.add_component(newTpShooter, Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos, 33, 31, 0.0f)},
                                      newTpShooter, Hitbox::TEAM::ENNEMY));
    r.add_component(newTpShooter,
        Drawable::Drawable("TP", true, sf::Vector2f(1.0f, 1.0f),
            {Drawable::FrameRect(0, 0, 33, 31), Drawable::FrameRect(33, 0, 33, 31), Drawable::FrameRect(66, 0, 33, 31)},
            0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f));
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
    r.add_component(newSinusoidaleShooter, Velocity(sf::Vector2i(-1, 0), 0.0, 0.01));
    r.add_component(
        newSinusoidaleShooter, Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, pos, 21, 24, 0.0f)},
                                   newSinusoidaleShooter, Hitbox::TEAM::ENNEMY));
    r.add_component(
        newSinusoidaleShooter, Drawable::Drawable("SS", true, sf::Vector2f(1.0f, 1.0f),
                                   {Drawable::FrameRect(0, 0, 21, 24), Drawable::FrameRect(21, 0, 21, 24),
                                       Drawable::FrameRect(42, 0, 21, 24), Drawable::FrameRect(63, 0, 21, 24),
                                       Drawable::FrameRect(84, 0, 21, 24), Drawable::FrameRect(105, 0, 21, 24),
                                       Drawable::FrameRect(126, 0, 21, 24), Drawable::FrameRect(147, 0, 21, 24)},
                                   0.1f, {}, 0.1f, {}, 0.1f, {}, 0.1f, {}, 0.1f));
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
    r.add_component(newForce, Velocity(sf::Vector2i(2, 0), 0.0, 0.01));
    r.add_component(newForce, Drawable::Drawable("Force1", true, sf::Vector2f(1.0f, 1.0f),
                                  {{Drawable::FrameRect(0, 0, 24, 18), Drawable::FrameRect(24, 0, 24, 18),
                                      Drawable::FrameRect(48, 0, 24, 18), Drawable::FrameRect(72, 0, 24, 18),
                                      Drawable::FrameRect(96, 0, 24, 18), Drawable::FrameRect(110, 0, 24, 18)}},
                                  0.1f, {}, 0.1f, {}, 0.1f, {}, 0.1f, {}, 0.1f));
    r.add_component(newForce, Force(pos.x));
    r.add_component(newForce, Area(55.0));
    return (newForce);
}

Entity CreateEntity::createAlienEmperor(sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong)
{
    Entity newAlienE = r.spawn_entity();
    r.add_component(newAlienE, Position(pos));
    r.add_component(newAlienE, Velocity(sf::Vector2i(-2, 0), 4.0, 0.01));
    r.add_component(newAlienE, Ennemy(15, std::make_shared<AlienEmperor>(0.2f)));
    r.add_component(
        newAlienE, Hitbox::Hitbox(pos,
                       {Hitbox::RectHitbox(Hitbox::RECTANGLE, sf::Vector2f(pos.x + 300, pos.y + 400), 150, 120, false)},
                       entityIDBelong, Hitbox::ENNEMY));
    r.add_component(newAlienE, Vitality(2500, 11));
    r.add_component(newAlienE, Drawable::Drawable("AlienEmperor", true, sf::Vector2f(4, 4),
                                   {Drawable::FrameRect(0, 0, 162, 213), Drawable::FrameRect(162, 0, 162, 213),
                                       Drawable::FrameRect(324, 0, 162, 213), Drawable::FrameRect(324, 213, 162, 213),
                                       Drawable::FrameRect(162, 213, 162, 213), Drawable::FrameRect(0, 213, 162, 213)},
                                   0.6f, {}, 0.6f, {}, 0.6f, {}, 0.6f, {}, 0.6f));
    return (newAlienE);
}

Entity CreateEntity::createSpatialDustman(sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong)
{
    Entity newSpatialD = r.spawn_entity();

    r.add_component(newSpatialD, Position(pos));
    r.add_component(newSpatialD, Velocity(sf::Vector2i(-2, 0), 4.0, 0.01));
    r.add_component(newSpatialD, Ennemy(16, std::make_shared<SpatialDustman>(0.2f)));
    r.add_component(
        newSpatialD, Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::RECTANGLE, pos, 65 * 4, 60 * 4, false)},
                         entityIDBelong, Hitbox::ENNEMY));
    r.add_component(newSpatialD, Vitality(1500, 12));
    r.add_component(newSpatialD, Drawable::Drawable("SpatialDustman", true, sf::Vector2f(4, 4),
                                     {Drawable::FrameRect(0, 0, 63, 60), Drawable::FrameRect(65, 0, 63, 60),
                                         Drawable::FrameRect(131, 0, 63, 60), Drawable::FrameRect(197, 0, 63, 60),
                                         Drawable::FrameRect(131, 0, 63, 60), Drawable::FrameRect(65, 0, 63, 60)},
                                     0.6f, {}, 0.6f, {}, 0.6f, {}, 0.6f, {}, 0.6f));
    return (newSpatialD);
}

Entity CreateEntity::createBigShip(sf::Vector2f pos, Registry &r, const std::size_t &entityIDBelong)
{
    Entity newBigShip = r.spawn_entity();

    r.add_component(newBigShip, Position(pos));
    r.add_component(newBigShip, Ennemy(17, std::make_shared<BigShip>(0.2f)));
    r.add_component(newBigShip,
        Hitbox::Hitbox(pos, {Hitbox::RectHitbox(Hitbox::RECTANGLE, pos, 180 * 4, 148 * 4, false)}, 10, Hitbox::ENNEMY));
    r.add_component(newBigShip, Vitality(2000, 13));
    r.add_component(newBigShip, Velocity(sf::Vector2i(-2, 0), 0.0, 0.01));
    r.add_component(newBigShip, Drawable::Drawable("BigShip", true, sf::Vector2f(4, 4),
                                    {Drawable::FrameRect(0, 0, 180, 148), Drawable::FrameRect(189, 0, 180, 148)}, 0.2f,
                                    {}, 0.6f, {}, 0.6f, {}, 0.6f, {}, 0.6f));
    return (newBigShip);
}

Entity CreateEntity::createOneUpBonus(sf::Vector2f pos, Registry &r)
{
    Entity newOneUpBonus = r.spawn_entity();

    r.add_component(newOneUpBonus, Position(pos));
    r.add_component(newOneUpBonus, Velocity(sf::Vector2i(-1, 0), 0.0, 0.01));
    r.add_component(
        newOneUpBonus, Drawable::Drawable("OneUpBonus", false, sf::Vector2f(3.0f, 3.0f),
                           {Drawable::FrameRect(0, 0, 33, 33)}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f));
    r.add_component(newOneUpBonus, Area(70.0));
    r.add_component(newOneUpBonus, Bonus(12, std::make_shared<OneUp>(20)));
    r.add_component(newOneUpBonus, Drawable::Drawable("BOU", false, sf::Vector2f(1, 1),
                                       {Drawable::FrameRect(0, 0, 16, 16)}, 15.0f, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
    return (newOneUpBonus);
}

Entity CreateEntity::createSpeedBonus(sf::Vector2f pos, Registry &r)
{
    Entity newSpeedBonus = r.spawn_entity();

    r.add_component(newSpeedBonus, Position(pos));
    r.add_component(newSpeedBonus, Velocity(sf::Vector2i(-1, 0), 0.0, 0.01));
    r.add_component(
        newSpeedBonus, Drawable::Drawable("SpeedBonus", false, sf::Vector2f(3.0f, 3.0f),
                           {Drawable::FrameRect(0, 0, 33, 33)}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f));
    r.add_component(newSpeedBonus, Area(70.0));
    r.add_component(newSpeedBonus, Bonus(11, std::make_shared<Speed>(5)));
    r.add_component(newSpeedBonus, Drawable::Drawable("BS", false, sf::Vector2f(1, 1),
                                       {Drawable::FrameRect(0, 0, 16, 16)}, 15.0f, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
    return (newSpeedBonus);
}

Entity CreateEntity::createStarBonus(sf::Vector2f pos, Registry &r)
{
    Entity newStarBonus = r.spawn_entity();

    r.add_component(newStarBonus, Position(pos));
    r.add_component(newStarBonus, Velocity(sf::Vector2i(-1, 0), 0.0, 0.01));
    r.add_component(
        newStarBonus, Drawable::Drawable("StarBonus", false, sf::Vector2f(3.0f, 3.0f),
                          {Drawable::FrameRect(0, 0, 33, 33)}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f, {}, 0.2f));
    r.add_component(newStarBonus, Area(70.0));
    r.add_component(newStarBonus, Bonus(14, std::make_shared<Star>(5.0f)));
    r.add_component(newStarBonus, Drawable::Drawable("BST", false, sf::Vector2f(1, 1),
                                      {Drawable::FrameRect(0, 0, 16, 16)}, 15.0f, {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
    return (newStarBonus);
}

Entity CreateEntity::createUpgradeForceBonus(sf::Vector2f pos, Registry &r)
{
    Entity newUpgradeForce = r.spawn_entity();

    r.add_component(newUpgradeForce, Position(pos));
    r.add_component(newUpgradeForce, Velocity(sf::Vector2i(-1, 0), 0.0, 0.01));
    r.add_component(newUpgradeForce, Area(70.0));
    r.add_component(newUpgradeForce, Bonus(13, std::make_shared<UpgradeForce>()));
    r.add_component(
        newUpgradeForce, Drawable::Drawable("BF", false, sf::Vector2f(1, 1), {Drawable::FrameRect(0, 0, 16, 16)}, 15.0f,
                             {}, 0.0, {}, 0.0, {}, 0.0, {}, 0.0));
    return (newUpgradeForce);
}
