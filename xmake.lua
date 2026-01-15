add_rules("mode.debug", "mode.release", "plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

target("tramdepot")
    set_kind("binary")
    add_files("tramdepot/**.cpp")
    add_includedirs("$(scriptdir)/tramdepot/client")
    add_links("glfw")