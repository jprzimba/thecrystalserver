local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)
local talkState = {}

function onCreatureAppear(cid)				npcHandler:onCreatureAppear(cid) 			end
function onCreatureDisappear(cid) 			npcHandler:onCreatureDisappear(cid) 		end
function onCreatureSay(cid, type, msg) 		npcHandler:onCreatureSay(cid, type, msg) 	end
function onThink() 							npcHandler:onThink() 						end
function onPlayerEndTrade(cid)				npcHandler:onPlayerEndTrade(cid)			end
function onPlayerCloseChannel(cid)			npcHandler:onPlayerCloseChannel(cid)		end

function creatureSayCallback(cid, type, msg)
	if(not npcHandler:isFocused(cid)) then
		return false
	end

	local talkUser = NPCHANDLER_CONVBEHAVIOR == CONVERSATION_DEFAULT and 0 or cid

--------------------MESSAGES------------------------------------------------------------------------------
	if msgcontains(msg, 'deposit') then
		npcHandler:say('Please tell me how much gold it is you would like to deposit.', cid)
		talkState[talkUser] = 1
	elseif msgcontains(msg, 'withdraw') then
		npcHandler:say('Please tell me how much gold you would like to withdraw.', cid)
		talkState[talkUser] = 3
	elseif msgcontains(msg, 'transfer') then
		npcHandler:say('Please tell me the amount of gold coins you would like to transfer.', cid)
		talkState[talkUser] = 5
	elseif msgcontains(msg, 'balance') then
		n = getPlayerTotalMoney(cid)
		npcHandler:say('Your balance are '..n..' golds.', cid)
		talkState[talkUser] = 0
----------------------DEPOSIT-------------------------------------------------------
	elseif talkState[talkUser] == 1 then
		if msgcontains(msg, 'all') then
			n = getPlayerMoney(cid)
			npcHandler:say('Do you want deposit '..n..' golds ?', cid)
			talkState[talkUser] = 2			
		else
			n = getNumber(msg)
			npcHandler:say('Do you want deposit '..n..' golds ?', cid)
			talkState[talkUser] = 2
		end
	elseif talkState[talkUser] == 2 then
		if msgcontains(msg, 'yes') then
			if getPlayerMoney(cid) >= n then
				doPlayerDepositMoney(cid, n)			
				npcHandler:say('You have successfully deposited ' .. n .. ' gold! Your account balance is '..getPlayerBalance(cid)..' golds.', cid) 
				talkState[talkUser] = 0
			else
				npcHandler:say('You don\'t have money.', cid)
			end
		else
			npcHandler:say('Ok then', cid)
		end
----------------------WITHDRAW------------------------------------------------------------------------------------------------------------------------------------	
	elseif talkState[talkUser] == 3 then
		if msgcontains(msg, 'all') then
			n = getPlayerBalance(cid)
			npcHandler:say('Do you want withdraw '..n..' golds ?', cid)
			talkState[talkUser] = 4			
		else
			n = getNumber(msg)
			npcHandler:say('Do you want withdraw '..n..' golds ?', cid)
			talkState[talkUser] = 4
		end
	elseif talkState[talkUser] == 4 then
		if msgcontains(msg, 'yes') then
			if getPlayerBalance(cid) >= n then
				doPlayerWithdrawMoney(cid, n)		
				npcHandler:say('Here you are, '..n..' gold. Now your balance account is ' ..getPlayerBalance(cid)..' golds.', cid)
				talkState[talkUser] = 0
			else
				npcHandler:say('There is not enough gold on your account', cid)
			end
		else
			npcHandler:say('Ok then', cid)
		end
----------------------TRANSFER----------------------------------------------------------------------------------------		
	elseif talkState[talkUser] == 5 then
		if msgcontains(msg, 'all') then
			n = getPlayerBalance(cid)
			npcHandler:say('Who would you like transfer '..n..' gold to?', cid)
			talkState[talkUser] = 6			
		else
			n = getNumber(msg)
			npcHandler:say('Who would you like transfer '..n..' gold to?', cid)
			talkState[talkUser] = 6
		end
	elseif talkState[talkUser] == 6 then
		p = msg
		npcHandler:say('So you would like to transfer '..n..' gold to '..p..'?', cid)
		talkState[talkUser] = 7
	elseif talkState[talkUser] == 7 then
		if msgcontains(msg, 'yes') then
			if getPlayerBalance(cid) >= n then
				if doPlayerTransferMoneyTo(cid, p, n) then
					npcHandler:say('You have transferred '..n..' gold to '..p..' and your account balance is '..getPlayerBalance(cid)..' golds.', cid)
					talkState[talkUser] = 0
				else
					npcHandler:say('This player does not exist. Please tell me a valid name!', cid)
				end
			else
				npcHandler:say('There is not enough gold on your account', cid)
			end
		else
			npcHandler:say('Ok then', cid)
		end
	end
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())

-- function maded by Gesior--
function getNumber(txt)
	x = string.gsub(txt,"%a","")
	x = tonumber(x)
	if x ~= nill and x > 0 then
		return x
	else
		return 0
	end
end