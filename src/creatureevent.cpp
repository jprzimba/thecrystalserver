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
#include "otpch.h"
#include "creatureevent.h"
#include "tools.h"

#include "monster.h"
#include "player.h"

extern CreatureEvents* g_creatureEvents;

CreatureEvents::CreatureEvents():
	m_interface("CreatureScript Interface")
{
	m_interface.initState();
}

CreatureEvents::~CreatureEvents()
{
	for(CreatureEventList::iterator it = m_creatureEvents.begin(); it != m_creatureEvents.end(); ++it)
		delete (*it);

	m_creatureEvents.clear();
}

void CreatureEvents::clear()
{
	//clear creature events
	for(CreatureEventList::iterator it = m_creatureEvents.begin(); it != m_creatureEvents.end(); ++it)
		(*it)->clearEvent();

	//clear lua state
	m_interface.reInitState();
}

Event* CreatureEvents::getEvent(const std::string& nodeName)
{
	std::string tmpNodeName = asLowerCaseString(nodeName);
	if(tmpNodeName == "event" || tmpNodeName == "creaturevent" || tmpNodeName == "creatureevent" || tmpNodeName == "creaturescript")
		return new CreatureEvent(&m_interface);

	return NULL;
}

bool CreatureEvents::registerEvent(Event* event, xmlNodePtr, bool override)
{
	CreatureEvent* creatureEvent = dynamic_cast<CreatureEvent*>(event);
	if(!creatureEvent)
		return false;

	if(creatureEvent->getEventType() == CREATURE_EVENT_NONE)
	{
		std::clog << "[Error - CreatureEvents::registerEvent] Trying to register event without type!" << std::endl;
		return false;
	}

	if(CreatureEvent* oldEvent = getEventByName(creatureEvent->getName()))
	{
		//if there was an event with the same type that is not loaded (happens when realoading), it is reused
		if(oldEvent->getEventType() == creatureEvent->getEventType())
		{
			if(!oldEvent->isLoaded() || override)
				oldEvent->copyEvent(creatureEvent);

			return override;
		}
	}

	//if not, register it normally
	m_creatureEvents.push_back(creatureEvent);
	return true;
}

CreatureEvent* CreatureEvents::getEventByName(const std::string& name)
{
	for(CreatureEventList::iterator it = m_creatureEvents.begin(); it != m_creatureEvents.end(); ++it)
	{
		if((*it)->getName() == name)
			return (*it);
	}

	return NULL;
}

bool CreatureEvents::playerLogin(Player* player)
{
	//fire global event if is registered
	bool result = true;
	for(CreatureEventList::iterator it = m_creatureEvents.begin(); it != m_creatureEvents.end(); ++it)
	{
		if((*it)->getEventType() == CREATURE_EVENT_LOGIN &&
			(*it)->isLoaded() && !(*it)->executePlayer(player) && result)
			result = false;
	}

	return result;
}

bool CreatureEvents::playerLogout(Player* player, bool forceLogout)
{
	//fire global event if is registered
	bool result = true;
	for(CreatureEventList::iterator it = m_creatureEvents.begin(); it != m_creatureEvents.end(); ++it)
	{
		if((*it)->getEventType() == CREATURE_EVENT_LOGOUT && (*it)->isLoaded()
			&& !(*it)->executeLogout(player, forceLogout) && result)
			result = false;
	}

	return result;
}

bool CreatureEvents::monsterSpawn(Monster* monster)
{
	//fire global event if is registered
	bool result = true;
	for(CreatureEventList::iterator it = m_creatureEvents.begin(); it != m_creatureEvents.end(); ++it)
	{
		if((*it)->getEventType() == CREATURE_EVENT_SPAWN_GLOBAL &&
			(*it)->isLoaded() && !(*it)->executeSpawn(monster) && result)
			result = false;
	}

	return result;
}

CreatureEventType_t CreatureEvents::getType(const std::string& type)
{
	CreatureEventType_t _type = CREATURE_EVENT_NONE;
	if(type == "login")
		_type = CREATURE_EVENT_LOGIN;
	else if(type == "logout")
		_type = CREATURE_EVENT_LOGOUT;
	else if(type == "channeljoin")
		_type = CREATURE_EVENT_CHANNEL_JOIN;
	else if(type == "channelleave")
		_type = CREATURE_EVENT_CHANNEL_LEAVE;
	else if(type == "channelrequest")
		_type = CREATURE_EVENT_CHANNEL_REQUEST;
	else if(type == "advance")
		_type = CREATURE_EVENT_ADVANCE;
	else if(type == "mailsend")
		_type = CREATURE_EVENT_MAIL_SEND;
	else if(type == "mailreceive")
		_type = CREATURE_EVENT_MAIL_RECEIVE;
	else if(type == "traderequest")
		_type = CREATURE_EVENT_TRADE_REQUEST;
	else if(type == "tradeaccept")
		_type = CREATURE_EVENT_TRADE_ACCEPT;
	else if(type == "textedit")
		_type = CREATURE_EVENT_TEXTEDIT;
	else if(type == "houseedit")
		_type = CREATURE_EVENT_HOUSEEDIT;
	else if(type == "reportbug")
		_type = CREATURE_EVENT_REPORTBUG;
	else if(type == "look")
		_type = CREATURE_EVENT_LOOK;
	else if(type == "spawn" || type == "spawn-single")
		_type = CREATURE_EVENT_SPAWN_SINGLE;
	else if(type == "spawnall" || type == "spawn-global")
		_type = CREATURE_EVENT_SPAWN_GLOBAL;
	else if(type == "think")
		_type = CREATURE_EVENT_THINK;
	else if(type == "direction")
		_type = CREATURE_EVENT_DIRECTION;
	else if(type == "outfit")
		_type = CREATURE_EVENT_OUTFIT;
	else if(type == "statschange")
		_type = CREATURE_EVENT_STATSCHANGE;
	else if(type == "areacombat")
		_type = CREATURE_EVENT_COMBAT_AREA;
	else if(type == "throw")
		_type = CREATURE_EVENT_THROW;
	else if(type == "push")
		_type = CREATURE_EVENT_PUSH;
	else if(type == "target")
		_type = CREATURE_EVENT_TARGET;
	else if(type == "follow")
		_type = CREATURE_EVENT_FOLLOW;
	else if(type == "combat")
		_type = CREATURE_EVENT_COMBAT;
	else if(type == "attack")
		_type = CREATURE_EVENT_ATTACK;
	else if(type == "cast")
		_type = CREATURE_EVENT_CAST;
	else if(type == "kill")
		_type = CREATURE_EVENT_KILL;
	else if(type == "death")
		_type = CREATURE_EVENT_DEATH;
	else if(type == "preparedeath")
		_type = CREATURE_EVENT_PREPAREDEATH;

	return _type;
}

CreatureEvent::CreatureEvent(LuaInterface* _interface):
Event(_interface)
{
	m_type = CREATURE_EVENT_NONE;
	m_loaded = false;
}

CreatureEvent::CreatureEvent(const CreatureEvent* copy):
Event(copy)
{
	m_type = copy->m_type;
	m_loaded = copy->m_loaded;
	m_scriptId = copy->m_scriptId;
	m_interface = copy->m_interface;
	m_scripted = copy->m_scripted;
	m_loaded = copy->m_loaded;
}

bool CreatureEvent::configureEvent(xmlNodePtr p)
{
	std::string strValue;
	if(!readXMLString(p, "name", strValue))
	{
		std::clog << "[Error - CreatureEvent::configureEvent] No name for creature event." << std::endl;
		return false;
	}

	m_eventName = strValue;
	if(!readXMLString(p, "type", strValue))
	{
		std::clog << "[Error - CreatureEvent::configureEvent] No type for creature event." << std::endl;
		return false;
	}

	m_type = g_creatureEvents->getType(asLowerCaseString(strValue));
	if(m_type == CREATURE_EVENT_NONE)
	{
		std::clog << "[Error - CreatureEvent::configureEvent] No valid type for creature event: " << strValue << "." << std::endl;
		return false;
	}

	m_loaded = true;
	return true;
}

std::string CreatureEvent::getScriptEventName() const
{
	switch(m_type)
	{
		case CREATURE_EVENT_LOGIN:
			return "onLogin";
		case CREATURE_EVENT_LOGOUT:
			return "onLogout";
		case CREATURE_EVENT_SPAWN_SINGLE:
		case CREATURE_EVENT_SPAWN_GLOBAL:
			return "onSpawn";
		case CREATURE_EVENT_CHANNEL_JOIN:
			return "onChannelJoin";
		case CREATURE_EVENT_CHANNEL_LEAVE:
			return "onChannelLeave";
		case CREATURE_EVENT_CHANNEL_REQUEST:
			return "onChannelRequest";
		case CREATURE_EVENT_THINK:
			return "onThink";
		case CREATURE_EVENT_ADVANCE:
			return "onAdvance";
		case CREATURE_EVENT_LOOK:
			return "onLook";
		case CREATURE_EVENT_DIRECTION:
			return "onDirection";
		case CREATURE_EVENT_OUTFIT:
			return "onOutfit";
		case CREATURE_EVENT_MAIL_SEND:
			return "onMailSend";
		case CREATURE_EVENT_MAIL_RECEIVE:
			return "onMailReceive";
		case CREATURE_EVENT_TRADE_REQUEST:
			return "onTradeRequest";
		case CREATURE_EVENT_TRADE_ACCEPT:
			return "onTradeAccept";
		case CREATURE_EVENT_TEXTEDIT:
			return "onTextEdit";
		case CREATURE_EVENT_HOUSEEDIT:
			return "onHouseEdit";
		case CREATURE_EVENT_REPORTBUG:
			return "onReportBug";
		case CREATURE_EVENT_STATSCHANGE:
			return "onStatsChange";
		case CREATURE_EVENT_COMBAT_AREA:
			return "onAreaCombat";
		case CREATURE_EVENT_THROW:
			return "onThrow";
		case CREATURE_EVENT_PUSH:
			return "onPush";
		case CREATURE_EVENT_TARGET:
			return "onTarget";
		case CREATURE_EVENT_FOLLOW:
			return "onFollow";
		case CREATURE_EVENT_COMBAT:
			return "onCombat";
		case CREATURE_EVENT_ATTACK:
			return "onAttack";
		case CREATURE_EVENT_CAST:
			return "onCast";
		case CREATURE_EVENT_KILL:
			return "onKill";
		case CREATURE_EVENT_DEATH:
			return "onDeath";
		case CREATURE_EVENT_PREPAREDEATH:
			return "onPrepareDeath";
		case CREATURE_EVENT_NONE:
		default:
			break;
	}

	return "";
}

std::string CreatureEvent::getScriptEventParams() const
{
	switch(m_type)
	{
		case CREATURE_EVENT_LOGIN:
		case CREATURE_EVENT_SPAWN_SINGLE:
		case CREATURE_EVENT_SPAWN_GLOBAL:
			return "cid";
		case CREATURE_EVENT_LOGOUT:
			return "cid, forceLogout";
		case CREATURE_EVENT_CHANNEL_JOIN:
		case CREATURE_EVENT_CHANNEL_LEAVE:
			return "cid, channel, users";
		case CREATURE_EVENT_CHANNEL_REQUEST:
			return "cid, channel, custom";
		case CREATURE_EVENT_ADVANCE:
			return "cid, skill, oldLevel, newLevel";
		case CREATURE_EVENT_LOOK:
			return "cid, thing, position, lookDistance";
		case CREATURE_EVENT_MAIL_SEND:
			return "cid, target, item, openBox";
		case CREATURE_EVENT_MAIL_RECEIVE:
			return "cid, target, item, openBox";
		case CREATURE_EVENT_TRADE_REQUEST:
			return "cid, target, item";
		case CREATURE_EVENT_TRADE_ACCEPT:
			return "cid, target, item, targetItem";
		case CREATURE_EVENT_TEXTEDIT:
			return "cid, item, newText";
		case CREATURE_EVENT_HOUSEEDIT:
			return "cid, house, list, text";
		case CREATURE_EVENT_REPORTBUG:
			return "cid, comment";
		case CREATURE_EVENT_THINK:
			return "cid, interval";
		case CREATURE_EVENT_DIRECTION:
		case CREATURE_EVENT_OUTFIT:
			return "cid, old, current";
		case CREATURE_EVENT_STATSCHANGE:
			return "cid, attacker, type, combat, value";
		case CREATURE_EVENT_COMBAT_AREA:
			return "cid, ground, position, aggressive";
		case CREATURE_EVENT_THROW:
			return "cid, item, fromPosition, toPosition";
		case CREATURE_EVENT_PUSH:
			return "cid, target, ground, position";
		case CREATURE_EVENT_COMBAT:
			return "cid, target, aggressive";
		case CREATURE_EVENT_TARGET:
		case CREATURE_EVENT_FOLLOW:
		case CREATURE_EVENT_ATTACK:
		case CREATURE_EVENT_CAST:
			return "cid, target";
		case CREATURE_EVENT_KILL:
			return "cid, target, damage, flags, war";
		case CREATURE_EVENT_DEATH:
			return "cid, corpse, deathList";
		case CREATURE_EVENT_PREPAREDEATH:
			return "cid, deathList";
		case CREATURE_EVENT_NONE:
		default:
			break;
	}

	return "";
}

void CreatureEvent::copyEvent(CreatureEvent* creatureEvent)
{
	m_scriptId = creatureEvent->m_scriptId;
	m_interface = creatureEvent->m_interface;
	m_scripted = creatureEvent->m_scripted;
}

void CreatureEvent::clearEvent()
{
	m_scriptId = 0;
	m_interface = NULL;
	m_scripted = false;
	m_loaded = false;
}

uint32_t CreatureEvent::executePlayer(Player* player)
{
	//onLogin(cid)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);
		lua_pushnumber(L, env->addThing(player));

		bool result = m_interface->callFunction(1);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executePlayer] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeLogout(Player* player, bool forceLogout)
{
	//onLogout(cid, forceLogout)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		lua_pushboolean(L, forceLogout);

		bool result = m_interface->callFunction(2);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeLogout] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeChannel(Player* player, uint16_t channelId, UsersMap usersMap)
{
	//onChannel[Join/Leave](cid, channel, users)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		lua_pushnumber(L, channelId);

		UsersMap::iterator it = usersMap.begin();
		lua_newtable(L);
		for(int32_t i = 1; it != usersMap.end(); ++it, ++i)
		{
			lua_pushnumber(L, i);
			lua_pushnumber(L, env->addThing(it->second));
			lua_settable(L, -3);
		}

		bool result = m_interface->callFunction(3);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeChannel] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeAdvance(Player* player, skills_t skill, uint32_t oldLevel, uint32_t newLevel)
{
	//onAdvance(cid, skill, oldLevel, newLevel)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		lua_pushnumber(L, (uint32_t)skill);

		lua_pushnumber(L, oldLevel);
		lua_pushnumber(L, newLevel);

		bool result = m_interface->callFunction(4);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeAdvance] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeMail(Player* player, Player* target, Item* item, bool openBox)
{
	//onMail[Send/Receive](cid, target, item, openBox)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		lua_pushnumber(L, env->addThing(target));

		LuaInterface::pushThing(L, item, env->addThing(item));
		lua_pushboolean(L, openBox);

		bool result = m_interface->callFunction(4);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeMail] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeChannelRequest(Player* player, const std::string& channel, bool isPrivate, bool custom)
{
	//onChannelRequest(cid, channel, custom)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		if(!isPrivate)
			lua_pushnumber(L, atoi(channel.c_str()));
		else
			lua_pushstring(L, channel.c_str());

		lua_pushboolean(L, custom);
		bool result = m_interface->callFunction(3);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeChannelRequest] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeTradeRequest(Player* player, Player* target, Item* item)
{
	//onTradeRequest(cid, target, item)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		lua_pushnumber(L, env->addThing(target));
		LuaInterface::pushThing(L, item, env->addThing(item));

		bool result = m_interface->callFunction(3);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeTradeRequest] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeTradeAccept(Player* player, Player* target, Item* item, Item* targetItem)
{
	//onTradeAccept(cid, target, item, targetItem)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		lua_pushnumber(L, env->addThing(target));
		LuaInterface::pushThing(L, item, env->addThing(item));
		LuaInterface::pushThing(L, targetItem, env->addThing(targetItem));

		bool result = m_interface->callFunction(4);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeTradeAccept] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeLook(Player* player, Thing* thing, const Position& position, int16_t stackpos, int32_t lookDistance)
{
	//onLook(cid, thing, position, lookDistance)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		LuaInterface::pushThing(L, thing, env->addThing(thing));

		LuaInterface::pushPosition(L, position, stackpos);
		lua_pushnumber(L, lookDistance);

		bool result = m_interface->callFunction(4);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeLook] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeSpawn(Monster* monster)
{
	//onSpawn(cid)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(monster->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);
		lua_pushnumber(L, env->addThing(monster));

		bool result = m_interface->callFunction(1);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeSpawn] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeDirection(Creature* creature, Direction old, Direction current)
{
	//onDirection(cid, old, current)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(creature->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(creature));
		lua_pushnumber(L, old);
		lua_pushnumber(L, current);

		bool result = m_interface->callFunction(3);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeDirection] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeOutfit(Creature* creature, const Outfit_t& old, const Outfit_t& current)
{
	//onOutfit(cid, old, current)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(creature->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(creature));
		LuaInterface::pushOutfit(L, old);
		LuaInterface::pushOutfit(L, current);

		bool result = m_interface->callFunction(3);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeOutfit] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeThink(Creature* creature, uint32_t interval)
{
	//onThink(cid, interval)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(creature->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(creature));
		lua_pushnumber(L, interval);

		bool result = m_interface->callFunction(2);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeThink] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeStatsChange(Creature* creature, Creature* attacker, StatsChange_t type, CombatType_t combat, int32_t value)
{
	//onStatsChange(cid, attacker, type, combat, value)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(creature->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(creature));
		lua_pushnumber(L, env->addThing(attacker));

		lua_pushnumber(L, (uint32_t)type);
		lua_pushnumber(L, (uint32_t)combat);
		lua_pushnumber(L, value);

		bool result = m_interface->callFunction(5);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeStatsChange] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeCombatArea(Creature* creature, Tile* tile, bool aggressive)
{
	//onAreaCombat(cid, ground, position, aggressive)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(creature->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(creature));
		LuaInterface::pushThing(L, tile->ground, env->addThing(tile->ground));

		LuaInterface::pushPosition(L, tile->getPosition(), 0);
		lua_pushboolean(L, aggressive);

		bool result = m_interface->callFunction(4);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeAreaCombat] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeCombat(Creature* creature, Creature* target, bool aggressive)
{
	//onCombat(cid, target, aggressive)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(creature->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(creature));
		lua_pushnumber(L, env->addThing(target));
		lua_pushboolean(L, aggressive);

		bool result = m_interface->callFunction(3);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeCombat] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeCast(Creature* creature, Creature* target/* = NULL*/)
{
	//onCast(cid[, target])
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(creature->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(creature));
		lua_pushnumber(L, env->addThing(target));

		bool result = m_interface->callFunction(2);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeCast] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeKill(Creature* creature, Creature* target, const DeathEntry& entry)
{
	//onKill(cid, target, damage, flags)
	if(m_interface->reserveEnv())
	{
		uint32_t flags = 0;
		if(entry.isLast())
			flags |= 1;

		if(entry.isJustify())
			flags |= 2;

		if(entry.isUnjustified())
			flags |= 4;

		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(creature->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(creature));
		lua_pushnumber(L, env->addThing(target));

		lua_pushnumber(L, entry.getDamage());
		lua_pushnumber(L, flags);
		lua_pushnumber(L, entry.getWar().war);

		bool result = m_interface->callFunction(5);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeKill] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeDeath(Creature* creature, Item* corpse, DeathList deathList)
{
	//onDeath(cid, corpse, deathList)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(creature->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(creature));
		LuaInterface::pushThing(L, corpse, env->addThing(corpse));

		lua_newtable(L);
		DeathList::iterator it = deathList.begin();
		for(int32_t i = 1; it != deathList.end(); ++it, ++i)
		{
			lua_pushnumber(L, i);
			if(it->isCreatureKill())
				lua_pushnumber(L, env->addThing(it->getKillerCreature()));
			else
				lua_pushstring(L, it->getKillerName().c_str());

			lua_settable(L, -3);
		}

		bool result = m_interface->callFunction(3);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeDeath] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executePrepareDeath(Creature* creature, DeathList deathList)
{
	//onPrepareDeath(cid, deathList)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(creature->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(creature));

		lua_newtable(L);
		DeathList::iterator it = deathList.begin();
		for(int32_t i = 1; it != deathList.end(); ++it, ++i)
		{
			lua_pushnumber(L, i);
			if(it->isCreatureKill())
				lua_pushnumber(L, env->addThing(it->getKillerCreature()));
			else
				lua_pushstring(L, it->getKillerName().c_str());

			lua_settable(L, -3);
		}

		bool result = m_interface->callFunction(2);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executePrepareDeath] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeTextEdit(Player* player, Item* item, const std::string& newText)
{
	//onTextEdit(cid, item, newText)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		LuaInterface::pushThing(L, item, env->addThing(item));
		lua_pushstring(L, newText.c_str());

		bool result = m_interface->callFunction(3);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeTextEdit] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeHouseEdit(Player* player, uint32_t houseId, uint32_t listId, const std::string& text)
{
	//onHouseEdit(cid, houseId, listId, text)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		lua_pushnumber(L, houseId);
		lua_pushnumber(L, listId);
		lua_pushstring(L, text.c_str());

		bool result = m_interface->callFunction(4);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeHouseEdit] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeReportBug(Player* player, const std::string& comment)
{
	//onReportBug(cid, comment)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		lua_pushstring(L, comment.c_str());

		bool result = m_interface->callFunction(2);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeReportBug] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executePush(Player* player, Creature* target, Tile* tile)
{
	//onPush(cid, target, ground, position)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		lua_pushnumber(L, env->addThing(target));

		LuaInterface::pushThing(L, tile->ground, env->addThing(tile->ground));
		LuaInterface::pushPosition(L, tile->getPosition(), 0);

		bool result = m_interface->callFunction(4);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executePush] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeThrow(Player* player, Item* item, const Position& fromPosition, const Position& toPosition)
{
	//onThrow(cid, item, fromPosition, toPosition)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(player->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(player));
		LuaInterface::pushThing(L, item, env->addThing(item));

		LuaInterface::pushPosition(L, fromPosition, 0);
		LuaInterface::pushPosition(L, toPosition, 0);

		bool result = m_interface->callFunction(4);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executePush] Call stack overflow." << std::endl;
		return 0;
	}
}

uint32_t CreatureEvent::executeAction(Creature* creature, Creature* target)
{
	//on[Target/Follow/Attack](cid, target)
	if(m_interface->reserveEnv())
	{
		ScriptEnviroment* env = m_interface->getEnv();
		env->setScriptId(m_scriptId, m_interface);
		env->setRealPos(creature->getPosition());

		lua_State* L = m_interface->getState();
		m_interface->pushFunction(m_scriptId);

		lua_pushnumber(L, env->addThing(creature));
		lua_pushnumber(L, env->addThing(target));

		bool result = m_interface->callFunction(2);
		m_interface->releaseEnv();
		return result;
	}
	else
	{
		std::clog << "[Error - CreatureEvent::executeAction] Call stack overflow." << std::endl;
		return 0;
	}
}
