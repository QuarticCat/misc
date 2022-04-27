# Provide functions `quote` and `unquote`.

def quote(s):
    r"""
    Add one level of quotes.
    E.g. r'\\' -> r'\\\\'
    """
    return s.encode('unicode_escape').decode()


def unquote(s):
    r"""
    Remove one level of quotes.
    E.g. r'\\\\' -> r'\\'
    """
    return s.encode().decode('unicode_escape')
