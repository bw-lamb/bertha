Card = {val = nil, suit = nil}

function Card.__eq(c1, c2)
    return c1.val == c2.val and c1.suit == c2.suit
end

function Card.__lt(c1, c2)
    return c1.val < c2.val
end

function Card:new(val, suit)
    local c = {val=val, suit=suit}
    setmetatable(c, self)
    self.__index = self
    return c
end

function Card.print(c)
    assert(c.val ~= nil and c.suit ~= nil)

    io.write(string.format(c.val .. c.suit .. " "))
end

Hand = {}

function Hand:new(other, initial_cards)
    other = other or {}
    setmetatable(other, self)
    self.__index = self

    if initial_cards then
        for _, c in pairs(initial_cards) do
            table.insert(other, c)
        end
    end;

    return other
end

function Hand:add(card)
    table.insert(self, card)
end

function Hand:remove(card)
    for i, v in pairs(self) do
        if v == card then
            table.remove(self, i)
            do return end
        end
    end
end

function Hand:all_with_val(val)
    assert(val > 0, 'Hand:sall_with_val - "val" is not an integer greater than zero.')

    local matches = {}

    for _, card in pairs(self) do
        if card["val"] == val then
            table.insert(matches, card)
        end
    end

    return matches
end

POSSIBLE_CARD_VALS = {1,2,3,4,5,6,7,8,9,10,11,12,13}

function Hand:has_nkind(num)
    assert(num > 0, 'Hand:has_nkind - "num" is not an integer greater than zero.')

    local kind = {}

    for i = 1, 13 do
        kind = self:all_with_val(i)

        io.write(string.format("Trying to find " .. num .. " of a kind with " .. i .. "\n"))
        for _,v in pairs(kind) do v:print() end
        print()

        if #kind >= num then
            for j=1,num do
                self:remove(kind[j])
            end

            for j=#kind, num+1, -1 do
                table.remove(kind, j)
            end
            do return kind end
        else
            kind = {}
        end
    end

    return nil
end

function Hand:has_nrun(num)
    assert(num > 0, 'Hand:has_nrun - "num" is not an integer greater than zero.')

    local run = {}

    for i=1, 13 do
        for j=0, num - 1 do
            local x = self:all_with_val(i+j)

            if x then
                table.insert(run, x[1])
            else
                run = {}
            end
        end

        if #run >= num then
            for j=1,num do
                self:remove(run[j])
            end

            for j=#run, num+1, -1 do
                table.remove(run, j)
            end
            do return run end
        else
            run = {}
        end
    end

    return nil
end

function Hand:level_one()
    local backup = Hand:new(self, self)

    local kind = self:has_nkind(3)

    if not kind then
        self = backup
        do return nil end
    end

    local run = self:has_nrun(4)
    if not run then
        self = backup
        do return nil end
    end

    return {kind, run}
end

init = {Card:new(7, 1), Card:new(2, 1), Card:new(2, 2), Card:new(2,3), Card:new(3, 1), Card:new(4, 1), Card:new(5, 1)}

--@type=Hand
h = Hand:new({}, init)

for _,v in pairs(h) do v.print(v) end
print()

res = h:level_one()

print("\nAFTER\n")

if res == nil then
    print("Failed")
else
    for _, v in pairs(res) do
        for _,c in pairs(res) do 
            v:print()
        end
    end
    print()
end

for _,v in pairs(h) do v:print() end
print()
