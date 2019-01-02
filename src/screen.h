#include <SensorflowListener.h>
#include <LiquidCrystalSensor.h>
#include "screen.pb.h"


void commandScreenStatus(SensorflowListener *listener){
  ScreenStatus status = {};
  listener->receive(ScreenStatus_fields, &status);
  LiquidCrystalSensor *screen = (LiquidCrystalSensor *)listener->devices["screen"];
  //screen->statusDenied();
  if (status.status == ScreenStatus_Status_IDLE) {
    screen->statusIdle();
  } else if (status.status == ScreenStatus_Status_LOADING) {
    screen->statusLoading();
  } else if (status.status == ScreenStatus_Status_DENIED) {
    screen->statusDenied();
  }
  
}

bool decode_message(pb_istream_t *stream, const pb_field_t *field, void **arg)
{

    uint8_t *buffer = (uint8_t *)*arg;
    // We could read block-by-block to avoid the large buffer...
    // Como no se sabe el tamano real de buffer, no se hace esta comprobacion
    //if (stream->bytes_left > sizeof(buffer) - 1)
    //    return false;
    buffer[stream->bytes_left] = 0;
    if (!pb_read(stream, buffer, stream->bytes_left))
        return false;

    return true;
}

void commandScreenGranted(SensorflowListener *listener){
  ScreenGranted granted_data = {};
  char buffer[20];
  granted_data.message.funcs.decode = &decode_message;
  granted_data.message.arg = buffer;
  listener->receive(ScreenGranted_fields, &granted_data);
  LiquidCrystalSensor *screen = (LiquidCrystalSensor *)listener->devices["screen"];
  screen->statusGranted(buffer);
}