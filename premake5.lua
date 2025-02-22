workspace "redcraft2D"
    configurations { "Debug", "Release" }


local buildCore = _ACTION == "buildCore"
local buildServer = _ACTION == "buildServer"


project "app"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    files { "src/app/**.h", "src/app/**.cpp" }
    links { "core", "server", "raylib", "fmt", "enet", "boost_system", "pthread" }
    includedirs { "src/core" }

    filter { "buildCore", "buildServer" }
        links { "core", "server" }


project "core"
    kind "StaticLib"
    language "C++"
    files { "src/core/**.h", "src/core/**.cpp"}
    filter "buildCore"
        flags { "NoPCH" }


project "server"
    kind "StaticLib"
    language "C++"
    files { "src/server/**.h", "src/server/**.cpp" }
    filter "buildServer"
        flags { "NoPCH" }