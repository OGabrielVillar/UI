project "UI"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. liboutputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. liboutputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/core.cpp"

	files
	{
		"src/**.cpp",
		"src/**.h",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/entt/include/entt/entt.hpp",
	}
	
	removefiles {
	}
	

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
	}

	includedirs
	{
		"src",
		"src/Hazel",
		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.spdlog}",
	}

	links
	{
		"Glad",
		"GLFW",
	}

	filter "files:vendor/**"
	flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"
		defines "_WINDOWS"

	filter "configurations:Debug"
		kind "ConsoleApp"
		defines "_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		kind "ConsoleApp"
		defines "_RELEASE"
		runtime "Release"
		optimize "on"

	filter { "configurations:Release", "system:windows" }
		postbuildcommands {
			"xcopy /y /i $(TargetDir)$(TargetFileName) $(SolutionDir)exe\\"
		}

	filter "configurations:Dist"
		kind "WindowedApp"
		defines "_DIST"
		runtime "Release"
		optimize "on"
