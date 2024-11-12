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

#ifndef __ENUMS__
#define __ENUMS__

#include <string>
#include <list>

#define AUTOID_PLAYERS 0x10000000
#define AUTOID_MONSTERS 0x40000000
#define AUTOID_NPCS 0x80000000

enum CreatureType_t
{
	CREATURETYPE_PLAYER = 0,
	CREATURETYPE_MONSTER = 1,
	CREATURETYPE_NPC = 2
};

enum DatabaseEngine_t
{
	DATABASE_ENGINE_NONE = 0,
	DATABASE_ENGINE_MYSQL,
	DATABASE_ENGINE_SQLITE
};

enum Encryption_t
{
	ENCRYPTION_PLAIN = 0,
	ENCRYPTION_MD5,
	ENCRYPTION_SHA1,
	ENCRYPTION_SHA256,
	ENCRYPTION_SHA512
};

enum GuildLevel_t
{
	GUILDLEVEL_NONE = 0,
	GUILDLEVEL_MEMBER,
	GUILDLEVEL_VICE,
	GUILDLEVEL_LEADER
};

enum Channels_t
{
	CHANNEL_GUILD = 0x00,
	CHANNEL_PARTY = 0x01,
	CHANNEL_RVR = 0x03,
	CHANNEL_HELP = 0x07,
	CHANNEL_DEFAULT = 0xFFFE, //internal usage only, there is no such channel
	CHANNEL_PRIVATE = 0xFFFF
};

enum RaceType_t
{
	RACE_NONE = 0,
	RACE_VENOM,
	RACE_BLOOD,
	RACE_UNDEAD,
	RACE_FIRE,
	RACE_ENERGY
};

enum ViolationAction_t
{
	ACTION_NOTATION = 0,
	ACTION_NAMEREPORT,
	ACTION_BANISHMENT,
	ACTION_BANREPORT,
	ACTION_BANFINAL,
	ACTION_BANREPORTFINAL,
	ACTION_STATEMENT,
	//internal use
	ACTION_DELETION,
	ACTION_NAMELOCK,
	ACTION_BANLOCK,
	ACTION_BANLOCKFINAL,
	ACTION_PLACEHOLDER
};

enum CombatType_t
{
	COMBAT_NONE				= 0x00,
	COMBAT_ALL				= COMBAT_NONE, /* for internal use only.*/

	COMBAT_PHYSICALDAMAGE	= 1 << 0,
	COMBAT_ENERGYDAMAGE		= 1 << 1,
	COMBAT_EARTHDAMAGE		= 1 << 2,
	COMBAT_FIREDAMAGE		= 1 << 3,
	COMBAT_UNDEFINEDDAMAGE	= 1 << 4,
	COMBAT_LIFEDRAIN		= 1 << 5,
	COMBAT_MANADRAIN		= 1 << 6,
	COMBAT_HEALING			= 1 << 7,
	COMBAT_DROWNDAMAGE		= 1 << 8,
	COMBAT_ICEDAMAGE		= 1 << 9,
	COMBAT_HOLYDAMAGE		= 1 << 10,
	COMBAT_DEATHDAMAGE		= 1 << 11,

	COMBAT_FIRST			= COMBAT_NONE,
	COMBAT_LAST				= COMBAT_DEATHDAMAGE
};

enum CombatParam_t
{
	COMBAT_PARAM_TYPE,
	COMBAT_PARAM_EFFECT,
	COMBAT_PARAM_DISTANCEEFFECT,
	COMBAT_PARAM_BLOCKSHIELD,
	COMBAT_PARAM_BLOCKARMOR,
	COMBAT_PARAM_TARGETCASTERORTOPMOST,
	COMBAT_PARAM_CREATEITEM,
	COMBAT_PARAM_AGGRESSIVE,
	COMBAT_PARAM_DISPEL,
	COMBAT_PARAM_USECHARGES,
	COMBAT_PARAM_TARGETPLAYERSORSUMMONS,
	COMBAT_PARAM_DIFFERENTAREADAMAGE,
	COMBAT_PARAM_HITEFFECT,
	COMBAT_PARAM_HITCOLOR,
	COMBAT_PARAM_ELEMENTTYPE,
	COMBAT_PARAM_ELEMENTDAMAGE
};

enum CallBackParam_t
{
	CALLBACK_PARAM_LEVELMAGICVALUE,
	CALLBACK_PARAM_SKILLVALUE,
	CALLBACK_PARAM_TARGETTILE,
	CALLBACK_PARAM_TARGETCREATURE
};

enum ConditionParam_t
{
	CONDITION_PARAM_OWNER = 1,
	CONDITION_PARAM_TICKS,
	CONDITION_PARAM_OUTFIT,
	CONDITION_PARAM_HEALTHGAIN,
	CONDITION_PARAM_HEALTHTICKS,
	CONDITION_PARAM_MANAGAIN,
	CONDITION_PARAM_MANATICKS,
	CONDITION_PARAM_DELAYED,
	CONDITION_PARAM_SPEED,
	CONDITION_PARAM_LIGHT_LEVEL,
	CONDITION_PARAM_LIGHT_COLOR,
	CONDITION_PARAM_SOULGAIN,
	CONDITION_PARAM_SOULTICKS,
	CONDITION_PARAM_MINVALUE,
	CONDITION_PARAM_MAXVALUE,
	CONDITION_PARAM_STARTVALUE,
	CONDITION_PARAM_TICKINTERVAL,
	CONDITION_PARAM_FORCEUPDATE,
	CONDITION_PARAM_SKILL_MELEE,
	CONDITION_PARAM_SKILL_FIST,
	CONDITION_PARAM_SKILL_CLUB,
	CONDITION_PARAM_SKILL_SWORD,
	CONDITION_PARAM_SKILL_AXE,
	CONDITION_PARAM_SKILL_DISTANCE,
	CONDITION_PARAM_SKILL_SHIELD,
	CONDITION_PARAM_SKILL_FISHING,
	CONDITION_PARAM_STAT_MAXHEALTH,
	CONDITION_PARAM_STAT_MAXMANA,
	CONDITION_PARAM_STAT_SOUL,
	CONDITION_PARAM_STAT_MAGICLEVEL,
	CONDITION_PARAM_STAT_MAXHEALTHPERCENT,
	CONDITION_PARAM_STAT_MAXMANAPERCENT,
	CONDITION_PARAM_STAT_SOULPERCENT,
	CONDITION_PARAM_STAT_MAGICLEVELPERCENT,
	CONDITION_PARAM_SKILL_MELEEPERCENT,
	CONDITION_PARAM_SKILL_FISTPERCENT,
	CONDITION_PARAM_SKILL_CLUBPERCENT,
	CONDITION_PARAM_SKILL_SWORDPERCENT,
	CONDITION_PARAM_SKILL_AXEPERCENT,
	CONDITION_PARAM_SKILL_DISTANCEPERCENT,
	CONDITION_PARAM_SKILL_SHIELDPERCENT,
	CONDITION_PARAM_SKILL_FISHINGPERCENT,
	CONDITION_PARAM_PERIODICDAMAGE,
	CONDITION_PARAM_BUFF,
	CONDITION_PARAM_SUBID,
	CONDITION_PARAM_FIELD
};

enum Exhaust_t
{
	EXHAUST_COMBAT = 1,
	EXHAUST_HEALING = 2
};

enum BlockType_t
{
	BLOCK_NONE = 0,
	BLOCK_DEFENSE,
	BLOCK_ARMOR,
	BLOCK_IMMUNITY
};

enum Reflect_t
{
	REFLECT_FIRST = 0,
	REFLECT_PERCENT = REFLECT_FIRST,
	REFLECT_CHANCE,
	REFLECT_LAST = REFLECT_CHANCE
};

enum Increment_t
{
	INCREMENT_FIRST = 0,
	HEALING_VALUE = INCREMENT_FIRST,
	HEALING_PERCENT,
	MAGIC_VALUE,
	MAGIC_PERCENT,
	INCREMENT_LAST = MAGIC_PERCENT
};

enum stats_t
{
	STAT_FIRST = 0,
	STAT_MAXHEALTH = STAT_FIRST,
	STAT_MAXMANA,
	STAT_SOUL,
	STAT_LEVEL,
	STAT_MAGICLEVEL,
	STAT_LAST = STAT_MAGICLEVEL
};

enum lossTypes_t
{
	LOSS_FIRST = 0,
	LOSS_EXPERIENCE = LOSS_FIRST,
	LOSS_MANA,
	LOSS_SKILLS,
	LOSS_CONTAINERS,
	LOSS_ITEMS,
	LOSS_LAST = LOSS_ITEMS
};

enum formulaType_t
{
	COMBAT_FORMULA_UNDEFINED = 0,
	COMBAT_FORMULA_LEVELMAGIC,
	COMBAT_FORMULA_SKILL,
	COMBAT_FORMULA_DAMAGE
};

enum ConditionId_t
{
	CONDITIONID_DEFAULT = -1,
	CONDITIONID_COMBAT = 0,
	CONDITIONID_HEAD,
	CONDITIONID_NECKLACE,
	CONDITIONID_BACKPACK,
	CONDITIONID_ARMOR,
	CONDITIONID_RIGHT,
	CONDITIONID_LEFT,
	CONDITIONID_LEGS,
	CONDITIONID_FEET,
	CONDITIONID_RING,
	CONDITIONID_AMMO,
	CONDITIONID_OUTFIT
};

enum PlayerSex_t
{
	PLAYERSEX_FEMALE = 0,
	PLAYERSEX_MALE
	// DO NOT ADD HERE! Every higher sex is only for your
	// own use- each female should be even and male odd.
};

enum WarType_t
{
	WAR_FIRST = 0,
	WAR_GUILD = WAR_FIRST,
	WAR_ENEMY,
	WAR_LAST = WAR_ENEMY
};

struct War_t
{
	War_t()
	{
		war = 0;
		type = WAR_FIRST;

		memset(ids, 0, sizeof(ids));
		memset(frags, 0, sizeof(frags));

		limit = 0;
		payment = 0;
	}

	uint32_t war;
	WarType_t type;

	uint32_t ids[WAR_LAST + 1];
	std::string names[WAR_LAST + 1];
	uint16_t frags[WAR_LAST + 1];

	uint16_t limit;
	uint64_t payment;
};

struct Outfit_t
{
	Outfit_t()
	{
		lookType = lookTypeEx = 0;
		lookHead = lookBody = lookLegs = lookFeet = lookAddons = 0;
	}
	Outfit_t(uint16_t _lookType)
	{
		lookType = _lookType;
		lookTypeEx = 0;
		lookHead = lookBody = lookLegs = lookFeet = lookAddons = 0;
	}

	uint16_t lookType, lookTypeEx;
	uint8_t lookHead, lookBody, lookLegs, lookFeet, lookAddons;

	bool operator==(const Outfit_t& o) const
	{
		return (o.lookAddons == lookAddons
			&& o.lookType == lookType && o.lookTypeEx == lookTypeEx
			&& o.lookHead == lookHead && o.lookBody == lookBody
			&& o.lookLegs == lookLegs && o.lookFeet == lookFeet);
	}

	bool operator!=(const Outfit_t& o) const
	{
		return !(*this == o);
	}
};

struct LightInfo
{
	uint32_t level, color;

	LightInfo() {level = color = 0;}
	LightInfo(uint32_t _level, uint32_t _color):
		level(_level), color(_color) {}
};

struct ShopInfo
{
	uint32_t itemId;
	int32_t subType, buyPrice, sellPrice;
	std::string itemName;

	ShopInfo()
	{
		itemId = 0;
		subType = 1;
		buyPrice = sellPrice = -1;
		itemName = "";
	}
	ShopInfo(uint32_t _itemId, int32_t _subType = 1, int32_t _buyPrice = -1, int32_t _sellPrice = -1,
		const std::string& _itemName = ""): itemId(_itemId), subType(_subType), buyPrice(_buyPrice),
		sellPrice(_sellPrice), itemName(_itemName) {}
};

typedef std::list<ShopInfo> ShopInfoList;
#endif
