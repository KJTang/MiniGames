local ScoreSprite = class("ScoreSprite", function ()
    return cc.Sprite:create()
end)

function ScoreSprite:ctor(num)
    if num == 0 then
        local sprite = cc.Sprite:createWithSpriteFrameName("num_0.png"):addTo(self)
    else
        local result = {}
        while num ~= 0 do
            table.insert(result, 1, num % 10)
            num = math.ceil(num / 10) - 1
        end
        -- the distance between 2 numbers
        local distance = 30
        for i, v in ipairs(result) do
            local sprite = cc.Sprite:createWithSpriteFrameName(string.format("num_%d.png", v)):addTo(self)
            sprite:setPositionX((i-(#result+1)/2) * distance)
        end
    end
end

return ScoreSprite