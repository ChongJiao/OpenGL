# 关于event事件的理解
> 定义了Event的事件，然后其他所有的事件继承了该Event。

> 定义了windows属性，并且通过std::function来定义事件回调函数变量，通过定义了windowsData，
这个data里面包括了这个回调函数变量，这个回调函数的参数是事件。在windows初始化的时候，将这个回调函数变量赋值在onEvent的函数中，
然后绑在data中，这个data通过用户绑进glfw的userpointer中，然后在gflw的不同事件回调函数中拿到data的回调函数变量，并进行相应的操作。

> std::bind可以理解成将一个函数并结合占位符的方式得到新的函数。