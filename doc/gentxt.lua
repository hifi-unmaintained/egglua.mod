#!/usr/bin/env lua

function table.implode(t, glue)
    local buf = ''
    local first = true
    if glue == nil then glue = ", " end
    for i,v in pairs(t) do
        if type(v) == 'string' then
            if first then first = false else buf = buf..glue end
            buf = buf..v
        end
    end
    return buf
end

function table.keys(t)
    local keys = { }
    for k,v in pairs(t) do
        table.insert(keys, 1, k)
    end
    return keys
end

loadfile('all.lua')()

print(reference.title)
print(string.rep("=", string.len(reference.title)))
print()

print("Table of contents")
print("-----------------")
for i,v in ipairs(reference.sections) do
    print (i..". "..v.title)
end
print()
print()

for num,section in ipairs(reference.sections) do
    local title = num..". "..section.title
    print(title)
    print(string.rep("-", string.len(title)))

    for i,topic in ipairs(section.topics) do
        local func = topic.func
        if type(topic.param) == 'table' then
            local tmp = { }
            for x,d in ipairs(topic.param) do
                table.insert(tmp, d.name)
            end
            func = func.."("..table.implode(tmp)..")"
        else
            func = func.."()"
        end
        print(func)
        if topic.desc ~= nil then
            print()
            print("\tDescription: "..topic.desc)
        end
        if topic.ret ~= nil then
            print()
            print("\tReturns: "..topic.ret)
        end
        if topic.mod ~= nil then
            print()
            print("\tEggdrop module: "..topic.mod)
        end
        print()
    end

end
