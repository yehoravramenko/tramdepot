project "TramDepot"
   characterset "Unicode"
   kind "WindowedApp"
   language "C++"
   cppdialect "C++23"
   buildstlmodules "On"

   targetdir (_MAIN_SCRIPT_DIR.."/build/%{cfg.buildcfg}/bin/")
   objdir (_MAIN_SCRIPT_DIR.."/build/obj/ItsTrain/%{cfg.buildcfg}/")

   warnings "Extra"

   files { "**.hpp", "**.cppm", "**.cpp"}

   includedirs {".", "%{prj.location}/../Alloy"}

   links {"Alloy"}

   buildoptions {"/utf-8"}

   defines {"ALLOY_EXPORT=__declspec(dllimport)"}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
