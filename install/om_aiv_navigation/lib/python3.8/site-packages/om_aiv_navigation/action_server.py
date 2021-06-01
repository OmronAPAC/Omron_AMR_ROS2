import rclpy
import time
from rclpy.action import ActionServer
from om_aiv_util.socket_taskmaster import *
from om_aiv_navigation.msg import ActionAction, ActionFeedback, ActionResult

class ActionServer():
    def __init__(self, node, socket_taskmaster):
        self._action_server = ActionServer(
            node,
            ActionAction,
            'action_server',
            self.execute_callback)

        self.socket_taskmaster = socket_taskmaster
        self._feedback = ActionFeedback()
        self._result = ActionResult()

    def execute_callback(self, goal):
        self.socket_taskmaster.push_command(
            goal.command,
            True,
            goal.identifier)

        while True:
            if self._as.is_preempt_requested():
                self._as.set_preempted()
                break

            (is_done, result, feedback) = self.socket_taskmaster.wait_command()
            if is_done:
                self._feedback.feed_msg = feedback
                self._as.publish_feedback(self._feedback)
                self._result.res_msg = result
                self._as.set_succeeded(self._result)
                break
            else:
                self._feedback.feed_msg = feedback
                self._as.publish_feedback(self._feedback)

            time.sleep(0.1)


def main():
    rclpy.init()
    node = rclpy.create_node('action_server')
    ip_address = node.declare_parameter("ip_address").value
    port = node.declare_parameter("port").value
    passwd = node.declare_parameter("def_arcl_passwd").value

    socket_taskmaster = SocketTaskmaster(node)
    socket_taskmaster.connect(str(ip_address), int(port))
    req_id = socket_taskmaster.login(bytes(passwd, 'utf-8'))

    action_server = ActionServer(node, socket_taskmaster)
    node.get_logger().info("DONE!!!")
    rclpy.spin(action_server)


if __name__ == '__main__':
    main()
