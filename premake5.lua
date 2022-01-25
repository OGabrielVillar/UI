include "./premake/premake_customization/solution_items.lua"

workspace "UI"
	architecture "x64"

    startproject "UI"

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
liboutputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/libs/"

IncludeDir = {}
IncludeDir["glm"] = "%{wks.location}/UI/vendor/glm"
IncludeDir["stb"] = "%{wks.location}/UI/vendor/stb"

IncludeDir["spdlog"] = "%{wks.location}/UI/vendor/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/UI/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/UI/vendor/glad/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/UI/vendor/yaml-cpp/include"
IncludeDir["entt"] = "%{wks.location}/UI/vendor/entt/include"

group "_Dependencies"
    include "premake"
    include "UI/vendor/glad"
    include "UI/vendor/GLFW"
	
group "Applications"
	include "UI"

group ""
        
