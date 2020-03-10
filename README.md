# 大闸蟹的交点检测

| 项目                 | 内容                                                         |
| -------------------- | ------------------------------------------------------------ |
| 这个作业属于哪个课程 | [2020春季计算机学院软件工程(罗杰 任健)](https://edu.cnblogs.com/campus/buaa/SoftwareEngineeringofComputerCollegeinSpring2020) [(北京航空航天大学 - 计算机学院)](https://edu.cnblogs.com/campus/buaa) |
| 这个作业的要求在哪里 | [个人项目作业](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ/homework/10429) |
| 我的教学班级         | 005                                                          |
| 这个项目的GitHub地址 | https://github.com/804035184/IntersectionProject.git         |

## 使用说明

### 功能：

一个能求解简单几何形状之间交点的控制台程序。

### 使用方法：

使用命令行参数intersect.exe -i input -o output

### 输入格式

- 第 1 行：一个自然数 N >= 1，表示输入的几何图形的数目。
- 第 2 行至第 N + 1 行：每行描述一个几何图形。具体格式如下：
  - 直线：`L <x1> <y1> <x2> <y2>`，表示通过点 (x1, y1) 和 (x2, y2) 的直线。输入保证给定两点不重合。
  - 圆：`C <x> <y> <r>`，表示以点 (x, y) 为中心，半径为 r 的圆。输入保证半径 r > 0。

所有直线参数均为整数，范围为 (-100000, 100000)。

保证交点个数有限个。

在bin/input.txt里输入；

### 输出格式

共 1 行，输出平面中满足需求的点的数目。在bin/output.txt

### 样例 

#### 输入

```
1
L 0 0 1 1
```

#### 输出

```
0
```

#### 输入

```
4
C 1 0 2
C 2 2 1
C 3 -2 6
L -1 4 4 -1
```

#### 输出

```
6
```

## PS:是使用VS2019编写的，拷贝出来上传的文件更改了文件夹名称以及应用程序的名称，直接使用除intersect.exe外的文件可能会发生错误（尤其指test中的文件，是在VS编写本机单元测试用的，拷贝出来时路径已经发生了变化），使用release模式，采用多线程M/T生成。

## PSP估算

| PSP2.1                                  | Personal Software Process Stages        | 预估耗时（分钟） | 实际耗时（分钟） |
| --------------------------------------- | --------------------------------------- | ---------------- | ---------------- |
| Planning                                | 计划                                    |                  |                  |
| · Estimate                              | · 估计这个任务需要多少时间              | 10               | 10               |
| Development                             | 开发                                    |                  |                  |
| · Analysis                              | · 需求分析 (包括学习新技术)             | 60               | 180              |
| · Design Spec                           | · 生成设计文档                          | 30               | 30               |
| · Design Review                         | · 设计复审 (和同事审核设计文档)         | 10               | 10               |
| · Coding Standard                       | · 代码规范 (为目前的开发制定合适的规范) | 10               | 10               |
| · Design                                | · 具体设计                              | 60               | 90               |
| · Coding                                | · 具体编码                              | 30               | 50               |
| · Code Review                           | · 代码复审                              | 20               | 30               |
| · Test                                  | · 测试（自我测试，修改代码，提交修改）  | 60               | 120              |
| Reporting                               | 报告                                    |                  |                  |
| · Test Report                           | · 测试报告                              | 30               | 30               |
| · Size Measurement                      | · 计算工作量                            | 30               | 30               |
| · Postmortem & Process Improvement Plan | · 事后总结, 并提出过程改进计划          | 30               | 30               |
| -                                       | 合计                                    | 380              | 620              |

第一次项目的估计时间与实际操作时间严重不符，其中差距最大的在需求分析阶段，这也是我耗时最长的步骤，主要是对于如何寻找两条以上共点以及对c++的学习（虽然学到最后基本还是C程序）。这些反映了c++编程经验缺失的弊端，以及上学期都在写编译器，接触到具体的编程问题较少，还需要在实践中逐渐适应，找回节奏。

## 设计思路分析

题目要求是求直线与直线的交点，附加题中还加入了圆。

**首先考虑如何表示直线，圆以及交点。**

可以建立类去管理，但根据书中[代码规范和代码复审](http://www.cnblogs.com/xinz/archive/2011/11/20/2255971.html)章节，我认为直线、圆与交点并不是必须使用类去表示，所以优先使用结构体。

直线的描述：直线常见的表示形式有

1：[一般式](https://baike.baidu.com/item/%E4%B8%80%E8%88%AC%E5%BC%8F):**Ax+By+C=0**(A、B不同时为0)【适用于所有直线】

2：[点斜式](https://baike.baidu.com/item/%E7%82%B9%E6%96%9C%E5%BC%8F):**y-y0=k(x-x0) 【**适用于不垂直于x轴的直线**】**

3：[截距式](https://baike.baidu.com/item/%E6%88%AA%E8%B7%9D%E5%BC%8F):**x/a+y/b=1**【适用于不过原点或不垂直于x轴、y轴的直线】

4：[斜截式](https://baike.baidu.com/item/%E6%96%9C%E6%88%AA%E5%BC%8F):y**=kx+b【**适用于不垂直于x轴的直线**】**

5：[两点式](https://baike.baidu.com/item/%E4%B8%A4%E7%82%B9%E5%BC%8F):**(y-y1)/(y2-y1)=(x-x1)/(x2-x1) (**x1≠x2，y1≠y2**)**【适用于不垂直于x轴、y轴的直线】

等

由于此题中直线可能斜率为0，所以尽可能避免使用斜率k的情形，计算中尽量使用原本的两个点的坐标代入运算或者转化为一般式运算。

圆采用圆心坐标与半径即可，交点存留其坐标即可。

**接下来是求解交点**

在开始构思的时候，我首先去搜寻了一下类似的问题，发现找到的问题均是当不存在三线共点时的情况，本题关键就是如何判断多条直线共点。

考虑到附加题中还有圆的加入，只考虑两条直线只能有0或1个交点是不够的，又考虑到直线与圆都是基本的解析几何对象，问题不超过二元二次，故打算采取联立求解的方式进行。

$x = ((x1 * y2 - x2 * y1) * (x3 - x4) - (x1 - x2) * (x3 * y4 - x4 * y3)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));$

$y = ((x1 * y2 - x2 * y1) * (y3 - y4) - (y1 - y2) * (x3 * y4 - x4 * y3)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));$

在求解之前还需要判断是否平行，以防没有解的情况。

一半比较平行需要看斜率是否相同，即$(y2-y1)/(x2-x1)$与$(y4-y3)/(x4-x3)$是否相同，但由于存在斜率不存在的情况，故采用判断$(y2-y1)*(x4-x3)-(x2-x1)*(y4-y3)$是否为零的方法判断是否平行。

由于浮点数会产生1.999999999999与2.000000000000是同一个数但使用=判断不同的情况，故定义

```
#define equals(a, b) (fabs((a) - (b)) < 1e-10)
```

来保证等于的正常判断。

**在寻找直线与圆的交点问题时**，发现能够找到使用向量求解的方法，但为了保持一致，依旧采用联立求解的方法。

首先将直线的两个点转化为一般式方便计算，

直线使用一般式$a*x+b*y+c=0$，圆心坐标(x,y)，半径r，得到

```
x1 = (2 * b * b * x - 2 * a * c - 2 * b * y * a + 
		sqrt((2 * b * b * x - 2 * c * a - 2 * b * y * a) * 
		(2 * b * b * x - 2 * c * a - 2 * b * y * a) - 4 * 
			(a * a + b * b) * (b * b * x * x + c * c + 2 *
				b * y * c + b * b * y * y - r * r * b * b))) / (2 * (a * a + b * b));
x2 = (2 * b * b * x - 2 * a * c - 2 * b * y * a -
		sqrt((2 * b * b * x - 2 * c * a - 2 * b * y * a) *
		(2 * b * b * x - 2 * c * a - 2 * b * y * a) - 4 *
			(a * a + b * b) * (b * b * x * x + c * c + 2 *
				b * y * c + b * b * y * y - r * r * b * b))) / (2 * (a * a + b * b));
y1 = (-c - a * x1) / b;
y2 = (-c - a * x2) / b;
```

在求解直线与圆的交点之前，还需判断直线与圆是否存在交点。若圆心到直线的距离大于半径，则不存在交点。

判断$(a * x + b * y + c) / sqrt(a * a + b * b) - r$是否大于0即可。

由于依旧存在精度问题，故在比较大小之前先使用之前定义的

```
#define equals(a, b) (fabs((a) - (b)) < 1e-10)
```

判断相切的情况。

**在寻找圆与圆的交点问题时**，由于都是二次方程，无法直接代入计算，但根据高中所学知识，若两个圆有交点，那么将两个圆方程作差就可以得到交点所在直线的方程，然后根据上述直线与圆的交点求解方法进行求解。

在求解前，依旧需要判断圆与圆的位置关系，采用圆心距与半径关系来计算。判断圆心距$dis = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y))$与r1，r2的关系即可

dis>r1+r2相离五交点，dis<abs(r1-r2)内含五交点。

依旧考虑精度问题，先使用equals对内切与外切先进行判断。

**求交点的问题告一段落，接下来是如何对交点进行去重。**

最先想到的是集合set，一种使用红黑树实现的，插入删除操作时仅仅需要指针操作节点即可完成，不涉及到内存移动和拷贝的高效率的容器。

但本题中set中要储存的是结构体point，默认的比较方式显然不满足。

查阅资料发现，set的去重原理是通过$operator<$进行，故重写$struct$ $point${}​中的$operator<$方法，使得横纵坐标均相等时返回false即可。

## 设计实现过程

采用结构体存储直线，圆以及交点，并且重写交点的<方法方便去重。

```
struct line {
	double x1;
	double y1;
	double x2;
	double y2;
};
struct circle {
	double x;
	double y;
	double r;
};
struct point {
	double x;
	double y;
	bool operator<(const struct point & right)const   
	{
		if (equals(x, right.x) && equals(y, right.y)) {
			return false;
		}
		else
		{
			return true;
		}
	}
};
```

分别编写函数进行平行判断；求解直线与直线交点；直线与圆相交，相切，相离判断；求解直线与圆的交点；圆与圆相交，相切，相离判断；求解圆与圆的交点；

主函数从命令行传入参数，读取文件中的直线与圆信息，然后进行遍历，分别计算并将交点置入set中，最后输出set的size至输出文件中。

## 单元测试

进行了正确性测试。编写本机单元测试，对求交点的方法进行了正确性测试。
对每个计算的方法进行了正确性测试。
进行了压力测试，随机使用1000个直线，验证耗时60000。
对附加题进行了正确性测试。
对于超出1000进行了测试，但遗憾的是500000条在60秒内并不能给出结果。

![Alt text](https://github.com/804035184/IntersectionProject/blob/master/image/3.png)

## 关键代码说明

判断直线平行采用上述乘积方法以及equals来避免斜率不存在和精度等问题

```
int ifpara(line a, line b) {
	if (equals((a.x1 - a.x2) * (b.y1 - b.y2) - (a.y1 - a.y2) * (b.x1 - b.x2), 0)) {
		return 1;
	}
	else {
		return 0;
	}
}
```

求直线交点，使用上述公式

```
point node(line a, line b) {
	double x1 = a.x1;
	double y1 = a.y1;
	double x2 = a.x2;
	double y2 = a.y2;
	double x3 = b.x1;
	double y3 = b.y1;
	double x4 = b.x2;
	double y4 = b.y2;
	double x, y;
	x = ((x1 * y2 - x2 * y1) * (x3 - x4) - (x1 - x2) * (x3 * y4 - x4 * y3)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
	y = ((x1 * y2 - x2 * y1) * (y3 - y4) - (y1 - y2) * (x3 * y4 - x4 * y3)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
	point temppoint;
	temppoint.x = x;
	temppoint.y = y;
	return temppoint;
}
```

判断直线与圆的位置关系，使用equals避免精度问题

```
int line_circle(line lin1, circle cir1) {
	double a, b, c, x, y, r;
	a = lin1.y2 - lin1.y1;
	b = lin1.x1 - lin1.x2;
	c = lin1.x2 * lin1.y1 - lin1.x1 * lin1.y2;
	x = cir1.x;
	y = cir1.y;
	r = cir1.r;
	double dis = (a * x + b * y + c) / sqrt(a * a + b * b) - r;
	if (equals(dis, 0)) {
		return 1;
	}
	else if (dis > 0) {
		return 0;
	}
	else {
		return 2;
	}
}
```

求直线与圆的交点

```
point_2 node_lc(line lin1, circle cir1) {
	double a, b, c, x, y, r;
	a = lin1.y2 - lin1.y1;
	b = lin1.x1 - lin1.x2;
	c = lin1.x2 * lin1.y1 - lin1.x1 * lin1.y2;
	x = cir1.x;
	y = cir1.y;
	r = cir1.r;
	double x1, y1, x2, y2;
	x1 = (2 * b * b * x - 2 * a * c - 2 * b * y * a + 
		sqrt((2 * b * b * x - 2 * c * a - 2 * b * y * a) * 
		(2 * b * b * x - 2 * c * a - 2 * b * y * a) - 4 * 
			(a * a + b * b) * (b * b * x * x + c * c + 2 *
				b * y * c + b * b * y * y - r * r * b * b))) / (2 * (a * a + b * b));
	x2 = (2 * b * b * x - 2 * a * c - 2 * b * y * a -
		sqrt((2 * b * b * x - 2 * c * a - 2 * b * y * a) *
		(2 * b * b * x - 2 * c * a - 2 * b * y * a) - 4 *
			(a * a + b * b) * (b * b * x * x + c * c + 2 *
				b * y * c + b * b * y * y - r * r * b * b))) / (2 * (a * a + b * b));
	if (!equals(b, 0)) {
		y1 = (-c - a * x1) / b;
		y2 = (-c - a * x2) / b;
	}
	else {
		y1 = y + sqrt(r * r - (x1 - x) * (x1 - x));
		y2 = y - sqrt(r * r - (x1 - x) * (x1 - x));
	}
	point_2 pt;
	point pt1;
	point pt2;
	pt1.x = x1;
	pt1.y = y1;
	pt2.x = x2;
	pt2.y = y2;
	pt.point1 = pt1;
	pt.point2 = pt2;
	return pt;
}
```

判断圆与圆的位置关系，使用equals避免精度问题

```
int circle_circle(circle a, circle b) {
	double dis = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	if (equals(dis - a.r - b.r, 0)) {
		return 1;
	}
	else if (equals(dis - abs(a.r - b.r),0)) {
		return 1;
	}
	else if (dis > a.r + b.r) {
		return 0;
	}
	else if (dis < abs(a.r - b.r)) {
		return 0;
	}
	else {
		return 1;
	}
}

```

求圆与圆的交点

```
point_2 node_cc(circle c1, circle c2) {
	double a, b, c, x, y, r;
	a = 2 * c2.x - 2 * c1.x;
	b = 2 * c2.y - 2 * c1.y;
	c = c1.x * c1.x - c2.x * c2.x + c1.y * c1.y - c2.y * c2.y + c2.r * c2.r - c1.r * c1.r;
	x = c1.x;
	y = c1.y;
	r = c1.r;
	double x1, y1, x2, y2;
	x1 = (2 * b * b * x - 2 * a * c - 2 * b * y * a +
		sqrt((2 * b * b * x - 2 * c * a - 2 * b * y * a) *
		(2 * b * b * x - 2 * c * a - 2 * b * y * a) - 4 *
			(a * a + b * b) * (b * b * x * x + c * c + 2 *
				b * y * c + b * b * y * y - r * r * b * b))) / (2 * (a * a + b * b));
	x2 = (2 * b * b * x - 2 * a * c - 2 * b * y * a -
		sqrt((2 * b * b * x - 2 * c * a - 2 * b * y * a) *
		(2 * b * b * x - 2 * c * a - 2 * b * y * a) - 4 *
			(a * a + b * b) * (b * b * x * x + c * c + 2 *
				b * y * c + b * b * y * y - r * r * b * b))) / (2 * (a * a + b * b));
	if (!equals(b, 0)) {
		y1 = (-c - a * x1) / b;
		y2 = (-c - a * x2) / b;
	}
	else {
		y1 = y + sqrt(r * r - (x1 - x) * (x1 - x));
		y2 = y - sqrt(r * r - (x1 - x) * (x1 - x));
	}
	point_2 pt;
	point pt1;
	point pt2;
	pt1.x = x1;
	pt1.y = y1;
	pt2.x = x2;
	pt2.y = y2;
	pt.point1 = pt1;
	pt.point2 = pt2;
	return pt;
}

```

## 性能分析

#### cpu使用

对10000条直线进行运算

![Alt text](https://github.com/804035184/IntersectionProject/blob/master/image/1.png)

#### 函数

![Alt text](https://github.com/804035184/IntersectionProject/blob/master/image/2.png)

发现绝大多数运算都是在set进行排序操作。

#### 性能改进

去重方法选择使用set，可以大大提升效率

遍历时每个图形不需要对其他的进行遍历，只需遍历剩下的，虽然没变复杂度，可以减少很多运算

在读入时就对之前的进行计算可能会提升一点点效率

### 消除所有警告的截图

![Alt text](https://github.com/804035184/IntersectionProject/blob/master/image/xc1.png)

![Alt text](https://github.com/804035184/IntersectionProject/blob/master/image/xc2.png)

