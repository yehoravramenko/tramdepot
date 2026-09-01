project "Alloy"
    --location "../../build/Alloy"
    kind "SharedLib"
    language "C++"
    cppdialect "C++26"
    staticruntime "off"

    targetdir ("%{wks.location}/build/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    objdir ("%{wks.location}/build/obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

    files
    {
       "**.h",
       "**.hpp",
       "**.cpp",
       "alloy.lua"
    }

    includedirs
    {
        "."
    }

    filter "system:windows"
        systemversion "latest"
        defines 
        { 
            "ALLOY_API=__declspec(dllexport)" 
        }

    filter "configurations:Debug"
        defines "ALLOY_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "ALLOY_NDEBUG"
        runtime "Release"
        optimize "on"