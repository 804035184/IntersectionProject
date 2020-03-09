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
				if (i % 100 == 0) {
					log(1);
				}
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
