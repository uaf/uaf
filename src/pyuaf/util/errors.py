
import pyuaf

class OldUafError(Exception):
    
    def __init__(self, status):
        if not isinstance(status, pyuaf.util.Status):
            raise Exception("No pyuaf.util.Status given, wrong type!")
        Exception.__init__(self, str(status))
        self.status = status


class ConfigurationError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class ConnectionError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class DataFormatError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class DataSizeError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class DataSourceError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class DisconnectionError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class DiscoveryError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class InvalidRequestError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class LowLevelError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class ResolutionError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class WrongTypeError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class OtherError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class SecurityError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class TimeoutError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class NoResultReceivedError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class SubscriptionError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class UnexpectedError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class UnknownHandleError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)
class UnsupportedError(OldUafError):
    def __init__(self, status):
        OldUafError.__init__(self, status)


__statusCodeToErrorDict__ = { pyuaf.util.statuscodes.ConfigurationError      : ConfigurationError,
                              pyuaf.util.statuscodes.ConnectionError         : ConnectionError,
                              pyuaf.util.statuscodes.DataFormatError         : DataFormatError,
                              pyuaf.util.statuscodes.DataSizeError           : DataSizeError,
                              pyuaf.util.statuscodes.DataSourceError         : DataSourceError,
                              pyuaf.util.statuscodes.DisconnectionError      : DisconnectionError,
                              pyuaf.util.statuscodes.DiscoveryError          : DiscoveryError,
                              pyuaf.util.statuscodes.InvalidRequestError     : InvalidRequestError,
                              pyuaf.util.statuscodes.LowLevelError           : LowLevelError,
                              pyuaf.util.statuscodes.ResolutionError         : ResolutionError,
                              pyuaf.util.statuscodes.WrongTypeError          : WrongTypeError,
                              pyuaf.util.statuscodes.OtherError              : OtherError,
                              pyuaf.util.statuscodes.SecurityError           : SecurityError,
                              pyuaf.util.statuscodes.TimeoutError            : TimeoutError,
                              pyuaf.util.statuscodes.NoResultReceivedError   : NoResultReceivedError,
                              pyuaf.util.statuscodes.SubscriptionError       : SubscriptionError,
                              pyuaf.util.statuscodes.UnexpectedError         : UnexpectedError,
                              pyuaf.util.statuscodes.UnknownHandleError      : UnknownHandleError,
                              pyuaf.util.statuscodes.UnsupportedError        : UnsupportedError
                            }
                             

def evaluate(status):
    try:
        exceptionClass = __statusCodeToErrorDict__[status.statusCode()]
    except KeyError:
        exceptionClass = None
    
    if exceptionClass is not None:
        raise exceptionClass(status)


def evaluateArg(arg, argName, argType, allowedValues=[]):
    if type(arg) != argType:
        try:
            allowedValue = arg in allowedValues
        except:
            allowedValue = False
        
        if not allowedValue:
            raise TypeError("Argument '%s' must be of type %s.%s" %(argName, argType.__module__, argType.__name__))


