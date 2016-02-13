#include "mbed-drivers/mbed.h"
#include "ble/BLE.h"
#include "ble/services/DFUService.h"

DFUService *dfuPtr;

const char DEVICE_NAME[] = "Tommy";

static void blinky(void) {
    static DigitalOut motor(MOTOR1);

    motor = !motor;
    printf("motor = %d \n\r",motor.read());
}

/**
 * This function is called when the ble initialization process has failled
 */
void onBleInitError(BLE &ble, ble_error_t error)
{
    /* Initialization error handling should go here */
}

void bleInitComplete(BLE::InitializationCompleteCallbackContext *params)
{
    BLE&        ble   = params->ble;
    ble_error_t error = params->error;

    if (error != BLE_ERROR_NONE) {
        /* In case of error, forward the error handling to onBleInitError */
        onBleInitError(ble, error);
        return;
    }

    /* Ensure that it is the default instance of BLE */
    if(ble.getInstanceID() != BLE::DEFAULT_INSTANCE) {
        return;
    }

    dfuPtr = new DFUService(ble);

    /* setup advertising */
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME, (uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME));

    ble.gap().setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
    ble.gap().setAdvertisingInterval(200);
    ble.gap().startAdvertising();
}

void app_start(int, char**)
{
    BLE &ble = BLE::Instance();
    ble.init(bleInitComplete);

    minar::Scheduler::postCallback(blinky).period(minar::milliseconds(500));
}