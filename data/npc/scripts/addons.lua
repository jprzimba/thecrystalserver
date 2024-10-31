local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)
local talkState = {}

function onCreatureAppear(cid)				npcHandler:onCreatureAppear(cid)			end
function onCreatureDisappear(cid)			npcHandler:onCreatureDisappear(cid)			end
function onCreatureSay(cid, type, msg)			npcHandler:onCreatureSay(cid, type, msg)		end
function onThink()					npcHandler:onThink()					end

local function addOutfits(cid, outfits, addon)
	for _, outfitId in ipairs(outfits) do
		doPlayerAddOutfit(cid, outfitId, addon)
	end
end

function creatureSayCallback(cid, type, msg)
	if(not npcHandler:isFocused(cid)) then
		return false
	end

	local talkUser = NPCHANDLER_CONVBEHAVIOR == CONVERSATION_DEFAULT and 0 or cid

	if(msgcontains(msg, 'first') or msgcontains(msg, 'first addon')) then
		if isPremium(cid) then
			if getPlayerTotalMoney(cid) >= 10000 then
				npcHandler:say('Did you buy first addons for 10k?', cid)
				talkState[talkUser] = 1
			else
				npcHandler:say('Come back when you have 10k.', cid)
			end
        else
            npcHandler:say('Sorry, you need a premium account to get addons.', cid)
        end
	elseif(msgcontains(msg, 'yes') and talkState[talkUser] == 1) then
        if getPlayerTotalMoney(cid) >= 10000 then
            if doPlayerRemoveMoney(cid, 10000) then
                npcHandler:say('Here you are.', cid)
                addOutfits(cid, maleOutfits, 1)
                addOutfits(cid, femaleOutfits, 1)
            end
        else
            npcHandler:say('Sorry, you don\'t have the items I requested.', cid)
        end
        talkState[talkUser] = 0
    elseif(msgcontains(msg, 'second') or msgcontains(msg, 'second addon')) then
        if isPremium(cid) then
			if getPlayerTotalMoney(cid) >= 20000 then
				npcHandler:say('Did you bring me the 20k?', cid)
                talkState[talkUser] = 4
            else
                npcHandler:say('Come back when you have the 20k.', cid)
            end
        else
            npcHandler:say('Sorry, you need a premium account to get addons.', cid)
        end
	elseif(msgcontains(msg, 'yes') and talkState[talkUser] == 4) then
		if getPlayerTotalMoney(cid) >= 20000 then
			if doPlayerRemoveMoney(cid, 20000) then
				npcHandler:say('Here you are.', cid)
				addOutfits(cid, maleOutfits, 2)
				addOutfits(cid, femaleOutfits, 2)
			end
		else
			npcHandler:say('Sorry, you don\'t have the items I requested.', cid)
		end
		talkState[talkUser] = 0
	elseif(msgcontains(msg, 'no') and isInArray({1}, talkState[talkUser])) then
		talkState[talkUser] = 0
		npcHandler:say('Ok then.', cid)
	end
	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())


