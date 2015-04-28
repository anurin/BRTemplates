#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>
#include "RectanglesCollection.h"

typedef boost::mpl::list<int, long long, float, double> test_types;

BOOST_AUTO_TEST_SUITE(Rectangles_Collection)

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangles_Collection_Constructor, Type, test_types){
	RectanglesCollection<Type> coll(5);
	BOOST_CHECK(coll.Empty());
	BOOST_CHECK(!coll.Full());
	BOOST_CHECK_EQUAL(coll.Size(), 5);
	BOOST_CHECK_EQUAL(coll.Index(), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangles_Collection_Push, Type, test_types){
	RectanglesCollection<Type> coll(4);
	Rectangle<Type> r(Point<Type>(1, 5), Point<Type>(3, 2));
	Rectangle<Type> result;
	coll.Push(r);
	result = coll.Get(0);

	BOOST_CHECK_EQUAL(result.GetLeftTopX(), 1);
	BOOST_CHECK_EQUAL(result.GetLeftTopY(), 5);
	BOOST_CHECK_EQUAL(result.GetRightBottomX(), 3);
	BOOST_CHECK_EQUAL(result.GetRightBottomY(), 2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangles_Collection_Set, Type, test_types){
	RectanglesCollection<Type> coll(4);
	Rectangle<Type> r1(Point<Type>(4, 9), Point<Type>(12, 2));
	coll.Set(2, r1);
	Rectangle<Type> result = coll.Get(2);

	BOOST_CHECK_EQUAL(result.GetLeftTopX(), 4);
	BOOST_CHECK_EQUAL(result.GetLeftTopY(), 9);
	BOOST_CHECK_EQUAL(result.GetRightBottomX(), 12);
	BOOST_CHECK_EQUAL(result.GetRightBottomY(), 2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangles_Collection_FindingFreePlace, Type, test_types){
	RectanglesCollection<Type> coll(4);
	Rectangle<Type> r1(Point<Type>(1, 5), Point<Type>(3, 2));
	coll.Set(0, r1);
	coll.Set(2, r1);
	Rectangle<Type> r2(Point<Type>(3, 9), Point<Type>(7, 2));
	coll.Push(r2);
	Rectangle<Type> result = coll.Get(1);
	BOOST_CHECK_EQUAL(result.GetLeftTopX(), 3);
	BOOST_CHECK_EQUAL(result.GetLeftTopY(), 9);
	BOOST_CHECK_EQUAL(result.GetRightBottomX(), 7);
	BOOST_CHECK_EQUAL(result.GetRightBottomY(), 2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangles_Collection_CyclicalBuffer, Type, test_types) {
	RectanglesCollection<Type> coll(5);
	Rectangle<Type> r1(Point<Type>(1, 5), Point<Type> (3, 2));
	for (auto i = 0; i < 5; i++)
		coll.Push(r1);
	Rectangle<Type> r2(Point<Type>(2, 9), Point<Type>(6, 1));
	coll.Push(r2);
	Rectangle<Type> result = coll.Get(0);

	BOOST_CHECK_EQUAL(coll.Index(), 1);
	BOOST_CHECK_EQUAL(result.GetLeftTopX(), 2);
	BOOST_CHECK_EQUAL(result.GetLeftTopY(), 9);
	BOOST_CHECK_EQUAL(result.GetRightBottomX(), 6);
	BOOST_CHECK_EQUAL(result.GetRightBottomY(), 1);
	BOOST_CHECK(coll.Full());
}


BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangles_Collection_ChangeSize, Type, test_types){
	RectanglesCollection<Type> coll(3);
	Rectangle<Type> r1(Point<Type>(1, 5), Point<Type>(3, 2));
	for (auto i = 0; i < 4; i++)
		coll.Push(r1);

	BOOST_CHECK(coll.Full());

	coll.ChangeSize(6);

	BOOST_CHECK(!coll.Full());
	BOOST_CHECK_EQUAL(coll.Index(), 3);
	BOOST_CHECK(coll.Get(4).Empty());
}


BOOST_AUTO_TEST_CASE_TEMPLATE(Rectangles_Collection_OuterRectangle, Type, test_types) {
	RectanglesCollection<Type> coll(5);
	Rectangle<Type> r1(Point<Type>(1, 5), Point<Type>(3, 2));
	for (auto i = 0; i < 3; i++)
		coll.Push(r1);
	Rectangle<Type> r2(Point<Type>(0, 7), Point<Type>(2, 2));
	coll.Push(r2);
	r1 = coll.OuterRectangle();

	BOOST_CHECK_EQUAL(r1.GetLeftTopX(), 0);
	BOOST_CHECK_EQUAL(r1.GetLeftTopY(), 7);
	BOOST_CHECK_EQUAL(r1.GetRightBottomX(), 3);
	BOOST_CHECK_EQUAL(r1.GetRightBottomY(), 2);
}

BOOST_AUTO_TEST_SUITE_END()