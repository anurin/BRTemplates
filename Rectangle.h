#ifndef RECTANGLE_H_
#define RECTANGLE_H_

template <typename Type>
struct Point {
	Type x;
	Type y;
	
	Point<Type>(Type xx=0, Type yy=0)
		:
		x(xx), y(yy)
	{}

	Point & operator=(const Point &);
};

template <typename Type>
class Rectangle {
public:
	Rectangle<Type>();
	Rectangle<Type>(const Point<Type>, const Point<Type>);

	bool Empty() const;
	Type GetLeftTopX() const;
	Type GetLeftTopY() const;
	Type GetRightBottomX() const;
	Type GetRightBottomY() const;

	void SetLeftTopX(Type);
	void SetLeftTopY(Type);
	void SetRightBottomX(Type);
	void SetRightBottomY(Type);

	Point<Type> GetLeftTop() const;
	Point<Type> GetRightBottom() const;

	void SetLeftTop(const Point<Type> &);
	void SetRightBottom(const Point<Type> &);

	bool Contains(const Point<Type> &) const;
	bool Contains(const Rectangle &) const;
	bool Intersects(const Rectangle &) const;
	Type Area() const;

	Rectangle<Type> & operator=(const Rectangle<Type> &);
	Rectangle<Type> & operator+=(const Rectangle<Type> &);
	Rectangle<Type> & operator*=(const Rectangle<Type> &);
private:
	void SetCorrection(bool);
	void CheckCorrection();
	bool correct;
	Point<Type> leftTop;
	Point<Type> rightBottom;
};

template <typename Type>
Rectangle<Type> operator+(const Rectangle<Type> &, const Rectangle<Type> &);

template <typename Type>
Rectangle<Type> operator*(const Rectangle<Type> &, const Rectangle<Type> &);

template <typename Type>
bool operator==(const Rectangle<Type> &, const Rectangle<Type> &);

template <typename Type>
Point<Type> & Point<Type>::operator=(const Point & pnt) {
	x = pnt.x;
	y = pnt.y;
	return *this;
}


template <typename Type>
Rectangle<Type>::Rectangle()
	: correct(false), leftTop(Point<Type>(1, 1)), rightBottom(Point<Type>(-1, -1))
	{}

template <typename Type>
Rectangle<Type>::Rectangle(const Point<Type> a, const Point<Type> b) 
	: correct(true){
	leftTop.x = (a.x < b.x) ? a.x : b.x;
	leftTop.y = (a.y > b.y) ? a.y : b.y;
	rightBottom.x = (a.x > b.x) ? a.x : b.x;
	rightBottom.y = (a.y < b.y) ? a.y : b.y;
}

template <typename Type>
bool Rectangle<Type>::Empty() const{
	return !correct;
}

template <typename Type>
void Rectangle<Type>::SetCorrection(bool c) {
	correct = c;
	if (!c) {
		leftTop = Point<Type>(1, 1);
		rightBottom = Point<Type>(-1, -1);
	}
}

template <typename Type>
void Rectangle<Type>::CheckCorrection() {
	if (leftTop.x <= rightBottom.x && leftTop.y >= rightBottom.y)
		correct = true;
	else
		correct = false;
}

template <typename Type>
Type Rectangle<Type>::GetLeftTopX() const{
	return leftTop.x;
}

template <typename Type>
Type Rectangle<Type>::GetLeftTopY() const{
	return leftTop.y;
}

template <typename Type>
Type Rectangle<Type>::GetRightBottomX() const{
	return rightBottom.x;
}

template <typename Type>
Type Rectangle<Type>::GetRightBottomY() const{
	return rightBottom.y;
}

template <typename Type>
void Rectangle<Type>::SetLeftTopX(Type a){
	leftTop.x = a;
	CheckCorrection();

}

template <typename Type>
void Rectangle<Type>::SetLeftTopY(Type a){
	leftTop.y = a;
	CheckCorrection();
}

template <typename Type>
void Rectangle<Type>::SetRightBottomX(Type a){
	rightBottom.x = a;
	CheckCorrection();
}

template <typename Type>
void Rectangle<Type>::SetRightBottomY(Type a){
	rightBottom.y = a;
	CheckCorrection();
}

template <typename Type>
Point<Type> Rectangle<Type>::GetLeftTop() const{
	return leftTop;
}

template <typename Type>
Point<Type> Rectangle<Type>::GetRightBottom() const{
	return rightBottom;
}

template <typename Type>
void Rectangle<Type>::SetLeftTop(const Point<Type> &a){
	leftTop = a;
}

template <typename Type>
void Rectangle<Type>::SetRightBottom(const Point<Type> &a){
	rightBottom = a;
}

template <typename Type>
bool Rectangle<Type>::Contains(const Point<Type> &pnt) const {
	if (!correct)
		return false;
	if (pnt.x >= leftTop.x && pnt.x <= rightBottom.x
		&&  pnt.y <= leftTop.y && pnt.y >= rightBottom.y)
		return true;
	else
		return false;
}

template <typename Type>
bool Rectangle<Type>::Contains(const Rectangle &rect) const {
	if (!correct || rect.Empty())
		return false;
	if (Contains(rect.leftTop) && Contains(rect.rightBottom))
		return true;
	else
		return false;
}

template <typename Type>
bool Rectangle<Type>::Intersects(const Rectangle &rect) const {
	if (!correct || rect.Empty())
		return false;

	Point<Type> temp1;
	Point<Type> temp2;

	temp1.x = rect.rightBottom.x;
	temp1.y = rect.leftTop.y;

	temp2.x = rect.leftTop.x;
	temp2.y = rect.rightBottom.y;

	if (Contains(rect.leftTop) || Contains(rect.rightBottom) || Contains(temp1) || Contains(temp2))
		return true;
	else
		return false;

}

template <typename Type>
Type Rectangle<Type>::Area() const {
	if (!correct)
		return -1;

	Type result = (rightBottom.x - leftTop.x) * (leftTop.y - rightBottom.y);
	if (result < 0)
		result *= (-1);
	return result;
}



template <typename Type>
Rectangle<Type> & Rectangle<Type>::operator=(const Rectangle &rect) {
	leftTop.x = rect.leftTop.x;
	leftTop.y = rect.leftTop.y;
	rightBottom.x = rect.rightBottom.x;
	rightBottom.y = rect.rightBottom.y;
	correct = !rect.Empty();
	return *this;
}

template <typename Type>
Rectangle<Type> & Rectangle<Type>::operator+=(const Rectangle &rect) {
	if (Empty()){
		*this = rect;
		return *this;
	}
	if (rect.Empty())
		return *this;

	leftTop.x = leftTop.x < rect.GetLeftTopX() ? leftTop.x : rect.GetLeftTopX();
	leftTop.y = leftTop.y > rect.GetLeftTopY() ? leftTop.y : rect.GetLeftTopY();
	rightBottom.x = rightBottom.x > rect.GetRightBottomX() ? rightBottom.x : rect.GetRightBottomX();
	rightBottom.y = rightBottom.y < rect.GetRightBottomY() ? rightBottom.y : rect.GetRightBottomY();

	return *this;
}

template <typename Type>
Rectangle<Type> & Rectangle<Type>::operator*=(const Rectangle &rect) {
	if (Empty() || rect.Empty()){
		SetCorrection(false);
		return *this;
	}

	if (Contains(rect) || rect.Contains(*this)){
		*this = (Area() > rect.Area()) ? rect : *this;
		return *this;
	}

	bool none = true;
	Point<Type> newLeftTop = leftTop;
	Point<Type> newRightBottom = rightBottom;
	Point<Type> temp = rect.GetLeftTop();

	if (Contains(rect.GetLeftTop())) {
		newLeftTop = temp;
		none = false;
	}

	temp.x = rect.GetRightBottomX();
	if (Contains(temp)){
		newLeftTop.y = temp.y;
		newRightBottom.x = temp.x;
		none = false;
	}

	temp.y = rect.GetRightBottomY();
	if (Contains(temp)) {
		newRightBottom = temp;
		none = false;
	}

	temp.x = rect.GetLeftTopX();
	if (Contains(temp)){
		newLeftTop.x = temp.x;
		newRightBottom.y = temp.y;
		none = false;
	}

	if (none) {
		SetCorrection(false);
	}
	else {
		leftTop = newLeftTop;
		rightBottom = newRightBottom;
	}
	return *this;
}

template <typename Type>
Rectangle<Type> operator+(const Rectangle<Type> &rect1, const Rectangle<Type> &rect2){
	Rectangle<Type> result = rect1;
	result += rect2;
	return result;
}

template <typename Type>
Rectangle<Type> operator*(const Rectangle<Type> &rect1, const Rectangle<Type> &rect2) {
	Rectangle<Type> result = rect1;
	result *= rect2;
	return result;
}

template <typename Type>
bool operator==(const Rectangle<Type> &rect1, const Rectangle<Type> &rect2) {
	if (!rect1.Empty() && !rect2.Empty()
		&& rect1.GetLeftTopX() == rect2.GetLeftTopX()
		&& rect1.GetLeftTopY() == rect2.GetLeftTopY()
		&& rect1.GetRightBottomX() == rect2.GetRightBottomX()
		&& rect1.GetRightBottomY() == rect2.GetRightBottomY()
		)
		return true;
	else
		return false;
}

#endif //RECTANGLE_H_