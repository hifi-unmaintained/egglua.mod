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

local htmlescape = function(s)
    -- keep this the first!
    s = string.gsub(s, '&', '&amp;')

    s = string.gsub(s, '<', '&lt;')
    s = string.gsub(s, '>', '&gt;')
    return s
end

loadfile('all.lua')()

print("<h2>"..reference.title.."</h2>")

print("<h3>Table of contents</h3>")
print("<ol>");
for i,v in ipairs(reference.sections) do
    print ('<li><a href="#sect'..i..'">'..v.title..'</a></li>')
end
print("</ol>");

for num,section in ipairs(reference.sections) do
    local title = num..". "..section.title
    print('<h3 id="sect'..num..'">'..title.."</h3>")

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
        print('<dl>')
        print('<dt>'..htmlescape(func).."</dt>")
        if topic.desc ~= nil then
            print("<dd><strong>Description:</strong> "..htmlescape(topic.desc).."</dd>")
        end
        if topic.ret ~= nil then
            print("<dd><strong>Returns:</strong> "..htmlescape(topic.ret).."</dd>")
        end
        if topic.mod ~= nil then
            print("<dd><strong>Eggdrop module:</strong> "..topic.mod.."</dd>")
        end
        print('</dl>')
    end

end
