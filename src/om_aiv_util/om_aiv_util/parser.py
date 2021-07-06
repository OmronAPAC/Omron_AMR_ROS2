"""
A text processing class that consolidates ARCL messages and simplifies them
"""
class Parser:
    def __init__(self):
        self.buffer = None

    # 0 for pass condition
    # 1 for fail condition
    # 2 for continue
    def process_arcl_server(self, input):
        PASS = 0
        FAIL = 1
        CONTINUE = 2
        if " Docked" in input:
            return (PASS, "Docked successfully.")
        elif "Stopped" in input:
            return (FAIL, "Command was interrupted.")
        elif "Failed going to goal" in input:
            return (FAIL, "Failed going to goal.")
        elif "Interrupted" in input:
            return(FAIL, "Interrupted.")
        elif "Failed" in input:
            return(FAIL, "Failed")
        elif "Error" in input:
            return (FAIL, ("An Error has occurred:" + input))
        elif "Going to" in input:
            return (CONTINUE, input)
        elif " Docking " in input:
            return (CONTINUE, "Docking.")
        else:
            return (CONTINUE, "yes" + input)