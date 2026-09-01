if _ACTION == "clean" then
    os.rmdir("build")
    os.rmdir(".vs")
    os.remove(os.matchfiles("**.sln*"))
    os.remove(os.matchfiles("**.vcxproj*"))
end

workspace "TramDepot"
    characterset "Unicode"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "TramDepot"

    DIST = "%{wks.location}/dist/TramDepot/"

include "src/Alloy/alloy.lua"
include "src/TramDepot/tramdepot.lua"