#include<iostream>    
#include<set>
#include<vector>
#include<cstring>
#include <fstream>
#define equals(a, b) (fabs((a) - (b)) < 1e-10)
using namespace std;
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

int ifpara(line a, line b) {
	if (equals((a.x1 - a.x2) * (b.y1 - b.y2) - (a.y1 - a.y2) * (b.x1 - b.x2), 0)) {
		return 1;
	}
	else {
		return 0;
	}
}
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
struct point_2 {
	point point1;
	point point2;
};
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
//line line_random() {
//	line a;
//	a.x1 = rand() % 1000;
//	a.x2 = rand() % 1000;
//	a.y1 = rand() % 1000;
//	a.y2 = rand() % 1000;
//	return a;
//}
int main(int argc, char* argv[]) {
	ifstream input;
	ofstream output;
	vector<line> lines;
	vector<circle> circles;
	set<point> points;
	for (int i = 0; i < argc; i++) {
		if (strncmp(argv[i], "-i", 2) == 0) {
			input.open(argv[i + 1]);
		}
		else if (strncmp(argv[i], "-o", 2) == 0) {
			output.open(argv[i + 1]);
		}
	}
	int n;
	char op;
	int x1, y1, x2, y2, r;
	input >> n;
	for (int i = 0; i < n; i++) {
		input >> op;
		if (op == 'L') {
			input >> x1 >> y1 >> x2 >> y2;
			line templine;
			templine.x1 = x1;
			templine.y1 = y1;
			templine.x2 = x2;
			templine.y2 = y2;
			lines.push_back(templine);
		}
		else if (op == 'C') {
			input >> x1 >> y1 >> r;
			circle tempcircle;
			tempcircle.x = x1;
			tempcircle.y = y1;
			tempcircle.r = r;
			circles.push_back(tempcircle);
		}
	}
	
	
	
	int i,j;
	/*for (i = 0; i < 10000; i++) {
		lines.push_back(line_random());
	}*/
	for (i = 0; i < (int)lines.size(); i++) {
		for (j = i + 1; j < (int)lines.size(); j++) {
			if (ifpara(lines.at(i), lines.at(j)) == 0) {
				point temppoint;
				temppoint = node(lines.at(i), lines.at(j));
				points.insert(temppoint);
				/*cout << temppoint.x << " " << temppoint.y << endl;*/
			}
		}
	}

	for (i = 0; i < (int)lines.size(); i++) {
		for (j = 0; j < (int)circles.size(); j++) {
			if (line_circle(lines.at(i), circles.at(j)) != 0) {
				point_2 pt;
				pt = node_lc(lines.at(i), circles.at(j));
				points.insert(pt.point1);
				points.insert(pt.point2);
				/*cout << pt.point1.x << " " << pt.point1.y << endl;
				cout << pt.point2.x << " " << pt.point2.y << endl;*/
			}
		}
	}

	for (i = 0; i < (int)circles.size(); i++) {
		for (j = i + 1; j < (int)circles.size(); j++) {
			if (circle_circle(circles.at(i), circles.at(j)) != 0) {
				point_2 pt;
				pt = node_cc(circles.at(i), circles.at(j));
				points.insert(pt.point1);
				points.insert(pt.point2);
				/*cout << pt.point1.x << " " << pt.point1.y << endl;
				cout << pt.point2.x << " " << pt.point2.y << endl;*/
			}
		}
	}
	//cout << points.size();
	output << points.size();
	return 0;
}