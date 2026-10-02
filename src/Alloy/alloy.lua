project "Alloy"
    kind "SharedLib"
    language "C++"
    cppdialect "C++26"
    staticruntime "off"

    targetdir ("%{wks.location}/build/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
    objdir ("%{wks.location}/build/obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

    files
    {
       "**.h",
       "**.hpp",
       "**.cpp",
       "**.hlsl",
       "alloy.lua"
    }

    includedirs
    {
        ".",
        "%{wks.location}/vendor/SDL3/include"
    }

    libdirs
    {
        "%{wks.location}/vendor/SDL3/lib/x64"
    }

    links
    {
        "SDL3",
        "d3d11",
        "dxgi"
    }

    filter "system:windows"
        systemversion "latest"
        defines 
        { 
            "ALLOY_API=__declspec(dllexport)" 
        }
    
    -- Shaders pre-compilation
    filter "files:**.hlsl"
        buildmessage "Compiling shaders: %{file.name}"
        buildcommands {
            -- Vertex Shader stage
            'fxc.exe /nologo /E "VSMain" /T vs_5_0 /Zi /Fo "%{cfg.targetdir}/%{file.basename}_VS.cso" "%{file.relpath}" ',

            -- Pixel Shader stage
            'fxc.exe /nologo /E "PSMain" /T ps_5_0 /Zi /Fo "%{cfg.targetdir}/%{file.basename}_PS.cso" "%{file.relpath}" '
        }
        buildoutputs {
            "%{cfg.targetdir}/%{file.basename}_VS.cso",
            "%{cfg.targetdir}/%{file.basename}_PS.cso"
        }

    filter "system:windows"

    filter "configurations:Debug"
        defines "ALLOY_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "ALLOY_NDEBUG"
        runtime "Release"
        optimize "on"