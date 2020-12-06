# parse the git tag version in store in the *_VAR variables in the parent scope
# supported git tag versions are in the format %d.%d.%d[-%s]
function (parse_git_tag_version MAJOR_VAR MINOR_VAR PATCH_VAR META_VAR)
    # read tag from git
    execute_process(
        COMMAND
            git describe --tag
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE
            VERSION
        ERROR_QUIET
    )

    if (DEFINED VERSION)
        message("PARSING ")
        string(STRIP ${VERSION} VERSION)
        if(VERSION MATCHES "^[0-9]+.[0-9]+.[0-9]+")
            string(REGEX REPLACE "([0-9]+).([0-9]+).([0-9]+)" "\\1;\\2;\\3" VERSION ${VERSION})
        else()
            message(DEBUG "the current git tag version is not supported")
            return()
        endif()

        if (VERSION MATCHES "^[^-]+-.*")
            string(REGEX REPLACE "([^-])-(.*)" "\\1;\\2" VERSION "${VERSION}")
        else()
            list(
                APPEND
                VERSION
                "" # add empty meta section to the parsed version
            )
        endif()

        list(GET VERSION 0 PARSED_MAJOR)
        list(GET VERSION 1 PARSED_MINOR)
        list(GET VERSION 2 PARSED_PATCH)
        list(GET VERSION 3 PARSED_META)

        set(${MAJOR_VAR} ${PARSED_MAJOR} PARENT_SCOPE)
        set(${MINOR_VAR} ${PARSED_MINOR} PARENT_SCOPE)
        set(${PATCH_VAR} ${PARSED_PATCH} PARENT_SCOPE)
        set(${META_VAR}  ${PARSED_META}  PARENT_SCOPE)
    else()
        message(DEBUG "\"git desribe --tags\" didn't return a tag version")
    endif()


endfunction()
