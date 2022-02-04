project "Client"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.cpp",
		"src/**.h",
	}

	includedirs
	{
		"src",
		"%{wks.location}/project/Hazel/src",
		"%{wks.location}/project/Hazel/src/Hazel",

		"%{IncludeDir.glm}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.spdlog}",
	}

	links
	{
		"Hazel",
	}

	filter { "configurations:Release", "system:windows" }
		postbuildcommands {
			"xcopy /y /i $(TargetDir)$(TargetFileName) $(SolutionDir)exe\\"
		}

	filter "system:windows"
		systemversion "latest"
		defines "HZ_PLATFORM_WINDOWS"

	filter "configurations:Debug"
		kind "ConsoleApp"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		kind "ConsoleApp"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		kind "WindowedApp"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"
