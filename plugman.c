/* Lua plugin manager in a C string for inclusion */
static char lua_plugman[] = "" \
/* -- for debugging */
"if dprintf == nil then " \
"    dprintf = function(...) " \
"        print(...) " \
"    end " \
"end " \
"" \
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
"                dprintf(DP_LOG, \"PlugMan: failed to call '\"..func..\"' in '\"..plugin.file..\"': \"..err) " \
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
"        dprintf(DP_LOG, \"Lua PlugMan Loaded\") " \
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
"        dprintf(DP_LOG, \"PlugMan: shutdown in progress...\") " \
"        for i,plugin in pairs(plugins) do " \
"                pm_unload(plugin.file) " \
"        end " \
"        dprintf(DP_LOG, \"PlugMan: all plugins unloaded!\") " \
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
"                dprintf(DP_LOG, \"PlugMan: failed to load file \"..plugin.file..\": \"..tostring(err)) " \
"                return false " \
"        end " \
"" \
"        plugin.env = copy_table(globals) " \
"        setfenv(chunk, plugin.env) " \
"        success, err = pcall(chunk) " \
"" \
"        if not success then " \
"                dprintf(DP_LOG, \"PlugMan: failed to compile file \"..plugin.file..\": \"..tostring(err)) " \
"                return false " \
"        end " \
"" \
"        dprintf(DP_LOG, \"PlugMan: loaded plugin \"..plugin.file) " \
"        pm_plugin_call(plugin, 'plug_load') " \
"" \
"        table.insert(plugins, plugin) " \
"        return true " \
"end " \
"" \
"function pm_unload(file) " \
"        for i,plugin in pairs(plugins) do " \
"                if plugin.file == file then " \
"                        pm_plugin_call(plugin, 'plug_unload') " \
"                        plugins[i] = nil " \
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
"function pm_call(func, def, ...) " \
"        for i,plugin in pairs(plugins) do " \
"                local ret = pm_plugin_call(plugin, func, ...) " \
"                if ret ~= def then " \
"                        return ret " \
"                end " \
"        end " \
"" \
"        return def " \
"end " \
"" \
/* -- functions called from eggdrop" */
"function irc_mpub() " \
"    return pm_call(\"irc_mpub\", false) " \
"end " \
"" \
"function irc_msg() " \
"    return pm_call(\"irc_msg\", false) " \
"end " \
;
