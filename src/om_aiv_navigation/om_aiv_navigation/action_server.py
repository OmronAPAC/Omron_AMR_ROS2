import rclpy
import time
from rclpy.action import ActionServer
from om_aiv_util.socket_taskmaster import *
from om_aiv_msg.action import Action
from rclpy.node import Node

class LDActionServer(Node):
    def __init__(self):
        super().__init__('action_server')
        self._action_server = ActionServer(
                    self,
                    Action,
                    'action_server',
                    self.execute_callback)
        self.ip_address = self.declare_parameter("ip_address").value
        self.port = self.declare_parameter("port").value
        self.passwd = self.declare_parameter("def_arcl_passwd").value

        self.socket_taskmaster = SocketTaskmaster()
        self.socket_taskmaster.connect(str(self.ip_address), int(self.port))
        self.socket_taskmaster.login(bytes(self.passwd, 'utf-8'))        
        self.get_logger().info("Action server is up!")
        
        self._feedback = Action.Feedback()
        self._result = Action.Result()

    def execute_callback(self, goal):
        self.socket_taskmaster.push_command(
            bytes(goal.request.command, "utf-8"),
            True,
            [bytes(goal.request.identifier[0], "utf-8")])
        while True:
            (is_done, result, feedback) = self.socket_taskmaster.wait_command()
            if is_done:
                self._feedback.feed_msg = str(feedback)
                self._result.res_msg = result
                break
            else:
                self._feedback.feed_msg = str(feedback)

            time.sleep(0.1)

        return self._result

def main():
    rclpy.init()
    
    action_server = LDActionServer()
    
    rclpy.spin(action_server)


if __name__ == '__main__':
    main()
