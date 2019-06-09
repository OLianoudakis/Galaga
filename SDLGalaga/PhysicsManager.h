
#ifndef _PHYSICSMANAGER_H
#define _PHYSICSMANAGER_H

#include "PhysicsEntity.h"
#include <bitset>

class PhysicsManager
{
public:

    enum class CollisionLayers 
    {
        Friendly = 0,
        FriendlyProjectiles,
        Hostile,
        HostileProjecttiles,
        //-----------------
        MaxLayers
    };

    enum class CollisionFlags
    {
        None                 = 0x00,
        Friendly             = 0x01,
        FriendlyProjectiles  = 0x02,
        Hostile              = 0x04,
        HostileProjectiles   = 0x08
    };

private:

    static PhysicsManager* sInstance;

    std::vector<PhysicsEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
    std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

    unsigned long mLastId;

public:

    static PhysicsManager* Instance();
    static void Release();

    void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

    unsigned long RegisterEntity(PhysicsEntity* entity, CollisionLayers layer);
    void UnregisteredEntity(unsigned long id);

    void Update();

private:

    PhysicsManager();
    ~PhysicsManager();
};

inline PhysicsManager::CollisionFlags operator | (PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b)
{
    return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline PhysicsManager::CollisionFlags operator & (PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b)
{
    return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

#endif // !_PHYSICSMANAGER_H
