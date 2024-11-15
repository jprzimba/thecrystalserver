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
#include "tools.h"

#include <iostream>
#include <iomanip>

#include <openssl/sha.h>
#include <openssl/md5.h>

#include "vocation.h"
#include "configmanager.h"

extern ConfigManager g_config;

std::string transformToMD5(std::string plainText, bool upperCase)
{
	MD5_CTX c;
	MD5_Init(&c);
	MD5_Update(&c, plainText.c_str(), plainText.length());

	uint8_t md[MD5_DIGEST_LENGTH];
	MD5_Final(md, &c);

	char output[(MD5_DIGEST_LENGTH << 1) + 1];
	for(int32_t i = 0; i < (int32_t)sizeof(md); ++i)
		sprintf(output + (i << 1), "%.2X", md[i]);

	if(upperCase)
		return std::string(output);

	return asLowerCaseString(std::string(output));
}

std::string transformToSHA1(std::string plainText, bool upperCase)
{
	SHA_CTX c;
	SHA1_Init(&c);
	SHA1_Update(&c, plainText.c_str(), plainText.length());

	uint8_t md[SHA_DIGEST_LENGTH];
	SHA1_Final(md, &c);

	char output[(SHA_DIGEST_LENGTH << 1) + 1];
	for(int32_t i = 0; i < (int32_t)sizeof(md); ++i)
		sprintf(output + (i << 1), "%.2X", md[i]);

	if(upperCase)
		return std::string(output);

	return asLowerCaseString(std::string(output));
}

std::string transformToSHA256(std::string plainText, bool upperCase)
{
	SHA256_CTX c;
	SHA256_Init(&c);
	SHA256_Update(&c, plainText.c_str(), plainText.length());

	uint8_t md[SHA256_DIGEST_LENGTH];
	SHA256_Final(md, &c);

	char output[(SHA256_DIGEST_LENGTH << 1) + 1];
	for(int32_t i = 0; i < (int32_t)sizeof(md); ++i)
		sprintf(output + (i << 1), "%.2X", md[i]);

	if(upperCase)
		return std::string(output);

	return asLowerCaseString(std::string(output));
}

std::string transformToSHA512(std::string plainText, bool upperCase)
{
	SHA512_CTX c;
	SHA512_Init(&c);
	SHA512_Update(&c, plainText.c_str(), plainText.length());

	uint8_t md[SHA512_DIGEST_LENGTH];
	SHA512_Final(md, &c);

	char output[(SHA512_DIGEST_LENGTH << 1) + 1];
	for(int32_t i = 0; i < (int32_t)sizeof(md); ++i)
		sprintf(output + (i << 1), "%.2X", md[i]);

	if(upperCase)
		return std::string(output);

	return asLowerCaseString(std::string(output));
}

void _encrypt(std::string& str, bool upperCase)
{
	switch(g_config.getNumber(ConfigManager::ENCRYPTION))
	{
		case ENCRYPTION_MD5:
			str = transformToMD5(str, upperCase);
			break;
		case ENCRYPTION_SHA1:
			str = transformToSHA1(str, upperCase);
			break;
		case ENCRYPTION_SHA256:
			str = transformToSHA256(str, upperCase);
			break;
		case ENCRYPTION_SHA512:
			str = transformToSHA512(str, upperCase);
			break;
		default:
		{
			if(upperCase)
				std::transform(str.begin(), str.end(), str.begin(), upchar);

			break;
		}
	}
}

bool encryptTest(std::string plain, std::string& hash)
{
	std::transform(hash.begin(), hash.end(), hash.begin(), upchar);
	_encrypt(plain, true);
	return plain == hash;
}

bool replaceString(std::string& text, const std::string& key, const std::string& value)
{
	if(text.find(key) == std::string::npos)
		return false;

	std::string::size_type start = 0, pos = 0;
	while((start = text.find(key, pos)) != std::string::npos)
	{
		text.replace(start, key.size(), value);
		pos = start + value.size();
	}

	return true;
}

void trim_right(std::string& source, const std::string& t)
{
	source.erase(source.find_last_not_of(t) + 1);
}

void trim_left(std::string& source, const std::string& t)
{
	source.erase(0, source.find_first_not_of(t));
}

void toLowerCaseString(std::string& source)
{
	std::transform(source.begin(), source.end(), source.begin(), tolower);
}

void toUpperCaseString(std::string& source)
{
	std::transform(source.begin(), source.end(), source.begin(), upchar);
}

std::string asLowerCaseString(const std::string& source)
{
	std::string s = source;
	toLowerCaseString(s);
	return s;
}

std::string asUpperCaseString(const std::string& source)
{
	std::string s = source;
	toUpperCaseString(s);
	return s;
}

bool booleanString(std::string source)
{
	toLowerCaseString(source);
	return (source == "yes" || source == "true" || atoi(source.c_str()) > 0);
}

std::string ucfirst(std::string source)
{
	for(uint16_t i = 0; i < (uint16_t)source.length(); ++i)
	{
		if(source[i] != ' ')
		{
			source[i] = upchar(source[i]);
			break;
		}
	}

	return source;
}

std::string ucwords(std::string source)
{
	bool tmp = true;
	for(uint16_t i = 0; i < (uint16_t)source.length(); ++i)
	{
		if(source[i] == ' ')
			tmp = true;
		else if(tmp)
		{
			source[i] = upchar(source[i]);
			tmp = false;
		}
	}

	return source;
}

bool readXMLInteger(xmlNodePtr node, const char* tag, int32_t& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	value = atoi(nodeValue);
	xmlFree(nodeValue);
	return true;
}

bool readXMLInteger64(xmlNodePtr node, const char* tag, int64_t& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	value = atoll(nodeValue);
	xmlFree(nodeValue);
	return true;
}

bool readXMLFloat(xmlNodePtr node, const char* tag, float& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	value = atof(nodeValue);
	xmlFree(nodeValue);
	return true;
}

bool readXMLString(xmlNodePtr node, const char* tag, std::string& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	if(!utf8ToLatin1(nodeValue, value))
		value = nodeValue;

	xmlFree(nodeValue);
	return true;
}

bool readXMLContentString(xmlNodePtr node, std::string& value)
{
	char* nodeValue = (char*)xmlNodeGetContent(node);
	if(!nodeValue)
		return false;

	if(!utf8ToLatin1(nodeValue, value))
		value = nodeValue;

	xmlFree(nodeValue);
	return true;
}

bool parseXMLContentString(xmlNodePtr node, std::string& value)
{
	bool result = false;
	std::string compareValue;
	while(node)
	{
		if(xmlStrcmp(node->name, (const xmlChar*)"text") && node->type != XML_CDATA_SECTION_NODE)
		{
			node = node->next;
			continue;
		}

		if(!readXMLContentString(node, compareValue))
		{
			node = node->next;
			continue;
		}

		trim_left(compareValue, "\r");
		trim_left(compareValue, "\n");
		trim_left(compareValue, " ");
		if(compareValue.length() > value.length())
		{
			value = compareValue;
			if(!result)
				result = true;
		}

		node = node->next;
	}

	return result;
}

std::string getLastXMLError()
{
	std::stringstream ss;
	xmlErrorPtr lastError = xmlGetLastError();
	if(lastError->line)
		ss << "Line: " << lastError->line << ", ";

	ss << "Info: " << lastError->message << std::endl;
	return ss.str();
}

bool utf8ToLatin1(char* inText, std::string& outText)
{
	outText = "";
	if(!inText)
		return false;

	int32_t inLen = strlen(inText);
	if(!inLen)
		return false;

	int32_t outLen = inLen << 1;
	uint8_t* outBuf = new uint8_t[outLen];

	int32_t res = UTF8Toisolat1(outBuf, &outLen, (uint8_t*)inText, &inLen);
	if(res < 0)
	{
		delete[] outBuf;
		return false;
	}

	outBuf[outLen] = '\0';
	outText = (char*)outBuf;

	delete[] outBuf;
	return true;
}

bool latin1ToUtf8(char* inText, std::string& outText)
{
	outText = "";
	if(!inText)
		return false;

	int32_t inLen = strlen(inText);
	if(!inLen)
		return false;

	int32_t outLen = inLen << 1;
	uint8_t* outBuf = new uint8_t[outLen];

	int32_t res = isolat1ToUTF8(outBuf, &outLen, (uint8_t*)inText, &inLen);
	if(res < 0)
	{
		delete[] outBuf;
		return false;
	}

	outBuf[outLen] = '\0';
	outText = (char*)outBuf;

	delete[] outBuf;
	return true;
}

StringVec explodeString(const std::string& string, const std::string& separator, bool trim/* = true*/, uint16_t limit/* = 0*/)
{
	StringVec returnVector;
	size_t start = 0, end = 0;

	uint16_t i = 1;
	while((end = string.find(separator, start)) != std::string::npos)
	{
		std::string t = string.substr(start, end - start);
		if(trim)
			trimString(t);

		returnVector.push_back(t);
		start = end + separator.size();

		++i;
		if(limit > 0 && i > limit)
			break;
	}

	returnVector.push_back(string.substr(start));
	return returnVector;
}

IntegerVec vectorAtoi(StringVec stringVector)
{
	IntegerVec returnVector;
	for(StringVec::iterator it = stringVector.begin(); it != stringVector.end(); ++it)
	{
		int32_t number = atoi((*it).c_str());
		if(number || (*it) == "0")
			returnVector.push_back(number);
	}

	return returnVector;
}

bool hasBitSet(uint32_t flag, uint32_t flags)
{
	return ((flags & flag) == flag);
}

uint32_t rand24b()
{
	return ((rand() << 12) ^ rand()) & 0xFFFFFF;
}

float box_muller(float m, float s)
{
	// normal random variate generator
	// mean m, standard deviation s
	float x1, x2, w, y1;
	static float y2;

	static bool useLast = false;
	if(useLast) // use value from previous call
	{
		y1 = y2;
		useLast = false;
		return (m + y1 * s);
	}

	do
	{
		double r1 = (((float)(rand()) / RAND_MAX));
		double r2 = (((float)(rand()) / RAND_MAX));

		x1 = 2.0 * r1 - 1.0;
		x2 = 2.0 * r2 - 1.0;
		w = x1 * x1 + x2 * x2;
	}
	while(w >= 1.0);
	w = sqrt((-2.0 * log(w)) / w);

	y1 = x1 * w;
	y2 = x2 * w;

	useLast = true;
	return (m + y1 * s);
}

int32_t random_range(int32_t lowestNumber, int32_t highestNumber, DistributionType_t type /*= DISTRO_UNIFORM*/)
{
	if(highestNumber == lowestNumber)
		return lowestNumber;

	if(lowestNumber > highestNumber)
		std::swap(lowestNumber, highestNumber);

	switch(type)
	{
		case DISTRO_UNIFORM:
			return (lowestNumber + ((int32_t)rand24b() % (highestNumber - lowestNumber + 1)));
		case DISTRO_NORMAL:
			return (lowestNumber + int32_t(float(highestNumber - lowestNumber) * (float)std::min((float)1, std::max((float)0, box_muller(0.5, 0.25)))));
		default:
			break;
	}

	const float randMax = 16777216;
	return (lowestNumber + int32_t(float(highestNumber - lowestNumber) * float(1.f - sqrt((1.f * rand24b()) / randMax))));
}

char upchar(char character)
{
	if((character >= 97 && character <= 122) || (character <= -1 && character >= -32))
		character -= 32;

	return character;
}

bool isNumber(char character)
{
	return (character >= 48 && character <= 57);
}

bool isLowercaseLetter(char character)
{
	return (character >= 97 && character <= 122);
}

bool isUppercaseLetter(char character)
{
	return (character >= 65 && character <= 90);
}

bool isPasswordCharacter(char character)
{
	return ((character >= 33 && character <= 47) || (character >= 58 && character <= 64) || (character >= 91 && character <= 96) || (character >= 123 && character <= 126));
}

bool isValidAccountName(std::string text)
{
	toLowerCaseString(text);

	uint32_t textLength = text.length();
	for(uint32_t size = 0; size < textLength; size++)
	{
		if(!isLowercaseLetter(text[size]) && !isNumber(text[size]))
			return false;
	}

	return true;
}

bool isValidPassword(std::string text)
{
	toLowerCaseString(text);

	uint32_t textLength = text.length();
	for(uint32_t size = 0; size < textLength; size++)
	{
		if(!isLowercaseLetter(text[size]) && !isNumber(text[size]) && !isPasswordCharacter(text[size]))
			return false;
	}

	return true;
}

bool isValidName(std::string text, bool forceUppercaseOnFirstLetter/* = true*/)
{
	uint32_t textLength = text.length(), lenBeforeSpace = 1, lenBeforeQuote = 1, lenBeforeDash = 1, repeatedCharacter = 0;
	char lastChar = 32;
	if(forceUppercaseOnFirstLetter)
	{
		if(!isUppercaseLetter(text[0]))
			return false;
	}
	else if(!isLowercaseLetter(text[0]) && !isUppercaseLetter(text[0]))
		return false;

	for(uint32_t size = 1; size < textLength; size++)
	{
		if(text[size] != 32)
		{
			lenBeforeSpace++;
			if(text[size] != 39)
				lenBeforeQuote++;
			else
			{
				if(lenBeforeQuote <= 1 || size == textLength - 1 || text[size + 1] == 32)
					return false;

				lenBeforeQuote = 0;
			}

			if(text[size] != 45)
				lenBeforeDash++;
			else
			{
				if(lenBeforeDash <= 1 || size == textLength - 1 || text[size + 1] == 32)
					return false;

				lenBeforeDash = 0;
			}

			if(text[size] == lastChar)
			{
				repeatedCharacter++;
				if(repeatedCharacter > 2)
					return false;
			}
			else
				repeatedCharacter = 0;

			lastChar = text[size];
		}
		else
		{
			if(lenBeforeSpace <= 1 || size == textLength - 1 || text[size + 1] == 32)
				return false;

			lenBeforeSpace = lenBeforeQuote = lenBeforeDash = 0;
		}

		if(!(isLowercaseLetter(text[size]) || text[size] == 32 || text[size] == 39 || text[size] == 45
			|| (isUppercaseLetter(text[size]) && text[size - 1] == 32)))
			return false;
	}

	return true;
}

bool isNumbers(std::string text)
{
	uint32_t textLength = text.length();
	for(uint32_t size = 0; size < textLength; size++)
	{
		if(!isNumber(text[size]))
			return false;
	}

	return true;
}

bool checkText(std::string text, std::string str)
{
	trimString(text);
	return asLowerCaseString(text) == str;
}

std::string generateRecoveryKey(int32_t fieldCount, int32_t fieldLenght, bool mixCase/* = false*/)
{
	std::stringstream key;
	int32_t i = 0, j = 0, lastNumber = 99, number = 0;

	char character = 0, lastCharacter = 0;
	bool madeNumber = false, madeCharacter = false;
	do
	{
		do
		{
			madeNumber = madeCharacter = false;
			if((mixCase && !random_range(0, 2)) || (!mixCase && !random_range(0, 1)))
			{
				number = random_range(2, 9);
				if(number != lastNumber)
				{
					key << number;
					lastNumber = number;
					madeNumber = true;
				}
			}
			else
			{
				if(mixCase && !random_range(0, 1))
					character = (char)random_range(97, 122);
				else
					character = (char)random_range(65, 90);

				if(character != lastCharacter)
				{
					key << character;
					lastCharacter = character;
					madeCharacter = true;
				}
			}
		}
		while((!madeCharacter && !madeNumber) ? true : (++j && j < fieldLenght));
		lastCharacter = character = number = j = 0;

		lastNumber = 99;
		if(i < fieldCount - 1)
			key << "-";
	}
	while(++i && i < fieldCount);
	return key.str();
}

std::string trimString(std::string& str)
{
	str.erase(str.find_last_not_of(" ") + 1);
	return str.erase(0, str.find_first_not_of(" "));
}

std::string parseParams(tokenizer::iterator &it, tokenizer::iterator end)
{
	if(it == end)
		return "";

	std::string tmp = (*it);
	++it;
	if(tmp[0] == '"')
	{
		tmp.erase(0, 1);
		while(it != end && tmp[tmp.length() - 1] != '"')
		{
			tmp += " " + (*it);
			++it;
		}

		if(tmp.length() > 0 && tmp[tmp.length() - 1] == '"')
			tmp.erase(tmp.length() - 1);
	}

	return tmp;
}

std::string formatDate(time_t _time/* = 0*/)
{
	if(!_time)
		_time = time(NULL);

	const tm* tms = localtime(&_time);
	std::stringstream s;
	if(tms)
		s << tms->tm_mday << "/" << (tms->tm_mon + 1) << "/" << (tms->tm_year + 1900) << " " << tms->tm_hour << ":" << tms->tm_min << ":" << tms->tm_sec;
	else
		s << "UNIX Time: " << (int32_t)_time;

	return s.str();
}

std::string formatDateEx(time_t _time/* = 0*/, std::string format/* = "%d %b %Y, %H:%M:%S"*/)
{
	if(!_time)
		_time = time(NULL);

	const tm* tms = localtime(&_time);
	char buffer[100];
	if(tms)
		strftime(buffer, 25, format.c_str(), tms);
	else
		sprintf(buffer, "UNIX Time: %d", (int32_t)_time);

	return buffer;
}

std::string formatTime(time_t _time/* = 0*/, bool ms/* = false*/)
{
	if(!_time)
		_time = time(NULL);
	else if(ms)
		ms = false;

	const tm* tms = localtime(&_time);
	std::stringstream s;
	if(tms)
	{
		s << tms->tm_hour << ":" << tms->tm_min << ":";
		if(tms->tm_sec < 10)
			s << "0";

		s << tms->tm_sec;
		if(ms)
		{
			timeb t;
			ftime(&t);

			s << "."; // make it format zzz
			if(t.millitm < 10)
				s << "0";

			if(t.millitm < 100)
				s << "0";

			s << t.millitm;
		}
	}
	else
		s << "UNIX Time: " << (int32_t)_time;

	return s.str();
}

std::string convertIPAddress(uint32_t ip)
{
	char buffer[17];
	sprintf(buffer, "%d.%d.%d.%d", ip & 0xFF, (ip >> 8) & 0xFF, (ip >> 16) & 0xFF, (ip >> 24));
	return buffer;
}

Skulls_t getSkulls(std::string strValue)
{
	std::string tmpStrValue = asLowerCaseString(strValue);
	if(tmpStrValue == "black" || tmpStrValue == "5")
		return SKULL_BLACK;

	if(tmpStrValue == "red" || tmpStrValue == "4")
		return SKULL_RED;

	if(tmpStrValue == "white" || tmpStrValue == "3")
		return SKULL_WHITE;

	if(tmpStrValue == "green" || tmpStrValue == "2")
		return SKULL_GREEN;

	if(tmpStrValue == "yellow" || tmpStrValue == "1")
		return SKULL_YELLOW;

	return SKULL_NONE;
}

PartyShields_t getShields(std::string strValue)
{
	std::string tmpStrValue = asLowerCaseString(strValue);
	if(tmpStrValue == "whitenoshareoff" || tmpStrValue == "10")
		return SHIELD_YELLOW_NOSHAREDEXP;

	if(tmpStrValue == "blueshareoff" || tmpStrValue == "9")
		return SHIELD_BLUE_NOSHAREDEXP;

	if(tmpStrValue == "yellowshareblink" || tmpStrValue == "8")
		return SHIELD_YELLOW_NOSHAREDEXP_BLINK;

	if(tmpStrValue == "blueshareblink" || tmpStrValue == "7")
		return SHIELD_BLUE_NOSHAREDEXP_BLINK;

	if(tmpStrValue == "yellowshareon" || tmpStrValue == "6")
		return SHIELD_YELLOW_SHAREDEXP;

	if(tmpStrValue == "blueshareon" || tmpStrValue == "5")
		return SHIELD_BLUE_SHAREDEXP;

	if(tmpStrValue == "yellow" || tmpStrValue == "4")
		return SHIELD_YELLOW;

	if(tmpStrValue == "blue" || tmpStrValue == "3")
		return SHIELD_BLUE;

	if(tmpStrValue == "whiteyellow" || tmpStrValue == "2")
		return SHIELD_WHITEYELLOW;

	if(tmpStrValue == "whiteblue" || tmpStrValue == "1")
		return SHIELD_WHITEBLUE;

	return SHIELD_NONE;
}

GuildEmblems_t getEmblems(std::string strValue)
{
	std::string tmpStrValue = asLowerCaseString(strValue);
	if(tmpStrValue == "blue" || tmpStrValue == "3")
		return EMBLEM_BLUE;

	if(tmpStrValue == "red" || tmpStrValue == "2")
		return EMBLEM_RED;

	if(tmpStrValue == "green" || tmpStrValue == "1")
		return EMBLEM_GREEN;

	return EMBLEM_NONE;
}

Direction getDirection(std::string string)
{
	if(string == "north" || string == "n" || string == "0")
		return NORTH;

	if(string == "east" || string == "e" || string == "1")
		return EAST;

	if(string == "south" || string == "s" || string == "2")
		return SOUTH;

	if(string == "west" || string == "w" || string == "3")
		return WEST;

	if(string == "southwest" || string == "south west" || string == "south-west" || string == "sw" || string == "4")
		return SOUTHWEST;

	if(string == "southeast" || string == "south east" || string == "south-east" || string == "se" || string == "5")
		return SOUTHEAST;

	if(string == "northwest" || string == "north west" || string == "north-west" || string == "nw" || string == "6")
		return NORTHWEST;

	if(string == "northeast" || string == "north east" || string == "north-east" || string == "ne" || string == "7")
		return NORTHEAST;

	return SOUTH;
}

Direction getDirectionTo(Position pos1, Position pos2, bool extended/* = true*/)
{
	Direction direction = NORTH;
	if(pos1.x > pos2.x)
	{
		direction = WEST;
		if(extended)
		{
			if(pos1.y > pos2.y)
				direction = NORTHWEST;
			else if(pos1.y < pos2.y)
				direction = SOUTHWEST;
		}
	}
	else if(pos1.x < pos2.x)
	{
		direction = EAST;
		if(extended)
		{
			if(pos1.y > pos2.y)
				direction = NORTHEAST;
			else if(pos1.y < pos2.y)
				direction = SOUTHEAST;
		}
	}
	else
	{
		if(pos1.y > pos2.y)
			direction = NORTH;
		else if(pos1.y < pos2.y)
			direction = SOUTH;
	}

	return direction;
}

Direction getReverseDirection(Direction dir)
{
	switch(dir)
	{
		case NORTH:
			return SOUTH;
		case SOUTH:
			return NORTH;
		case WEST:
			return EAST;
		case EAST:
			return WEST;
		case SOUTHWEST:
			return NORTHEAST;
		case NORTHWEST:
			return SOUTHEAST;
		case NORTHEAST:
			return SOUTHWEST;
		case SOUTHEAST:
			return NORTHWEST;
	}

	return SOUTH;
}

Position getNextPosition(Direction direction, Position pos)
{
	switch(direction)
	{
		case NORTH:
			pos.y--;
			break;
		case SOUTH:
			pos.y++;
			break;
		case WEST:
			pos.x--;
			break;
		case EAST:
			pos.x++;
			break;
		case SOUTHWEST:
			pos.x--;
			pos.y++;
			break;
		case NORTHWEST:
			pos.x--;
			pos.y--;
			break;
		case SOUTHEAST:
			pos.x++;
			pos.y++;
			break;
		case NORTHEAST:
			pos.x++;
			pos.y--;
			break;
	}

	return pos;
}

struct AmmoTypeNames
{
	const char* name;
	Ammo_t ammoType;
};

struct MagicEffectNames
{
	const char* name;
	MagicEffect_t magicEffect;
};

struct ShootTypeNames
{
	const char* name;
	ShootEffect_t shootType;
};

struct CombatTypeNames
{
	const char* name;
	CombatType_t combatType;
};

struct AmmoActionNames
{
	const char* name;
	AmmoAction_t ammoAction;
};

struct FluidTypeNames
{
	const char* name;
	FluidTypes_t fluidType;
};

struct SkillIdNames
{
	const char* name;
	skills_t skillId;
};

struct WeaponTypeNames
{
	const char* name;
	WeaponType_t weaponType;
};

MagicEffectNames magicEffectNames[] =
{
	{"redspark",			CONST_ME_DRAWBLOOD},
	{"bluebubble",			CONST_ME_LOSEENERGY},
	{"poff",				CONST_ME_POFF},
	{"yellowspark",			CONST_ME_BLOCKHIT},
	{"explosionarea",		CONST_ME_EXPLOSIONAREA},
	{"explosion",			CONST_ME_EXPLOSIONHIT},
	{"firearea",			CONST_ME_FIREAREA},
	{"yellowbubble",		CONST_ME_YELLOW_RINGS},
	{"greenbubble",			CONST_ME_GREEN_RINGS},
	{"blackspark",			CONST_ME_HITAREA},
	{"teleport",			CONST_ME_TELEPORT},
	{"energy",				CONST_ME_ENERGYHIT},
	{"blueshimmer",			CONST_ME_MAGIC_BLUE},
	{"redshimmer",			CONST_ME_MAGIC_RED},
	{"greenshimmer",		CONST_ME_MAGIC_GREEN},
	{"fire",				CONST_ME_HITBYFIRE},
	{"greenspark",			CONST_ME_HITBYPOISON},
	{"mortarea",			CONST_ME_MORTAREA},
	{"greennote",			CONST_ME_SOUND_GREEN},
	{"rednote",				CONST_ME_SOUND_RED},
	{"poison",				CONST_ME_POISONAREA},
	{"yellownote",			CONST_ME_SOUND_YELLOW},
	{"purplenote",			CONST_ME_SOUND_PURPLE},
	{"bluenote",			CONST_ME_SOUND_BLUE},
	{"whitenote",			CONST_ME_SOUND_WHITE},
	{"bubbles",				CONST_ME_BUBBLES},
	{"dice",				CONST_ME_CRAPS},
	{"giftwraps",			CONST_ME_GIFT_WRAPS},
	{"yellowfirework",		CONST_ME_FIREWORK_YELLOW},
	{"redfirework",			CONST_ME_FIREWORK_RED},
	{"bluefirework",		CONST_ME_FIREWORK_BLUE},
	{"stun",				CONST_ME_STUN},
	{"sleep",				CONST_ME_SLEEP},
	{"watercreature",		CONST_ME_WATERCREATURE},
	{"groundshaker",		CONST_ME_GROUNDSHAKER},
	{"hearts",				CONST_ME_HEARTS},
	{"fireattack",			CONST_ME_FIREATTACK},
	{"energyarea",			CONST_ME_ENERGYAREA},
	{"smallclouds",			CONST_ME_SMALLCLOUDS},
	{"holydamage",			CONST_ME_HOLYDAMAGE},
	{"bigclouds",			CONST_ME_BIGCLOUDS},
	{"icearea",				CONST_ME_ICEAREA},
	{"icetornado",			CONST_ME_ICETORNADO},
	{"iceattack",			CONST_ME_ICEATTACK},
	{"stones",				CONST_ME_STONES},
	{"smallplants",			CONST_ME_SMALLPLANTS},
	{"carniphila",			CONST_ME_CARNIPHILA},
	{"purpleenergy",		CONST_ME_PURPLEENERGY},
	{"yellowenergy",		CONST_ME_YELLOWENERGY},
	{"holyarea",			CONST_ME_HOLYAREA},
	{"bigplants",			CONST_ME_BIGPLANTS},
	{"cake",				CONST_ME_CAKE},
	{"giantice",			CONST_ME_GIANTICE},
	{"watersplash",			CONST_ME_WATERSPLASH},
	{"plantattack",			CONST_ME_PLANTATTACK},
	{"tutorialarrow",		CONST_ME_TUTORIALARROW},
	{"tutorialsquare",		CONST_ME_TUTORIALSQUARE},
	{"mirrorhorizontal",	CONST_ME_MIRRORHORIZONTAL},
	{"mirrorvertical",		CONST_ME_MIRRORVERTICAL},
	{"skullhorizontal",		CONST_ME_SKULLHORIZONTAL},
	{"skullvertical",		CONST_ME_SKULLVERTICAL},
	{"assassin",			CONST_ME_ASSASSIN},
	{"stepshorizontal",		CONST_ME_STEPSHORIZONTAL},
	{"bloodysteps",			CONST_ME_BLOODYSTEPS},
	{"stepsvertical",		CONST_ME_STEPSVERTICAL},
	{"yalaharighost",		CONST_ME_YALAHARIGHOST},
	{"bats",				CONST_ME_BATS},
	{"smoke",				CONST_ME_SMOKE},
	{"insects",				CONST_ME_INSECTS},
	{"dragonhead",			CONST_ME_DRAGONHEAD}
};

ShootTypeNames shootTypeNames[] =
{
	{"spear",			CONST_ANI_SPEAR},
	{"bolt",			CONST_ANI_BOLT},
	{"arrow",			CONST_ANI_ARROW},
	{"fire",			CONST_ANI_FIRE},
	{"energy",			CONST_ANI_ENERGY},
	{"poisonarrow",		CONST_ANI_POISONARROW},
	{"burstarrow",		CONST_ANI_BURSTARROW},
	{"throwingstar",	CONST_ANI_THROWINGSTAR},
	{"throwingknife",	CONST_ANI_THROWINGKNIFE},
	{"smallstone",		CONST_ANI_SMALLSTONE},
	{"death",			CONST_ANI_DEATH},
	{"largerock",		CONST_ANI_LARGEROCK},
	{"snowball",		CONST_ANI_SNOWBALL},
	{"powerbolt",		CONST_ANI_POWERBOLT},
	{"poison",			CONST_ANI_POISON},
	{"infernalbolt",	CONST_ANI_INFERNALBOLT},
	{"huntingspear",	CONST_ANI_HUNTINGSPEAR},
	{"enchantedspear",	CONST_ANI_ENCHANTEDSPEAR},
	{"redstar",			CONST_ANI_REDSTAR},
	{"greenstar",		CONST_ANI_GREENSTAR},
	{"royalspear",		CONST_ANI_ROYALSPEAR},
	{"sniperarrow",		CONST_ANI_SNIPERARROW},
	{"onyxarrow",		CONST_ANI_ONYXARROW},
	{"piercingbolt",	CONST_ANI_PIERCINGBOLT},
	{"whirlwindsword",	CONST_ANI_WHIRLWINDSWORD},
	{"whirlwindaxe",	CONST_ANI_WHIRLWINDAXE},
	{"whirlwindclub",	CONST_ANI_WHIRLWINDCLUB},
	{"etherealspear",	CONST_ANI_ETHEREALSPEAR},
	{"ice",				CONST_ANI_ICE},
	{"earth",			CONST_ANI_EARTH},
	{"holy",			CONST_ANI_HOLY},
	{"suddendeath",		CONST_ANI_SUDDENDEATH},
	{"flasharrow",		CONST_ANI_FLASHARROW},
	{"flammingarrow",	CONST_ANI_FLAMMINGARROW},
	{"flamingarrow",	CONST_ANI_FLAMMINGARROW},
	{"shiverarrow",		CONST_ANI_SHIVERARROW},
	{"energyball",		CONST_ANI_ENERGYBALL},
	{"smallice",		CONST_ANI_SMALLICE},
	{"smallholy",		CONST_ANI_SMALLHOLY},
	{"smallearth",		CONST_ANI_SMALLEARTH},
	{"eartharrow",		CONST_ANI_EARTHARROW},
	{"explosion",		CONST_ANI_EXPLOSION},
	{"cake",			CONST_ANI_CAKE}
};

CombatTypeNames combatTypeNames[] =
{
	{"physical",	COMBAT_PHYSICALDAMAGE},
	{"energy",		COMBAT_ENERGYDAMAGE},
	{"earth",		COMBAT_EARTHDAMAGE},
	{"fire",		COMBAT_FIREDAMAGE},
	{"undefined",	COMBAT_UNDEFINEDDAMAGE},
	{"lifedrain",	COMBAT_LIFEDRAIN},
	{"life drain",	COMBAT_LIFEDRAIN},
	{"manadrain",	COMBAT_MANADRAIN},
	{"mana drain",	COMBAT_MANADRAIN},
	{"healing",		COMBAT_HEALING},
	{"drown",		COMBAT_DROWNDAMAGE},
	{"ice",			COMBAT_ICEDAMAGE},
	{"holy",		COMBAT_HOLYDAMAGE},
	{"death",		COMBAT_DEATHDAMAGE}
};

AmmoTypeNames ammoTypeNames[] =
{
	{"spear",			AMMO_SPEAR},
	{"arrow",			AMMO_ARROW},
	{"poisonarrow",		AMMO_ARROW},
	{"burstarrow",		AMMO_ARROW},
	{"bolt",			AMMO_BOLT},
	{"powerbolt",		AMMO_BOLT},
	{"smallstone",		AMMO_STONE},
	{"largerock",		AMMO_STONE},
	{"throwingstar",	AMMO_THROWINGSTAR},
	{"throwingknife",	AMMO_THROWINGKNIFE},
	{"snowball",		AMMO_SNOWBALL},
	{"huntingspear",	AMMO_SPEAR},
	{"royalspear",		AMMO_SPEAR},
	{"enchantedspear",	AMMO_SPEAR},
	{"sniperarrow",		AMMO_ARROW},
	{"onyxarrow",		AMMO_ARROW},
	{"piercingbolt",	AMMO_BOLT},
	{"infernalbolt",	AMMO_BOLT},
	{"flasharrow",		AMMO_ARROW},
	{"flammingarrow",	AMMO_ARROW},
	{"flamingarrow",	AMMO_ARROW},
	{"shiverarrow",		AMMO_ARROW},
	{"eartharrow",		AMMO_ARROW},
	{"etherealspear",	AMMO_SPEAR}
};

AmmoActionNames ammoActionNames[] =
{
	{"move",			AMMOACTION_MOVE},
	{"moveback",		AMMOACTION_MOVEBACK},
	{"move back",		AMMOACTION_MOVEBACK},
	{"removecharge",	AMMOACTION_REMOVECHARGE},
	{"remove charge",	AMMOACTION_REMOVECHARGE},
	{"removecount",		AMMOACTION_REMOVECOUNT},
	{"remove count",	AMMOACTION_REMOVECOUNT}
};

FluidTypeNames fluidTypeNames[] =
{
	{"none",		FLUID_NONE},
	{"water",		FLUID_WATER},
	{"blood",		FLUID_BLOOD},
	{"beer",		FLUID_BEER},
	{"slime",		FLUID_SLIME},
	{"lemonade",	FLUID_LEMONADE},
	{"milk",		FLUID_MILK},
	{"mana",		FLUID_MANA},
	{"life",		FLUID_LIFE},
	{"oil",			FLUID_OIL},
	{"urine",		FLUID_URINE},
	{"coconutmilk",	FLUID_COCONUTMILK},
	{"coconut milk",FLUID_COCONUTMILK},
	{"wine",		FLUID_WINE},
	{"mud",			FLUID_MUD},
	{"fruitjuice",	FLUID_FRUITJUICE},
	{"fruit juice",	FLUID_FRUITJUICE},
	{"lava",		FLUID_LAVA},
	{"rum",			FLUID_RUM},
	{"swamp",		FLUID_SWAMP},
	{"tea",			FLUID_TEA},
	{"mead",		FLUID_MEAD}
};

SkillIdNames skillIdNames[] =
{
	{"fist",		SKILL_FIST},
	{"club",		SKILL_CLUB},
	{"sword",		SKILL_SWORD},
	{"axe",			SKILL_AXE},
	{"distance",	SKILL_DISTANCE},
	{"dist",		SKILL_DISTANCE},
	{"shielding",	SKILL_SHIELD},
	{"shield",		SKILL_SHIELD},
	{"fishing",		SKILL_FISHING},
	{"fish",		SKILL_FISHING},
	{"level",		SKILL__LEVEL},
	{"magiclevel",	SKILL__MAGLEVEL},
	{"magic level",	SKILL__MAGLEVEL},
	{"experience",	SKILL__EXPERIENCE}
};

WeaponTypeNames weaponTypeNames[] = {
	{"",			WEAPON_NONE},
	{"sword",		WEAPON_SWORD},
	{"club",		WEAPON_CLUB},
	{"axe",			WEAPON_AXE},
	{"distance",	WEAPON_DISTANCE},
	{"shield",		WEAPON_SHIELD},
	{"fist",		WEAPON_FIST},
	{"wand",		WEAPON_WAND},
	{"ammunition",	WEAPON_AMMO}
};

MagicEffect_t getMagicEffect(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(magicEffectNames) / sizeof(MagicEffectNames); ++i)
	{
		if(boost::algorithm::iequals(strValue.c_str(), magicEffectNames[i].name))
			return magicEffectNames[i].magicEffect;
	}

	return CONST_ME_UNKNOWN;
}

ShootEffect_t getShootType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(shootTypeNames) / sizeof(ShootTypeNames); ++i)
	{
		if(boost::algorithm::iequals(strValue.c_str(), shootTypeNames[i].name))
			return shootTypeNames[i].shootType;
	}

	return CONST_ANI_UNKNOWN;
}

CombatType_t getCombatType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(combatTypeNames) / sizeof(CombatTypeNames); ++i)
	{
		if(boost::algorithm::iequals(strValue.c_str(), combatTypeNames[i].name))
			return combatTypeNames[i].combatType;
	}

	return COMBAT_NONE;
}

Ammo_t getAmmoType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(ammoTypeNames) / sizeof(AmmoTypeNames); ++i)
	{
		if(boost::algorithm::iequals(strValue.c_str(), ammoTypeNames[i].name))
			return ammoTypeNames[i].ammoType;
	}

	return AMMO_NONE;
}

AmmoAction_t getAmmoAction(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(ammoActionNames) / sizeof(AmmoActionNames); ++i)
	{
		if(boost::algorithm::iequals(strValue.c_str(), ammoActionNames[i].name))
			return ammoActionNames[i].ammoAction;
	}

	return AMMOACTION_NONE;
}

FluidTypes_t getFluidType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(fluidTypeNames) / sizeof(FluidTypeNames); ++i)
	{
		if(boost::algorithm::iequals(strValue.c_str(), fluidTypeNames[i].name))
			return fluidTypeNames[i].fluidType;
	}

	return FLUID_NONE;
}

skills_t getSkillId(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(skillIdNames) / sizeof(SkillIdNames); ++i)
	{
		if(boost::algorithm::iequals(strValue.c_str(), skillIdNames[i].name))
			return skillIdNames[i].skillId;
	}

	return SKILL_FIST;
}

WeaponType_t getWeaponType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(weaponTypeNames) / sizeof(WeaponTypeNames); ++i)
	{
		if(boost::algorithm::iequals(strValue.c_str(), weaponTypeNames[i].name))
			return weaponTypeNames[i].weaponType;
	}

	return WEAPON_NONE;
}

void getCombatDetails(CombatType_t combatType, MagicEffect_t& magicEffect, Color_t& textColor)
{
	switch(combatType)
	{
		case COMBAT_PHYSICALDAMAGE:
		{
			textColor = COLOR_RED;
			magicEffect = CONST_ME_DRAWBLOOD;
			break;
		}

		case COMBAT_ENERGYDAMAGE:
		{
			textColor = COLOR_PURPLE;
			magicEffect = CONST_ME_ENERGYHIT;
			break;
		}

		case COMBAT_EARTHDAMAGE:
		{
			textColor = COLOR_LIGHTGREEN;
			magicEffect = CONST_ME_GREEN_RINGS;
			break;
		}

		case COMBAT_DROWNDAMAGE:
		{
			textColor = COLOR_LIGHTBLUE;
			magicEffect = CONST_ME_LOSEENERGY;
			break;
		}

		case COMBAT_FIREDAMAGE:
		{
			textColor = COLOR_ORANGE;
			magicEffect = CONST_ME_HITBYFIRE;
			break;
		}

		case COMBAT_ICEDAMAGE:
		{
			textColor = COLOR_TEAL;
			magicEffect = CONST_ME_ICEATTACK;
			break;
		}

		case COMBAT_HOLYDAMAGE:
		{
			textColor = COLOR_YELLOW;
			magicEffect = CONST_ME_HOLYDAMAGE;
			break;
		}

		case COMBAT_DEATHDAMAGE:
		{
			textColor = COLOR_DARKRED;
			magicEffect = CONST_ME_SMALLCLOUDS;
			break;
		}

		case COMBAT_LIFEDRAIN:
		{
			textColor = COLOR_RED;
			magicEffect = CONST_ME_MAGIC_RED;
			break;
		}

		case COMBAT_MANADRAIN:
		{
			textColor = COLOR_BLUE;
			magicEffect = CONST_ME_LOSEENERGY;
		}

		default:
			break;
	}
}

std::string getCombatName(CombatType_t combatType)
{
	switch(combatType)
	{
		case COMBAT_PHYSICALDAMAGE:
			return "physical";
		case COMBAT_ENERGYDAMAGE:
			return "energy";
		case COMBAT_EARTHDAMAGE:
			return "earth";
		case COMBAT_FIREDAMAGE:
			return "fire";
		case COMBAT_UNDEFINEDDAMAGE:
			return "undefined";
		case COMBAT_LIFEDRAIN:
			return "life drain";
		case COMBAT_MANADRAIN:
			return "mana drain";
		case COMBAT_HEALING:
			return "healing";
		case COMBAT_DROWNDAMAGE:
			return "drown";
		case COMBAT_ICEDAMAGE:
			return "ice";
		case COMBAT_HOLYDAMAGE:
			return "holy";
		case COMBAT_DEATHDAMAGE:
			return "death";
		default:
			break;
	}

	return "unknown";
}

std::string getSkillName(uint16_t skillId, bool suffix/* = true*/)
{
	switch(skillId)
	{
		case SKILL_FIST:
		{
			std::string tmp = "fist";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_CLUB:
		{
			std::string tmp = "club";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_SWORD:
		{
			std::string tmp = "sword";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_AXE:
		{
			std::string tmp = "axe";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_DISTANCE:
		{
			std::string tmp = "distance";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_SHIELD:
			return "shielding";
		case SKILL_FISHING:
			return "fishing";
		case SKILL__MAGLEVEL:
			return "magic level";
		case SKILL__LEVEL:
			return "level";
		default:
			break;
	}

	return "unknown";
}

std::string getWeaponName(WeaponType_t weaponType)
{
	switch(weaponType)
	{
		case WEAPON_SWORD:
			return "sword";
		case WEAPON_CLUB:
			return "club";
		case WEAPON_AXE:
			return "axe";
		case WEAPON_DISTANCE:
			return "distance";
		case WEAPON_SHIELD:
			return "shield";
		case WEAPON_WAND:
			return "wand";
		case WEAPON_FIST:
			return "fist";
		case WEAPON_AMMO:
			return "ammunition";
		default:
			break;
	}

	return "";
}

std::string parseVocationString(StringVec vocStringVec)
{
	std::string str = "";
	if(!vocStringVec.empty())
	{
		for(StringVec::iterator it = vocStringVec.begin(); it != vocStringVec.end(); ++it)
		{
			if((*it) != vocStringVec.front())
			{
				if((*it) != vocStringVec.back())
					str += ", ";
				else
					str += " and ";
			}

			str += (*it);
			str += "s";
		}
	}

	return str;
}

bool parseVocationNode(xmlNodePtr vocationNode, VocationMap& vocationMap, StringVec& vocStringVec, std::string& errorStr)
{
	if(xmlStrcmp(vocationNode->name,(const xmlChar*)"vocation"))
		return true;

	int32_t vocationId = -1;
	std::string strValue, tmpStrValue;
	if(readXMLString(vocationNode, "name", strValue))
	{
		vocationId = Vocations::getInstance()->getVocationId(strValue);
		if(vocationId != -1)
		{
			vocationMap[vocationId] = true;
			int32_t promotedVocation = Vocations::getInstance()->getPromotedVocation(vocationId);
			if(promotedVocation != -1)
				vocationMap[promotedVocation] = true;
		}
		else
		{
			errorStr = "Wrong vocation name: " + strValue;
			return false;
		}
	}
	else if(readXMLString(vocationNode, "id", strValue))
	{
		IntegerVec intVector;
		if(!parseIntegerVec(strValue, intVector))
		{
			errorStr = "Invalid vocation id - '" + strValue + "'";
			return false;
		}

		size_t size = intVector.size();
		for(size_t i = 0; i < size; ++i)
		{
			Vocation* vocation = Vocations::getInstance()->getVocation(intVector[i]);
			if(vocation && vocation->getName() != "")
			{
				vocationId = vocation->getId();
				strValue = vocation->getName();

				vocationMap[vocationId] = true;
				int32_t promotedVocation = Vocations::getInstance()->getPromotedVocation(vocationId);
				if(promotedVocation != -1)
					vocationMap[promotedVocation] = true;
			}
			else
			{
				std::stringstream ss;
				ss << "Wrong vocation id: " << intVector[i];

				errorStr = ss.str();
				return false;
			}
		}
	}

	if(vocationId != -1 && (!readXMLString(vocationNode, "showInDescription", tmpStrValue) || booleanString(tmpStrValue)))
		vocStringVec.push_back(asLowerCaseString(strValue));

	return true;
}

bool parseIntegerVec(std::string str, IntegerVec& intVector)
{
	StringVec strVector = explodeString(str, ";");
	IntegerVec tmpIntVector;
	for(StringVec::iterator it = strVector.begin(); it != strVector.end(); ++it)
	{
		tmpIntVector = vectorAtoi(explodeString((*it), "-"));
		if(!tmpIntVector[0] && it->substr(0, 1) != "0")
			continue;

		intVector.push_back(tmpIntVector[0]);
		if(tmpIntVector.size() > 1)
		{
			while(tmpIntVector[0] < tmpIntVector[1])
				intVector.push_back(++tmpIntVector[0]);
		}
	}

	return true;
}

bool fileExists(const char* filename)
{
	FILE* f = fopen(filename, "rb");
	if(!f)
		return false;

	fclose(f);
	return true;
}

uint32_t adlerChecksum(uint8_t* data, size_t length)
{
	if(length > NETWORK_MAX_SIZE || !length)
		return 0;

	const uint16_t adler = 65521;
	uint32_t a = 1, b = 0;
	while(length > 0)
	{
		size_t tmp = length > 5552 ? 5552 : length;
		length -= tmp;
		do
		{
			a += *data++;
			b += a;
		}
		while(--tmp);
		a %= adler;
		b %= adler;
	}

	return (b << 16) | a;
}

std::string getReason(int32_t reasonId)
{
	switch(reasonId)
	{
		case 0:
			return "Offensive Name";
		case 1:
			return "Invalid Name Format";
		case 2:
			return "Unsuitable Name";
		case 3:
			return "Name Inciting Rule Violation";
		case 4:
			return "Offensive Statement";
		case 5:
			return "Spamming";
		case 6:
			return "Illegal Advertising";
		case 7:
			return "Off-Topic Public Statement";
		case 8:
			return "Non-English Public Statement";
		case 9:
			return "Inciting Rule Violation";
		case 10:
			return "Bug Abuse";
		case 11:
			return "Game Weakness Abuse";
		case 12:
			return "Using Unofficial Software to Play";
		case 13:
			return "Hacking";
		case 14:
			return "Multi-Clienting";
		case 15:
			return "Account Trading or Sharing";
		case 16:
			return "Threatening Gamemaster";
		case 17:
			return "Pretending to Have Influence on Rule Enforcement";
		case 18:
			return "False Report to Gamemaster";
		case 19:
			return "Destructive Behaviour";
		case 20:
			return "Excessive Unjustified Player Killing";
		default:
			break;
	}

	return "Unknown Reason";
}

std::string getAction(ViolationAction_t actionId, bool ipBanishment)
{
	std::string action = "Unknown";
	switch(actionId)
	{
		case ACTION_NOTATION:
			action = "Notation";
			break;
		case ACTION_NAMEREPORT:
			action = "Name Report";
			break;
		case ACTION_BANISHMENT:
			action = "Banishment";
			break;
		case ACTION_BANREPORT:
			action = "Name Report + Banishment";
			break;
		case ACTION_BANFINAL:
			action = "Banishment + Final Warning";
			break;
		case ACTION_BANREPORTFINAL:
			action = "Name Report + Banishment + Final Warning";
			break;
		case ACTION_STATEMENT:
			action = "Statement Report";
			break;
		//internal use
		case ACTION_DELETION:
			action = "Deletion";
			break;
		case ACTION_NAMELOCK:
			action = "Name Lock";
			break;
		case ACTION_BANLOCK:
			action = "Name Lock + Banishment";
			break;
		case ACTION_BANLOCKFINAL:
			action = "Name Lock + Banishment + Final Warning";
			break;
		default:
			break;
	}

	if(ipBanishment)
		action += " + IP Banishment";

	return action;
}

std::string getFilePath(FileType_t type, std::string name/* = ""*/)
{
	#ifdef __FILESYSTEM_HIERARCHY_STANDARD__
	std::string path = "/var/lib/tcs/";
	#else
	std::string path = g_config.getString(ConfigManager::DATA_DIRECTORY);
	#endif
	switch(type)
	{
		case FILE_TYPE_OTHER:
			path += name;
			break;
		case FILE_TYPE_XML:
			path += "XML/" + name;
			break;
		case FILE_TYPE_LOG:
			#ifndef __FILESYSTEM_HIERARCHY_STANDARD__
			path = g_config.getString(ConfigManager::LOGS_DIRECTORY) + name;
			#else
			path = "/var/log/tcs/" + name;
			#endif
			break;
		case FILE_TYPE_CONFIG:
		{
			#if defined(__HOMEDIR_CONF__)
			if(fileExists("~/.tcs/" + name))
				path = "~/.tcs/" + name;
			else
			#endif
			#if defined(__FILESYSTEM_HIERARCHY_STANDARD__)
				path = "/etc/tcs/" + name;
			#else
				path = name;
			#endif
			break;
		}
		default:
			std::clog << "ERROR: Wrong file type!" << std::endl;
			break;
	}
	return path;
}

std::string convertString(int number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}
