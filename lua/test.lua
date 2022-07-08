function hello()
    print("[Lua] Hello World")
end

function greets(name)
    print("[Lua] Hello "..name)
end

function printBoth(a, b)
    print("[Lua] "..a.." "..b)
end

function nope()
    return 1, 2
end

function add(nb1, nb2)
    print("[Lua] add "..nb1.." "..nb2)
    return nb1 + nb2
end

function dump(o)
    if type(o) == 'table' then
        local s = '{ '
        for k,v in pairs(o) do
            if type(k) ~= 'number' then k = '"'..k..'"' end
            s = s .. '['..k..'] = ' .. dump(v) .. ','
        end
        return s .. '} '
    else
        return tostring(o)
    end
 end

function main()
    hello()
    greets("Frodo")
    yeet._yeet()
    a, b = nope()
    print(a, b)
end
