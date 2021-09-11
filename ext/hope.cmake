# Download hope
ExternalProject_Add(
    hope
    PREFIX "ext"
    GIT_REPOSITORY "https://github.com/glensand/hope"
    GIT_TAG 0.0.1
    TIMEOUT 10
    CMAKE_ARGS
        -DHOPE_BUILD_TESTS=OFF
        -DHOPE_BUILD_EXAMPLES=OFF
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
)

ExternalProject_Get_Property(hope source_dir)
set(HOPE_INCLUDE_DIR ${source_dir}/lib)