## [Читать на русском](README.ru.md)

## What is this?

This include fixes errors related to weapon usage and prevents the use of certain cheats in SA-MP servers.

### Features:

1. **Fire rate checking** - prevents the use of cheats like +C, Rapid and other fire rate boosters
2. **Melee attack rate checking** - prevents the use of damage boosters for melee weapons

## Installation

To use this include, simply add `anti-weapon-cheats.inc` to your code:

```cpp
#include <anti-weapon-cheats>
```

### Configuration before including

You can disable individual checks by defining the corresponding constants before including the file:

```cpp
// Disable fire rate checking
#define AWCheats_FireRateOver 0

// Disable melee attack rate checking
#define AWCheats_MeleeRateOver 0

#include <anti-weapon-cheats>
```

## How it works

### Fire rate checking
The script tracks the time between shots for each player and each weapon type. If a player shoots too quickly (faster than the set limit), the shot is blocked.

### Melee attack checking
Similarly to shooting, the script controls the attack speed of melee weapons and blocks attacks that are too frequent.

## Compatibility

The script uses standard SA-MP callbacks:
- `OnPlayerWeaponShot` - for shot checking
- `OnPlayerGiveDamage` - for melee attack checking

All callbacks are properly hooked, so the script is compatible with other modifications.

## Customizing limits

If you need to change limits for specific weapons, edit the `s_MaxWeaponShootRate` array in the include file:

```cpp
static s_MaxWeaponShootRate[] = {
    250, // 0 - Fist
    250, // 1 - Brass knuckles
    // ... modify the values you need
};
```

## Authors

**timmylich. | [VKontakte](https://vk.com/timmylich) | [Telegram](https://t.me/timmylich) | [Discord](http://discordapp.com/users/523177185062682685)**