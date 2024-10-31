local teleportPositions = {
	goTp = {x = 655, y = 975, z = 4},
	backTp = {x = 646, y = 986, z = 3},
	flameGo = {x = 649, y = 916, z = 6},
	flameBack = {x = 649, y = 920, z = 6}
}

function onStepIn(cid, item, position, lastPosition, fromPosition, toPosition, actor)
	if(not isPlayer(cid)) then
		return false
	end

	if item.actionid == 49331 then
		doTeleportThing(cid, teleportPositions.goTp)
		doSendMagicEffect(getCreaturePosition(cid), CONST_ME_TELEPORT)
	elseif item.actionid == 49340 then
		doTeleportThing(cid, teleportPositions.backTp)
		doSendMagicEffect(getCreaturePosition(cid), CONST_ME_TELEPORT)
	elseif item.actionid == 49341 then
		doTeleportThing(cid, teleportPositions.flameGo)
		doSendMagicEffect(getCreaturePosition(cid), CONST_ME_TELEPORT)
	elseif item.actionid == 49342 then
		doTeleportThing(cid, teleportPositions.flameBack)
		doSendMagicEffect(getCreaturePosition(cid), CONST_ME_TELEPORT)
	end

	return true
end
