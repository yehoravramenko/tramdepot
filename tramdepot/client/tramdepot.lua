project "TramDepot"
   kind "WindowedApp"
   language "C++"
   cppdialect "C++23"
   buildstlmodules "On"

   targetdir (_MAIN_SCRIPT_DIR.."/build/%{cfg.buildcfg}/bin/")
   objdir (_MAIN_SCRIPT_DIR.."/build/obj/%{cfg.buildcfg}/")

   warnings "Extra"

   files { "**.hpp", "**.cppm", "**.cpp",
            "tramdepot.lua",
            _MAIN_SCRIPT,
   }

--[[   vpaths {
      ["Headers/*"] = "**.hpp",
      ["Modules/*"] = "**.ixx",
      ["Sources/*"] = "**.cpp",
      --["Resources/*"] = "**.rc",
      ["*"] = {"tramdepot.lua",_MAIN_SCRIPT},
   }]]

      -- Global includes
   includedirs {"."}

   links {"d3d11"}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"