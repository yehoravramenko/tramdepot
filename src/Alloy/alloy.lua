project "Alloy"
   characterset "Unicode"
   kind "SharedLib"
   language "C++"
   cppdialect "C++23"
   buildstlmodules "On"

   targetdir (_MAIN_SCRIPT_DIR.."/build/%{cfg.buildcfg}/bin/")
   objdir (_MAIN_SCRIPT_DIR.."/build/obj/Alloy/%{cfg.buildcfg}/")

   warnings "Extra"

   files { "**.hpp", "**.cppm", "**.cpp",
      "thirdparty/gl3w/src/gl3w.c"}

   includedirs {".", "thirdparty/gl3w/include", "thirdparty/RGFW/include"}
   publicmoduledirectories {"%{prj.location}/"}

   links {}

   buildoptions {"/utf-8"}

   defines {"ALLOY_EXPORT=__declspec(dllexport)"}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
