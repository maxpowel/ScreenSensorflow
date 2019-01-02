from sensorflow.messenger import SensorflowSerialMessenger
import screen_command
import sensorflow.model as command_sf


class ScreenMessenger(SensorflowSerialMessenger):
    def status(self, status):
        status_command = command_sf.Command()
        status_command.command = "scs"
        self.messenger.send(status_command)

        status_command = screen_command.ScreenStatus()
        status_command.status = status
        self.messenger.send(status_command)

    def granted(self, message):
        status_command = command_sf.Command()
        status_command.command = "scg"
        self.messenger.send(status_command)

        status_command = screen_command.ScreenGranted()
        status_command.message = message
        self.messenger.send(status_command)



sfm = ScreenMessenger()
import time
time.sleep(3) # If you have to wait for your devices
print(sfm.ping())
for i in range(2):
    r = sfm.notification()
    print("NOTIFICATION TYPE", r.what)

sfm.status(screen_command.ScreenStatus.Status.LOADING)
time.sleep(1)
sfm.status(screen_command.ScreenStatus.Status.DENIED)
time.sleep(1)
sfm.granted("HOLAAA")
time.sleep(1)
sfm.status(screen_command.ScreenStatus.Status.IDLE)