 solution("UselessScript")
	language "C++"
	debugdir "$(OutDir)"
	objdir "build/"
	targetdir "$(SolutionDir)../app/"
	targetname "$(ProjectName)_$(Configuration)_$(Platform)"
	
	configurations{
		"Debug",
		"Release",
	}
	
	platforms{
		"Win32",
		"x64",
	}
	
	configuration "Debug"
		symbols "On"
		defines{
			"DEBUG"
		}
		
	configuration "Release"
		optimize "On"
		defines{
			"RELEASE",
			"NDEBUG"
		}
		
	configuration{}
	
project("UselessScript")
	kind "ConsoleApp"
	includedirs{
		"code/",
		"code/",
	}
	files{
		"code/**.h",
		"code/**.cpp",
	}