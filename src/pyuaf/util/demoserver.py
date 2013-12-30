from subprocess import Popen, PIPE
from time import sleep

# the variables between '@' will be overwritten by CMake!
DEMOSERVER_COMMAND     = "@DEMOSERVER_COMMAND@" # the startup command for the demo server
DEMOSERVER_STARTUPTIME = 1 # seconds until the demo server is started


class DemoServerRunner():
    """
    Just a simple class to start/stop the Unified Automation demo server.
    (formerly called UaDemoServer, since SDK v1.4 called UaServerCPP).
    """
    
    def __init__(self, command=DEMOSERVER_COMMAND):
        """
        Create an instance of the demoserver runner.
        """
        self.command = command
        self.popen   = None
    
    
    def start(self):
        """
        Start the demo server.
        """
        try:
            self.popen = Popen([DEMOSERVER_PATH], stdout=PIPE, stderr=PIPE)
            sleep(DEMOSERVER_STARTUPTIME)
        except Exception, e:
            raise Exception("The demo server '%s' could not be started (%s)", (self.command, e))
    
    
    def stop(self):
        """
        Stop the demo server.
        """
        try:
            self.popen.terminate()
        except Exception, e:
            raise Exception("The demo server '%s' could not be stopped (%s)", (self.command, e))


    def test(self):
        """
        Test the demo server.
        """
        try:
            self.start()
            sleep(DEMOSERVER_STARTUPTIME)
            self.stop()
            (stdout, stderr) = self.popen.communicate()
            
            if stdout == "":
                raise Exception("The demo server started without returning output... " \
                                "is the demo server already running?")
            elif stderr != "":
                raise Exception("The demo server finished with the following error: %s" %stderr)
        except Exception, e:
            raise Exception("Testing the demo server failed (%s)", (self.command, e))
