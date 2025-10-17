local td = "tramdepot" 
local clDir = td.."/client/"

workspace "TramDepot"
   characterset "Unicode"
   architecture "x86_64"
   configurations { "Debug", "Release" }
   --location "projects"
   startproject "TramDepot"

group "Client"
    include "tramdepot/client/tramdepot.lua"