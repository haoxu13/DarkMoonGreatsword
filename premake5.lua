include "Dependencies.lua"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "DarkMoonGreatsword"
  language "C++"
  cppdialect "C++17"
  architecture "x86"
  buildoptions { "/Zi"}

  targetdir("%{wks.location}/Bin/" .. outputdir .. "/%{prj.name}")
  objdir("%{wks.location}/Bin-int/" .. outputdir .. "/%{prj.name}")

  configurations {'Debug', 'Release'}

  flags
  {
    "MultiProcessorCompile"
  }

  filter {"configurations:Debug"}
    kind "ConsoleApp"
    defines {"DEBUG"}
    symbols "On"
  filter {"configurations:Release"}
    kind "ConsoleApp"
    defines {"NDEBUG"}
    optimize "On"


include("ThirdParty")
include("DarkMoonGreatsword")