#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

class Time {
   public:
    Time() : m_time_point(std::chrono::microseconds(0)) {}

    Time(std::chrono::microseconds us) : m_time_point(us) {}

    Time(std::chrono::milliseconds ms)
        : m_time_point(
              std::chrono::duration_cast<std::chrono::microseconds>(ms)) {}

    static Time Now() {
        return Time(std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()));
    }

    int64_t Microseconds() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(
                   m_time_point)
            .count();
    }

    int64_t Milliseconds() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   m_time_point)
            .count();
    }

    bool operator>(const Time& other) const {
        return m_time_point > other.m_time_point;
    }

    bool operator<(const Time& other) const {
        return m_time_point < other.m_time_point;
    }

    bool operator==(const Time& other) const {
        return m_time_point == other.m_time_point;
    }

    Time& operator=(const Time& other) {
        if (this != &other) {
            m_time_point = other.m_time_point;
        }
        return *this;
    }

   private:
    std::chrono::microseconds m_time_point;
};

#endif  // TIME_HPP