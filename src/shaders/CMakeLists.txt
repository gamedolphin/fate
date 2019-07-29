cmake_minimum_required(VERSION 3.10.2)

file(GLOB_RECURSE FRAGMENT_SHADERS
  "*.fshader"
  )
file(GLOB_RECURSE vertex_shaders
  "*.vshader"
  )

set(BGFX_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/../libs/bgfx/src)
set(SHADERC "${CMAKE_CURRENT_SOURCE_DIR}/../libs/bgfx/.build/linux64_gcc/bin/shadercRelease")

foreach(SHADER ${FRAGMENT_SHADERS})
  get_filename_component(FILE_NAME ${SHADER} NAME_WE)
  set(FRAG "${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}.bin")
  add_custom_command(
    OUTPUT ${FRAG}
    COMMAND ${SHADERC} -f ${SHADER} -o ${FRAG} --platform "linux" --type "fragment" --verbose -i ${BGFX_HEADER}
    DEPENDS ${SHADER}
    COMMENT ${SHADER})
  message(${BGFX_HEADER})
  list(APPEND SHADER_BINARY_FILES ${FRAG})
endforeach(SHADER)


add_custom_target(
    Shaders
    DEPENDS ${SHADER_BINARY_FILES}
    )
