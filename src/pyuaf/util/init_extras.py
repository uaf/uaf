%pythoncode %{
################################ BEGINNING OF INCLUDED PYTHON FILE #################################


def __get__repr__(fullname, description):
    lines  = description.split("\n")
    ret    = fullname + "("
    if len(lines) == 0:
        return ret + ")"
    elif len(lines) == 1:
        return ret + lines[0] + ")"
    else:
        indent = len(ret) * " "
        ret += lines[0]
        for line in lines[1:]:
            ret += '\n' + indent + line
        return ret + ")"

def convert_uint32_to_int32(uint32):
    return int(uint32) if uint32 < 2**31 else int(uint32 - 2**32)

def convert_int32_to_uint32(int32):
    return int(int32 & 0xffffffff)

################################### END OF INCLUDED PYTHON FILE ####################################
%}
