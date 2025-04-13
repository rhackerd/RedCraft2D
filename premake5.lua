workspace "redcraft2D"
    configurations { "Debug", "Release" }

    -- Custom build options
    newoption {
        trigger = "buildCore",
        description = "Build core module"
    }

    newoption {
        trigger = "buildServer",
        description = "Build server module"
    }

    filter "configurations:Debug"
        symbols "On"
        optimize "Off"
        buildoptions { "-g" }

    location "build"



project "app"
    kind "ConsoleApp"
    language "C++"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/%{cfg.buildcfg}"
    files { "src/app/**.h", "src/app/**.cpp" }
    links { "core", "raylib", "fmt"}
    includedirs { "src/core" , "json/single_include" }

    if _OPTIONS["buildCore"] then
        links { "core" }
    end
    if _OPTIONS["buildServer"] then
        links { "server" }
    end

project "core"
    kind "StaticLib"
    language "C++"
    files { "src/core/**.h", "src/core/**.cpp" }
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/%{cfg.buildcfg}"


    if _OPTIONS["buildCore"] then
        defines { "BUILD_CORE" }
    end