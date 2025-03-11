#include <memory>
#include <future>
#include <iostream>

using namespace std;

template <typename F>
class Task{
public:
    Task(F&& f): mTask(move(f)) {}
    using T = invoke_result_t<F>;
    packaged_task<T()> mTask;
};

template <typename F, typename T = invoke_result_t<F>>
future<T> schedule(F&& f){
    auto [task, future] = makeTask(move(f));
    task->mTask();
    return move(future);
}

template <typename F>
auto makeTask(F&& f)
{
    shared_ptr<Task<F>> task = make_shared<Task<F>>(std::forward<F>(f));
    return make_pair(task, task->mTask.get_future());
}

int main()
{
    auto r = schedule([]{ cout << "lambda task" << endl; return 1;});
    cout << r.get() << endl;
    return 0;
}