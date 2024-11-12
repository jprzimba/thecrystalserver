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

#ifndef __THING__
#define __THING__
#include "position.h"

enum ReturnValue
{
	RETURNVALUE_NOERROR = 0,
	RETURNVALUE_NOTPOSSIBLE = 1,
	RETURNVALUE_NOTENOUGHROOM = 2,
	RETURNVALUE_PLAYERISPZLOCKED = 3,
	RETURNVALUE_PLAYERISNOTINVITED = 4,
	RETURNVALUE_CANNOTTHROW = 5,
	RETURNVALUE_THEREISNOWAY = 6,
	RETURNVALUE_DESTINATIONOUTOFREACH = 7,
	RETURNVALUE_NOTMOVABLE = 8,
	RETURNVALUE_DROPTWOHANDEDITEM = 9,
	RETURNVALUE_BOTHHANDSNEEDTOBEFREE = 10,
	RETURNVALUE_CANONLYUSEONEWEAPON = 11,
	RETURNVALUE_NEEDEXCHANGE = 12,
	RETURNVALUE_CANNOTBEDRESSED = 13,
	RETURNVALUE_PUTTHISOBJECTINYOURHAND = 14,
	RETURNVALUE_PUTTHISOBJECTINBOTHHANDS = 15,
	RETURNVALUE_TOOFARAWAY = 16,
	RETURNVALUE_FIRSTGODOWNSTAIRS = 17,
	RETURNVALUE_FIRSTGOUPSTAIRS = 18,
	RETURNVALUE_CONTAINERNOTENOUGHROOM = 19,
	RETURNVALUE_NOTENOUGHCAPACITY = 20,
	RETURNVALUE_CANNOTPICKUP = 21,
	RETURNVALUE_THISISIMPOSSIBLE = 22,
	RETURNVALUE_DEPOTISFULL = 23,
	RETURNVALUE_CREATUREDOESNOTEXIST = 24,
	RETURNVALUE_CANNOTUSETHISOBJECT = 25,
	RETURNVALUE_PLAYERWITHTHISNAMEISNOTONLINE = 26,
	RETURNVALUE_YOUAREALREADYTRADING = 27,
	RETURNVALUE_THISPLAYERISALREADYTRADING = 28,
	RETURNVALUE_YOUMAYNOTLOGOUTDURINGAFIGHT = 29,
	RETURNVALUE_DIRECTPLAYERSHOOT = 30,
	RETURNVALUE_NOTENOUGHLEVEL = 31,
	RETURNVALUE_NOTENOUGHMAGICLEVEL = 32,
	RETURNVALUE_NOTENOUGHMANA = 33,
	RETURNVALUE_NOTENOUGHSOUL = 34,
	RETURNVALUE_YOUAREEXHAUSTED = 35,
	RETURNVALUE_CANONLYUSETHISRUNEONCREATURES = 36,
	RETURNVALUE_ACTIONNOTPERMITTEDINPROTECTIONZONE = 37,
	RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER = 38,
	RETURNVALUE_YOUMAYNOTATTACKAPERSONINPROTECTIONZONE = 39,
	RETURNVALUE_YOUMAYNOTATTACKAPERSONWHILEINPROTECTIONZONE = 40,
	RETURNVALUE_YOUMAYNOTATTACKTHISCREATURE = 41,
	RETURNVALUE_YOUCANONLYUSEITONCREATURES = 42,
	RETURNVALUE_CREATUREISNOTREACHABLE = 43,
	RETURNVALUE_TURNSECUREMODETOATTACKUNMARKEDPLAYERS = 44,
	RETURNVALUE_YOUNEEDPREMIUMACCOUNT = 45,
	RETURNVALUE_YOUNEEDTOLEARNTHISSPELL = 46,
	RETURNVALUE_YOURVOCATIONCANNOTUSETHISSPELL = 47,
	RETURNVALUE_YOUNEEDAWEAPONTOUSETHISSPELL = 48,
	RETURNVALUE_PLAYERISPZLOCKEDLEAVEPVPZONE = 49,
	RETURNVALUE_PLAYERISPZLOCKEDENTERPVPZONE = 50,
	RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE = 51,
	RETURNVALUE_YOUCANNOTLOGOUTHERE = 52,
	RETURNVALUE_YOUNEEDAMAGICITEMTOCASTSPELL = 53,
	RETURNVALUE_CANNOTCONJUREITEMHERE = 54,
	RETURNVALUE_TILEISFULL = 55,
	RETURNVALUE_NAMEISTOOAMBIGUOUS = 56,
	RETURNVALUE_CANONLYUSEONESHIELD = 57,
	RETURNVALUE_YOUARENOTTHEOWNER = 58,
	RETURNVALUE_YOUMAYNOTCASTAREAONBLACKSKULL = 59,
	RETURNVALUE_NOTENOUGHSKILL = 60
};

class Tile;
class Cylinder;
class Item;
class Creature;

class Thing
{
	protected:
		Thing(): parent(NULL), refCount(0) {}

	public:
		virtual ~Thing() {}

		void addRef() {++refCount;}
		void unRef()
		{
			--refCount;
			if(!refCount)
				delete this;
		}

		virtual std::string getDescription(int32_t lookDistance) const = 0;

		Cylinder* getParent() {return parent;}
		const Cylinder* getParent() const {return parent;}

		virtual void setParent(Cylinder* cylinder) {parent = cylinder;}

		Cylinder* getTopParent();
		const Cylinder* getTopParent() const;

		virtual Tile* getTile();
		virtual const Tile* getTile() const;

		virtual Position getPosition() const;
		virtual int32_t getThrowRange() const = 0;
		virtual bool isPushable() const = 0;

		virtual Item* getItem() {return NULL;}
		virtual const Item* getItem() const {return NULL;}
		virtual Creature* getCreature() {return NULL;}
		virtual const Creature* getCreature() const {return NULL;}

		virtual bool isRemoved() const;

	private:
		Cylinder* parent;
		int16_t refCount;
};
#endif
