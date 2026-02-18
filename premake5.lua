local td = "tramdepot"
local clDir = td.."/client/"

if _ACTION == "clean" then
   os.rmdir("build")
   os.rmdir(".vs")
   os.remove(os.matchfiles("**.sln*"))
   os.remove(os.matchfiles("**.vcxproj*"))
end

workspace "TramDepot"
   characterset "Unicode"
   architecture "x86_64"
   configurations { "Debug", "Release" }
   --location "projects"
   startproject "TramDepot"

group "Client"
    include "tramdepot/client/tramdepot.lua"
        