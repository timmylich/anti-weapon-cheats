/*
 | English:
 - This include fixes errors related to weapon usage and prevents the use of certain cheats.
 - 1. Checks the rate of fire for firearms, preventing +C, Rapid, etc.
 - 2. Checks the rate of melee attacks, preventing damage boosters.

 | Русский:
 - Данный инклуд исправляет ошибки, связанные с использованием оружия и препятствует использованию некоторых читов.
 - 1. Проверяет скорость выстрелов с огнестрельного оружия, препятствуя +C, Rapid и т.п.
 - 2. Проверяет скорость ударов в ближнем бою, препятствуя дамагерам.

 - Author: timmylich. (originally for Brentwood Project)
 - Version: 1.0.
 - Date: 22 June 2025.
 - GitHub Repo: https://github.com/timmylich/anti-weapon-cheats

 - Connect with author:
 - VKontake: https://vk.com/timmylich
 - Telegram: https://t.me/timmylich
 - Discord: http://discordapp.com/users/523177185062682685 (@timmylich.)
*/

/*
[EN] Define as 0 before including the include to disable the rate of fire check.
[RU] Определите как 0 до подключения инклуда, чтобы отключить проверку скорости выстрелов.
*/
#if !defined AWCheats_FireRateOver
	#define AWCheats_FireRateOver 1
#endif

/*
[EN] Define as 0 before including the include to disable the rate of melee attacks check.
[RU] Определите как 0 до подключения инклуда, чтобы отключить проверку скорости ударов в ближнем бою.
*/
#if !defined AWCheats_MeleeRateOver
	#define AWCheats_MeleeRateOver 1
#endif

#if AWCheats_FireRateOver == 1 || AWCheats_MeleeRateOver == 1
	static s_MaxWeaponShootRate[] = {
		250, // 0 - Fist
		250, // 1 - Brass knuckles
		250, // 2 - Golf club
		250, // 3 - Nitestick
		250, // 4 - Knife
		250, // 5 - Bat
		250, // 6 - Shovel
		250, // 7 - Pool cue
		250, // 8 - Katana
		30, // 9 - Chainsaw
		250, // 10 - Dildo
		250, // 11 - Dildo 2
		250, // 12 - Vibrator
		250, // 13 - Vibrator 2
		250, // 14 - Flowers
		250, // 15 - Cane
		0, // 16 - Grenade
		0, // 17 - Teargas
		0, // 18 - Molotov
		90, // 19 - Vehicle M4 (custom)
		20, // 20 - Vehicle minigun (custom)
		0, // 21 - Vehicle rocket (custom)
		160, // 22 - Colt 45
		120, // 23 - Silenced
		120, // 24 - Deagle
		800, // 25 - Shotgun
		120, // 26 - Sawed-off
		120, // 27 - Spas
		50, // 28 - UZI
		90, // 29 - MP5
		90, // 30 - AK47
		90, // 31 - M4
		50, // 32 - Tec9
		800, // 33 - Cuntgun
		800, // 34 - Sniper
		0, // 35 - Rocket launcher
		0, // 36 - Heatseeker
		0, // 37 - Flamethrower
		20, // 38 - Minigun
		0, // 39 - Satchel
		0, // 40 - Detonator
		10, // 41 - Spraycan
		10, // 42 - Fire extinguisher
		0, // 43 - Camera
		0, // 44 - Night vision
		0, // 45 - Infrared
		0, // 46 - Parachute
		0, // 47 - Fake pistol
		400 // 48 - Pistol whip (custom)
	};

	static s_LastShootTick[MAX_PLAYERS];
#endif


public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	#if AWCheats_FireRateOver == 1
		if(GetTickCount() - s_LastShootTick[playerid] < s_MaxWeaponShootRate[weaponid])
		{
			return 0;
		}
		else s_LastShootTick[playerid] = GetTickCount();
	#endif


    #if defined AWCheats_OnPlayerWeaponShot
        return AWCheats_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, fX, fY, fZ);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnPlayerWeaponShot
    #undef OnPlayerWeaponShot
#else
    #define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot AWCheats_OnPlayerWeaponShot
#if defined AWCheats_OnPlayerWeaponShot
    forward AWCheats_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif


#if defined AWCheats_MeleeRateOver
	#if !defined IsMeleeWeapon
		stock IsMeleeWeapon(weaponid)
		{
			switch(weaponid)
			{
				case 0..15, 41..42, 48: return true;
				default: return false;
			}
		}
	#endif
#endif


public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	#if AWCheats_MeleeRateOver == 1
		if(IsMeleeWeapon(weaponid))
		{
			if(GetTickCount() - s_LastShootTick[playerid] < s_MaxWeaponShootRate[weaponid])
			{
				return 0;
			}
			else s_LastShootTick[playerid] = GetTickCount();
		}
	#endif


    #if defined AWCheats_OnPlayerGiveDamage
        return AWCheats_OnPlayerGiveDamage(playerid, damagedid, amount, weaponid, bodypart);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnPlayerGiveDamage
    #undef OnPlayerGiveDamage
#else
    #define _ALS_OnPlayerGiveDamage
#endif
#define OnPlayerGiveDamage AWCheats_OnPlayerGiveDamage
#if defined AWCheats_OnPlayerGiveDamage
    forward AWCheats_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart);
#endif