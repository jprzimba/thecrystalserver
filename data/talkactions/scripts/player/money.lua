function onSay(cid, words, param, channel)
	doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You have " .. doNumberFormat(getPlayerTotalMoney(cid)) .. " gold.")
	return true
end
