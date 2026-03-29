--local td = "tramdepot"
--local clDir = td.."/client/"

if _ACTION == "clean" then
   os.rmdir("build")
   os.rmdir("ItsTrain/.vs")
   os.remove(os.matchfiles("**.sln*"))
   os.remove(os.matchfiles("**.vcxproj*"))
end

workspace "TramDepot"
   characterset "Unicode"
   architecture "x86_64"
   configurations { "Debug", "Release" }
   startproject "TramDepot"

   DIST = "${wks.location}/dist/TramDepot/"

   include "src/TramDepot/tramdepot.lua"
   include "src/Alloy/alloy.lua"