#ifndef BUFFERED_CHANNEL_H_
#define BUFFERED_CHANNEL_H_

#include <mutex>
#include <condition_variable>
#include <queue>

template<class T>
class BufferedChannel {
  private:
    const int bufSize;
    std::queue<T> q;
    mutable std::mutex lockAdd;
    std::condition_variable qCheck;
    bool isOpen;

  public:
    explicit BufferedChannel(int size) : bufSize(size), isOpen(true) {}

    void Send(T value) {
      std::unique_lock<std::mutex> lock(lockAdd);
      while(q.size() >= bufSize) qCheck.wait(lock);
      if(!isOpen) throw std::runtime_error("channel is closed");
      q.push(value);
      lock.unlock();
      qCheck.notify_all();
    }

    std::pair<T, bool> Recv() {
      std::unique_lock<std::mutex> lock(lockAdd);
      while(q.empty()) qCheck.wait(lock);
      T el;
      el = q.front();
      q.pop();
      lock.unlock();
      return std::make_pair(el, isOpen);
    }

    void Close() {
      std::unique_lock<std::mutex> lock(lockAdd);
      isOpen = false;
      lock.unlock();
      qCheck.notify_all();
    }
};

#endif // BUFFERED_CHANNEL_H_
