
import appleCalendarIf

dayslist = [
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-05-20 19:00",
        "end_date": "2025-05-20 21:00",
        "description": "开班，导论",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-05-26 19:00",
        "end_date": "2025-05-26 21:00",
        "description": "数论内容",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-05-28 19:00",
        "end_date": "2025-05-28 21:00",
        "description": "DP，背包",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-06-04 19:00",
        "end_date": "2025-06-04 21:00",
        "description": "DP分析法",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-06-06 19:00",
        "end_date": "2025-06-06 21:00",
        "description": "数位DP",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-06-09 19:00",
        "end_date": "2025-06-09 21:00",
        "description": "状态压缩DP",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-06-11 19:00",
        "end_date": "2025-06-11 21:00",
        "description": "队列",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-06-13 19:00",
        "end_date": "2025-06-13 21:00",
        "description": "哈希",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-06-16 19:00",
        "end_date": "2025-06-16 21:00",
        "description": "分块",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-06-18 19:00",
        "end_date": "2025-06-18 21:00",
        "description": "线段树",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-06-20 19:00",
        "end_date": "2025-06-20 21:00",
        "description": "LCA",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-06-23 19:00",
        "end_date": "2025-06-23 21:00",
        "description": "生成树",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-06-25 19:00",
        "end_date": "2025-06-25 21:00",
        "description": "带权并查集，拓扑排序",
        "calendar_name": "工作"
    },
    {
        "summary": "蓝桥讲座",
        "start_date": "2025-06-27 19:00",
        "end_date": "2025-06-27 21:00",
        "description": "蓝桥讲座14结束啦😄",
        "calendar_name": "工作"
    },
]

if __name__ == '__main__':
    for day in dayslist:
        appleCalendarIf.create_calendar_event(
            summary=day["summary"],
            start_date=day["start_date"],
            end_date=day["end_date"],
            description=day["description"],
            calendar_name=day["calendar_name"]
        )