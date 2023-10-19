idf_component_register(SRCS "main.cpp"
                            "src/drivers/gpio/GPIO.cpp"
                            "src/drivers/distanceSensor/HC_SR04_DistanceSensor.cpp"
                            "src/drivers/hbridge/L293D_HBridge.cpp"
                            "src/drivers/stepperMotor/ULN200X_StepperMotor.cpp"
                            "src/scanner/Scanner.cpp"
                            "src/movement/MovementController.cpp"
                    INCLUDE_DIRS "./include/")
