group "RayTracer"

local CurrentDir = path.getabsolute(".")
local AssetDir = path.join(CurrentDir , "Content")

project "DarkMoonGreatsword"
  openmp "On"

  files
  {
    "**.h", 
    "**.cpp",
  }

  defines 
  {
    "ASSET_DIR=" .. AssetDir
  }

  includedirs 
  {
    "Source",
    "%{IncludeDir.TinyObjLoader}",
  }

  links 
  {
    "TinyObjLoader",
  }