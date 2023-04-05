workspace "gola"
    configurations { "Debug", "Release" }

project "gola"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    files { "**.h", "**.cpp" }
    targetdir "bin/%{cfg.buildcfg}"

    includedirs {
        "C:/SDL2/include",
    }

    filter "system:windows"
        libdirs { "C:/SDL2/lib/x86", "C:/SDL2/lib/x64" }
        links { "SDL2", "SDL2main" }

    filter "system:macosx"
        libdirs { "/usr/local/lib" }
        links { "SDL2" }

    filter "system:linux"
        libdirs { "/usr/lib/x86_64-linux-gnu", "/usr/lib/i386-linux-gnu" }
        links { "SDL2", "SDL2main" }

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"

