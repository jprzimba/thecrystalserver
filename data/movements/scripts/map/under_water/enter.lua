local config = {
	helmetId = 5461,  -- Helmet of the Deep item ID
	actionId = 4550,  -- Required action ID for the script to run
	zones = {
		{ 
			entryPositions = { {x = 345, y = 429, z = 7}, {x = 345, y = 430, z = 7} },
			teleportPosition = {x = 345, y = 429, z = 8},
			failOffset = {x = -1, y = 0}
		},
		{ 
			entryPositions = { {x = 265, y = 395, z = 7}, {x = 266, y = 395, z = 7} },
			teleportPosition = {x = 265, y = 395, z = 8},
			failOffset = {x = 0, y = 1}
		},
		{ 
			entryPositions = { {x = 628, y = 675, z = 7}, {x = 628, y = 676, z = 7} },
			teleportPosition = {x = 627, y = 676, z = 8},
			failOffset = {x = -1, y = 0}
		},
		{ 
			entryPositions = { {x = 537, y = 559, z = 7}, {x = 538, y = 559, z = 7} },
			teleportPosition = {x = 538, y = 559, z = 8},
			failOffset = {x = 0, y = -1}
		}
	},
	failMessage = "You must wear a Helmet of the Deep to go underwater."
}

function onStepIn(cid, item, position, fromPosition)
	if item.actionid ~= config.actionId then
		return true
	end

	for _, zone in ipairs(config.zones) do
		for _, entryPos in ipairs(zone.entryPositions) do
			if position.x == entryPos.x and position.y == entryPos.y and position.z == entryPos.z then
				if getPlayerInventoryItemId(cid, CONST_SLOT_HEAD) == config.helmetId then
					doTeleportThing(cid, zone.teleportPosition, false)
				else
					local failPosition = {x = position.x + zone.failOffset.x, y = position.y + zone.failOffset.y, z = position.z}
					doTeleportThing(cid, failPosition, false)
					doPlayerSendCancel(cid, config.failMessage)
				end
				return true
			end
		end
	end

	return true
end
