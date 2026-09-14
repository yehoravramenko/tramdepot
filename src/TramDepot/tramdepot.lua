project "TramDepot"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++26"
    staticruntime "off"

    dependson "Alloy"

    targetdir ("%{wks.location}/build/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    objdir ("%{wks.location}/build/obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

    files
    {
       "**.h",
       "**.hpp",
       "**.cpp",
       "tramdepot.lua"
    }

    includedirs
    {
        "%{wks.location}/src/Alloy",
        "%{wks.location}/vendor/SDL3/include"
    }

    libdirs
    {
        "%{wks.location}/vendor/SDL3/lib/x64"
    }

    links
    {
        "Alloy",
        "SDL3"
    }

    filter "system:windows"
        systemversion "latest"
        defines 
        { 
            "ALLOY_API=__declspec(dllimport)" 
        }

	postbuildcommands
	{
    	   '{COPYFILEIFNEWER} "%{wks.location}/vendor/SDL3/lib/x64/SDL3.dll" "%{cfg.targetdir}/"'
	}

    filter "configurations:Debug"
        defines "ALLOY_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "ALLOY_NDEBUG"
        runtime "Release"
        optimize "on"