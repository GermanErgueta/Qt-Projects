# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\UpdateLTspiceCL_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\UpdateLTspiceCL_autogen.dir\\ParseCache.txt"
  "UpdateLTspiceCL_autogen"
  )
endif()
