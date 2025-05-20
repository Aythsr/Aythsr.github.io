from datetime import datetime, timedelta
import json
from appleCalendarIf import create_calendar_event
calendar = json.load(open("./class.json", "r", encoding="utf-8"))

print(calendar)

def enumerate_dates(start_date, end_date):
    """
    枚举指定日期范围内的所有日期。

    :param start_date: 开始日期 (格式: "YYYY-MM-DD")
    :param end_date: 结束日期 (格式: "YYYY-MM-DD")
    :return: 日期列表
    """
    start = datetime.strptime(start_date, "%Y-%m-%d")
    end = datetime.strptime(end_date, "%Y-%m-%d")
    delta = timedelta(days=1)
    now = start
    day = 0
    while now <= end:
        weekid = day // 7 + 1
        day += 1
        weekday = now.weekday() + 1
        for i in calendar:
            name = i["name"]
            start_time = i["start"]
            end_time = i["end"]
            local = i["local"]
            wb = i["wb"]
            startw = i["startw"]
            endw = i["endw"]
            if startw <= weekid <= endw and wb == weekday:
                st = now.strftime("%Y-%m-%d") + " " + start_time
                et = now.strftime("%Y-%m-%d") + " " + end_time
                
                create_calendar_event(
                    summary=name,
                    start_date=st,
                    end_date=et,
                    location=local,
                    description="课程",
                    calendar_name="学习"
                )


        now += delta


# 示例调用
start_date = "2025-02-24"
end_date = "2025-06-29"
enumerate_dates(start_date, end_date)
# print(dates)