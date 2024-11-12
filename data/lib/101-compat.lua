--[[
 * File containing deprecated functions and constants used by alot of scripts and other engines
]]--

TRUE = true
FALSE = false
LUA_ERROR = false
LUA_NO_ERROR = true
LUA_NULL = nil

COMBAT_POISONDAMAGE = COMBAT_EARTHDAMAGE

MESSAGE_EXPERIENCE = MESSAGE_EVENT_DEFAULT
MESSAGE_EXPERIENCE_OTHERS = MESSAGE_EVENT_DEFAULT

PLAYERLOSS_EXPERIENCE = LOSS_EXPERIENCE
PLAYERLOSS_MANA = LOSS_MANA
PLAYERLOSS_SKILLS = LOSS_SKILLS
PLAYERLOSS_CONTAINERS = LOSS_CONTAINERS
PLAYERLOSS_ITEMS = LOSS_ITEMS

TALKTYPE_CHANNEL_R1 = TALKTYPE_CHANNEL_RN
TALKTYPE_CHANNEL_R2 = TALKTYPE_CHANNEL_RA
TALKTYPE_CHANNEL_RA = TALKTYPE_CHANNEL_W
TALKTYPE_ORANGE_1 = TALKTYPE_MONSTER
TALKTYPE_ORANGE_2 = TALKTYPE_MONSTER_YELL

TEXTCOLOR_BLACK = COLOR_BLACK
TEXTCOLOR_BLUE = COLOR_BLUE
TEXTCOLOR_GREEN = COLOR_GREEN
TEXTCOLOR_TEAL = COLOR_TEAL
TEXTCOLOR_LIGHTGREEN = COLOR_LIGHTGREEN
TEXTCOLOR_DARKBROWN = COLOR_DARKBROWN
TEXTCOLOR_LIGHTBLUE = COLOR_LIGHTBLUE
TEXTCOLOR_DARKRED = COLOR_DARKRED
TEXTCOLOR_DARKPURPLE = COLOR_DARKPURPLE
TEXTCOLOR_BROWN = COLOR_BROWN
TEXTCOLOR_GREY = COLOR_GREY
TEXTCOLOR_DARKPINK = COLOR_DARKPINK
TEXTCOLOR_PURPLE = COLOR_PURPLE
TEXTCOLOR_DARKORANGE = COLOR_DARKORANGE
TEXTCOLOR_RED = COLOR_RED
TEXTCOLOR_PINK = COLOR_PINK
TEXTCOLOR_ORANGE = COLOR_ORANGE
TEXTCOLOR_DARKYELLOW = COLOR_DARKYELLOW
TEXTCOLOR_YELLOW = COLOR_YELLOW
TEXTCOLOR_WHITE = COLOR_WHITE
TEXTCOLOR_NONE = COLOR_NONE

CONDITION_PARAM_STAT_MAXHITPOINTS = CONDITION_PARAM_STAT_MAXHEALTH
CONDITION_PARAM_STAT_MAXMANAPOINTS = CONDITION_PARAM_STAT_MAXMANA
CONDITION_PARAM_STAT_SOULPOINTS = CONDITION_PARAM_STAT_SOUL
CONDITION_PARAM_STAT_MAGICPOINTS = CONDITION_PARAM_STAT_MAGICLEVEL
CONDITION_PARAM_STAT_MAXHITPOINTSPERCENT = CONDITION_PARAM_STAT_MAXHEALTHPERCENT
CONDITION_PARAM_STAT_MAXMANAPOINTSPERCENT = CONDITION_PARAM_STAT_MAXMANAPERCENT
CONDITION_PARAM_STAT_SOULPOINTSPERCENT = CONDITION_PARAM_STAT_SOULPERCENT
CONDITION_PARAM_STAT_MAGICPOINTSPERCENT = CONDITION_PARAM_STAT_MAGICLEVELPERCENT

STACKPOS_FIRST_ITEM_ABOVE_GROUNDTILE = 1
STACKPOS_SECOND_ITEM_ABOVE_GROUNDTILE = 2
STACKPOS_THIRD_ITEM_ABOVE_GROUNDTILE = 3
STACKPOS_FOURTH_ITEM_ABOVE_GROUNDTILE = 4
STACKPOS_FIFTH_ITEM_ABOVE_GROUNDTILE = 5

WORLD_TYPE_NO_PVP = WORLDTYPE_OPTIONAL
WORLD_TYPE_PVP = WORLDTYPE_OPEN
WORLD_TYPE_PVP_ENFORCED = WORLDTYPE_HARDCORE

WORLDTYPE_NO_PVP = WORLDTYPE_OPTIONAL
WORLDTYPE_PVP = WORLDTYPE_OPEN
WORLDTYPE_PVP_ENFORCED = WORLDTYPE_HARDCORE

GUILD_MEMBER = GUILDLEVEL_MEMBER
GUILD_VICE = GUILDLEVEL_VICE
GUILDLEVEL_LEADER = GUILD_LEADER

DATABASE_NONE = DATABASE_ENGINE_NONE
DATABASE_MYSQL = DATABASE_ENGINE_MYSQL
DATABASE_SQLITE = DATABASE_ENGINE_SQLITE

CHANNEL_STAFF = 4
CHANNEL_COUNSELOR = 2
CHANNEL_GAMECHAT = 5
CHANNEL_TRADE = 6
CHANNEL_TRADEROOK = 7
CHANNEL_RLCHAT = 8

BANTYPE_IP_BANISHMENT = 1
BANTYPE_NAMELOCK = 2
BANTYPE_BANISHMENT = 3
BANTYPE_NOTATION = 4
BANTYPE_DELETION = 3

CONST_PROP_MOVEABLE = CONST_PROP_MOVABLE
CONST_PROP_BLOCKINGANDNOTMOVEABLE = CONST_PROP_BLOCKINGANDNOTMOVABLE

CONDITION_EARTH = CONDITION_POISON

STACKPOS_TOP_MOVEABLE_ITEM_OR_CREATURE = STACKPOS_TOP_MOVABLE_ITEM_OR_CREATURE

RETURNVALUE_NOTMOVEABLE = RETURNVALUE_NOTMOVABLE

SKILLS = SKILL_NAMES

doSetCreatureDropLoot = doCreatureSetDropLoot
doPlayerSay = doCreatureSay
doPlayerAddMana = doCreatureAddMana
playerLearnInstantSpell = doPlayerLearnInstantSpell
doPlayerRemOutfit = doPlayerRemoveOutfit
pay = doPlayerRemoveMoney
broadcastMessage = doBroadcastMessage
getPlayerName = getCreatureName
getCreaturePosition = getThingPosition
getPlayerPosition = getCreaturePosition
getCreaturePos = getCreaturePosition
creatureGetPosition = getCreaturePosition
getPlayerMana = getCreatureMana
getPlayerMaxMana = getCreatureMaxMana
hasCondition = hasCreatureCondition
getCreatureCondition = hasCreatureCondition
isMoveable = isMovable
isItemMoveable = isItemMovable
saveData = saveServer
savePlayers = saveServer
getPlayerSkill = getPlayerSkillLevel
getPlayerSkullType = getCreatureSkullType
getCreatureSkull = getCreatureSkullType
getAccountNumberByName = getAccountIdByName
getIPByName = getIpByName
getPlayersByIP = getPlayersByIp
getThingFromPos = getThingFromPosition
getThingfromPos = getThingFromPos
getHouseFromPos = getHouseFromPosition
getPlayersByAccountNumber = getPlayersByAccountId
getIPByPlayerName = getIpByName
getPlayersByIPNumber = getPlayersByIp
getAccountNumberByPlayerName = getAccountIdByName
convertIntToIP = doConvertIntegerToIp
convertIPToInt = doConvertIpToInteger
queryTileAddThing = doTileQueryAdd
getTileHouseInfo = getHouseFromPos
executeRaid = doExecuteRaid
saveServer = doSaveServer
cleanHouse = doCleanHouse
cleanMap = doCleanMap
shutdown = doShutdown
mayNotMove = doCreatureSetNoMove
getTileItemsByType = getTileItemByType
doPlayerSetNoMove = doCreatureSetNoMove
getPlayerNoMove = getCreatureNoMove
getConfigInfo = getConfigValue
doPlayerAddExp = doPlayerAddExperience
isInArea = isInRange
doPlayerSetSkillRate = doPlayerSetRate
getCreatureLookDir = getCreatureLookDirection
getPlayerLookDir = getCreatureLookDirection
getPlayerLookDirection = getCreatureLookDirection
doCreatureSetLookDir = doCreatureSetLookDirection
getPlayerLookPos = getCreatureLookPosition
setPlayerStamina = doPlayerSetStamina
setPlayerPromotionLevel = doPlayerSetPromotionLevel
setPlayerGroupId = doPlayerSetGroupId
setPlayerPartner = doPlayerSetPartner
doPlayerSetStorageValue = doCreatureSetStorage
setPlayerStorageValue = doPlayerSetStorageValue
getPlayerStorageValue = getCreatureStorage
getGlobalStorageValue = getStorage
setGlobalStorageValue = doSetStorage
getPlayerMount = canPlayerRideMount
setPlayerBalance = doPlayerSetBalance
doAddMapMark = doPlayerAddMapMark
doSendTutorial = doPlayerSendTutorial
getWaypointsList = getWaypointList
getPlayerLastLoginSaved = getPlayerLastLogin
getThingPos = getThingPosition
doAreaCombatHealth = doCombatAreaHealth
doAreaCombatMana = doCombatAreaMana
doAreaCombatCondition = doCombatAreaCondition
doAreaCombatDispel = doCombatAreaDispel
getItemDescriptionsById = getItemInfo
hasProperty = hasItemProperty
hasClient = hasPlayerClient
print = std.cout
getPosByDir = getPositionByDirection
isNumber = isNumeric
doSetItemActionId = doItemSetActionId
getOnlinePlayers = getPlayersOnlineEx