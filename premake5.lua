workspace "MathLib"
	architecture "x64"
	startproject "MathLibTest"
	configurations {"Debug", "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "MathLib"
	location "MathLib"
	kind "StaticLib"
	language "C++"
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")
	
	files{"%{prj.name}/**.h", "%{prj.name}/**.cpp"}
	
	cppdialect "C++17"
	systemversion "latest"
	
	filter "configurations:Debug"
		defines {"ML_DEBUG"}
		symbols "On"
	
	filter "configurations:Release"
		defines {"ML_RELEASE"}
		optimize "On"
		
project "MathLibTest"
	location "MathLibTest"
	kind "ConsoleApp"
	language "C++"
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pch.h"
	pchsource "pch.cpp"
	
	includedirs {"MathLib"}
	nuget{"Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn:1.8.1"}
	
	files{"%{prj.name}/**.h", "%{prj.name}/**.cpp"}
	
	cppdialect "C++17"
	systemversion "latest"
	
	filter "configurations:Debug"
		defines {"ML_DEBUG"}
		symbols "On"
	
	filter "configurations:Release"
		defines {"ML_RELEASE"}
		optimize "On"
		
project "TestEngine"
	location "TestEngine"
	kind "ConsoleApp"
	language "C++"
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")
	
	includedirs {"MathLib", "%{prj.name}/dependencies/olcPixelGameEngine"}
	
	files{"%{prj.name}/**.h", "%{prj.name}/**.cpp"}
	
	cppdialect "C++17"
	systemversion "latest"
	defines{"OLC_PGE_APPLICATION"}
	filter "configurations:Debug"
		defines {"ML_DEBUG"}
		symbols "On"
	
	filter "configurations:Release"
		defines {"ML_RELEASE"}
		optimize "On"