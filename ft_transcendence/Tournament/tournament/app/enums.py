from enum import Enum
from enum import auto

class Round(Enum):
    QU = 'quarter'
    HF = 'half'
    FN = 'final'

    @classmethod
    def choices(cls):
        return tuple((i.name, i.value) for i in cls)

class Tourn_status(Enum):
    PN = 'pending'
    ST = 'start'
    EN = 'end'

    @classmethod
    def choices(cls):
        return tuple((i.name, i.value) for i in cls)
    

class M_status(Enum):
    UNP = 'unplayed'
    PLY = 'played'

    @classmethod
    def choices(cls):
        return tuple((i.name, i.value) for i in cls)
    
    
