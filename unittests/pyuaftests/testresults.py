import threading

class TestResults:
    def __init__(self, total):
        self.__total      = total
        self.__finished   = 0
        self.__failed     = 0
        self.__lock       = threading.Lock()
        self.__extraInts  = {}
        self.__extraLists = {}
    
    def clear(self):
        self.__lock.acquire()
        self.__finished = 0
        self.__failed   = 0
        self.__lock.release()
    
    def initializeInt(self, name, value=0):
        try:
            self.__lock.acquire()
            self.__extraInts[name] = value
        finally:
            self.__lock.release()
    
    def initializeList(self, name, value=[]):
        try:
            self.__lock.acquire()
            self.__extraLists[name] = value
        finally:
            self.__lock.release()
    
    def appendToList(self, name, value):
        try:
            self.__lock.acquire()
            self.__extraLists[name].append(value)
        finally:
            self.__lock.release()
    
    def removeFromList(self, name, value):
        try:
            self.__lock.acquire()
            self.__extraLists[name].remove(value)
        finally:
            self.__lock.release()
    
    def getListCopy(self, name):
        try:
            self.__lock.acquire()
            copiedList = list(self.__extraLists[name])
            return copiedList
        finally:
            self.__lock.release()
    
    def incrementInt(self, name):
        try:
            self.__lock.acquire()
            self.__extraInts[name] += 1
        finally:
            self.__lock.release()
    
    def decrementInt(self, name):
        try:
            self.__lock.acquire()
            self.__extraInts[name] -= 1
        finally:
            self.__lock.release()
    
    def setInt(self, name, value):
        try:
            self.__lock.acquire()
            self.__extraInts[name] = value
        finally:
            self.__lock.release()
    
    def getIntValue(self, name):
        try:
            self.__lock.acquire()
            return __extraInts[name]
        finally:
            self.__lock.release()
    
    def finish(self):
        try:
            self.__lock.acquire()
            self.__finished += 1
        finally:
            self.__lock.release()
    
    def fail(self):
        try:
            self.__lock.acquire()
            self.__failed += 1
        finally:
            self.__lock.release()
    
    def total(self):
        return self.__total
    
    def finished(self):
        return self.__finished

    def failed(self):
        return self.__failed
