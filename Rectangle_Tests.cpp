#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "Rectangle.h"

typedef boost::mpl::list<int, long long, float, double> test_types;
typedef boost::mpl::list<int, long long> test_types_int;
BOOST_AUTO_TEST_SUITE(Rectangle_Methods)

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Constructor, Type, test_types){
	Rectangle<Type> r;
	BOOST_CHECK_EQUAL(r.GetLeftTopX(), 1);
	BOOST_CHECK_EQUAL(r.GetLeftTopY(), 1);
	BOOST_CHECK_EQUAL(r.GetRightBottomX(), -1);
	BOOST_CHECK_EQUAL(r.GetRightBottomY(), -1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Constructor_With_Values, Type, test_types){
	Rectangle<Type> r(Point<Type>(2, 6), Point<Type>(10, 1));

	BOOST_CHECK_EQUAL(r.GetLeftTopX(), 2);
	BOOST_CHECK_EQUAL(r.GetLeftTopY(), 6);
	BOOST_CHECK_EQUAL(r.GetRightBottomX(), 10);
	BOOST_CHECK_EQUAL(r.GetRightBottomY(), 1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Set, Type, test_types) {
	Point<Type> a(0, 5);
	Point<Type> b(5, 0);
	Rectangle<Type> r;
	r.SetLeftTop(a);
	r.SetRightBottom(b);

	BOOST_CHECK_EQUAL(r.GetLeftTopX(), 0);
	BOOST_CHECK_EQUAL(r.GetLeftTopY(), 5);
	BOOST_CHECK_EQUAL(r.GetRightBottomX(), 5);
	BOOST_CHECK_EQUAL(r.GetRightBottomY(), 0);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Contains_Point, Type, test_types){
	Rectangle<Type> r(Point<Type>(234, 345678), Point<Type> (87654, 98));
	Point<Type> a(65676, 168);

	BOOST_CHECK_EQUAL(r.Contains(a), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Doesnt_Contain_Point, Type, test_types){
	Rectangle<Type> r(Point<Type>(2, 7), Point<Type> (11, 1));
	Point<Type> a(8, 8);
	BOOST_CHECK_EQUAL(r.Contains(a), false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Contains_Rectangle, Type, test_types){
	Rectangle<Type> r1(Point<Type>(234, 345678), Point<Type> (87654, 98));
	Rectangle<Type> r2(Point<Type>(235, 345677), Point<Type>(87653, 99));
	BOOST_CHECK_EQUAL(r1.Contains(r2), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Doesnt_Contain_Rectangle, Type, test_types){
	Rectangle<Type> r1(Point<Type>(234, 345678), Point<Type>(87654, 98));
	Rectangle<Type> r2(Point<Type>(1236, 345677), Point<Type>(87653, 97));
	BOOST_CHECK_EQUAL(r1.Contains(r2), false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Intersects, Type, test_types) {
	Rectangle<Type> r1(Point<Type>(0, 5), Point<Type>(5, 0));
	Rectangle<Type> r2(Point<Type>(3, 7), Point<Type>(4, 1));
	r1.Intersects(r2);
	BOOST_CHECK_EQUAL(r1.Intersects(r2), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Doesnt_Intersects, Type, test_types) {
	Rectangle<Type> r1(Point<Type>(0, 5), Point<Type>(5, 0));
	Rectangle<Type> r2(Point<Type>(0, 7), Point<Type>(5, 6));
	r1.Intersects(r2);
	BOOST_CHECK_EQUAL(r1.Intersects(r2), false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Area, Type, test_types_int){
	Rectangle<Type> r(Point<Type>(0, 5), Point<Type>(5, 0));
	BOOST_CHECK_EQUAL(r.Area(), 25);
}

BOOST_AUTO_TEST_CASE(Rectangle_Area_Double) {
	Rectangle<double> r(Point<double>(3.2, 5), Point<double>(5, 1.7));
	BOOST_CHECK_CLOSE(r.Area(), 5.94, 0.0001);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(Rectangle_Operators)

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Assinging, Type, test_types){
	Rectangle<Type> r1(Point<Type>(2, 6), Point<Type> (10, 1));
	Rectangle<Type> r2;
	r2 = r1;

	BOOST_CHECK_EQUAL(r2.GetLeftTopX(), 2);
	BOOST_CHECK_EQUAL(r2.GetLeftTopY(), 6);
	BOOST_CHECK_EQUAL(r2.GetRightBottomX(), 10);
	BOOST_CHECK_EQUAL(r2.GetRightBottomY(), 1);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Addition_With_Assinging, Type, test_types){
	Rectangle<Type> r1(Point<Type>(0, 5), Point<Type>(5, 0));
	Rectangle<Type> r2(Point<Type>(2, 3), Point<Type>(7, 1));
	r1 += r2;

	BOOST_CHECK_EQUAL(r1.GetLeftTopX(), 0);
	BOOST_CHECK_EQUAL(r1.GetLeftTopY(), 5);
	BOOST_CHECK_EQUAL(r1.GetRightBottomX(), 7);
	BOOST_CHECK_EQUAL(r1.GetRightBottomY(), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Addition, Type, test_types) {
	Rectangle<Type> r1(Point<Type>(0, 5), Point<Type>(5, 0));
	Rectangle<Type> r2(Point<Type>(2, 3), Point<Type>(7, 1));
	Rectangle<Type> r3;
	r3 = r1 + r2;

	BOOST_CHECK_EQUAL(r3.GetLeftTopX(), 0);
	BOOST_CHECK_EQUAL(r3.GetLeftTopY(), 5);
	BOOST_CHECK_EQUAL(r3.GetRightBottomX(), 7);
	BOOST_CHECK_EQUAL(r3.GetRightBottomY(), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Intersection_With_Assigning, Type, test_types) {
	Rectangle<Type> r1(Point<Type>(2, 3), Point<Type>(7, 1));
	Rectangle<Type> r2(Point<Type>(1, 8), Point<Type>(5, 2));
	r1 *= r2;

	BOOST_CHECK_EQUAL(r1.GetLeftTopX(), 2);
	BOOST_CHECK_EQUAL(r1.GetLeftTopY(), 3);
	BOOST_CHECK_EQUAL(r1.GetRightBottomX(), 5);
	BOOST_CHECK_EQUAL(r1.GetRightBottomY(), 2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Intersection, Type, test_types) {
	Rectangle<Type> r1(Point<Type>(2, 5), Point<Type>(7, 3));
	Rectangle<Type> r2(Point<Type>(1, 4), Point<Type>(3, 2));
	Rectangle<Type> r3;
	r3 = r1 * r2;

	BOOST_CHECK_EQUAL(r3.GetLeftTopX(), 2);
	BOOST_CHECK_EQUAL(r3.GetLeftTopY(), 4);
	BOOST_CHECK_EQUAL(r3.GetRightBottomX(), 3);
	BOOST_CHECK_EQUAL(r3.GetRightBottomY(), 3);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_Empty_Intersection, Type, test_types) {
	Rectangle<Type> r1(Point<Type>(1, 1), Point<Type>(2, 0));
	Rectangle<Type> r2(Point<Type>(4, 4), Point<Type>(5, 3));
	r1 = r1 * r2;

	BOOST_CHECK(r1.Empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_ComparisonTrue, Type, test_types) {
	Rectangle<Type> r1(Point<Type>(1, 1), Point<Type>(2, 0));
	Rectangle<Type> r2(Point<Type>(1, 1), Point<Type>(2, 0));
	bool comp = (r1 == r2);
	BOOST_CHECK(comp);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangle_ComparisonFalse, Type, test_types) {
	Rectangle<Type> r1(Point<Type>(1, 1), Point<Type>(2, 0));
	Rectangle<Type> r2;
	bool comp = (r1 == r2);
	BOOST_CHECK(!comp);
}


BOOST_AUTO_TEST_SUITE_END()