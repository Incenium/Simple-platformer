-- A solution contains projects, and defines the available configurations
solution "sdl tuts"
	configurations { "Debug", "Release" }
 
   -- A project defines one build target
	project "tutorial"
		location "build"
		kind "ConsoleApp"
		language "C++"
		files { "src/**.cpp" }
		buildoptions {"-std=c++11"}
		includedirs{"include/"}
		--for libjson and other small static libraries
		libdirs {"libs/"}
		links {"SDL2", "SDL2_image", "SDL2_ttf", "SDL2_mixer", "png", "asound", "pulse", "jsoncpp"}
 
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
