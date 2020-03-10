#include "pch.h"
#include "CppUnitTest.h"
#include<time.h>
#include<stdio.h>
#include "../IntersectProject/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
line line_random() {
	line a;
	a.x1 = rand() % 1000;
	a.x2 = rand() % 1000;
	a.y1 = rand() % 1000;
	a.y2 = rand() % 1000;
	return a;
}
circle ciecle_random() {
	circle a;
	a.x = rand() % 1000;
	a.y = rand() % 1000;
	a.r = rand() % 1000;
	return a;

}
line line_init(int x1, int y1, int x2, int y2) {
	line a;
	a.x1 = x1;
	a.x2 = x2;
	a.y1 = y1;
	a.y2 = y2;
	return a;
}
circle circle_init(int x, int y, int r) {
	circle a;
	a.x = x;
	a.y = y;
	a.r = r;
	return a;
}
namespace IntersectProjectTest
{
	TEST_CLASS(IntersectProjectTest)
	{
	public:

		TEST_METHOD(Testnodell)
		{
			point tp1;
			tp1.x = 0;
			tp1.y = 0;
			line l1;
			line l2;
			l1.x1 = 0;
			l1.y1 = 0;
			l1.x2 = 1;
			l1.y2 = 1;
			l2.x1 = 0;
			l2.y1 = 0;
			l2.x2 = 0;
			l2.y2 = 1;
			Assert::AreEqual(tp1.x, node(l1, l2).x);
			Assert::AreEqual(tp1.y, node(l1, l2).y);
		}
		TEST_METHOD(Testtime)
		{
			srand(time(NULL));
			long l = clock();
			vector<line> lines;
			vector<circle> circles;
			set<point> points;
			
			int i, j;
			for (i = 0; i < 1000; i++) {
				lines.push_back(line_random());
			}
			for (i = 0; i < (int)lines.size(); i++) {
				for (j = i + 1; j < (int)lines.size(); j++) {
					if (ifpara(lines.at(i), lines.at(j)) == 0) {
						point temppoint;
						temppoint = node(lines.at(i), lines.at(j));
						points.insert(temppoint);
					}
				}


			}
			Assert::IsTrue(clock() - l < 60000);
		}
		TEST_METHOD(Testnodelc)
		{
			point tp1;
			tp1.x = 0;
			tp1.y = 3;
			point tp2;
			tp2.x = 0;
			tp2.y = -3;
			line l1 = line_init(0, 0, 0, -1);
			circle c1 = circle_init(0, 0, 3);
			point_2 tp;
			tp.point1 = tp1;
			tp.point2 = tp2;
			Assert::AreEqual(tp.point1.x, node_lc(l1, c1).point1.x);
			Assert::AreEqual(tp.point1.y, node_lc(l1, c1).point1.y);
			Assert::AreEqual(tp.point2.x, node_lc(l1, c1).point2.x);
			Assert::AreEqual(tp.point2.y, node_lc(l1, c1).point2.y);
		}
		TEST_METHOD(Testnodecc)
		{
			point tp1;
			tp1.x = 1;
			tp1.y = 0;
			point tp2;
			tp2.x = 1;
			tp2.y = 0;
			circle c1 = circle_init(0, 0, 1);
			circle c2 = circle_init(2, 0, 1);
			point_2 tp;
			tp.point1 = tp1;
			tp.point2 = tp2;
			Assert::AreEqual(tp.point1.x, node_cc(c1, c2).point1.x);
			Assert::AreEqual(tp.point1.y, node_cc(c1, c2).point1.y);
			Assert::AreEqual(tp.point2.x, node_cc(c1, c2).point2.x);
			Assert::AreEqual(tp.point2.y, node_cc(c1, c2).point2.y);
		}
		TEST_METHOD(Testset)
		{
			vector<line> lines;
			vector<circle> circles;
			set<point> points;
			circles.push_back(circle_init(1, 0, 2));
			circles.push_back(circle_init(2, 2, 1));
			circles.push_back(circle_init(3, -2, 6));
			lines.push_back(line_init(1, 4, 4, -1));
			int i, j;
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
			Assert::AreEqual(6, (int)points.size());
		}
		TEST_METHOD(Testultmate)
		{
			srand(time(NULL));
			long l = clock();
			vector<line> lines;
			vector<circle> circles;
			set<point> points;

			int i, j;
			for (i = 0; i < 10000; i++) {
				lines.push_back(line_random());
			}
			for (i = 0; i < (int)lines.size(); i++) {
				for (j = i + 1; j < (int)lines.size(); j++) {
					if (ifpara(lines.at(i), lines.at(j)) == 0) {
						point temppoint;
						temppoint = node(lines.at(i), lines.at(j));
						points.insert(temppoint);
					}
				}


			}
			Assert::IsTrue(clock() - l < 60000);
		}
		TEST_METHOD(Testex)
		{
			srand(time(NULL));
			long l = clock();
			vector<line> lines;
			vector<circle> circles;
			set<point> points;

			int i, j;
			for (i = 0; i < 500000; i++) {
				lines.push_back(line_random());
			}
			for (i = 0; i < (int)lines.size(); i++) {
				for (j = i + 1; j < (int)lines.size(); j++) {
					if (ifpara(lines.at(i), lines.at(j)) == 0) {
						point temppoint;
						temppoint = node(lines.at(i), lines.at(j));
						points.insert(temppoint);
					}
				}


			}
			Assert::IsTrue(clock() - l < 60000);
		}
	};

}
