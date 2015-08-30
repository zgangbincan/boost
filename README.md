##### 这个project是我通过学习boost的asio, bind等用法，结合网上的一些教程，实现的一个聊天的server.
##### 使用方法如下：
1.  首先你得编译boost,我使用的版本是1.57.0，编译的方法和源码库的获取请前往[官网](http://www.boost.org/doc/libs/1_59_0/more/getting_started/unix-variants.html "Title") 获取相关资料
2.  使用git clone git@github.com:zgangbincan/boost.git 获取代码
3.  在文件目录下输入make, 生成server可执行文件，如果你没有设置LD_LIBRARY_PATH="boost库路径"，通过如下执行:LD_LIBRARY_PATH="boost库路径" ./server port
