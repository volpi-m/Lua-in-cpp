function hello()
    print("Hello World")
end

function greets(name)
    print("Hello "..name)
end

function nope()
    return 1, 2
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
    a, b = nope()
    print(a, b)
end
