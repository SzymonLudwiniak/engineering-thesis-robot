idf_component_register(SRCS "main.cpp"
                            "src/externals/gpio/GPIO.cpp"
                            "src/distanceSensor/HC_SR04_DistanceSensor.cpp"
                            "src/hbridge/L293D_HBridge.cpp"
                    INCLUDE_DIRS "./include/")
