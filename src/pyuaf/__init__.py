__all__ = ["util", "client"]

# the code below is needed from SWIG 3.0.10 onwards
# because this swig uses importlib, and importlib needs 
# the right path to resolve the ___init__.so files
import os,sys
THIS_DIR = os.path.dirname(os.path.realpath(__file__))
UTIL_DIR = os.path.join(THIS_DIR, "util")
CLIENT_DIR = os.path.join(THIS_DIR, "client")
sys.path.append(os.path.realpath(UTIL_DIR))
sys.path.append(os.path.realpath(CLIENT_DIR))

from pyuaf import util, client

initialized = util.initializeUaf()

if not initialized:
    raise RuntimeError("WARNING: the UAF could not be initialized!")

__version__ = "2.3.0"