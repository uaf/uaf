__all__ = ["util", "client"]
from pyuaf import util, client

initialized = util.initializeUaf()

if not initialized:
    raise RuntimeError("WARNING: the UAF could not be initialized!")