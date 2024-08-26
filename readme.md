# About
Implementation of a logger that synchronizes using a file and allows simultaneous logging to a file and the console

# Build
To use it in your project do:
```cmake
add_subdirectory(path/to/c-logger)
[ ... ]
target_link_libraries(${PROJECT_NAME} [ ... ] c_logger)
```

Optionally you can set defines:
```cmake
target_compile_definitions(c-logger PUBLIC DEBUG=ON)
target_compile_definitions(c-logger PUBLIC LOG_FILE=ON)
target_compile_definitions(c-logger PUBLIC LOG_SYNC=ON)
```
