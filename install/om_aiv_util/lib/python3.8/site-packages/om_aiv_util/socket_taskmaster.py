import io
import selectors2 as selectors
import socket
import traceback
import time
import threading
from collections import deque

RECV_BUFFER = 4096

"""A driver class to handle all input and output communication with ARCL server.
"""
class SocketTaskmaster(object):
    def __init__(self):
        self.selector = None
        self.sock = None
        self.addr = None
        self._recv_buffer = b""
        self._send_buffer = b""
        self._check_end = list()
        self._result = b""
        self._feedback = b""

    
    """Given the event mask from selectors, do read or write accordingly.
    param mask:
    The mask to use to decide which event can be executed.
    
    """
    def process_events(self, mask):
        if mask & selectors.EVENT_READ:
            self.read()
        if mask & selectors.EVENT_WRITE:
            self.write()

    # TODO: Do better than this!!!
    def clear_recv_buf(self):
        cleared = False
        while not cleared:
            events = self.selector.select()
            for key, mask in events:
                if mask & selectors.EVENT_READ:
                    try:
                        recv = self.sock.recv(RECV_BUFFER)
                    except io.BlockingIOError:
                        pass
                    else:
                        if len(recv) < RECV_BUFFER:
                            return
                else:
                    cleared = True
                    break

    """
    Read incoming bytes from the socket and save into receive buffer.
    If there are data received, append into the receiver buffer.
    
    """
    def _read(self):
        try:
            recv_data = self.sock.recv(RECV_BUFFER)
        except io.BlockingIOError:
            pass
        else:
            if recv_data:
                self._recv_buffer += recv_data

    """
    Push bytes from the send buffer to the socket buffer.
    If not all the bytes are pushed, keep the remaining bytes in the send buffer.
    
    """
    def _write(self):
        if self._send_buffer:
            try:
                num_bytes_sent = self.sock.send(self._send_buffer)
            except io.BlockingIOError:
                pass
            else:
                self._send_buffer = self._send_buffer[num_bytes_sent:]
    
    """
    Read incoming bytes and generate the correct responses.
    
    """
    def read(self):
        self._read()

        if len(self._check_end) > 0:
            self.extract_resp()

    """
    Check if there are commands to be transmitted.
    If there exists at least 1 command, push the command to the send buffer.
    """
    def write(self):
        self._write() # We want to process the send buffer.

    """
    Extracts the required string to find from the receive buffer.
    
    Returns:
        str -- The extracted string.
    """
    def extract_resp(self):
        while True:
            try:
                line_e = self._recv_buffer.index(b"\r\n")
            except ValueError:
                break
            else:
                # If there is no ValueError here, there is at least one complete line.
                line = self._recv_buffer[:line_e+2]
                self._recv_buffer = self._recv_buffer[line_e+2:]
                #print ("line = " + str(line))

                # Check if this line is contained in any of the identifier lines, substring included.
                if any(chk in line for chk in self._check_end):
                    self._result = line
                    self._command_queued = False
                    break
                else:
                    self._feedback += line

    """
    Put a command into the command list.
    The function returns an identifier integer that can be used to retrieve the corresponding response.
    
    param command:
    The command string to queue.
    param newline:
    Boolean to indicate if newline characters ('\r\n') should be appended to the command string.
    param last_line:
    String that should be used to identify the last line of the supposed ARCL response to the given
    command.
    If set to None, the command does not expect a response from ARCL. Useful if caller would like to
    read response from ARCL at the next command.
    NOTE: This string is case sensitive! Refer to ARCL documentation for appropriate responses.
    
    Returns:
        int -- The identifier integer associated with this command.
    """
    def push_command(self, command, newline=False, end_lines=list()):
        cmd_str = command
        if newline:
            cmd_str += b"\r\n"
        self._recv_buffer = b""
        self._send_buffer = b"\r\n" + cmd_str
        self._check_end = end_lines
        self._result = b""
        self._feedback = b""
        self.clear_recv_buf()

    """
    Retrieve the response associated with the given identifier integer.
    param identifier:
    The identifier integer associated with returned response.
    
    Returns:
        str -- The response string associated with the identifier integer.
    """
    def wait_command(self):
        events = self.selector.select()
        for key, mask in events:
            self.process_events(mask)

        res = self._result
        feed = self._feedback

        if len(self._result) == 0:
            return (False, b"", feed)
        else:
            self._feedback = b""
            self._result = b""
            return (True, res, feed)

    """
    # TODO: Add check for failed connection
    Connects the driver to the given address and port.
    param addr:
    Address to connect to.
    param port:
    Port number to connect to.
    """
    def connect(self, addr, port):
        server_addr = (str(addr), int(port))
        self.addr = server_addr
        print("Starting connection to", server_addr)
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.setblocking(False)
        sock.connect_ex(server_addr)
        self.sock = sock
        events = selectors.EVENT_READ | selectors.EVENT_WRITE
        self.selector = selectors.DefaultSelector()
        self.selector.register(sock, events, data=self)

    """
    Log in to the server with the given password.
    Useful for servers that requires password.
    NOTE: This function is not secure as the password is exposed in plaintext.
    param passwd:
    The password string to log in with.
    Returns:
        int -- The identifier integer associated with the response after login.
    """
    def login(self, passwd):
        self.push_command(passwd, newline=True, end_lines=[b"End of commands"])
        self.wait_until_login()

    # TODO: find a better way to do this!!!
    def wait_until_login(self):

        while True:
            try:
                events = self.selector.select()
                for key, mask in events:
                    self.process_events(mask)
            except Exception as exc:
                print("Login error: Exception for", traceback.format_exc())
                pass
        
            if any(chk in self._result for chk in self._check_end):
                self._result = b""
                self._feedback = b""
                self._check_end = list()
                break 