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



project "app"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    files { "src/app/**.h", "src/app/**.cpp" }
    links { "core", "server", "raylib", "fmt", "enet", "boost_system", "pthread"}
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


    if _OPTIONS["buildCore"] then
        defines { "BUILD_CORE" }
    end

project "server"
    kind "StaticLib"
    language "C++"
    files { "src/server/**.h", "src/server/**.cpp" }


    if _OPTIONS["buildServer"] then
        defines { "BUILD_SERVER" }
    end
