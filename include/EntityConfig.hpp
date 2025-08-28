#pragma once

namespace EntityConfig {
    namespace Wolf {
        constexpr int kHP = 150;
        constexpr int kMaxHP = 150;
        constexpr int kDamage = 35;
        constexpr int kHunger = 5;
        constexpr int kMaxHunger = 5;
    }

    namespace Human {
        constexpr int kHP = 100;
        constexpr int kMaxHP = 100;
        constexpr int kDamage = 30;
        constexpr int kHunger = 10;
        constexpr int kMaxHunger = 10;
    }

    namespace Plant {
        constexpr int kHP = 10;
        constexpr int kMaxHP = 100;
        constexpr int kDamage = 5;
    }

    namespace Wall {
        constexpr int kHP = 300;
        constexpr int kMaxHP = 300;
    }
}