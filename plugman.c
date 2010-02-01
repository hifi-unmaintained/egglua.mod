/* Lua plugin manager in a C string for inclusion */
static char lua_plugman[] = "" \
"local function copy_table(orig) " \
"    local new = {} " \
"" \
"    for k,v in pairs(orig) do " \
"        new[k] = v " \
"    end " \
"" \
"    return new " \
"end " \
"" \
"local function pm_plugin_call(plugin, func, ...) " \
"        if type(plugin.env[func]) ~= 'function' then " \
"                return " \
"        end " \
"" \
"        success, err = pcall(plugin.env[func], ...) " \
"        if not success then" \
"                putlog(\"egglua: failed to call '\"..func..\"' in '\"..plugin.file..\"': \"..err) " \
"                if not plugin.unloading then " \
"                        pm_unload(plugin.file) " \
"                end " \
"" \
"                return false " \
"        end " \
"" \
"        return err " \
"end " \
"" \
"local globals = {} " \
"local plugins = {} " \
"" \
"function pm_init() " \
"        globals = copy_table(_G) " \
"        globals.pm_init = nil " \
"        globals.pm_shutdown = nil " \
"        globals.pm_load = nil " \
"        globals.pm_unload = nil " \
"        globals.pm_reload = nil " \
"        globals.pm_call = nil " \
"end " \
"" \
"function pm_shutdown() " \
"        for i,plugin in pairs(plugins) do " \
"                pm_unload(plugin.file) " \
"        end " \
"end " \
"" \
"function pm_load(file) " \
"        local success, err, chunk " \
"" \
"        local plugin = {} " \
"        plugin.file = file " \
"" \
"        chunk, err = loadfile(plugin.file) " \
"        if chunk == nil then " \
"                putlog(\"egglua: \"..tostring(err)) " \
"                return false " \
"        end " \
"" \
"        plugin.env = copy_table(globals) " \
"        setfenv(chunk, plugin.env) " \
"        success, err = pcall(chunk) " \
"" \
"        if not success then " \
"                putlog(\"egglua: \"..tostring(err)) " \
"                return false " \
"        end " \
"" \
"        putlog(\"egglua: loaded plugin \"..plugin.file) " \
"        pm_plugin_call(plugin, 'onload') " \
"" \
"        table.insert(plugins, plugin) " \
"        return true " \
"end " \
"" \
"function pm_unload(file) " \
"        for i,plugin in pairs(plugins) do " \
"                if plugin.file == file then " \
"                        plugin.unloading = true " \
"                        pm_plugin_call(plugin, 'onunload') " \
"                        plugins[i] = nil " \
"                        putlog(\"egglua: unloaded plugin \"..plugin.file) " \
"                        return true " \
"                end " \
"        end " \
"" \
"        return false " \
"end " \
"" \
"function pm_reload(file) " \
"        pm_unload(file) " \
"        pm_load(file) " \
"end " \
"" \
"function pm_call(func, ...) " \
"        local def = false " \
"        for i,plugin in pairs(plugins) do " \
"                local ret = pm_plugin_call(plugin, func, ...) " \
"                if ret ~= def then " \
"                        return ret " \
"                end " \
"        end " \
"" \
"        return def " \
"end " \
;
