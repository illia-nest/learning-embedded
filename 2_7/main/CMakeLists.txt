idf_component_register(
    SRCS
        "src/main.c"
        "src/traffic_lights.c"
        "src/button.c"
    INCLUDE_DIRS "." "include"
    PRIV_REQUIRES esp_timer esp_driver_gpio log
)