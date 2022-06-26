function hello(name)
    print("Hello "..name)
end

function main()
    mod = {}
    mod.greets = hello
    mod.weather = "sunny"
    mod.temperature = 24
    mod.unit = "Celsius"

    mod.greets("Frodo")
    print(mod.unit)
end

main()
