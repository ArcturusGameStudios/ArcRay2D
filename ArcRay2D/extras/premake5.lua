
baseName = path.getbasename(os.getcwd());

project (baseName)
    kind "StaticLib"
    location "../_build"
    targetdir "../_bin/%{cfg.buildcfg}"

    includedirs { "./" }
    includedirs { "./include" }
	includedirs { "../raylib-master/src"}
	
	vpaths 
	{
		["Header Files"] = { "cameras/rlFPCamera/*.h"},
		["Source Files"] = {"cameras/rlFPCamera/*.cpp"},
		["Header Files"] = { "cameras/rlTPCamera/*.h"},
		["Source Files"] = {"cameras/rlTPCamera/*.cpp"},
	}
	files {"cameras/rlFPCamera/*.cpp","cameras/rlFPCamera/*.h"}
	files {"cameras/rlTPCamera/*.cpp","cameras/rlTPCamera/*.h"}
	
	include_raylib()