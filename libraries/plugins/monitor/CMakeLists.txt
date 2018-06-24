file(GLOB HEADERS "include/graphene/monitor/*.hpp")

add_library( graphene_monitor
             monitor.cpp
           )

target_link_libraries( graphene_monitor graphene_chain graphene_app )
target_include_directories( graphene_monitor
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   graphene_monitor

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
