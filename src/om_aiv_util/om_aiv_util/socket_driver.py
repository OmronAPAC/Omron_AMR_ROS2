import io
import selectors2 as selectors
import socket
import traceback
import time
import threading
from collections import deque

RECV_BUFFER = 4096

"""
A driver class to handle all input and output communication with ARCL server.
"""
class SocketDriver(object):
    def __init__(self):
        self.selector = None
        self.sock = None
        self.addr = None
        self.commands = deque() # shared
        self.responses = dict()
        self._recv_buffer = b""
        self._send_buffer = b""
        self._command_queued = False
        self.id_tracker = list() # Sorted list of IDs assigned at current moment. #
        self.curr_id = -1 # Valid IDs are from 0 to inf.
        self._find_str = None
        self.lock = threading.Lock()

    
    """Given the event mask from selectors, do read or write accordingly.

    param mask:
    The mask to use to decide which event can be executed.
    
    """
    def process_events(self, mask):
        if mask & selectors.EVENT_READ:
            self.read()
        if mask & selectors.EVENT_WRITE:
            self.write()

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
        if self._find_str is not None:
            try:
                resp = self.extract_resp()
            except ValueError:
                # No value is found, do nothing and continue reading.
                pass
            else:
                self._find_str = None
                self.responses[self.curr_id] = resp
                self.selector.modify(self.sock, selectors.EVENT_READ | selectors.EVENT_WRITE, data=self)

    # 
    """
    Check if there are commands to be transmitted.
    If there exists at least 1 command, push the command to the send buffer.

    """
    def write(self):
        # Put any available command in the list to send buffer.
        if len(self.commands) > 0 and not self._command_queued:
            self._put_to_buffer()

        self._write() # We want to process the send buffer.

        # If the send buffer is empty and there are no strings to find in the receive buffer, 
        # we set the command queue flag to False to allow the next availble command in the list to
        # be queued.
        if self._command_queued:
            if len(self._send_buffer) == 0 and self._find_str is None:
                self._command_queued = False
    """
    Extracts the required string to find from the receive buffer.
    
    Returns:
        str -- The extracted string.
    """
    def extract_resp(self):
        line_s = self._recv_buffer.index(bytes(self._find_str, 'utf-8'))
        resp_e = self._recv_buffer.index(b"\r\n", line_s) + 1 # Add one to get the index of \n.
        ret = self._recv_buffer[:resp_e+1] # We want the \n char.
        self._recv_buffer = self._recv_buffer[resp_e+1:]
        return ret

    """
    Generates an identifier that is the lowest unassigned int from the identifier tracking list.
    
    Returns:
        int -- The identifier integer generated.
    """
    def gen_id(self):
        self.lock.acquire()
        cnt = 0
        for val in self.id_tracker:
            if val == cnt:
                cnt += 1
                continue
            else:
                break
        self.id_tracker.append(cnt)
        self.id_tracker.sort()
        self.lock.release()
        return cnt
    
    """
    Deletes an identifier in the identifier tracking list.
    Used when we want to free an identifier number for next use.

    param identifier:
    The identifier integer to delete.
    
    """
    def clr_id(self, identifier):
        self.lock.acquire()
        try:
            self.id_tracker.remove(identifier)
        except ValueError:
            pass
        self.lock.release()

    """
    Put the oldest command in the list queue to send buffer.
    
    """
    def _put_to_buffer(self):
        cmd = self.commands.popleft()
        self.curr_id = cmd[0]
        self._send_buffer += cmd[1]
        self._find_str = cmd[2]
        self._command_queued = True
        self.selector.modify(self.sock, selectors.EVENT_READ, data=self)
        
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
    def queue_command(self, command, newline=False, last_line=None):
        _id = self.gen_id()
        cmd_str = command
        if newline:
            cmd_str += "\r\n"
        to_queue = (_id, bytes(cmd_str, "utf-8"), last_line)
        self.commands.append(to_queue)
        return _id

    """
    Retrieve the response associated with the given identifier integer.

    param identifier:
    The identifier integer associated with returned response.
    
    Returns:
        str -- The response string associated with the identifier integer.
    """
    def get_response(self, identifier):
        ret = self.responses.pop(identifier)
        self.clr_id(identifier)
        return ret

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
        print("starting connection to", server_addr)
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
        _id = self.queue_command(passwd, newline=True, last_line="End of commands")
        self.wait_until_login(_id)
        

    # TODO: find a better way to do this!!!
    def wait_until_login(self, _id):
        self._find_str = "End of commands"
        while True:
            try:
                events = self.selector.select()
                for key, mask in events:
                    self.process_events(mask)
            except Exception as exc:
                print("Login error: Exception for", traceback.format_exc())
                pass
        
            try:
                if b"End of commands" in self.responses[_id]:
                    self.get_response(_id)
                    break
            except:
                # Continue looking for the welcome message.
                pass

                
        
