local config = {
	costPremiumDays = 3 
}

function onSay(cid, words, param, channel)
	if(getPlayerSex(cid) > 1) then
		doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You cannot change your gender.")
		return true
	end

	if(not getConfigValue('freePremium')) then
		if(getPlayerPremiumDays(cid) < config.costPremiumDays) then
			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "Sorry, not enough premium time- changing gender costs " .. config.costPremiumDays .. " days.")
			doSendMagicEffect(getCreaturePosition(cid), CONST_ME_POFF)
			return true
		end

		if(getPlayerPremiumDays(cid) < 65535) then
			doPlayerAddPremiumDays(cid, -config.costPremiumDays)
		end
	end

	doPlayerSetSex(cid, getPlayerSex(cid) == PLAYERSEX_FEMALE and PLAYERSEX_MALE or PLAYERSEX_FEMALE)
	doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have changed your gender and lost " .. config.costPremiumDays .. " days of premium time.")
	doSendMagicEffect(getCreaturePosition(cid), CONST_ME_MAGIC_RED)
	return true
end
