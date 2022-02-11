include "./premake/premake_customization/solution_items.lua"

workspace "Hazel"
	architecture "x64"

    startproject "Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}	
	    
	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
liboutputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/lib/"
hzvendordir = "project/Hazel/vendor/"

IncludeDir = {}
IncludeDir["glm"] =				("%{wks.location}/" .. hzvendordir .. "glm")
IncludeDir["stb"] =				("%{wks.location}/" .. hzvendordir .. "stb/include")
IncludeDir["spdlog"] =			("%{wks.location}/" .. hzvendordir .. "spdlog/include")
IncludeDir["GLFW"] =			("%{wks.location}/" .. hzvendordir .. "GLFW/include")
IncludeDir["Glad"] =			("%{wks.location}/" .. hzvendordir .. "glad/include")
IncludeDir["yaml_cpp"] =		("%{wks.location}/" .. hzvendordir .. "yaml-cpp/include")
IncludeDir["entt"] =			("%{wks.location}/" .. hzvendordir .. "entt/include")
IncludeDir["msdf_atlas_gen"] =	("%{wks.location}/" .. hzvendordir .. "msdf-atlas-gen/msdf-atlas-gen")
IncludeDir["msdfgen"] =			("%{wks.location}/" .. hzvendordir .. "msdf-atlas-gen/msdfgen")

group "_Dependencies"
    include "premake"
    include (hzvendordir .. "glad")
    include (hzvendordir .. "GLFW")
group "_Dependencies/msdf"
	include (hzvendordir .. "msdf-atlas-gen")
	
group "Applications"
	include "project/Editor"
	include "project/Client"
	
group "API"
	include "project/Hazel"

group ""
        
