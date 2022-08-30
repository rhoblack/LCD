add_executable(${PROJECT_NAME}
    main.cpp
    ./hw/I2C/I2C.cpp
    ./hw/LCD/LCD.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ./
    ./ap
    ./hw
    ./hw/I2C
    ./hw/LCD
)
 
target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    -lwiringPi
)