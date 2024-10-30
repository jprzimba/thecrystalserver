local config = {
    itemUID = 7000,
    itemIdStart = 1946,
    itemIdEnd = 1945,
    questLevel = 100,
    summonCreatureName = "Demon",
    playerPositions = {
        {x = 500, y = 755, z = 9, stackpos = 253},
        {x = 499, y = 755, z = 9, stackpos = 253},
        {x = 498, y = 755, z = 9, stackpos = 253},
        {x = 497, y = 755, z = 9, stackpos = 253},
    },
    demonPositions = {
        {x = 498, y = 753, z = 10},
        {x = 500, y = 753, z = 10},
        {x = 499, y = 757, z = 10},
        {x = 497, y = 757, z = 10},
        {x = 502, y = 755, z = 10},
        {x = 501, y = 755, z = 10},
    },
    newPlayerPositions = {
        {x = 500, y = 755, z = 10},
        {x = 499, y = 755, z = 10},
        {x = 498, y = 755, z = 10},
        {x = 497, y = 755, z = 10},
    },
    startingPos = {x = 495, y = 751, z = 10, stackpos = 253},
    endingPos = {x = 502, y = 759, z = 10, stackpos = 253},
}

function onUse(cid, item, fromPosition, itemEx, toPosition)
    if item.uid == config.itemUID then
        if item.itemid == config.itemIdStart then
            local players = {}
            local canSummon = true

            for i, pos in ipairs(config.playerPositions) do
                local player = getThingfromPos(pos)
                if player.itemid <= 0 then
                    canSummon = false
                    break
                end
                table.insert(players, player)
            end

            if canSummon then
                for _, player in ipairs(players) do
                    if getPlayerLevel(player.uid) < config.questLevel then
                        canSummon = false
                        break
                    end
                end

                if canSummon then
                    local questStatusValid = true
                    for _, player in ipairs(players) do
                        if getPlayerStorageValue(player.uid, 100) ~= -1 then
                            questStatusValid = false
                            break
                        end
                    end

                    if questStatusValid then
                        for _, pos in ipairs(config.demonPositions) do
                            doSummonCreature(config.summonCreatureName, pos)
                        end

                        for i, player in ipairs(players) do
                            doSendMagicEffect(config.playerPositions[i], CONST_ME_POFF)
                            doTeleportThing(player.uid, config.newPlayerPositions[i], 0)
                            doSendMagicEffect(config.newPlayerPositions[i], CONST_ME_TELEPORT)
                        end

                        doTransformItem(item.uid, config.itemIdEnd)
                    else
                        doPlayerSendCancel(cid, "Sorry, not possible.")
                    end
                else
                    doPlayerSendCancel(cid, "Sorry, not possible.")
                end
            else
                doPlayerSendCancel(cid, "Sorry, not possible.")
            end
        end

        if item.itemid == config.itemIdEnd then
            local playersCount = 0
            local monstersCount = 0
            local monsters = {}
            local checking = {x = config.startingPos.x, y = config.startingPos.y, z = config.startingPos.z, stackpos = config.startingPos.stackpos}

            repeat
                local creature = getThingfromPos(checking)
                if creature.itemid > 0 then
                    if getPlayerAccess(creature.uid) == 0 then
                        playersCount = playersCount + 1
                    elseif getPlayerAccess(creature.uid) ~= 0 and getPlayerAccess(creature.uid) ~= 3 then
                        monstersCount = monstersCount + 1
                        monsters[monstersCount] = creature.uid
                    end
                end

                checking.x = checking.x + 1
                if checking.x > config.endingPos.x then
                    checking.x = config.startingPos.x
                    checking.y = checking.y + 1
                end
            until checking.y > config.endingPos.y

            if playersCount == 0 then
                local trash = {x = 547, y = 407, z = 10}
                for i = 1, monstersCount do
                    doTeleportThing(monsters[i], trash)
                end
                doTransformItem(item.uid, config.itemIdStart)
            end
        end
    end
    return true
end
