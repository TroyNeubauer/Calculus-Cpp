
project "Calculus-Cpp"
	kind "StaticLib"

	files
	{
		"src/**.c",
		"src/**.cpp",
	}

	excludes
	{
		"src/Samples/**",
		"src/Compiler/**",
		"src/Lemon/**",
	}

	includedirs
	{
		"include",
	}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

