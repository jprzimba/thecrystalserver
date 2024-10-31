local config = {
	access = 3
}

function onSay(cid, words, param, channel)
	-- Check player access and that param is not empty
	if getPlayerAccess(cid) >= config.access and param ~= "" then
		local x, y, z

		if param:match("{x%s*=%s*%d+,%s*y%s*=%s*%d+,%s*z%s*=%s*%d+}") then
			x = tonumber(param:match("x%s*=%s*(%d+)"))
			y = tonumber(param:match("y%s*=%s*(%d+)"))
			z = tonumber(param:match("z%s*=%s*(%d+)"))
		else
			local t = string.explode(param, ",")
			x = tonumber(t[1])
			y = tonumber(t[2])
			z = tonumber(t[3])
		end

		-- Verify that x, y, and z are valid numbers
		if x and y and z then
			local position = {x = x, y = y, z = z}
			doTeleportThing(cid, position)
		else
			doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Invalid coordinates. Use format: /pos x,y,z or /pos {x = ..., y = ..., z = ...}")
		end
	else
		-- Get current position if access level is not sufficient or no param provided
		local position = getCreaturePosition(cid)
		doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Your current position is [X: " .. position.x .. " | Y: " .. position.y .. " | Z: " .. position.z .. "]")
	end
	return true
end
