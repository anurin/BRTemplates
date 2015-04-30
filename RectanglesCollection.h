#ifndef RECTANGLES_COLLECTION_H_
#define RECTANGLES_COLLECTION_H_
#include "Rectangle.h"
#include <memory>

template<typename Type>
class RectanglesCollection{
public:
	RectanglesCollection(int);

	bool Empty() const;
	bool Full() const;
	int Size() const;
	int Index() const;
	void Push(const Rectangle<Type> &);
	Rectangle<Type> Get(int = 0) const;
	void Set(int, const Rectangle<Type> &);
	bool ChangeSize(int);
	Rectangle<Type> OuterRectangle() const;

private:
	std::unique_ptr<Rectangle<Type>[]> rectangles;
	bool empty;
	bool full;
	int size;
	int index;

	int End() const;
};


template<typename Type>
RectanglesCollection<Type>::RectanglesCollection(int xx)
	: empty(true), full(false), size(0), index(0)
{
	if (xx > 0) {
		size = xx;
		rectangles.reset(new Rectangle<Type>[xx]);
	}
}

template<typename Type>
bool RectanglesCollection<Type>::Empty() const {
	return empty;
}

template<typename Type>
bool RectanglesCollection<Type>::Full() const {
	return full;
}

template<typename Type>
int RectanglesCollection<Type>::Size() const {
	return size;
}

template<typename Type>
int RectanglesCollection<Type>::Index() const {
	return index;
}

template<typename Type>
int RectanglesCollection<Type>::End() const {
	return full ? size : index; 
}

template<typename Type>
void RectanglesCollection<Type>::Push(const Rectangle<Type> & rect) {
	bool unsaved = true;
	while (unsaved){
		if (rectangles[index].Empty() || full){
			rectangles[index] = rect;
			unsaved = false;
		}
		if (++index == size){
				index = 0;
				full = true;
			}
	}
}

template<typename Type>
Rectangle<Type> RectanglesCollection<Type>::Get(int position) const {
	return rectangles[position];
}

template<typename Type>
void RectanglesCollection<Type>::Set(int position, const Rectangle<Type> &rect){
	rectangles[position] = rect;
}

template<typename Type>
bool RectanglesCollection<Type>::ChangeSize(int newSize) {
	if (newSize <= size)
		return false;
	std::unique_ptr<Rectangle<Type>[]> temp(new Rectangle<Type>[newSize]);
	int end = End();
	for (auto i = 0; i < end; i++)
		temp[i] = rectangles[i];
	rectangles = std::move(temp);
	index = size;
	size = newSize;
	full = false;
	return true;
}

template<typename Type>
Rectangle<Type> RectanglesCollection<Type>::OuterRectangle() const{
	Rectangle<Type> sum;
	for (auto i = 0; i < size; i++)
		sum += rectangles[i];
	return sum;
}
#endif // !RECTANGLES_COLLECTION_H_
