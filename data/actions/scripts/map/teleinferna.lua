local config = {
    scarabPos = {x = 649, y = 615, z = 10, stackpos = STACKPOS_TOP_MOVEABLE_ITEM_OR_CREATURE},
    telePos = {x = 607, y = 649, z = 10, stackpos = 1},
    effect1Pos = {x = 649, y = 616, z = 10, stackpos = 1},
    scarabItemId = 5954,
    demonHornItemId = 1485,
}

function onUse(cid, item, fromPosition, itemEx, toPosition)
    local scarab = getThingfromPos(config.scarabPos)
    local playerPos = getPlayerPosition(cid)

    if scarab.itemid == config.scarabItemId and playerPos.x == 649 and playerPos.y == 616 and playerPos.z == 10 then
        doTeleportThing(cid, config.telePos)
        doSendMagicEffect(config.effect1Pos, CONST_ME_MAGIC_BLUE)
        doSendMagicEffect(config.telePos, CONST_ME_ENERGYAREA)
        doSendMagicEffect(config.scarabPos, CONST_ME_POFF)
        doRemoveItem(scarab.uid, 1)
    else
        doPlayerSendCancel(cid, "You need to stay in the fire.")
    end

    if item.itemid == config.demonHornItemId then
        doPlayerSendCancel(cid, "Put Demon Horn on coal basin.")
    end

    return true
end
