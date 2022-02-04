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

IncludeDir = {}
IncludeDir["glm"] = "%{wks.location}/project/Hazel/vendor/glm"
IncludeDir["stb"] = "%{wks.location}/project/Hazel/vendor/stb"

IncludeDir["spdlog"] = "%{wks.location}/project/Hazel/vendor/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/project/Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/project/Hazel/vendor/glad/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/project/Hazel/vendor/yaml-cpp/include"
IncludeDir["entt"] = "%{wks.location}/project/Hazel/vendor/entt/include"

group "_Dependencies"
    include "premake"
    include "project/Hazel/vendor/glad"
    include "project/Hazel/vendor/GLFW"
	
group "Applications"
	include "project/Editor"
	include "project/Client"
	
group "API"
	include "project/Hazel"

group ""
        
