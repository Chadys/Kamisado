"""Taken from here : http://eyalarubas.com/python-subproc-nonblock.html"""
from threading import Thread
from queue import Queue, Empty
import time


# pylint: disable=too-few-public-methods
class NonBlockingStreamReader:
    """Non blocking stream reader"""
    def __init__(self, stream, doprint=False, idd=-1):
        """stream: the stream to read from. Usually a process' stdout or stderr."""

        self._stream = stream
        self._queue = Queue()

        def _populatequeue(stream, queue):
            '''Collect lines from 'stream' and put them in 'quque'.'''
            while True:
                line = stream.readline().strip().decode()
                if line:
                    if doprint:
                        print('\033[1;34m{} ({})\033[0;0m'.format(line, idd))
                    queue.put(line)
                time.sleep(0.1)

        self._thread = Thread(target=_populatequeue, args=(self._stream, self._queue))
        self._thread.daemon = True
        self._thread.start() #start collecting lines from the stream

    def readline(self, timeout=None):
        """Read last line from the queue."""
        try:
            return self._queue.get(block=True, timeout=timeout)
        except Empty:
            return None
