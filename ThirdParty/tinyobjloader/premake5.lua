group "ThirdParty"

project "TinyObjLoader"
  kind "StaticLib"
  language "C++"

  targetdir("Bin/" .. outputdir .. "/%{prj.name}")
  objdir("Bin-int/" .. outputdir .. "/%{prj.name}")

  files 
  {
    "tiny_obj_loader.cc",
    "tiny_obj_loader.h"
  }