-- no paramater, no return
function greets()
   print("Bonjouw")
end

-- String parameter, no return
function catHello(str)
   print(str .. "Hello")
end

-- Two int paramater, one return
function add(a, b)
   return a + b, 2
end

-- String, Number, Nil, Boolean, no return
function printAllType(str, nb, null, boolean, float)
   print(str)
   print(nb)
   print(null)
   print(boolean)
   print(float)
end

function returnAllType(a)
   return 1, "2", 3.0, true, 5
end
