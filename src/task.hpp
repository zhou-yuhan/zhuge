#ifndef TASK_HPP
#define TASK_HPP

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <utility>
#include <vector>

#include "time.hpp"

using Task = std::pair<Time, std::function<void()>>;

class TaskManager {
   public:
    TaskManager() {}

    void PushTask(const Time& timestamp, const std::function<void()>& task) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_task_q.push(Task(timestamp, task));
        m_cond.notify_one();
    }

    Task PopTask() {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_cond.wait(lock, [this] { return !m_task_q.empty(); });
        Task task = m_task_q.top();
        m_task_q.pop();

        lock.unlock();
        return task;
    }

    bool isEmpty() {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_task_q.empty();
    }

   private:
    struct TaskComparison {
        bool operator()(const Task& lhs, const Task& rhs) const {
            return lhs.first > rhs.first;
        }
    };

    std::priority_queue<Task, std::vector<Task>, TaskComparison> m_task_q;
    std::mutex m_mutex;
    std::condition_variable m_cond;
};

#endif  // TASK_HPP