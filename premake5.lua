workspace "TicTacToeCustomSize"
	architecture "x64"
	startproject "TicTacToeMinMax"
	configurations { "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "TicTacToeMinMax"
	location "MathLib"
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
	location "MathLibTest"
	kind "ConsoleApp"
	language "C++"
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")

	includedirs {"TicTacToeMinMax"}
	nuget{"Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn:1.8.1"}
	
	files{"%{prj.name}/**.h", "%{prj.name}/**.cpp"}
	
	cppdialect "C++17"
	systemversion "latest"
	
	
	filter "configurations:Release"
		defines {"TTT_RELEASE"}
		optimize "On"
		