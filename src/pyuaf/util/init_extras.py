

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


################################### END OF INCLUDED PYTHON FILE ####################################
%}