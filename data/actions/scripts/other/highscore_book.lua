function onUse(cid, item, fromPosition, itemEx, toPosition)
    if(item.actionid >= 150 and item.actionid <= 158) then
        doShowTextDialog(cid, item.itemid, getHighscoreString((item.actionid - 150)))
    else
        _result = false
    end
end