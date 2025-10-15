project "TramDepot"
   kind "WindowedApp"
   language "C++"
   cppdialect "C++23"
   targetdir (_MAIN_SCRIPT_DIR.."/build/%{cfg.buildcfg}/bin/")

   warnings "Extra"

   files { "**.hpp", "**.cppm", "**.cpp",
            "tramdepot.lua",
            _MAIN_SCRIPT,
   }

   vpaths {
      ["Headers/*"] = "**.hpp",
      ["Modules/*"] = "**.cppm",
      ["Sources/*"] = "**.cpp",
      ["Resources/*"] = "**/*.rc",
      ["*"] = {"tramdepot.lua",_MAIN_SCRIPT},
   }

      -- Global includes
   includedirs {"."}

   links {"d3d11"}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"