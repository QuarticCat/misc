def quote(s):
    """
    Add one level of quotes.
    E.g. r'\\' -> r'\\\\'
    """
    return s.encode('unicode_escape').decode()


def unquote(s):
    """
    Remove one level of quotes.
    E.g. r'\\\\' -> r'\\'
    """
    return s.encode().decode('unicode_escape')
