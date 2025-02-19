workspace "redcraft2D"
    configurations { "Debug", "Release" }

project "app"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    files { "src/app/**.h", "src/app/**.cpp" }
    links { "core", "server", "raylib", "fmt", "enet", "boost" }
    includedirs { "src/core" }


project "core"
    kind "StaticLib"
    language "C++"
    files { "src/core/**.h", "src/core/**.cpp"}


project "server"
    kind "StaticLib"
    language "C++"
    files { "src/server/**.h", "src/server/**.cpp" }
