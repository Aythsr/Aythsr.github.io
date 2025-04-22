import subprocess

def create_calendar_event(summary, start_date, end_date, location, description="课程", calendar_name="学习"):
    """
    调用 AppleScript 创建日历事件。

    :param summary: 事件标题
    :param start_date: 开始时间 (格式: "YYYY-MM-DD HH:MM:SS")
    :param end_date: 结束时间 (格式: "YYYY-MM-DD HH:MM:SS")
    :param location: 事件地点
    :param description: 事件描述
    :param calendar_name: 日历名称 (默认: "学习")
    """
    applescript = f"""
    tell application "Calendar"
        set targetCalendar to calendar "{calendar_name}"
        tell targetCalendar
            make new event at end with properties {{ summary:"{summary}", start date:(date "{start_date}"), end date:(date "{end_date}"), location:"{location}", description:"{description}" }}
        end tell
    end tell"""
    # print(applescript)
    try:
        # 调用 osascript 执行 AppleScript
        subprocess.run(["osascript", "-e", applescript], check=True)
        print("事件已成功创建！")
    except subprocess.CalledProcessError as e:
        print(f"创建事件时出错: {e}")

if __name__ == '__main__':
# 示例调用
    create_calendar_event(
        summary="项目会议",
        start_date="2025-04-21 9:00",
        end_date="2025-04-21 11:00",
        location="会议室 A",
        description="讨论项目进展",
        calendar_name="学习"
    )