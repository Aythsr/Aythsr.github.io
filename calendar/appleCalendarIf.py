import subprocess

def create_calendar_event(summary, start_date, end_date, location = "", description="课程", calendar_name="学习", alarm_minutes_before=0):
    """
    调用 AppleScript 创建日历事件，并可设置提前提醒。

    :param summary: 事件标题
    :param start_date: 开始时间 (格式: "YYYY-MM-DD HH:MM:SS")
    :param end_date: 结束时间 (格式: "YYYY-MM-DD HH:MM:SS")
    :param location: 事件地点
    :param description: 事件描述
    :param calendar_name: 日历名称 (默认: "学习")
    :param alarm_minutes_before: 提前多少分钟提醒（0为不提醒）
    """
    applescript = f"""
    tell application "Calendar"
        set targetCalendar to calendar "{calendar_name}"
        tell targetCalendar
            set newEvent to make new event at end with properties {{ summary:"{summary}", start date:(date "{start_date}"), end date:(date "{end_date}"), location:"{location}", description:"{description}" }}
    """
    if alarm_minutes_before > 0:
        applescript += f"""
            tell newEvent
                make new display alarm at end with properties {{trigger interval:-{alarm_minutes_before}}}
            end tell
        """
    applescript += """
        end tell
    end tell"""
    # print(applescript)
    try:
        subprocess.run(["osascript", "-e", applescript], check=True)
        print(f"{summary} 事件已成功创建！ {start_date} -> {end_date} | {description}")
    except subprocess.CalledProcessError as e:
        print(f"创建事件时出错: {e}")

def delete_calendar_event(summary, start_date, end_date, location = "", description="课程", calendar_name="学习", date_range_start="2025-05-20 00:00:00", date_range_end="2026-05-21 00:00:00"):
    """
    删除指定参数的日历事件，可限制在某个时间段内。

    :param summary: 事件标题
    :param start_date: 开始时间 (格式: "YYYY-MM-DD HH:MM:SS")
    :param end_date: 结束时间 (格式: "YYYY-MM-DD HH:MM:SS")
    :param location: 事件地点
    :param description: 事件描述
    :param calendar_name: 日历名称 (默认: "学习")
    :param date_range_start: 限定查找的起始时间 (格式: "YYYY-MM-DD HH:MM:SS")，可选
    :param date_range_end: 限定查找的结束时间 (格式: "YYYY-MM-DD HH:MM:SS")，可选
    """
    # 构建时间范围条件
    time_range_condition = ""
    if date_range_start and date_range_end:
        time_range_condition = f' and start date ≥ (date "{date_range_start}") and end date ≤ (date "{date_range_end}")'
    applescript = f'''
    tell application "Calendar"
        set targetCalendar to calendar "{calendar_name}"
        set theEvents to every event of targetCalendar whose summary is "{summary}" and location is "{location}" and description is "{description}" and start date is (date "{start_date}") and end date is (date "{end_date}"){time_range_condition}
        repeat with theEvent in theEvents
            delete theEvent
        end repeat
    end tell'''
    try:
        subprocess.run(["osascript", "-e", applescript], check=True)
        print(f"{summary} 事件已删除！ {start_date} -> {end_date} | {description}")
    except subprocess.CalledProcessError as e:
        print(f"删除事件时出错: {e}")

# 示例调用
if __name__ == '__main__':
    create_calendar_event(
        summary="项目会议",
        start_date="2025-05-20 9:00",
        end_date="2025-05-20 11:00",
        location="会议室 A",
        description="讨论项目进展",
        calendar_name="学习",
        alarm_minutes_before=23  # 提前15分钟提醒
    )
    import time
    # time.sleep(5)  # 等待5秒钟
    delete_calendar_event(
        summary="项目会议",
        start_date="2025-05-20 9:00",
        end_date="2025-05-20 11:00",
        location="会议室 A",
        description="讨论项目进展",
        calendar_name="学习",
    )