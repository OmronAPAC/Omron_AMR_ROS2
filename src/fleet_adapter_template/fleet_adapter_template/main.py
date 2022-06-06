from .RobotClientAPI import RobotAPI

def main():
    api = RobotAPI("prefix", "user", "password")
    target = api.position("blah")
    x, y, theta = target
    x -= 1000
    target = [x, y, theta]
    api.navigate("blah", target, "lol")
    
    print(api.navigation_completed("blah"))
    # battery = api.battery_soc("blah")
    # print(battery)

if __name__ == '__main__':
    main()