
# add all .cpp files to project (stored in "raidmonitor_SRCS" variable")

# and finally an resource file
set(_SRCS
	libgensolver.cpp
	libnnet.cpp
	librand.cpp
	libnetsolver.cpp
	)


include_directories(
			../include
			${CMAKE_CURRENT_BINARY_DIR}

			${FLEXPARS_INCLUDE_DIR}
			)

ADD_LIBRARY( gensolver SHARED ${_SRCS} )
ADD_LIBRARY( gensolver-static STATIC ${_SRCS} )

#give the static version the same name as the shared one
set_target_properties(gensolver-static PROPERTIES OUTPUT_NAME gensolver)

target_link_libraries( gensolver
			${FLEXPARS_LIBRARY}			
			)
		#target_link_libraries( gensolver-static
		#	${FLEXPARS_LIBRARY}			
		#	)
# install(TARGETS gensolver DESTINATION lib${LIB_SUFFIX}/gensolver)
# install(TARGETS gensolver-static DESTINATION lib${LIB_SUFFIX}/gensolver)

install(TARGETS gensolver DESTINATION lib${LIB_SUFFIX})
install(TARGETS gensolver-static DESTINATION lib${LIB_SUFFIX})

INSTALL(DIRECTORY ../include/ DESTINATION include/gensolver)
