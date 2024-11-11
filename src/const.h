////////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////

#ifndef __CONST__
#define __CONST__
#include "definitions.h"

enum OperatingSystem_t
{
	CLIENTOS_LINUX		= 0x01,
	CLIENTOS_WINDOWS	= 0x02
};

enum MagicEffect_t
{
	CONST_ME_DRAWBLOOD			= 0x00,
	CONST_ME_LOSEENERGY		= 0x01,
	CONST_ME_POFF				= 0x02,
	CONST_ME_BLOCKHIT			= 0x03,
	CONST_ME_EXPLOSIONAREA		= 0x04,
	CONST_ME_EXPLOSIONHIT	= 0x05,
	CONST_ME_FIREAREA			= 0x06,
	CONST_ME_YELLOW_RINGS		= 0x07,
	CONST_ME_GREEN_RINGS		= 0x08,
	CONST_ME_HITAREA			= 0x09,
	CONST_ME_TELEPORT			= 0x0A, //10
	CONST_ME_ENERGYHIT		= 0x0B, //11
	CONST_ME_MAGIC_BLUE			= 0x0C, //12
	CONST_ME_MAGIC_RED			= 0x0D, //13
	CONST_ME_MAGIC_GREEN		= 0x0E, //14
	CONST_ME_HITBYFIRE			= 0x0F, //15
	CONST_ME_HITBYPOISON				= 0x10, //16
	CONST_ME_MORTAREA			= 0x11, //17
	CONST_ME_SOUND_GREEN		= 0x12, //18
	CONST_ME_SOUND_RED			= 0x13, //19
	CONST_ME_POISONAREA		= 0x14, //20
	CONST_ME_SOUND_YELLOW		= 0x15, //21
	CONST_ME_SOUND_PURPLE		= 0x16, //22
	CONST_ME_SOUND_BLUE			= 0x17, //23
	CONST_ME_SOUND_WHITE		= 0x18, //24
	CONST_ME_BUBBLES			= 0x19, //25
	CONST_ME_CRAPS				= 0x1A, //26
	CONST_ME_GIFT_WRAPS			= 0x1B, //27
	CONST_ME_FIREWORK_YELLOW	= 0x1C, //28
	CONST_ME_FIREWORK_RED		= 0x1D, //29
	CONST_ME_FIREWORK_BLUE		= 0x1E, //30
	CONST_ME_STUN				= 0x1F, //31
	CONST_ME_SLEEP				= 0x20, //32
	CONST_ME_WATERCREATURE		= 0x21, //33
	CONST_ME_GROUNDSHAKER		= 0x22, //34
	CONST_ME_HEARTS				= 0x23, //35
	CONST_ME_FIREATTACK			= 0x24, //36
	CONST_ME_ENERGYAREA		= 0x25, //37
	CONST_ME_SMALLCLOUDS		= 0x26, //38
	CONST_ME_HOLYDAMAGE			= 0x27, //39
	CONST_ME_BIGCLOUDS			= 0x28, //40
	CONST_ME_ICEAREA			= 0x29, //41
	CONST_ME_ICETORNADO			= 0x2A, //42
	CONST_ME_ICEATTACK			= 0x2B, //43
	CONST_ME_STONES				= 0x2C, //44
	CONST_ME_SMALLPLANTS		= 0x2D, //45
	CONST_ME_CARNIPHILA			= 0x2E, //46
	CONST_ME_PURPLEENERGY		= 0x2F, //47
	CONST_ME_YELLOWENERGY		= 0x30, //48
	CONST_ME_HOLYAREA			= 0x31, //49
	CONST_ME_BIGPLANTS			= 0x32, //50
	CONST_ME_CAKE				= 0x33, //51
	CONST_ME_GIANTICE			= 0x34, //52
	CONST_ME_WATERSPLASH		= 0x35, //53
	CONST_ME_PLANTATTACK		= 0x36, //54
	CONST_ME_TUTORIALARROW		= 0x37, //55
	CONST_ME_TUTORIALSQUARE		= 0x38, //56
	CONST_ME_MIRRORHORIZONTAL	= 0x39, //57
	CONST_ME_MIRRORVERTICAL		= 0x3A, //58
	CONST_ME_SKULLHORIZONTAL	= 0x3B, //59
	CONST_ME_SKULLVERTICAL		= 0x3C, //60
	CONST_ME_ASSASSIN			= 0x3D, //61
	CONST_ME_STEPSHORIZONTAL	= 0x3E, //62
	CONST_ME_BLOODYSTEPS		= 0x3F, //63
	CONST_ME_STEPSVERTICAL		= 0x40, //64
	CONST_ME_YALAHARIGHOST		= 0x41, //65
	CONST_ME_BATS				= 0x42, //66
	CONST_ME_SMOKE				= 0x43, //67
	CONST_ME_INSECTS			= 0x44, //68
	CONST_ME_DRAGONHEAD			= 0x45, //69
	CONST_ME_LAST				= CONST_ME_DRAGONHEAD,

	//for internal use, dont send to client
	CONST_ME_NONE				= 0xFF,
	CONST_ME_UNKNOWN			= 0xFFFF
};

enum ShootEffect_t
{
	CONST_ANI_SPEAR			= 0x00,
	CONST_ANI_BOLT			= 0x01,
	CONST_ANI_ARROW			= 0x02,
	CONST_ANI_FIRE			= 0x03,
	CONST_ANI_ENERGY			= 0x04,
	CONST_ANI_POISONARROW	= 0x05,
	CONST_ANI_BURSTARROW		= 0x06,
	CONST_ANI_THROWINGSTAR	= 0x07,
	CONST_ANI_THROWINGKNIFE	= 0x08,
	CONST_ANI_SMALLSTONE		= 0x09,
	CONST_ANI_DEATH			= 0x0A, //10
	CONST_ANI_LARGEROCK		= 0x0B, //11
	CONST_ANI_SNOWBALL		= 0x0C, //12
	CONST_ANI_POWERBOLT		= 0x0D, //13
	CONST_ANI_POISON	= 0x0E, //14
	CONST_ANI_INFERNALBOLT	= 0x0F, //15
	CONST_ANI_HUNTINGSPEAR	= 0x10, //16
	CONST_ANI_ENCHANTEDSPEAR	= 0x11, //17
	CONST_ANI_REDSTAR		= 0x12, //18
	CONST_ANI_GREENSTAR		= 0x13, //19
	CONST_ANI_ROYALSPEAR		= 0x14, //20
	CONST_ANI_SNIPERARROW	= 0x15, //21
	CONST_ANI_ONYXARROW		= 0x16, //22
	CONST_ANI_PIERCINGBOLT	= 0x17, //23
	CONST_ANI_WHIRLWINDSWORD	= 0x18, //24
	CONST_ANI_WHIRLWINDAXE	= 0x19, //25
	CONST_ANI_WHIRLWINDCLUB	= 0x1A, //26
	CONST_ANI_ETHEREALSPEAR	= 0x1B, //27
	CONST_ANI_ICE			= 0x1C, //28
	CONST_ANI_EARTH			= 0x1D, //29
	CONST_ANI_HOLY			= 0x1E, //30
	CONST_ANI_SUDDENDEATH	= 0x1F, //31
	CONST_ANI_FLASHARROW		= 0x20, //32
	CONST_ANI_FLAMMINGARROW	= 0x21, //33
	CONST_ANI_SHIVERARROW	= 0x22, //34
	CONST_ANI_ENERGYBALL		= 0x23, //35
	CONST_ANI_SMALLICE		= 0x24, //36
	CONST_ANI_SMALLHOLY		= 0x25, //37
	CONST_ANI_SMALLEARTH		= 0x26, //38
	CONST_ANI_EARTHARROW		= 0x27, //39
	CONST_ANI_EXPLOSION		= 0x28, //40
	CONST_ANI_CAKE			= 0x29, //41
	CONST_ANI_LAST			= CONST_ANI_CAKE,

	//for internal use, dont send to client
	CONST_ANI_WEAPONTYPE		= 0xFE, //254
	CONST_ANI_NONE			= 0xFF,
	CONST_ANI_UNKNOWN		= 0xFFFF
};

enum SpeakClasses
{
	SPEAK_CLASS_NONE	= 0x00,
	SPEAK_CLASS_FIRST 	= 0x01,
	SPEAK_SAY		= SPEAK_CLASS_FIRST,
	SPEAK_WHISPER		= 0x02,
	SPEAK_YELL		= 0x03,
	SPEAK_PRIVATE_PN	= 0x04,
	SPEAK_PRIVATE_NP	= 0x05,
	SPEAK_PRIVATE		= 0x06,
	SPEAK_CHANNEL_Y		= 0x07,
	SPEAK_CHANNEL_W		= 0x08,
	SPEAK_RVR_CHANNEL	= 0x09,
	SPEAK_RVR_ANSWER	= 0x0A,
	SPEAK_RVR_CONTINUE	= 0x0B,
	SPEAK_BROADCAST		= 0x0C,
	SPEAK_CHANNEL_RN	= 0x0D, //red - #c text
	SPEAK_PRIVATE_RED	= 0x0E,	//@name@text
	SPEAK_CHANNEL_O		= 0x0F,
	//SPEAK_UNKNOWN_1		= 0x10,
	SPEAK_CHANNEL_RA	= 0x11,	//red anonymous - #d text
	//SPEAK_UNKNOWN_2		= 0x12,
	SPEAK_MONSTER_SAY	= 0x13,
	SPEAK_MONSTER_YELL	= 0x14,
	SPEAK_CLASS_LAST 	= SPEAK_MONSTER_YELL
};

enum MessageClasses
{
	MESSAGE_FIRST			= 0x12,
	MESSAGE_STATUS_CONSOLE_RED		= MESSAGE_FIRST, /*Red message in the console*/
	MESSAGE_EVENT_ORANGE		= 0x13, /*Orange message in the console*/
	MESSAGE_STATUS_CONSOLE_ORANGE	= 0x14, /*Orange message in the console*/
	MESSAGE_STATUS_WARNING		= 0x15, /*Red message in game window and in the console*/
	MESSAGE_EVENT_ADVANCE		= 0x16, /*White message in game window and in the console*/
	MESSAGE_EVENT_DEFAULT		= 0x17, /*White message at the bottom of the game window and in the console*/
	MESSAGE_STATUS_DEFAULT		= 0x18, /*White message at the bottom of the game window and in the console*/
	MESSAGE_INFO_DESCR			= 0x19, /*Green message in game window and in the console*/
	MESSAGE_STATUS_SMALL		= 0x1A, /*White message at the bottom of the game window"*/
	MESSAGE_STATUS_CONSOLE_BLUE		= 0x1B, /*Blue message in the console*/
	MESSAGE_LAST			= MESSAGE_STATUS_CONSOLE_BLUE
};

enum MapMarks_t
{
	MAPMARK_TICK		= 0x00,
	MAPMARK_QUESTION	= 0x01,
	MAPMARK_EXCLAMATION	= 0x02,
	MAPMARK_STAR		= 0x03,
	MAPMARK_CROSS		= 0x04,
	MAPMARK_TEMPLE		= 0x05,
	MAPMARK_KISS		= 0x06,
	MAPMARK_SHOVEL		= 0x07,
	MAPMARK_SWORD		= 0x08,
	MAPMARK_FLAG		= 0x09,
	MAPMARK_LOCK		= 0x0A,
	MAPMARK_BAG			= 0x0B,
	MAPMARK_SKULL		= 0x0C,
	MAPMARK_DOLLAR		= 0x0D,
	MAPMARK_REDNORTH	= 0x0E,
	MAPMARK_REDSOUTH	= 0x0F,
	MAPMARK_REDEAST		= 0x10,
	MAPMARK_REDWEST		= 0x11,
	MAPMARK_GREENNORTH	= 0x12,
	MAPMARK_GREENSOUTH	= 0x13
};

enum FluidColors_t
{
	FLUID_EMPTY		= 0x00,
	FLUID_BLUE		= 0x01,
	FLUID_RED		= 0x02,
	FLUID_BROWN		= 0x03,
	FLUID_GREEN		= 0x04,
	FLUID_YELLOW	= 0x05,
	FLUID_WHITE		= 0x06,
	FLUID_PURPLE	= 0x07
};

enum FluidTypes_t
{
	FLUID_NONE			= FLUID_EMPTY,
	FLUID_WATER			= FLUID_BLUE,
	FLUID_BLOOD			= FLUID_RED,
	FLUID_BEER			= FLUID_BROWN,
	FLUID_SLIME			= FLUID_GREEN,
	FLUID_LEMONADE		= FLUID_YELLOW,
	FLUID_MILK			= FLUID_WHITE,
	FLUID_MANA			= FLUID_PURPLE,

	FLUID_LIFE			= FLUID_RED + 8,
	FLUID_OIL			= FLUID_BROWN + 8,
	FLUID_URINE			= FLUID_YELLOW + 8,
	FLUID_COCONUTMILK	= FLUID_WHITE + 8,
	FLUID_WINE			= FLUID_PURPLE + 8,

	FLUID_MUD			= FLUID_BROWN + 16,
	FLUID_FRUITJUICE	= FLUID_YELLOW + 16,

	FLUID_LAVA			= FLUID_RED + 24,
	FLUID_RUM			= FLUID_BROWN + 24,
	FLUID_SWAMP			= FLUID_GREEN + 24,

	FLUID_TEA			= FLUID_BROWN + 32,
	FLUID_MEAD			= FLUID_BROWN + 40
};

const uint8_t reverseFluidMap[] =
{
	FLUID_EMPTY,
	FLUID_WATER,
	FLUID_MANA,
	FLUID_BEER,
	FLUID_EMPTY,
	FLUID_BLOOD,
	FLUID_SLIME,
	FLUID_EMPTY,
	FLUID_LEMONADE,
	FLUID_MILK
};

enum ClientFluidTypes_t
{
	CLIENTFLUID_EMPTY	= 0x00,
	CLIENTFLUID_BLUE	= 0x01,
	CLIENTFLUID_PURPLE	= 0x02,
	CLIENTFLUID_BROWN_1	= 0x03,
	CLIENTFLUID_BROWN_2	= 0x04,
	CLIENTFLUID_RED		= 0x05,
	CLIENTFLUID_GREEN	= 0x06,
	CLIENTFLUID_BROWN	= 0x07,
	CLIENTFLUID_YELLOW	= 0x08,
	CLIENTFLUID_WHITE	= 0x09
};

const uint8_t fluidMap[] =
{
	CLIENTFLUID_EMPTY,
	CLIENTFLUID_BLUE,
	CLIENTFLUID_RED,
	CLIENTFLUID_BROWN_1,
	CLIENTFLUID_GREEN,
	CLIENTFLUID_YELLOW,
	CLIENTFLUID_WHITE,
	CLIENTFLUID_PURPLE
};

enum Color_t
{
	COLOR_BLACK		= 0,
	COLOR_BLUE		= 5,
	COLOR_GREEN		= 18,
	COLOR_TEAL		= 35,
	COLOR_LIGHTGREEN	= 66,
	COLOR_DARKBROWN		= 78,
	COLOR_LIGHTBLUE		= 89,
	COLOR_DARKRED		= 108,
	COLOR_DARKPURPLE	= 112,
	COLOR_BROWN		= 120,
	COLOR_GREY		= 129,
	COLOR_DARKPINK		= 152,
	COLOR_PURPLE		= 154,
	COLOR_DARKORANGE	= 156,
	COLOR_RED		= 180,
	COLOR_PINK		= 190,
	COLOR_ORANGE		= 192,
	COLOR_DARKYELLOW	= 205,
	COLOR_YELLOW		= 210,
	COLOR_WHITE		= 215,

	COLOR_NONE		= 255,
	COLOR_UNKNOWN		= 256
};

enum Icons_t
{
	ICON_NONE = 0,
	ICON_POISON = 1 << 0,
	ICON_BURN = 1 << 1,
	ICON_ENERGY = 1 << 2,
	ICON_DRUNK = 1 << 3,
	ICON_MANASHIELD = 1 << 4,
	ICON_PARALYZE = 1 << 5,
	ICON_HASTE = 1 << 6,
	ICON_SWORDS = 1 << 7,
	ICON_DROWNING = 1 << 8,
	ICON_FREEZING = 1 << 9,
	ICON_DAZZLED = 1 << 10,
	ICON_CURSED = 1 << 11,
	ICON_BUFF = 1 << 12,
	ICON_PZ = 1 << 13,
	ICON_PROTECTIONZONE = 1 << 14
};

enum skills_t
{
	SKILL_FIRST = 0,
	SKILL_FIST = SKILL_FIRST,
	SKILL_CLUB,
	SKILL_SWORD,
	SKILL_AXE,
	SKILL_DIST,
	SKILL_SHIELD,
	SKILL_FISH,
	SKILL__MAGLEVEL,
	SKILL__LEVEL,
	SKILL__EXPERIENCE,
	SKILL_LAST = SKILL_FISH,
	SKILL__LAST = SKILL__EXPERIENCE
};

enum WeaponType_t
{
	WEAPON_NONE = 0,
	WEAPON_SWORD,
	WEAPON_CLUB,
	WEAPON_AXE,
	WEAPON_DIST,
	WEAPON_SHIELD,
	WEAPON_FIST,
	WEAPON_WAND,
	WEAPON_AMMO
};

enum Ammo_t
{
	AMMO_NONE = 0,
	AMMO_BOLT,
	AMMO_ARROW,
	AMMO_SPEAR,
	AMMO_THROWINGSTAR,
	AMMO_THROWINGKNIFE,
	AMMO_STONE,
	AMMO_SNOWBALL
};

enum AmmoAction_t
{
	AMMOACTION_NONE = 0,
	AMMOACTION_REMOVECOUNT,
	AMMOACTION_REMOVECHARGE,
	AMMOACTION_MOVE,
	AMMOACTION_MOVEBACK
};

enum WieldInfo_t
{
	WIELDINFO_LEVEL		= 1,
	WIELDINFO_MAGLV		= 2,
	WIELDINFO_VOCREQ	= 4,
	WIELDINFO_PREMIUM	= 8
};

enum Skulls_t
{
	SKULL_NONE = 0,
	SKULL_YELLOW,
	SKULL_GREEN,
	SKULL_WHITE,
	SKULL_RED,
	SKULL_BLACK,
	SKULL_LAST = SKULL_BLACK
};

enum PartyShields_t
{
	SHIELD_NONE = 0,
	SHIELD_WHITEYELLOW,
	SHIELD_WHITEBLUE,
	SHIELD_BLUE,
	SHIELD_YELLOW,
	SHIELD_BLUE_SHAREDEXP,
	SHIELD_YELLOW_SHAREDEXP,
	SHIELD_BLUE_NOSHAREDEXP_BLINK,
	SHIELD_YELLOW_NOSHAREDEXP_BLINK,
	SHIELD_BLUE_NOSHAREDEXP,
	SHIELD_YELLOW_NOSHAREDEXP,
	SHIELD_LAST = SHIELD_YELLOW_NOSHAREDEXP
};

enum GuildEmblems_t
{
	EMBLEM_NONE = 0,
	EMBLEM_GREEN,
	EMBLEM_RED,
	EMBLEM_BLUE
};

enum SpellGroup_t
{
	SPELLGROUP_NONE		= 0,
	SPELLGROUP_ATTACK	= 1,
	SPELLGROUP_HEALING	= 2,
	SPELLGROUP_SUPPORT	= 3,
	SPELLGROUP_SPECIAL	= 4
};

enum item_t
{
	ITEM_FIREFIELD			= 1492,
	ITEM_FIREFIELD_SAFE		= 1500,

	ITEM_POISONFIELD		= 1496,
	ITEM_POISONFIELD_SAFE	= 1503,

	ITEM_ENERGYFIELD		= 1495,
	ITEM_ENERGYFIELD_SAFE	= 1504,

	ITEM_MAGICWALL			= 1497,
	ITEM_MAGICWALL_SAFE		= 11098,

	ITEM_WILDGROWTH			= 1499,
	ITEM_WILDGROWTH_SAFE	= 11099,

	ITEM_DEPOT				= 2594,
	ITEM_LOCKER				= 2589,

	ITEM_MALE_CORPSE		= 3058,
	ITEM_FEMALE_CORPSE		= 3065,

	ITEM_FULLSPLASH			= 2016,
	ITEM_SMALLSPLASH		= 2019,

	ITEM_PARCEL				= 2595,
	ITEM_PARCEL_STAMPED		= 2596,
	ITEM_LETTER				= 2597,
	ITEM_LETTER_STAMPED		= 2598,
	ITEM_LABEL				= 2599,

	ITEM_WATERBALL_SPLASH	= 7711,
	ITEM_WATERBALL			= 7956,

	ITEM_GOLD_COIN = 2148,
	ITEM_PLATINUM_COIN = 2152,
	ITEM_CRYSTAL_COIN = 2160,

	ITEM_STEALTH_RING		= 2202,
	ITEM_HOUSE_TRANSFER		= 1968 //read-only
};

enum PlayerFlags
{
	PlayerFlag_CannotUseCombat = 0,			//2^0 = 1
	PlayerFlag_CannotAttackPlayer,			//2^1 = 2
	PlayerFlag_CannotAttackMonster,			//2^2 = 4
	PlayerFlag_CannotBeAttacked,			//2^3 = 8
	PlayerFlag_CanConvinceAll,				//2^4 = 16
	PlayerFlag_CanSummonAll,				//2^5 = 32
	PlayerFlag_CanIllusionAll,				//2^6 = 64
	PlayerFlag_CanSenseInvisibility,		//2^7 = 128
	PlayerFlag_IgnoredByMonsters,			//2^8 = 256
	PlayerFlag_NotGainInFight,				//2^9 = 512
	PlayerFlag_HasInfiniteMana,				//2^10 = 1024
	PlayerFlag_HasInfiniteSoul,				//2^11 = 2048
	PlayerFlag_HasNoExhaustion,				//2^12 = 4096
	PlayerFlag_CannotUseSpells,				//2^13 = 8192
	PlayerFlag_CannotPickupItem,			//2^14 = 16384
	PlayerFlag_CanAlwaysLogin,				//2^15 = 32768
	PlayerFlag_CanBroadcast,				//2^16 = 65536
	PlayerFlag_CanEditHouses,				//2^17 = 131072
	PlayerFlag_CannotBeBanned,				//2^18 = 262144
	PlayerFlag_CannotBePushed,				//2^19 = 524288
	PlayerFlag_HasInfiniteCapacity,			//2^20 = 1048576
	PlayerFlag_CanPushAllCreatures,			//2^21 = 2097152
	PlayerFlag_CanTalkRedPrivate,			//2^22 = 4194304
	PlayerFlag_CanTalkRedChannel,			//2^23 = 8388608
	PlayerFlag_TalkOrangeHelpChannel,		//2^24 = 16777216
	PlayerFlag_NotGainExperience,			//2^25 = 33554432
	PlayerFlag_NotGainMana,					//2^26 = 67108864
	PlayerFlag_NotGainHealth,				//2^27 = 134217728
	PlayerFlag_NotGainSkill,				//2^28 = 268435456
	PlayerFlag_SetMaxSpeed,					//2^29 = 536870912
	PlayerFlag_SpecialVIP,					//2^30 = 1073741824
	PlayerFlag_NotGenerateLoot,				//2^31 = 2147483648
	PlayerFlag_CanTalkRedChannelAnonymous,	//2^32 = 4294967296
	PlayerFlag_IgnoreProtectionZone,		//2^33 = 8589934592
	PlayerFlag_IgnoreSpellCheck,			//2^34 = 17179869184
	PlayerFlag_IgnoreEquipCheck,			//2^35 = 34359738368
	PlayerFlag_CannotBeMuted,				//2^36 = 68719476736
	PlayerFlag_IsAlwaysPremium,				//2^37 = 137438953472
	PlayerFlag_38,							//2^38 = 274877906944 //obsolete, can be re-used
	PlayerFlag_39,							//2^39 = 549755813888 //not used by us
	PlayerFlag_ShowGroupNameInsteadOfVocation,	//2^40 = 1099511627776
	PlayerFlag_HasInfiniteStamina,			//2^41 = 2199023255552
	PlayerFlag_CannotMoveItems,				//2^42 = 4398046511104
	PlayerFlag_CannotMoveCreatures,			//2^43 = 8796093022208
	PlayerFlag_CanReportBugs,				//2^44 = 17592186044416
	PlayerFlag_45,							//2^45 = 35184372088832 //not used by us
	PlayerFlag_CannotBeSeen,				//2^46 = 70368744177664
	PlayerFlag_HideHealth,					//2^47 = 140737488355328
	PlayerFlag_CanPassThroughAllCreatures,	//2^48 = 281474976710656

	PlayerFlag_LastFlag
};

enum PlayerCustomFlags
{
	PlayerCustomFlag_AllowIdle = 0,				//2^0 = 1
	PlayerCustomFlag_CanSeePosition,			//2^1 = 2
	PlayerCustomFlag_CanSeeItemDetails,			//2^2 = 4
	PlayerCustomFlag_CanSeeCreatureDetails,		//2^3 = 8
	PlayerCustomFlag_NotSearchable,				//2^4 = 16
	PlayerCustomFlag_GamemasterPrivileges,		//2^5 = 32
	PlayerCustomFlag_CanThrowAnywhere,			//2^6 = 64
	PlayerCustomFlag_CanPushAllItems,			//2^7 = 128
	PlayerCustomFlag_CanMoveAnywhere,			//2^8 = 256
	PlayerCustomFlag_CanMoveFromFar,			//2^9 = 512
	PlayerCustomFlag_CanUseFar,					//2^10 = 1024
	PlayerCustomFlag_CanLoginMultipleCharacters,//2^11 = 2048 (account flag)
	PlayerCustomFlag_CanLogoutAnytime,			//2^12 = 4096 (account flag)
	PlayerCustomFlag_HideLevel,					//2^13 = 8192
	PlayerCustomFlag_IsProtected,				//2^14 = 16384
	PlayerCustomFlag_IsImmune,					//2^15 = 32768
	PlayerCustomFlag_NotGainSkull,				//2^16 = 65536
	PlayerCustomFlag_NotGainUnjustified,		//2^17 = 131072
	PlayerCustomFlag_IgnorePacification,		//2^18 = 262144
	PlayerCustomFlag_IgnoreLoginDelay,			//2^19 = 524288
	PlayerCustomFlag_CanStairhop,				//2^20 = 1048576
	PlayerCustomFlag_CanTurnhop,				//2^21 = 2097152
	PlayerCustomFlag_IgnoreHouseRent,			//2^22 = 4194304
	PlayerCustomFlag_CanWearAllAddons,			//2^23 = 8388608
	PlayerCustomFlag_IsWalkable,				//2^24 = 16777216
	PlayerCustomFlag_HasFullLight,				//2^25 = 33554432

	PlayerCustomFlag_LastFlag
};

//Reserved player storage key ranges
//[10000000 - 20000000]
#define PSTRG_RESERVED_RANGE_START	10000000
#define PSTRG_RESERVED_RANGE_SIZE	10000000

//[1000 - 1500]
#define PSTRG_OUTFITS_RANGE_START	(PSTRG_RESERVED_RANGE_START + 1000)
#define PSTRG_OUTFITS_RANGE_SIZE	500

//[1500 - 2000]
#define PSTRG_OUTFITSID_RANGE_START	(PSTRG_RESERVED_RANGE_START + 1500)
#define PSTRG_OUTFITSID_RANGE_SIZE	500

#define NETWORK_CRYPTOHEADER_SIZE 8
#define NETWORK_RETRY_TIMEOUT 5000
#define NETWORK_DEFAULT_SIZE 4096
#define NETWORK_HEADER_SIZE 2
#define NETWORK_MAX_SIZE 16384

#define LOCALHOST 2130706433
#define SWIMMING_OUTFIT 267
#define GRATIS_PREMIUM 65535
#define IPBAN_FLAG 128

#define IS_IN_KEYRANGE(key, range) (key >= PSTRG_##range##_START && ((key - PSTRG_##range##_START) < PSTRG_##range##_SIZE))
#endif
