include_directories(
    "${PROJECT_SOURCE_DIR}/gtest/src/gtest/googletest/include"
    "${PROJECT_SOURCE_DIR}/gtest/src/gtest/googlemock/include"
)

add_subdirectory (util)
add_subdirectory (gui)
add_subdirectory (peca)
