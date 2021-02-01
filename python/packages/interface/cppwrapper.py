"""Encapsulates the cppwrapper embedding module defined in c++.

When the module was not embedded, the exported functions are still usable
with corresponding warning messages. This allows for debugging interface code
without running CORSIKA.
"""
try:
    import cppwrapper_emb
except ModuleNotFoundError:

    import sys

    def eprint(*args, **kwargs):
        """Print message to stderr instead of stdout.

        Parameters
        ----------
        See python print() function.
        """
        retval = print(*args, file=sys.stderr, **kwargs)
        return retval
    
    def disableWrite():
        """Disable COAST calls to python write()."""
        eprint("warning: not in embedding mode - cppwrapper is ineffective")
        pass

    def enableWrite():
        """Enable COAST calls to python write()."""
        eprint("warning: not in embedding mode - cppwrapper is ineffective")
        pass

    def disableInteraction():
        """Disable COAST calls to python interaction()."""
        eprint("warning: not in embedding mode - cppwrapper is ineffective")
        pass

    def enableInteraction():
        """Enable COAST calls to python interaction()."""
        eprint("warning: not in embedding mode - cppwrapper is ineffective")
        pass

    def disableTrack():
        """Disable COAST calls to python track()."""
        eprint("warning: not in embedding mode - cppwrapper is ineffective")
        pass

    def enableTrack():
        """Enable COAST calls to python track()."""
        eprint("warning: not in embedding mode - cppwrapper is ineffective")
        pass

else:

    disableWrite = cppwrapper_emb.disableWrite
    enableWrite = cppwrapper_emb.enableWrite
    disableInteraction = cppwrapper_emb.disableInteraction
    enableInteraction = cppwrapper_emb.enableInteraction
    disableTrack = cppwrapper_emb.disableTrack
    enableTrack = cppwrapper_emb.enableTrack

