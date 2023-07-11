
baseName = path.getbasename(os.getcwd());

project (baseName)
    kind "ConsoleApp"
    location "../_build"
    targetdir "../_bin/%{cfg.buildcfg}"

    filter "action:vs*"
        debugdir "$(SolutionDir)"
		
	filter {"action:vs*", "configurations:Release"}
		kind "WindowedApp"
		entrypoint "mainCRTStartup"
		
    filter{}

    vpaths 
    {
        ["Header Files/*"] = { "src/**.h", "src/**.hpp", "**.h", "**.hpp"},
        ["Source Files/*"] = {"src/**.c", "src/**.cpp","**.c", "**.cpp"},
		["Include Files/*"] = { "include/**.h", "include/**.hpp", "include/**.cpp", "include/**.c"}
    }
    files {"**.c", "**.cpp", "**.h", "**.hpp", "**.txt"}
  
    includedirs { "./" }
    includedirs { "src" }
    includedirs { "include" }

	pchheader "arcpch.h"
	pchsource "arcpch.cpp"
    
    link_raylib()
	link_to("extras")
	link_to("steam_api64")
	link_to("box2D")
	link_to("cereal")
	links {"steam_api64.lib"}
	
	-- To link to a lib use link_to("LIB_FOLDER_NAME")
	
	defines
	{
		"RAYGUI_IMPLEMENTATION"
	}