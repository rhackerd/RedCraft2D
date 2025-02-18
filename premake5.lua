workspace "redcraft2D"
    configurations { "Debug", "Release" }

project "app"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    files { "src/app/**.h", "src/app/**.cpp" }
    links { "core", "raylib", "fmt" }
    includedirs { "src/core", "raygui/src" }


project "core"
    kind "StaticLib"
    language "C++"
    files { "src/core/**.h", "src/core/**.cpp"}
    includedirs { "raygui/src" }