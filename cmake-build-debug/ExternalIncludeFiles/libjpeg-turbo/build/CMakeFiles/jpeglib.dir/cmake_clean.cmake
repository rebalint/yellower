file(REMOVE_RECURSE
  "libjpeglib.a"
  "libjpeglib.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/jpeglib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
