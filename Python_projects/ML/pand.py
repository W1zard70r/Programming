from datetime import datetime


class TaskLogger:
    def __init__(self):
        self.pending_tasks = []
        self.completed_tasks = []

    def add_task(self, task_name, priority):
        # Добавляем задачу в список pending_tasks с временем добавления
        self.pending_tasks.append({
            "name": task_name,
            "priority": priority,
            "added_time": datetime.now(),
            "completed": False
        })

    def complete_the_highest_priority_task(self):
        if not self.pending_tasks:
            return

        highest_priority_task = max(self.pending_tasks, key=lambda x: x["priority"])

        highest_priority_tasks = [task for task in self.pending_tasks if
                                  task["priority"] == highest_priority_task["priority"]]
        task_to_complete = min(highest_priority_tasks, key=lambda x: x["added_time"])

        self.pending_tasks.remove(task_to_complete)
        task_to_complete["completed"] = True
        task_to_complete["completed_time"] = datetime.now()
        self.completed_tasks.append(task_to_complete)

    def get_pending_tasks(self):
        sorted_tasks = sorted(self.pending_tasks, key=lambda x: (-x["priority"], x["added_time"]))

        return [task["name"] for task in sorted_tasks]

    def get_completed_tasks(self):
        sorted_tasks = sorted(self.completed_tasks, key=lambda x: x["completed_time"])

        return [task["name"] for task in sorted_tasks]
