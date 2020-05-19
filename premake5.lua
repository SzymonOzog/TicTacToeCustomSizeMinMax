workspace "TicTacToeCustomSize"
	architecture "x64"
	startproject "TicTacToeMinMax"
	configurations { "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "TicTacToeMinMax"
	location "TicTacToeMinMax"
	kind "ConsoleApp"
	language "C++"
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")
	
	files{"%{prj.name}/**.h", "%{prj.name}/**.cpp"}
	
	cppdialect "C++17"
	systemversion "latest"
	
	filter "configurations:Release"
		defines {"TTT_RELEASE"}
		optimize "On"
		
project "TicTacToeTest"
	location "TicTacToeTest"
	kind "ConsoleApp"
	language "C++"
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")

	includedirs {"TicTacToeMinMax"}
	nuget{"Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn:1.8.1.3"}
	
	files{"%{prj.name}/**.h", "%{prj.name}/**.cpp", "TicTacToeMinMax/TicTacToe.h", "TicTacToeMinMax/TicTacToe.cpp"}
	
	cppdialect "C++17"
	systemversion "latest"
	
	
	filter "configurations:Release"
		defines {"TTT_RELEASE"}
		optimize "On"
		