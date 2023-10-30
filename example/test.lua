function greets(name)
    print("[Lua] Hello "..name)
end

function my_sin_int(x)
    print("[Lua] "..math.sin(x))
end

function is_true(b)
    print("[Lua] ", b == true)
end

function my_sin_float(x)
    print("[Lua] "..math.sin(x))
end

function both_sin(x1, x2)
    my_sin_float(x1)
    my_sin_int(x2)
end

function all(name, b, f, i)
    greets(name)
    is_true(b)
    my_sin_float(f)
    my_sin_int(i)
    return 1234
end

function add_test()
    print("[Lua] "..mymath.add(1, 2))
end
