function onSay(cid, words, param, channel)
    local t = string.explode(param, ",")
    local balance = getPlayerBalance(cid)
    
    if not t[1] then
        doPlayerPopupFYI(cid, "The commands are:\n !bank balance\n !bank deposit XXXX\n !bank depositall\n !bank transfer amount toPlayer")
        return true
    end

    if t[1] == 'balance' then
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Your account balance is " .. balance .. ".")
    
    elseif t[1] == 'deposit' then
        local amount = tonumber(t[2])
        if not amount then
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You need to specify the amount of money to deposit.")
            return true
        end
        amount = math.abs(amount)
        if amount > 0 and amount <= getPlayerMoney(cid) then
            doPlayerDepositMoney(cid, amount)
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You added " .. amount .. " to your account.\nYour account balance is " .. getPlayerBalance(cid) .. ".")
        else
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You do not have enough money to deposit.")
        end

    elseif t[1] == 'depositall' then
        local amount = getPlayerMoney(cid)
        if amount > 0 then
            doPlayerDepositMoney(cid, amount)
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You added " .. amount .. " to your account.\nYour account balance is " .. getPlayerBalance(cid) .. ".")
        else
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You do not have enough money to deposit.")
        end

    elseif t[1] == 'withdraw' then
        local amount = tonumber(t[2])
        if not amount then
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You need to specify the amount of money to withdraw.")
            return true
        end
        amount = math.abs(amount)
        if amount > 0 and amount <= getPlayerBalance(cid) then
            doPlayerWithdrawMoney(cid, amount)
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Here is " .. amount .. " from your account.\nYour account balance is " .. getPlayerBalance(cid) .. ".")
        else
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You do not have enough money in your bank account.")
        end

    elseif t[1] == 'withdrawall' then
        local amount = getPlayerBalance(cid)
        if amount > 0 then
            doPlayerWithdrawMoney(cid, amount)
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Here is all your money from your account.\nYour account balance is " .. getPlayerBalance(cid) .. ".")
        else
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You do not have enough money in your bank account.")
        end

    elseif t[1] == 'transfer' then
        local amount = tonumber(t[2])
        local targetPlayer = t[3]
        
        if not amount then
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You need to enter a valid amount.")
            return true
        end
        if not targetPlayer then
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You need to enter the player's name.")
            return true
        end

        amount = math.abs(amount)
        if amount <= balance then
            local targetGUID = getPlayerGUIDByName(targetPlayer)
            if targetGUID then
                doPlayerSetBalance(cid, balance - amount)
                db.query("UPDATE players SET balance = balance + " .. amount .. " WHERE id = " .. targetGUID) -- Adiciona ao jogador alvo
                
                doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You successfully transferred " .. amount .. " to " .. targetPlayer .. "'s bank account.")
            else
                doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "A player with the name '" .. targetPlayer .. "' does not exist.")
            end
        else
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You do not have enough money in your bank account to complete this transfer.")
        end
    else
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Invalid parameter.")
    end
    return true
end
