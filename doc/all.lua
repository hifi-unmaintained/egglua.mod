--
-- Complete egglua function and hook reference
--

reference =
{
    title = "egglua command reference",
    sections =
    {
        {
            title = "Output commands",
            topics = {
                {
                    func = "putserv",
                    param = {
                        {
                            name = "<text>",
                        },
                        {
                            name = "[next]",
                            type = "boolean",
                            desc = "flag if the message should be put in front of the queue"
                        }
                    },
                    ret = "nil",
                    desc = "sends text to the server, like '.dump' (intended for direct server commands); output is queued so that the bot won't flood itself off the server.",
                    mod = "server"
                },
                {
                    func = "puthelp",
                    param = {
                        {
                            name = "<text>",
                        },
                        {
                            name = "[next]",
                            type = "boolean",
                            desc = "flag if the message should be put in front of the queue"
                        }
                    },
                    ret = "nil",
                    desc = "sends text to the server, like 'putserv', but it uses a different queue intended for sending messages to channels or people.",
                    mod = "server"
                },
                {
                    func = "putquick",
                    param = {
                        {
                            name = "<text>",
                        },
                        {
                            name = "[next]",
                            type = "boolean",
                            desc = "flag if the message should be put in front of the queue"
                        }
                    },
                    ret = "nil",
                    desc = "sends text to the server, like 'putserv', but it uses a different (and faster) queue.",
                    mod = "server"
                },
                {
                    func = "putlog",
                    param = {
                        {
                            name = "<text>",
                        }
                    },
                    ret = "nil",
                    desc = "sends text to the bot's logfile, marked as 'misc' (o)",
                    mod = "core"
                },
                {
                    func = "putcmdlog",
                    param = {
                        {
                            name = "<text>",
                        }
                    },
                    ret = "nil",
                    desc = "sends text to the bot's logfile, marked as 'command' (c)",
                    mod = "core"
                },
                {
                    func = "putxferlog",
                    param = {
                        {
                            name = "<text>",
                        }
                    },
                    ret = "nil",
                    desc = "sends text to the bot's logfile, marked as 'file-area' (x)",
                    mod = "core"
                },
            } -- topics
        }, -- section
        {
            title = "User record manipulation commands",
            topics = {
                {
                    func = "chattr",
                    param = {
                        {
                            name = "<handle>",
                        },
                        {
                            name = "[changes]",
                        },
                        {
                            name = "[channel]",
                        }
                    },
                    ret = "new flags for the user (if you made no changes, the current flags are returned). If a channel was specified, the global AND the channel-specific flags for that channel are returned in the format of globalflags|channelflags. '*' is returned if the specified user does not exist.",
                    desc = "changes the attributes for a user record, if you include any. Changes are of the form '+f', '-o', '+dk', '-o+d', etc. If changes are specified in the format of <changes> <channel<, the channel-specific flags for that channel are altered. You can now use the +o|-o #channel format here too.",
                    mod = "core"
                },
                {
                    func = "matchattr",
                    param = {
                        {
                            name = "<handle>",
                        },
                        {
                            name = "<flags>",
                        },
                        {
                            name = "[channel]",
                        }
                    },
                    ret = "true if the specified user has the specified flags; false otherwise",
                    mod = "core"
                },
            }
        },
        {
            title = "Channel commands",
            topics = {
                {
                    func = "isop",
                    param = {
                        {
                            name = "<nickname>",
                        },
                        {
                            name = "[channel]",
                        }
                    },
                    ret = "true if someone by the specified nickname is on the channel (or any channel if no channel name is specified) and has ops; false otherwise",
                    mod = "irc"
                },
                {
                    func = "ishalfop",
                    param = {
                        {
                            name = "<nickname>",
                        },
                        {
                            name = "[channel]",
                        }
                    },
                    ret = "true if someone by the specified nickname is on the channel (or any channel if no channel name is specified) and has halfops; false otherwise",
                    mod = "irc"
                },
                {
                    func = "isvoice",
                    param = {
                        {
                            name = "<nickname>",
                        },
                        {
                            name = "[channel]",
                        }
                    },
                    ret = "true if someone by the specified nickname is on the channel (or any channel if no channel name is specified) and has voice (+v); false otherwise",
                    mod = "irc"
                },
                {
                    func = "onchan",
                    param = {
                        {
                            name = "<nickname>",
                        },
                        {
                            name = "[channel]",
                        }
                    },
                    ret = "true if someone by that nickname is on the specified channel (or any channel if none is specified); false otherwise",
                    mod = "irc"
                },
            }
        },
        {
            title = "Callbacks (hooks)",
            topics = {
                {
                    func = "onload",
                    desc = "called when the script is first loaded"
                },
                {
                    func = "onunload",
                    desc = "called when the script is unloaded, expect it to be the last call"
                },
                {
                    func = "hook_secondly",
                    desc = "called every second"
                },
                {
                    func = "hook_minutely",
                    desc = "called every minute"
                },
                {
                    func = "hook_5minutely",
                    desc = "called every five minutes"
                },
                {
                    func = "hook_hourly",
                    desc = "called every hour"
                },
                {
                    func = "hook_daily",
                    desc = "called every day"
                },
                {
                    func = "hook_kick",
                    param = {
                        {
                            name = "nick",
                            desc = "nickname of the kicker"
                        },
                        {
                            name = "uhost",
                            desc = "hostname of the kicker"
                        },
                        {
                            name = "handle",
                            desc = "handle of the kicker"
                        },
                        {
                            name = "channel",
                        },
                        {
                            name = "victim",
                            desc = "nickname of the victim"
                        },
                        {
                            name = "reason",
                        },
                    },
                    desc = "called when someone is kicked from a channel"
                },
                {
                    func = "hook_nick",
                    param = {
                        {
                            name = "nick",
                        },
                        {
                            name = "uhost",
                        },
                        {
                            name = "handle",
                        },
                        {
                            name = "channel",
                        },
                        {
                            name = "newnick",
                        },
                    },
                    desc = "called when someone changes his nick"
                },
                {
                    func = "hook_join",
                    param = {
                        {
                            name = "nick",
                        },
                        {
                            name = "uhost",
                        },
                        {
                            name = "handle",
                        },
                        {
                            name = "channel",
                        },
                    },
                    desc = "called when someone joins a channel"
                },
                {
                    func = "hook_part",
                    param = {
                        {
                            name = "nick",
                        },
                        {
                            name = "uhost",
                        },
                        {
                            name = "handle",
                        },
                        {
                            name = "channel",
                        },
                    },
                    desc = "called when someone leaves a channel"
                },
                {
                    func = "hook_sign",
                    param = {
                        {
                            name = "nick",
                        },
                        {
                            name = "uhost",
                        },
                        {
                            name = "handle",
                        },
                        {
                            name = "channel",
                        },
                        {
                            name = "reason",
                        },
                    },
                    desc = "called when someone signs out (quits)"
                },
                {
                    func = "msg_pub",
                    param = {
                        {
                            name = "nick",
                        },
                        {
                            name = "uhost",
                        },
                        {
                            name = "handle",
                        },
                        {
                            name = "channel",
                        },
                        {
                            name = "message",
                        },
                    },
                    desc = "called when someone says something in a channel"
                },
                {
                    func = "msg_priv",
                    param = {
                        {
                            name = "nick",
                        },
                        {
                            name = "uhost",
                        },
                        {
                            name = "message",
                        },
                    },
                    desc = "called when someone says something privately"
                },
            } -- topics
        } -- section
    } -- sections
} -- reference
