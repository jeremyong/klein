# Klein C-bindings

add_library(klein_c klein_c.cpp)
target_link_libraries(klein_c PRIVATE klein)
target_compile_features(klein_c PRIVATE cxx_std_11)