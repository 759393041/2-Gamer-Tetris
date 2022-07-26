# 2-Gamer-Tetris
做了一个二人对战的俄罗斯方块，参考tetris99

# Cell类 方格

背景板由许许多多的小格子组成，所以我们从由小到大开始设计。

## 类成员

```c++
class cell
{
    
    //类成员函数
public:
    cell() {}//构造函数
    cell(QPoint &, QPointF &, int _color = NO_COLOR);//重载构造函数，给方块的两个坐标和颜色赋值
    cell(const cell& c) { copy(c); }//拷贝构造
    //操作函数：
    cell& copy(const cell&);//方块拷贝
    cell& operator=(const cell& c) { return copy(c); }//方块拷贝，但是是重载操作符
    void set_color(int _color) { color = _color; }//设置方块的颜色
    QColor draw_cell_color() const;//根据类内的color 给颜色，所以不用参数
    int get_color() { return color; }//读取方块颜色
    QPointF& get_position() { return position_on_window; }//读取当前方块在窗口上的位置
    QPoint& get_location() { return location_on_board; }//读取当前方块在棋盘(格格)上的位置
    
    //类成员变量
private:
    QPointF position_on_window;//方块在窗口上的位置
    QPoint location_on_board;//方块在棋盘(格格)上的位置
    int color;//方块的颜色

};
```

cell虽然是棋盘上的格子，但也是存在于窗口内的，所以需要两个坐标:

一个用于记录方格的左上角的坐标，也就是**方格在窗口内的坐标**：

QPointF position_on_window；**(f是浮点数，窗口的坐标是小树的x和y)**

一个用于记录方格在棋盘中是哪一个格子的坐标

QPoint location_on_board;

还有一个是记录方格本身的颜色，颜色想要用宏替换的方法去存储颜色种类，利于后面用switch case给方格绘图染色用：

int color;

## 源程序实现

### 有参构造

参数:QPoint &, QPointF &, int _color = NO_COLOR

给类内方块在窗口上的位置和方块在棋盘(格格)上的位置赋初值，一个为Qpoint类型，一个为Qpointf类型，默认为无背景颜色

### 拷贝构造

### 深拷贝

参数：const cell& c

相关函数：copy()函数与重载操作符=

操作：

1. 将外部变量cell的成员变量值赋给类内cell的变量
2. 返回类内成员的地址

### 返回当前cell的颜色

draw_cell_color()

根据cell对象里的color，来决定返回什么颜色的QColor，用于染色

操作：

1. 创建Qcolor类对象
2. 根据cell类内成员color进行switch-case选择颜色分支，并根据颜色分支调用Qcolor类对象的有参初始化去赋值Qcolor颜色，其中color为整形，可以通过宏定义替换的方式为switch-case进行选择。
3. 返回已赋值的qcolor类对象

### 设定方块颜色

# Board类 背景

board由cell组成

## 类成员

```c++
class board
{
//类成员函数
public:
    board(){}
    board(int, int, int, int);//有参构造，赋值类成员变量
    board(const board& bd) { copy(bd); }//有参构造，参数为另一个类对象
    cell& get_a_cell(int, int) const;//创建背景
    void clear_board();//清空背景板
    void set_cell_color(cell &, int);//设定目标格子颜色
    int get_cell_color(cell &);//获得背景中目标格子的颜色
    bool is_full(int);//判断一行是否满了
    bool is_empty(int);//判断一行是否是空的
    bool is_something(int);//判断一行是否有东西
    void clear_row(int);//清空这一行
    void row_cut_paste(int from,int to);//把这行从from行整体移动到to行(所以类似于裁剪)
    const QPoint get_start_location(int, int, int);//获取在棋盘上开始的位置
    board& operator=(const board& bd) { return copy(bd); }
    ~board();
private:
    board& copy(const board&);
    
//类成员变量
private:
    cell *board_space;//背景数组
    int board_h;//背景高度
    int board_w;//背景宽度
};

```

## 源程序实现

### 有参构造

参数：x，y两个窗口坐标，窗口宽，窗口高。

int x, int y, int board_height, int board_width

操作:

1. 窗口宽、高赋值给类内成员w、h

2. 在堆区new一个细胞数组给类内成员，即给背景开辟空间

3. 循环初始化背景板:

   1. 计算出当前格子在窗口上的坐标,即：

      ```c++
      float _x = float(w) * float(CELL_LENGTH) + float(x);
      float _y = float(h) * float(CELL_LENGTH) + float(y);
      //这个w和h用于循环体中的循环变量，就是记录细胞的行与列数，
      ```

   2. 创建关于背景板中当前格子在背景板上的坐标Qpoint对象和格子在窗口上的坐标Qpointf对象，并将刚才的结果进行赋值。

   3. 对当前背景板坐标下的cell格子进行有参初始化，即第二部的两个类对象作为变量输入。

   4. 如此循环至board中每一个空间cell都初始化了。

一维数组不是二维数组，但依旧是连续空间，对齐取下标的算法为：

```c++
 board_space[h * board_width + w] = cell(location_on_board, position_on_window);
```

### 清空背景板颜色

操作：

1. 遍历背景类成员变量board_space，细胞空间。
2. 调用setcolor设置颜色为无颜色。

### 设定背景板中方块的颜色

参数：目标细胞cell& _cell，整型的颜色(宏替换)int _color

操作：

1. 记录目标细胞的x与背景板宽度相乘在加上y坐标
2. 将该记录作为细胞空间数组下标索引，并调用该索引下细胞的设定方块颜色函数

实际上获取背景板的变量都是这么索引的，只不过操作不一样，搜索是一样的。

### 判断某一行是否满

参数：int行数

操作：

1. 创建计数变量，用于记录同行内有颜色的方块数量
2. 循环通过对board内细胞空间目标行数那一行进行判断，调用getcolor函数，若颜色不等于NOcolor，计数器++；
3. 返回时如果count计数器与背景的宽度相同，返回真，否则返回假。

### 判断某一行是否空

参数:int num，判断num那一行

与上一步相似，不过在第二部的判断里，若颜色等于NOcolor 计数器++；如果计数器等于背景宽度，那就是空，反之为假。

### 判断否一行是否有格子

参数:int num，判断num那一行

不满也不空，那就是有被。

```C++
    return (!is_empty(num) && !is_full(num));
```

### 清空这一行

参数:int num ，num为想要清空的那一行的标号

把那一行颜色变回NOcolor就完事了

操作：

1. 遍历背景空间的那一行
2. 对同行的每一个元素调用setcolor函数并设置成无颜色

### 方块整行移动(把某一行移动至另一行)

参数：int from, int to

操作:

1. 遍历背景空间的一行
2. 记录源行的颜色
3. 目标行变成源行的颜色
4. 源行变为无色

因为是一行一行的，不是整体的，具体变哪行是游戏引擎的事。

### 深拷贝

参数:const board&bd

变量赋值，给类成员变量背景空间开辟空间，然后将源背景赋值给类成员背景空间，而不是让两个变量的空间指向同一个堆区空间。

### 根据形状获取起始位置

每个方块的形状各不相同，所有起始坐标的位置也不相同。

采用switch-case和宏替换的方式来根据不同的形状选择不同的位置

同时也要注意，游戏内是有两个背景的，一个背景显示游戏界面，一个显示下一个方块。

所以参数：int 形状(宏替换)，int 水平格式，int 竖直格式

如果参数输入的水平格式是居中，竖直格式也是居中，那就是放到小背景板的

如果水平格式是居中，但竖直不是，那就是放到大背景板的

采用这样的方法，根据每个形状的起始位置偏差不一样，记录其初始位置。

并返回一个Qpoint(起始x，起始y)的坐标类对象。

### 析构

不要忘了回收背景空间的堆区空间

# shape类 形状

形状也是由方格组成

## 类成员

```c++
class shape
{

//类成员函数
public:
    shape(cell &, board& bd);//初始化形状
    virtual ~shape() = 0;
    virtual void rotate();//形状旋转函数
    int get_color() { return color; }
    cell& get_a_cell(int n) { return cells[n]; }
    void set_a_cell(int n, cell& _cell) { cells[n] = _cell; }//设置方块

    //疑问 是否需要加入染色操作函数
    //答案 不需要，在构造的时候就可以给了，而且还有继承

protected:
    virtual void compute_rotate_positions();//实际上计算的是以谁为为中心转，二维数组中四个形态中旋转中心块那一列是不变的。
    //这函数就是为了写死那个中心，但每个块转的中心都不一样，所以一个父类，其他的重写。
    
    //类成员变量
    bool is_vaild_position(int);
    int color;//形状的颜色 每个形状颜色各不相同
    cell cells[NUM_OF_CELLS];//形状的空间
    QPoint rotate_positions[NUMBER_OF_ROTATE_POSITIONS][NUM_OF_CELLS];//以二维数组来记录每一个形状内方块旋转后的坐标位置
    int which_position;    //Which position的意思是我旋转了多少下。也就是按了多少次上
    //对它取余4不久是能确定转的形态是0/1/2/3哪种么 :)
    board m_bd;
};

```

## 源程序

### 有参构造

无论是啥**形状**，都由**四个方块**组成，是肯定要开辟空间的。

参数:第一个位置的方块cell& first_cell，放入的背景板 board& bd

操作:

1. 给定颜色，并初始化为无颜色；将参数传入类内背景板，用于记录这个形状是放在哪个背景里的
2. 遍历并为形状的每一个单元初始化方块
3. 将形状的空间数组首元素给予第一个位置的方块信息
4. 旋转位置初始化为0

### 计算旋转中心的位置

​	每一个形状的旋转位置各不相同，所以该函数写成了虚函数，将7个形状均继承父类形状，其中子类重写父类的计算旋转中心位置函数。

思路：我们自行选择，固定住形状中四个方块的一个方块，就是以每一个形状数组第二个下标的方块为固定位置，但固定位置的坐标我们自己选择

因为旋转时，只有中心位置的坐标是永远不会变的。

操作:

1. 记录旋转中心的坐标x与y
2. 以旋转中心的坐标x与y为基准，计算出该形状其他方块旋转后的位置，并记录在旋转坐标二维数组内。

这个函数需要子类中实现，并且7个子类形状的旋转后位置坐标是各不相同的。

### 是否能旋转

参数：int which_position 下一个旋转形态

操作:

1. 根据下一个which_position形态编号去遍历二维数组rotate_positions的一列坐标
2. 对这个形态的每一个方块的坐标进行判断：
   1. 是否横纵坐标>0
   2. 横纵坐标是否<背景板边界
   3. 遍历的这一组坐标下的方格是否为无颜色
3. 满足则返回true，否则返回false 并给类内旋转许可标志is_vaild赋对应的值。

### 旋转操作

通过对which_position进行取余4的操作，得到0123四个形态，对应旋转的四个形态。

无参数

操作:

1. 计算旋转的位置
2. 记录旋转的次数
3. 对旋转次数取余获得下一个旋转的形态编号
4. 预先对旋转后的位置做判断：调用旋转判断函数is_vaild_position 利用其返回值真假判断
5. 能转的话，从形状坐标二维数组中提出每个方块的横纵坐标作为参数，输入背景板方格的获得方块函数get_a_cell，返回值输入给形状空间数组cells；如果转不了，旋转次数回退-1

染色不在这里染色，这里只是找到旋转后的空间，这么做的原因在游戏引擎里细讲。

# 7个形状子类

以Z型为例，所有形状与之拥有相同的类成员

## 类成员

```c++
class zshape:public shape
{

public:
    zshape(cell &, board &);//有参构造函数，给继承的两个参数赋值
    ~zshape();

private:
    virtual void compute_rotate_positions() override;
};
```

## 源程序

计算旋转坐标的函数操作方法与父类里写的默认操作一致，但是要根据每个形状自己去设定。

# 游戏引擎类

## 类成员

```c++
class gameEngine
{
public:
    gameEngine(int, int, int, int);//重载构造函数
    ~gameEngine();

   //操作函数：

    board& get_main_bd() { return main_bd; }
    board& get_next_bd() { return next_bd; }
    bool get_move_down_ok() { return move_down_ok; }//获取下落判断标志

    void next_place_a_shape();//下一个放的形状
    void main_place_a_shape();//当前放的形状

    void move_down();//形状向下移动
    void move_left();//左
    void move_right();//右

    void clear_rows();//清空行
    int num_rows_cld();//将图形转换成固定背景
    void rows_move_down();//图形向下移动
    void rotate();//形状旋转操作
    int compute_score();//计分 可以在此调用信号槽 发送攻击信号
    bool is_game_over();//判断游戏结束
    
private:
    void traverse_rows(int* cld_rows = NULL);//将图形转换成固定背景
    int set_shape_color(int);//设置形状颜色
    shape* place_a_shape(board &, int, int, int);//放置形状
    bool is_moveable(int, int, bool);//可移动判定
    void move(int, int);//移动函数
    
    
   //类成员变量
    board main_bd;
    board next_bd;
    shape* tracked_shape;//放入主面板的下一个形状
    bool move_down_ok;
    int m_ishape;//下一个形状的编号

};

```

## 源程序

### 有参构造函数

参数：主背景板的坐标x和y，副背景板的坐标x和y

操作：

1. ​	给类内成员赋初值，以参数作为输入
2. 初始化其余成员，当前形状为NULL，下一个形状编号设置为0，下落判定设置为真

### 在背景创建形状

参数：board& bd哪一个背景, int hrz水平显示方式, int vrtx竖直显示方式, int num形状的编号

主背景就用主背景的显示方式输入

副背景就用副背景的显示方式输入

操作:

1. 创建形状指针
2. 根据switch-case选择语句创建7个形状的分支，分支下:
   1. 通过水平和数值方式获取每个形状的起始位置(调用get start location)，
   2. 通过起始位置放入背景板
   3. 让形状指针指向其子类形状指针，开辟空间new
3. 返回形状指针

### 主面板放置形状

无参数，主要是操作

操作:

1. 设定下落判定为真
2. 如果当前主背景记录的形状不为空，delete掉
3. 让记录形状获得新的形状，调用place a shape函数

### 副面板放置形状

无参数

操作:

1. 产生0-3的一个随机数
2. 将形状放置入副面板
3. 将随机数传给类内下个形转的记录变量

### 将形状颜色传入主背景

参数:int color 颜色

操作:

1. 获得主面板追踪形状的颜色
2. 4次循环去获取形状里的坐标，以此坐标为参数，将对应的主背景板颜色类成员置位对应形状的颜色。

注意形状里的方块位置信息都是村的初始位置

### 主背景下的形状旋转

思路：

![image](https://user-images.githubusercontent.com/81805379/180642703-5255801a-8379-40b4-8b04-cde091e11b0a.png)

采用先将形状颜色置为无颜色，判断宣传后的位置是否存在颜色，存在则不能旋转，不存在则可以旋转。

如果我要判断能不能旋转，我就要判断旋转后的位置是不是没有颜色的，可是像T这样的方块，它本来就有别的方块占着位置，有颜色的，没法判断的，所以选择先将T方块的颜色变为无颜色，然后判断，此时若仍然存在颜色，那就是之前其他方块落下的方块。反之则可以旋转。

操作:

1. 将主背景下的形状颜色设置为无颜色，调用set_shape_color函数
2. 主背景下形状调用其类内的旋转函数
3. 将颜色再次还给形状

实际上能不能转是第二步判断的，能转他就改坐标了，转不了坐标也不会变。

### 形状移动判断

```c++
bool gameEngine::is_moveable(int up_down, int left_right, bool is_move_down)
```

参数:判断上下能否移动，判断左右额能否移动，判断是否已经下落

思路：

依旧是和旋转一样，先变为无色，然后判断下一次移动的路径上有没有颜色方块，有则不能移动，没有且没超过边界则可以移动

操作:

1. 形状转换为无颜色
2. 判断移动后的位置是否有颜色
3. 判断移动后的位置是否超出边界且是否已经下落完成

### 形状移动

思路：无论是上下左右，都是先判断能不能动，然后调用move移动函数

```c++
void gameEngine::move_down()
{
    bool moveable = is_moveable(DOWN, NO_MOVE, true);
    if(moveable) move(DOWN, NO_MOVE);
}
```

所以我们主要谈move函数

```
move
```

参数:int up_down, int left_right，一个控制上下，一个控制左右

也可以填写No_move  宏替换 右边x+1 左边x-1 同理上下y-1和y+1

实际上改变的是**窗口坐标**而不是棋盘坐标。

操作:

1. 对形状shape的空间进行遍历
2. 获取每一个shape里方格cell的坐标
3. 根据参数对坐标进行加减

### 对主背景内已经固定的形状操作traverse_rows

```
traverse_rows
```

参数:整形指针

转换固定背景的过程中，就有着对满行的判定，满行是需要清空的，需要返回一个标志告诉它清空了几行。如果传入的是空指针，则清空每一行。

操作:

1. 遍历主背景的每一行
2. 判断每一行是否为满(isfull)，若满，判断传入的指针是否为空
3. 传入的指针为空，则清空每一行，如果传入了不为空的指针，则对指针内计数++

清空每一行的清空是在重新开始游戏的时候有用，所以在这里可以先写好。

### 清空每一行

```
clear_rows
```

刚才封装好了函数，现在调用即可

操作:调用traverse_rows，但不给参数，所以清空每一行

### 对清空行的计数

```
num_rows_cld
```

同理，给traverse_rows一个指针，里面是0就可以，让他自己++

返回值可作为分数计数

### 消除之后向下整体下移

```
rows_move_down
```

操作:

1. 遍历主背景板的每一行，一定要从下往上遍历
2. 若下面某一行存在一个空行,标记
3. 再次从下往上遍历，找到第一个方块颜色不为空的行
4. 将存在方块的行移植至标记的空行

### 判断是否游戏结束

思路：如果下一个出现的形状的初始坐标里，四个格子有一个有颜色，则游戏失败

```
is_game_over
```

操作:

1. 根据七种形状简历选择语句,以类内变量下一个形状编号为判定
2. 获取形状各方块的初始坐标
3. 判断棋盘上这些方块的初始坐标是否有颜色

# 服务器主窗口类

```
MAINWINDOW
```

## 类成员

```c++
class MainWindow : public QMainWindow
{
    Q_OBJECT
//类成员方法
public:
    MainWindow(QWidget *parent = nullptr);//构造 初始化操作
    ~MainWindow();//析构 回收空间
public:
    void paintEvent(QPaintEvent *) override;//重绘画图事件
    void keyReleaseEvent(QKeyEvent * event) override;//按键抬起事件
    void keyPressEvent(QKeyEvent * event) override;//按键按下事件
    void timerEvent(QTimerEvent *event)override;//定时器事件
    int re=-1;//抬起定时器编号记录
    int ps=-1;//按键按下定时器编号记录
public slots:
    void start_game();//按下开始游戏按键的槽函数
    void new_game();//按下newgame按键的槽函数
    void slot_mainwindowserver_dealdata(uint socket ,char*,int);//服务器接收数据的槽函数
    
    //类成员属性
public:
    opponents_window* ow;//对手窗口
private:
    Ui::MainWindow *ui;//主窗口ui
    gameEngine* ge;//游戏引擎
    int timer_pressdown_id;//按键按下定时器ID记录
    int timer_releaseup_id;//按键抬起定时器ID记录
    bool game_is_started;//游戏开始判定标志
    INetMediator* m_server;//网络中介者类成员变量
    uint client_socket;//记录发消息给服务器的客户端的套接字，用于返回消息
};
```

## 源程序

### 构造函数

主要是初始化引擎、打开子窗口、打开服务器、绑定槽函数、初始化类内属性

操作：

1. 将ui空间里的两个frame组件大小传给游戏引擎类成员属性，并开辟堆区空间
2. 绑定两个按键槽函数
3. 打开子窗口，为子窗口开辟空间
4. 调整子窗口初始位置，并显示
5. 开启服务器，调用TCP中介者类的opennet函数
6. 绑定关于网络的信号槽，一共两个，一个调用主窗口的处理槽函数，一个调用对手窗口控件下的处理槽函数
7. 类内记录客户端套接字初始化为0，将游戏启动标志置位假

### 开始游戏按键槽

```
start_game
```

思路:开始游戏的时候是需要预先给next窗口放置形状的，是因为主窗口捕捉的是next窗口里的形状，形状是从next传导到main窗口的。

操作:

1. 游戏引擎调用next_place_a_shape去给next窗口放置图形
2. 调用主窗口放置图形main_place_a_shape
3. 清空next窗口
4. 再次在next窗口放置形状next_place_a_shape
5. 调用update函数触发绘图事件
6. 将开始按键设为失效，让它变灰setEnabled
7. 启动按键抬起的定时器，并将id记录在类内成员属性里
8. 将游戏启动标志位置为真

最开始要启的一定是抬起按键的定时器，因为它一开始就要自己落下，而这个状态与按键抬起后的状态一致，做的事是一样的。

### 协议包

协议包用于网络传输

第一个类成员为自定义的标志，用于接收端处理信息用

第二个为方格，数据信息

```c++
class BoardTrasInfo
{
public:
    int mark;//
    cell opponents_colorful_cell;
};
```

### 绘图事件

思路:绘图遍历一次是要遍历一次主背景，遍历一次next背景，然后根据

操作：

1. 创建一个指向本窗口的Qpainter
2. 遍历获取背景板的方格，第一轮遍历主背景，第二轮遍历next背景:
   1. 获取方格在窗口的位置坐标
   2. 创建QRectF 对象，并将坐标与方块大小作为参数加入其构造函数
   3. 创建Qcolor，并从方格中抽取颜色
   4. 通过Qpainter调用fillRect函数画出方格与其颜色
   5. 创建一个协议包类BoardTrasInfo,记录背景板标号和方块信息，并判断，若客户端socket！=0证明已经有客户端发给服务器信息了，那就把协议包传回客户端，客户端根据背景板标号在其客户端下的对手显示窗口调用绘图事件去更新对手背景板

我们选择在服务端和客户端调用绘图事件的时候，发送相应的数据给彼此的子窗口去显示。

### 按键按下事件

思路：判断能否下->记录定时器->killtimer->开启新的定时器

操作:

1. 判定是否能落下的同时游戏也启动了
2. 记录事件的标识符，在event->key()里
3. 根据switch-case对事件标识符进行选择
   1. 左键按下，就调用游戏引擎的类内函数move_left
   2. 右键->move_right
   3. 上->rotate
   4. 下，将类内粗存的按键按下定时器id取出若不等于-1则证明已经记录有在开启的定时器，所以需要关闭掉定时器后，再重新开一个速率更快的定时器
   5. update调用绘图事件

这里用starttimer的原因是->文档里有，槽函数信号冲突，在一个是需要改速率

### 按键抬起事件

其实只有抬起，而且还和上一步类似，也是记录抬起的定时器，然后删掉老定时器开启新的定时器

### 定时器事件处理函数

```
timerEvent
```

参数:QTimerEvent *event

思路:利用event内的timerId，控制每个编号下控制器做不同的事情

操作:

1. 判断是哪一个定时器
2. 判定能否下落
   1. 若能，调用movedown下落
   2. 不能，判定是否消除快>0
      1. 若大于0，说明有消除行需求，记录分数，显示分数，清空满的行，未满行下移
3. 判定是否玩家输了
   1. 若输了，关掉定时器
   2. 弹出Qmessage对话框游戏结束
   3. 返回
4. 若没输，继续在主背景板放形状，清空next背景板，再在next背景板上放置形状，游戏继续
5. update调用绘图事件

实际上两个定时器做的事类似，但对话框只能再一个定时器里弹出，而且方块下落是常驻需求，所以抬起按键的事件只需要判断不能下落的情况即可，不再复述，操作与上述类似。

### newgame按键槽

操作:

1. 将游戏启动标志置假
2. 关闭定时器id
3. 释放 游戏引擎类成员空间
4. 重新未游戏引擎类成员开辟空间
5. 清空计分器面板
6. 将开始按键置灰(setEnabled)
7. 更新画面调用绘图事件

### 网络信号处理函数

```
slot_mainwindowserver_dealdata
```

实际上在不论是服务器和客户端，都会在主窗口绑定一个槽函数，当接收到数据时，会发送自定信号，接收端一个调用主窗口的数据处理函数，一个调用子窗口的处理函数

服务器的主窗口数据处理函数用于接收客户端的socket，用于返回信息用

子窗口的处理函数用于将信息接收到后启动绘图事件，将方格显示在子窗口上

```c++
connect(m_server,SIGNAL(SIG_ReadyData(uint,char*,int)),this->ow,SLOT(slot_ServerDealData(uint ,char*,int)));//主窗口的
    connect(m_server,SIGNAL(SIG_ReadyData(uint,char*,int)),this,SLOT(slot_mainwindowserver_dealdata(uint ,char*,int)));//子窗口的
```

我们先谈主窗口的处理函数slot_ServerDealData

操作就一个：将客户端的socket赋值给



### 析构

操作:回收空间ui和ge

# 客户端主窗口类

客户端主窗口与服务器大体相同，但不一样的地方一个在于需要找到服务器的IP地址、另一个是不需要主窗口去处理数据，直接交给对手的子窗口去处理

客户端主要负责发送即可，而发送的地方在绘图事件里，一旦触发绘图事件，意味着整个背景板有颜色的更变，此时发送就可以了，而对于接收到的数据时触发自定义信号，仅需要调用子窗口的绘图事件即可。

# 对手副窗口类

## 类成员函数

```c++
class opponents_window : public QWidget
{
    Q_OBJECT

public:
    explicit opponents_window(QWidget *parent = nullptr);
    ~opponents_window();

    void paintEvent(QPaintEvent *);
public slots:
    void slot_ClientDealData(unsigned int Socket,char*,int);

private:

    Ui::opponents_window *ui;

    gameEngine* ge_opponents;

};
```

### 源程序

### 构造初始化

给子窗口的游戏引擎开辟空间

### 子窗口处理数据槽

```
slot_ClientDealData
```

参数:uint套接字，char*数据，int长度

操作:

1. 接收数据
2. 更新子窗口主背景和副背景的颜色
3. 收回缓冲区空间

### 子窗口绘图事件

其实和服务器里一样，但不需要再发送东西了，只是单纯的更新画面，遍历背景板，设置颜色，画矩形，添加颜色。

操作:

1. 绑定QPainter为当前框架下
2. 遍历取背景板的方格
3. 根据方格画矩形，填颜色
4. 显示 调用fillRect

# 网络中介者

## 添加路径

每一次装载库我都要去做这些操作，效率太低了，所以我把这些东西封装成为一个pri文件，每使用一个QT项目，只需要再对应项目里包含以下这个pri工程文件和该pri文件的路径，就可以了，很省事。



![image](https://user-images.githubusercontent.com/81805379/181427722-f7b6f871-638a-478d-832c-9cc6d546de02.png)

## 客户端类图

![客户端类图](https://user-images.githubusercontent.com/81805379/185544081-a7b40752-77ef-4786-a78d-dc9f8a6ec53a.jpg)

![image](https://user-images.githubusercontent.com/81805379/185544461-78086fb5-6fe2-4066-80e3-aa4a98b25ed6.png)

采用的是中介者模式，写好网络后，交由中介者去进行操作

网络是一层封装，这个网络是跟QT一点关系都没有的，加了一层中介者就是为了实现网络层和ui之间的交互。

中介者类指向TCP就用TCP，也可以指向UDP使用UDP协议

本项目中主要用的是TCP网络传输协议

# 中介者父类

```
INetMediator
```

## 类成员函数

```c++
class INet;
class INetMediator : public QObject
{
    Q_OBJECT
signals:
    void SIG_ReadyData( unsigned int lSendIP , char* buf , int nlen );
    //客户端断开连接
    void SIG_disConnect();
public:
    INetMediator();
    ~INetMediator();//使用时, 父类指针指向子类, 使用虚析构
	//初始化网络
    virtual bool OpenNet( const char* szBufIP = "0.0.0.0"
                    , unsigned short port = _DEF_TCP_PORT ) = 0 ;

	//关闭网络
	virtual void CloseNet() = 0 ; 
	//发送 : 同时兼容tcp udp 
    virtual bool SendData( unsigned int lSendIP , char* buf , int nlen ) = 0;
    //接收 处理
    virtual void DealData( unsigned int lSendIP , char* buf , int nlen ) = 0 ;

    //设置 ip port
    void setIpAndPort(const char* szBufIP  , unsigned short port  );
    //客户端是否连接服务器
    virtual bool IsConnected(){
        return true;
    }

    virtual void disConnect(){}

protected:
	INet * m_pNet; //网络
    //ip地址 ipv4
    char  m_szBufIP[18];
    //port
    unsigned short m_port ;
};
```

### 自定义信号

```c++
void SIG_ReadyData( unsigned int lSendIP , char* buf , int nlen );
void SIG_disConnect();
```

## 源程序

实际上使用时，父类指针指向子类，使用虚析构

# 客户端TCP中介者子类:public inet

```c++
class TcpClientMediator :public INetMediator
{
//    Q_OBJECT
public:
	TcpClientMediator(void);
	~TcpClientMediator(void);

	//初始化网络
    bool OpenNet(const char* szBufIP = "0.0.0.0"
                    , unsigned short port = _DEF_TCP_PORT );
	//关闭网络
	void CloseNet(); 
	//发送 : 同时兼容tcp udp 
    bool SendData( unsigned int lSendIP , char* buf , int nlen );
	//接收
    void DealData( unsigned int lSendIP , char* buf , int nlen );

    void disConnect();
    bool IsConnected();
};
```

## 源程序

### 构造函数

操作:使网络接口类变量m_pNet指向子类TCP的网络()

### 析构函数

操作:回收网络接口类的m_pNet的空间

### 初始化网络

```c++
bool TcpClientMediator::OpenNet(const char *szBufIP, unsigned short port)
```

操作:

1. 给记录IP的变量赋值
2. 给端口号赋值
3. 调用初始化网络函数InitNet并返回真

### 关闭网络

调用网络接口类变量m_pNet下的关闭网络函数UnInitNet

### 发送数据

```c++
bool TcpClientMediator::SendData( unsigned int lSendIP , char* buf , int nlen )
```

操作:

1. 判断是否连接成功
   1. 成功，返回真
   2. 否则先卸载网络库，回收网络接口变量空间，重新开启一次

### 处理数据

```c++
//将这几个参数 以信号的形式发送出去  -- IKernel类 的槽函数处理 -- 注意空间回收
    //std::cout<< lSendIP << ":" << buf <<std::endl;
    Q_EMIT SIG_ReadyData( lSendIP , buf , nlen);
```

操作:发射信号

### 断开连接

```c++
void TcpClientMediator::disConnect()
{
    Q_EMIT SIG_disConnect();
}
```

发射断开连接的信号被

### 判断是否连接

```c++
bool TcpClientMediator::IsConnected()
{
    return m_pNet->IsConnected();
}

```

# 服务器TCP中介者与客户端一样

# Windows下TCP服务器

## 类成员

```c++
class TcpServer : public INet
{
public:
	TcpServer(INetMediator * pMediator);
	~TcpServer(void);

	//初始化网络
    bool InitNet(const char* szBufIP , unsigned short port);
	//关闭网络
	void UnInitNet(); 
	//发送 : 同时兼容tcp udp 
    bool SendData( unsigned int lSendIP , char* buf , int nlen );
	
protected:
	//线程函数 : 接收数据
	static unsigned int __stdcall RecvThread( void * lpvoid); // 多个 每一个客户端有一个
	//线程函数 :接收客户端连接
	static unsigned int __stdcall AcceptThread( void * lpvoid); // 1个 
	//接收
	virtual void RecvData();

	SOCKET m_sock; // 主套接字
	//SOCKET sockWaiter; // 用户和客户端对话的套接字 --> 一组 
	map<unsigned int , SOCKET> m_mapThreadIdToSocket;
	list<HANDLE> m_hThreadHandleLst; // 控制线程

	bool m_isStop;
};

```

## 源程序

### 初始化网络InitNet

参数：const char *szBufIP ip地址, unsigned short port 端口号

操作:

1. 加载库
2. 创建套接字，进程与外界网络通讯需要的接口决定了与外界的通讯方式(udp tcp)
3. bind绑定ip地址、端口号、选择ipv4
4. 监听socket，如果返回-1 解除网络，卸载库
5. 创建接连接线程，等待客户端连接
   1. 收数据--创建AcceptThread接收连接的线程 createthread
   2. 若线程创建成功，将线程加入链表中

就是创建接收连接的线程后，在这个里面接收的线程内再创建线程去处理

### 接收数据线程

```c++
unsigned int __stdcall TcpServer::RecvThread( void * lpvoid)
```

操作:调用RecvData接收数据

### 接收连接线程

如果连接多个客户端的话，每一个客户端都需要一个线程去接收连接，因为accept函数也会产生

```c++
//每一个客户端都对应一个套接字
//每一个客户端 会对应 一个线程 一个套接字 --> 线程和套接字也是对应的
//可以在创建线程的时候 把线程id 和套接字 绑定在一起 形成映射 m_mapThreadIdToSocket
```

操作:

1. 当连接标志位为真时进入循环
2. 调用accept函数接收连接的同时返回该客户端的套接字
3. 为每一个客户端创建一个接收数据线程，并调用RecvThread去处理数据
4. 用映射的关系，每一个线程id映射为客户端的套接字

### 关闭网络

```
UnInitNet
```

操作:

1. 尝试推出线程
2. 每一个套接字回收

### 发送数据

```
SendData
```

```
防止粘包  策略: 先发包大小 再发数据包
```

我选择用vector，把包大小和包数据一起发过去，这样防止了两个send容易出现发了两个大小两个数据的这种毡包情况

而且vector是堆区空间自动会回收

### 接收数据

操作:

1. 取得套接字 线程id --> 套接字 
2. 获取线程的id  GetCurrentThreadId();
3. 循环内，先接收包大小，再接收包内容
4. 调用dealdata 处理数据

# 客户端TCP与服务器TCP的区别

不需要accpet接收线程为客户端分配，只需要recv函数去开辟空间接收线程去接收数据即可。

注意服务器连接服务器给0.0.0.0就行，但客户端需要服务器的ip地址 在第三步连接的时候注意一一下
