在多线程环境下 有以下情景
比如 对同一链队列进行入队操作时 一个线程正在将 新的队列节点 挂载到 队尾节点的next上
可是还没来的及更新队尾节点 但同一时刻另一个线程也在进行入队操作 将 新的队列节点 也挂在到了 没更新的队尾节点 那么先挂载的节点就丢失了
为了解决多线程环境下的这些问题
我们第一时间肯定想到了加上互斥锁 控制同一时刻只能有一个线程可以对队列进行写操作
但是加锁的操作太消耗系统资源了 很繁重 
因为对临界区的操作只有一步 就是对队列的尾节点进行更新
只要让这一步进行的是原子操作就可以了
所以使用到了CAS操作
为了有一个对比 写了一份thread_queue.c是用锁对临界区进行控制访问的
另一份是lock_free_queue.c是用CAS确保对临界区的操作是原子操作

依赖关系 
lock_free_queue.c -> queue.h -> queue.c
thread_queue.c -> queue.h -> queue.c

gcc lock_free_queue.c queue.c -lpthread -o lock_free_queue
gcc thread_queue.c queue.c -lpthread -o thread_queue