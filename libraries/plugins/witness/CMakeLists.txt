file(GLOB HEADERS "include/scorum/witness/*.hpp")

add_library( scorum_witness
             witness_plugin.cpp
             witness_evaluators.cpp
             witness_operations.cpp
           )

target_link_libraries( scorum_witness scorum_chain scorum_protocol scorum_app )
target_include_directories( scorum_witness
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   scorum_witness

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
